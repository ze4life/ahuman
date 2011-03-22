#include "fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

NNStrategyScan::NNStrategyScan()
:	NNStrategy( logger )
{
	p = NULL;

	maxTime = 0;
	bestMax = 10;
	tolerance = 0;
}

NNStrategyScan::~NNStrategyScan()
{
}

void NNStrategyScan::init( NN *p_p )
{
	attach( p_p );
}

NNStrategyScan *NNStrategyScan::newInit( NN *p_p )
{
	NNStrategyScan *ps = new NNStrategyScan;
	ps -> init( p_p );
	return( ps );
}

void NNStrategyScan::setMaxTime( int ms )
{
	maxTime = ms;
}

// learn functions
bool NNStrategyScan::learn( NNSamples *samples , NNWeights *pwBest , float *pvar )
{
	NNScanPoint sp( p );

	if( !doLearn( samples , NULL , &sp ) )
		return( false );

	pwBest -> setTo( sp.getWeights() );
	*pvar = sp.getVariance();
	return( true );
}

bool NNStrategyScan::learnSample( NNSamples *samples , int id , NNWeights *pwBest , float *pvar )
{
	NNSample *sample = samples -> getById( id );
	NNScanPoint sp( p );
	if( !doLearn( samples , sample , &sp ) )
		return( false );

	pwBest -> setTo( sp.getWeights() );
	*pvar = sp.getVariance();
	return( true );
}

int NNStrategyScan::getIterationsPerSec( NNSample *sample )
{
	// calculate iterations within 100 ms
	Timer t( true );
	NNErrorFunction *ef = NNStrategy::getErrorFunction();
	int k = 0;
	for( ; t.timePassed() < 100; k++ )
		{
			p -> execute();
			ef -> getErrorSampleProgress( sample );
		}

	int maxIteratons = k * 10;

	return( maxIteratons );
}

int NNStrategyScan::getVariableCount()
{
	int nVars = 0;
	for( int k = 0; k < p -> getNLayers(); k++ )
		{
			NNLayer *pl = p -> getLayer( k );
			nVars += pl -> getNVars();
		}

	return( nVars );
}

bool NNStrategyScan::doLearn( NNSamples *samples , NNSample *sample , NNScanPoint *spBest )
{
	ASSERT( samples -> count() > 0 );

	Timer t( maxTime );

	// set sample
	NNSample *startSample = ( sample != NULL )? sample : samples -> getByPos( 0 );
	p -> setSensors( startSample );

	// show initial
	helper.showPerceptron( "INITIAL STATE" );

	// calculate number of iterations allowed
	int numberOfIterations = getIterationsPerSec( startSample );

	// save current state of perceptron
	NNWeights pwSave( p );
	pwSave.getFromPerceptron();

	// create run search iterations by precision
	ClassList<NNStrategyScanIteration> runByPrecision;
	NNScanPoint *bestPoint = createRunsAndStartPoint( runByPrecision );
	
	// run in cycle till time expired or given tolerance achieved
	Timer ct( true );
	bool loopDetected = false;
	int iterationsDone = 0;
	for( int iteration = 0; /* t.go() && */ bestPoint -> getVariance() > tolerance && iteration < 100; iteration++ )
		{
			logger.logInfo( String( "doLearn ITERATION #" ) + iteration );
			bool found = runFindByPrecisions( samples , sample , t , runByPrecision , bestPoint , iterationsDone );
			if( !found )
				break;
		}

	helper.onDoLearnScan( samples , iterationsDone , ct.timePassed() , numberOfIterations , runByPrecision , bestPoint , loopDetected );

	// restore perceptron state
	pwSave.setToPerceptron();

	// set best
	if( !loopDetected )
		spBest -> setFromPoint( bestPoint );

	// free data
	runByPrecision.destroy();

	if( loopDetected )
		return( false );

	return( true );
}

NNScanPoint *NNStrategyScan::createRunsAndStartPoint( ClassList<NNStrategyScanIteration>& runByPrecision )
{
	int maxPrecision = abs( ( int )log10( tolerance ) ) - 1;
	int axisItems = 3;
	int pointsToCheck = 10;
	float searchArea = wLimitMax - wLimitMin;

	float range = searchArea;
	for( int k = 0; k < maxPrecision; k++ , range /= 10 )
		{
			NNStrategyScanIteration *run = new NNStrategyScanIteration( this , p , bestMax , axisItems , pointsToCheck );
			run -> setSearchArea( range );
			runByPrecision.add( run );
		}

	// create start point
	NNStrategyScanIteration *run = runByPrecision[ 0 ];
	// NNWeights *pwStartPoint = getRandomStartPoint();
	NNWeights *pwStartPoint = getFixedStartPoint();
	NNScanPoint *bestPoint = run -> createBestPoint( pwStartPoint );
	delete pwStartPoint;

	return( bestPoint );
}

bool NNStrategyScan::runFindByPrecisions( NNSamples *samples , NNSample *sample , Timer& t , ClassList<NNStrategyScanIteration>& runByPrecision , NNScanPoint *& bestPoint , int& iterationsDone )
{
	bool currentSampleOnly = ( sample != NULL );
	int maxRuns = runByPrecision.count();

	bool found = false;
	for( int k = 0; bestPoint -> getVariance() > tolerance && k < maxRuns; k++ )
		{
			NNStrategyScanIteration *run = runByPrecision[ k ];
			logger.logInfo( String( "runFindByPrecisions: precision=" ) + run -> getSearchArea() );

			if( run -> getBestPoints().count() == 0 )
				break;

			NNStrategyScanIteration *runNext = NULL;
			if( k < maxRuns - 1 )
				runNext = runByPrecision[ k + 1 ];

			// run find with given precision
			bool foundRun = runFindByOnePrecision( samples , sample , run , runNext , bestPoint , iterationsDone );
			if( foundRun )
				found = true;
		}

	return( found );
}

bool NNStrategyScan::runFindByOnePrecision( NNSamples *samples , NNSample *sample , NNStrategyScanIteration *run , NNStrategyScanIteration *runNext , NNScanPoint *& bestPoint , int& iterationsDone )
{
	float error;

	// do runs while error is improving and at least nVars times
	float errorRunBest = -1;
	bool foundRun = false;

	for( int k = 1; bestPoint -> getVariance() > tolerance; k++ )
		{
			// run existing best points in different directions
			logger.logInfo( String( "runFindByOnePrecision before find: #" ) + k +
				" - best=" + run -> getBestPoints().first() -> getVariance() +
				", last=" + run -> getBestPoints().last() -> getVariance() +
				", range=" + run -> getSearchArea() );

			bool found = run -> scanBestPoints( samples , sample , runNext );

			// get iterations
			iterationsDone += run -> getIterationCount();

			if( found )
				{
					foundRun = true;

					logger.logInfo( String( "found: " ) + 
						" - best=" + run -> getBestPoints().first() -> getVariance() +
						", last=" + run -> getBestPoints().last() -> getVariance() );

					// get results
					NNScanPoint *bestPointRun = run -> getBestPoints().first();
					error = bestPointRun -> getVariance();

					// compare with current best point
					if( error < bestPoint -> getVariance() )
						bestPoint = bestPointRun;

					if( error >= errorRunBest )
						{
							// exit only after anough iterations were done
							if( k >= p -> getNVars() )
								break;
						}

					errorRunBest = error;
				}
			else
				{
					// if not found - exit after enough iterations
					if( k >= p -> getNVars() )
						break;
				}
		}

	return( foundRun );
}

NNWeights *NNStrategyScan::getFixedStartPoint()
{
	NNWeights *pwStartPoint = new NNWeights;

	AIDB db;
	db.load( pwStartPoint , "foreignXOR" );
	pwStartPoint -> attach( p );

	return( pwStartPoint );
}

NNWeights *NNStrategyScan::getRandomStartPoint()
{
	NNWeights *pwStartPoint = new NNWeights( p );
	pwStartPoint -> setRandomDefault();

	return( pwStartPoint );
}

void NNStrategyScan::mergeBest( ClassList<NNScanPoint>& best , ClassList<NNScanPoint>& bestIteration )
{
	for( int k = 0; k < bestIteration.count(); k++ )
		{
			NNScanPoint *psIteration = bestIteration[ k ];

			// find position in best
			int m = best.count() - 1;
			for( ; m >= 0; m-- )
				{
					NNScanPoint *ps = best[ m ];
					if( psIteration -> getVariance() > ps -> getVariance() )
						break;
				}
			m++;
			best.insert( m , psIteration );
		}

	bestIteration.clear();

	// remove all beyond max
	for( int z = best.count() - 1; z >= bestMax; z-- )
		{
			NNScanPoint *ps = best[ z ];
			delete ps;
			best.remove( z );
		}
}

void NNStrategyScan::setWeightRange( float p_valueMin , float p_valueMax )
{
	wLimitMin = p_valueMin;
	wLimitMax = p_valueMax;
}

void NNStrategyScan::getWeightRange( float& p_valueMin , float& p_valueMax )
{
	p_valueMin = wLimitMin;
	p_valueMax = wLimitMax;
}

void NNStrategyScan::setTolerance( float p_value )
{
	tolerance = p_value;
}

void NNStrategyScan::attach( NN *p_p )
{
	p = p_p;
	helper.attach( p_p );
	helper.attach( this );
}

const char *NNStrategyScan::NAME = "NNStrategyScan";

void NNStrategyScan::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNStrategyScan::onCreate );

	so -> addFieldInt( "maxTime" );
	so -> addFieldFloat( "wLimitMin" );
	so -> addFieldFloat( "wLimitMax" );
	so -> addFieldFloat( "tolerance" );
}

void NNStrategyScan::serialize( SerializeObject& so )
{
	so.setPropInt( maxTime , "maxTime" );
	so.setPropFloat( wLimitMin , "wLimitMin" );
	so.setPropFloat( wLimitMax , "wLimitMax" );
	so.setPropFloat( tolerance , "tolerance" );
}

void NNStrategyScan::deserialize( Object *parent , SerializeObject& so )
{
	maxTime = so.getPropInt( "maxTime" );
	wLimitMin = so.getPropFloat( "wLimitMin" );
	wLimitMax = so.getPropFloat( "wLimitMax" );
	tolerance = so.getPropFloat( "tolerance" );
}
