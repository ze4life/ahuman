#include "ainnlib_impl.h"

#define MINIMAL_IMPROVEMENT_CHANGE 0.001

/*#########################################################################*/
/*#########################################################################*/

NNStrategyScanIteration::NNStrategyScanIteration( NNStrategyScan *p_strategy , NN *p_p , 
	int p_bestMax , int p_axisItems , int p_pointsToCheck )
:	p( p_p ) ,
	engine( AIEngine::getInstance() ) ,
	pwc( p_p ) ,
	helper( logger )
{
	strategy = p_strategy;

	bestMax = p_bestMax;
	pointsToCheck = p_pointsToCheck;
	axisItems = p_axisItems;
	nVars = p -> getNVars();

	axisErrorData = ( float * )calloc( nVars , sizeof( float ) );
	axisIndex = ( int * )calloc( nVars , sizeof( int ) );

	int total = 1;
	for( int k = 0; k < axisItems; k++ )
		total *= pointsToCheck;
	errorValues = ( float * )calloc( total , sizeof( float ) );
	
	bestChanges = 0;
	pwStartPoint = NULL;

	searchArea = 0;
	countRuns = 0;
	axisSelection = false;
	minPoints = 0;

	searchArea = 0;
	uniqueID = 0;

	findBest = 0;
	findLast = 0;
	findCount = 0;

	randoms4Axes.createRangeRandomsInt( 0 , nVars - axisItems - 1 );
	errFunc = PACKET_ERRFUNC_VAR;
}

NNStrategyScanIteration::~NNStrategyScanIteration()
{
	axisValues.destroy();

	free( axisErrorData );
	free( axisIndex );
	free( errorValues );

	best.destroy();
}

bool NNStrategyScanIteration::find( NNScanPoint *p_spStartPoint , float *error )
{
	findBest = 0;
	findLast = 0;
	findCount = 0;

	pwStartPoint = p_spStartPoint -> getWeights();

	// init perceptron weights by start point
	pwStartPoint -> setToPerceptron();

	// show start point
	// helper.showPerceptron();

	// choose search direction - by source
	axisSelection = true;
	bool searchOk = selectSearchDirection( p_spStartPoint -> getSourcePoint() );
	axisSelection = false;
	if( !searchOk )
		return( false );

	// recursion by random variables
	countRuns = 0;
	bestChanges = 0;
	float *pe = errorValues;
	findWalk( 0 , pe );

	// show data
	// helper.showScanSlices( axisValues , errorValues , axisItems , pointsToCheck );

	// find minimums
	minPoints = 0;
	findMinPoints();
	if( minPoints == 0 )
		throw RuntimeError( "NNStrategyScanIteration::find: minPoints == 0" );

	// show search iteration
	// helper.showScanIteration( pwStartPoint , &best , axisValues , countRuns , minPoints , bestChanges , searchArea );

	*error = best.first() -> getVariance();
	return( true );
}

int NNStrategyScanIteration::onSortAxis( const int& v1 , const int& v2 )
{
	if( axisErrorData[ v1 ] < axisErrorData[ v2 ] )
		return( -1 );
	if( axisErrorData[ v1 ] > axisErrorData[ v2 ] )
		return( 1 );

	return( 0 );
}

int NNStrategyScanIteration::onSortAxisFirst( const int& v1 , const int& v2 )
{
	if( v1 < v2 )
		return( -1 );
	if( v1 > v2 )
		return( 1 );

	return( 0 );
}

bool NNStrategyScanIteration::selectSearchDirection( NNScanPoint *p_spStartPoint )
{
	axisValues.destroy();

	if( !chooseRandomAxisItems( p_spStartPoint ) )
		return( false );

	// get best axes
	int index;
	float *ptr;
	for( int b = 0; b < axisItems; b++ )
		{
			index = axisIndex[ b ];
			ptr = pwStartPoint -> getVarPtrByIndex( index );
			addAxis( index , ptr );
		}

	return( true );
}

bool NNStrategyScanIteration::chooseRandomAxisItems( NNScanPoint *p_spStartPoint )
{
	for( int z = 0; z < 100; z++ )
		{
			// generate random axes
			for( int k = 0; k < axisItems; k++ )
				axisIndex[ k ] = randoms4Axes.getRandomInt();
			
			// sort by value
			Sort<int,NNStrategyScanIteration> doSortFirst( axisIndex , axisItems , this , &NNStrategyScanIteration::onSortAxisFirst );

			// adjust to make different
			for( int m = 1; m < axisItems; m++ )
				axisIndex[ m ] += m;

			// get direction ID
			String direction = getDirection( axisIndex );

			// check exists
			if( !p_spStartPoint -> isSearchDirectionUsed( direction ) )
				{
					searchDirection = direction;
					return( true );
				}

			// engine.logInfo( String( "POINT #" ) + p_spStartPoint -> getId() +
			//	": skip search direction - " + direction );
		}

	return( false );
}

String NNStrategyScanIteration::getDirection( int *axes )
{
	String direction;
	for( int m = 0; m < axisItems; m++ )
		{
			int index = axes[ m ];
			
			// check exists
			if( m == 0 )
				direction = String( "SD-" ) + index;
			else
				direction += String( "-" ) + index;
		}
	return( direction );
}

bool NNStrategyScanIteration::chooseBestAxisItems( NNScanPoint *p_spStartPoint )
{
	// search across axis
	for( int k = 0; k < nVars; k++ )
		{
			float errorByAxis = calculateErrorByAxis( k );
			axisErrorData[ k ] = errorByAxis;
			axisIndex[ k ] = k;
		}

	Sort<int, NNStrategyScanIteration> doSort( axisIndex , nVars , this , &NNStrategyScanIteration::onSortAxis );

	// show status of axis
	// helper.showAxisError( axisIndex , axisErrorData , nVars );

	// select direction set not used by point
	// iterate axes combinations
	MultiIndexIterator mi( axisItems , nVars );
	mi.startDistinctUnsorted();
	int *axes = new int[ axisItems ];

	bool found = false;
	while( mi.nextDistinctUnsorted() )
		{
			// get direction
			for( int z = 0; z < axisItems; z++ )
				axes[ z ] = axisIndex[ mi.getAxisIndex( z ) ];
			Sort<int, NNStrategyScanIteration> doSortFirst( axes , axisItems , this , &NNStrategyScanIteration::onSortAxisFirst );

			String direction = getDirection( axes );

			// check exists
			if( !p_spStartPoint -> isSearchDirectionUsed( direction ) )
				{
					searchDirection = direction;
					found = true;
					break;
				}

			// engine.logInfo( String( "POINT #" ) + p_spStartPoint -> getId() +
			//	": skip search direction - " + direction );
		}

	if( found )
		{
			// replace axisItems
			for( int a = 0; a < axisItems; a++ )
				axisIndex[ a ] = axes[ a ];
		}

	delete axes;
	return( found );
}

NNStrategyScanItem *NNStrategyScanIteration::addAxis( int axisIndex , float *ptr )
{
	NNStrategyScanItem *item = new NNStrategyScanItem;

	item -> index = axisIndex;
	item -> centerValue = pwStartPoint -> getVarValue( axisIndex );

	if( ptr != NULL )
		item -> ptrValue = ptr;
	else
		item -> ptrValue = pwStartPoint -> getVarPtrByIndex( axisIndex );

	strategy -> getWeightRange( item -> wValueLimitMin , item -> wValueLimitMax );

	item -> fromValue = getMax( item -> centerValue - searchArea , item -> wValueLimitMin );
	item -> toValue = getMin( item -> centerValue + searchArea , item -> wValueLimitMax );
	item -> totalPoints = pointsToCheck;

	axisValues.add( item );

	return( item );
}

void NNStrategyScanIteration::findWalk( int p_axisItem , float*& pe )
{
	NNStrategyScanItem *item = axisValues[ p_axisItem ];
	float *pf = item -> ptrValue;

	// iterate
	float fromValue = item -> fromValue;
	float toValue = item -> toValue;
	if( fromValue >= toValue )
		throw RuntimeError( "NNStrategyScanIteration::findWalk: from >= to" );

	float delta = ( toValue - fromValue ) / ( pointsToCheck - 1 );
	*pf = fromValue;
	for( int k = 0; k < pointsToCheck; k++ , *pf += delta )
		{
			if( p_axisItem == axisValues.count() - 1 )
				{
					float errorValue = calculateCurrentError();
					int index = pe - errorValues;
					// engine.logInfo( String( "P#" ) + index + "=" + errorValue );

					*pe++ = errorValue;
				}
			else
				{
					findWalk( p_axisItem + 1 , pe );
					//if( p_axisItem == 0 )
					//	engine.logInfo( String( "countRuns=" ) + countRuns );
				}
		}
}

float NNStrategyScanIteration::calculateCurrentError()
{
	NNErrorFunction *ef = strategy -> getErrorFunction();
	if( sample != NULL )
		{
			p -> execute();
			countRuns++;
			return( ef -> getErrorSampleProgress( sample ) );
		}

	// get max of all samples
	float errorValue = 0;
	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sampleLocal = samples -> getByPos( k );
			p -> setSensors( sampleLocal );

			float errorValueSingle = ef -> getErrorSampleProgress( sampleLocal );
			countRuns++;

			switch( errFunc ) 
				{
					case PACKET_ERRFUNC_MAX :
						if( errorValueSingle > errorValue )
							errorValue = errorValueSingle;
						break;
					case PACKET_ERRFUNC_VAR :
						errorValue += errorValueSingle * errorValueSingle;
						break;
				}
		}

	switch( errFunc ) 
		{
			case PACKET_ERRFUNC_MAX :
				return( errorValue );
			case PACKET_ERRFUNC_VAR :
				return( sqrt( errorValue / samples -> count() ) );
		}

	throw RuntimeError( "NNStrategyScanIteration::calculateCurrentError: unknown error function" );
}

float NNStrategyScanIteration::calculateErrorByAxis( int axis )
{
	// iterate
	float centerValue = pwStartPoint -> getVarValue( axis );

	float cwLimitMin , cwLimitMax;
	strategy -> getWeightRange( cwLimitMin , cwLimitMax );

	float fromValue = getMax( centerValue - searchArea , cwLimitMin );
	float toValue = getMin( centerValue + searchArea , cwLimitMax );
	if( fromValue >= toValue )
		throw RuntimeError( String( "NNStrategyScanIteration::calculateErrorByAxis: from >= to" ) );

	float *pf = pwStartPoint -> getVarPtrByIndex( axis );
	float delta = ( toValue - fromValue ) / ( pointsToCheck - 1 );

	// save start point
	float pfSave = *pf;

	// iterate with values by axis
	*pf = fromValue;
	float minError = -1;
	for( int k = 0; k < pointsToCheck; k++ , *pf += delta )
		{
			float error = calculateCurrentError();
			if( error < minError || minError < 0 )
				minError = error;

			// show value/error
			// engine.logInfo( String( "AXIS SELECTION #" ) + axis + ": " + *pf + " -> " + error );
		}

	// restore start point
	*pf = pfSave;

	return( minError );
}

// find minimums
void NNStrategyScanIteration::findMinPoints()
{
	// examine all points
	MultiIndexIterator mp( axisItems , pointsToCheck );
	MultiIndexIterator mpAround( axisItems , pointsToCheck );
	mp.start();
	while( mp.next() )
		{
			int pos = mp.getGlobalIndex();
			float errorValue = errorValues[ pos ];

			// scan 1-cube around
			bool allGreater = true;
			mpAround.startAround( mp );
			// helper.showIndexes( mp , errorValue );

			while( mpAround.nextAround() )
				{
					int posAround = mpAround.getGlobalIndexAround();
					float errorValueAround = errorValues[ posAround ];
					// helper.showIndexesAround( mpAround , errorValueAround );

					// check greater
					if( errorValueAround < errorValue )
						{
							allGreater = false;
							break;
						}
				}

			if( !allGreater )
				continue;

			// show minimum
			addMinItem( mp , errorValue );
		}
}

int NNStrategyScanIteration::addMinItem( MultiIndexIterator& mp , float errorValue )
{
	minPoints++;

	// show
	int globalIndex = mp.getGlobalIndex();
	// engine.logInfo( String( "MIN: error=" ) + errorValue + ", index=" + globalIndex );

	// don't add items only slightly better than last
	float last = 0;
	if( best.count() > 0 )
		{
			last = best.last() -> getVariance();
			if( last - errorValue < MINIMAL_IMPROVEMENT_CHANGE )
				return( -1 );
		}

	// check the result - from end of best - find position to insert after
	int bk = best.count() - 1;
	for( ; bk >= 0; bk-- )
		{
			NNScanPoint *pw = best.get( bk );
			if( errorValue >= pw -> getVariance() )
				break;
		}
	bk++;

	// too bad for best list
	ASSERT( bk < bestMax );

	// get weights and check adding the same
	setWeightsFromMultiIndexIterator( &pwc , mp );
	if( checkTheSamePoint( &pwc , bk ) )
		return( -1 );

	// engine.logInfo( String( "addMinItem: improve worst from " ) + last + 
	//	" to " + errorValue + ", total=" + best.count() );

	// insert
	bestChanges++;
	NNScanPoint *ps;
	if( best.count() < bestMax )
		{
			ps = new NNScanPoint( p , ++uniqueID );
			best.insert( bk , ps );
		}
	else
		{
			best.move( best.count() - 1 , bk );
			ps = best.get( bk );
			ps -> reuse( ++uniqueID );
		}

	ps -> getWeights() -> setTo( &pwc );
	ps -> setVariance( errorValue );

	// find statistics
	findCount++;
	if( findBest == 0 )
		findBest = findLast = errorValue;
	else
		{
			if( errorValue < findBest )
				findBest = errorValue;
			if( errorValue > findLast )
				findLast = errorValue;
		}

	// helper.showScanPoint( bk , ps );

	return( bk );
}

void NNStrategyScanIteration::setWeightsFromMultiIndexIterator( NNWeights *pw , MultiIndexIterator& mp )
{
	// copy all weights from start points
	pw -> setTo( pwStartPoint );

	// set points from multiindex
	for( int k = 0; k < axisValues.count(); k++ )
		{
			NNStrategyScanItem *axis = axisValues[ k ];
			int point = mp.getAxisIndex( k );
			float value = axis -> getPointValue( point );

			pw -> setIndexValue( axis -> index , value );
		}
}

void NNStrategyScanIteration::copyBestPoints( ClassList<NNScanPoint> *dstList )
{
	for( int k = 0; k < best.count(); k++ )
		{
			NNScanPoint *src = best[ k ];
			NNScanPoint *dst = new NNScanPoint( src );
			dstList -> add( dst );
		}
}

ClassList<NNScanPoint>& NNStrategyScanIteration::getBestPoints()
{
	return( best );
}

int NNStrategyScanIteration::addMinPoint( NNScanPoint *psSrc )
{
	minPoints++;

	// show
	float errorValue = psSrc -> getVariance();
	// engine.logInfo( String( "MIN: error=" ) + errorValue );

	// don't add items only slightly better than last
	float last = 0;
	if( best.count() > 0 )
		{
			last = best.last() -> getVariance();
			if( last - errorValue < MINIMAL_IMPROVEMENT_CHANGE )
				return( -1 );
		}

	// check the result - from end of best - find position to insert after
	int bk = best.count() - 1;
	for( ; bk >= 0; bk-- )
		{
			NNScanPoint *pw = best.get( bk );
			if( errorValue >= pw -> getVariance() )
				break;
		}
	bk++;

	// too bad for best list
	ASSERT( bk < bestMax );

	// check the same point already exists
	if( checkTheSamePoint( psSrc -> getWeights() , bk ) )
		return( -1 );

	// engine.logInfo( String( "addMinPoint: improve worst from " ) + last + 
	//	" to " + errorValue + ", total=" + best.count() );

	// insert
	bestChanges++;
	NNScanPoint *ps;
	if( best.count() < bestMax )
		{
			ps = new NNScanPoint( p , psSrc -> getId() );
			best.insert( bk , ps );
		}
	else
		{
			best.move( best.count() - 1 , bk );
			ps = best.get( bk );
			ps -> reuse( psSrc -> getId() );
		}

	ps -> getWeights() -> setTo( psSrc -> getWeights() );
	ps -> setVariance( errorValue );

	// helper.showScanPoint( bk , ps );
	return( bk );
}

bool NNStrategyScanIteration::scanBestPoints( NNSamples *p_samples , NNSample *p_sample , NNStrategyScanIteration *runNext )
{
	samples = p_samples;
	sample = p_sample;

	ClassList<NNScanPoint> bestBefore;
	copyBestPoints( &bestBefore );

	// for all current best points - choose direction/find again
	int findCountTotal = 0;
	int iterationsDone = 0;
	countRuns = 0;
	for( int k = 0; k < bestBefore.count(); k++ )
		{
			NNScanPoint *ps = bestBefore[ k ];

			// no need to check if too bad now
			if( ps -> getSourcePoint() == NULL )
				continue;

			float error;
			bool findRes = find( ps , &error );
			iterationsDone += countRuns;
 			if( !findRes )
				{
					// engine.logInfo( String( "scanBestPoints: point#" ) + ps -> getId() +
					//	" - unable to find search direction" );
					continue;
				}
			findCountTotal += findCount;

			// add search direction (can be NULL if replaced by found points)
			NNScanPoint *psSrc = ps -> getSourcePoint();
			if( psSrc != NULL )
				psSrc -> addSearchDirection( searchDirection );

			/*
			engine.logInfo( String( "scanBestPoints: point#" ) + ps -> getId() +
				" - search=" + searchDirection +
				" - start=" + ps -> getVariance() +
				", best=" + best.first() -> getVariance() +
				", last=" + best.last() -> getVariance() +
				", findCount=" + findCount +
				", findBest=" + findBest + 
				", findLast=" + findLast );
			*/
		}

	// set total number of runs
	countRuns = iterationsDone;

	// check latest best points - for global min
	ClassList<NNScanPoint>& bestAfter = getBestPoints();
	for( int b = 0; b < bestAfter.count(); b++ )
		{
			NNScanPoint *ps = bestAfter[ b ];
			if( !ps -> isStatusUnknown() )
				continue;

			bool isMin = checkGlobalMin( b , searchArea / 10 , ps );
			ps -> setMinimum( isMin );

			if( isMin && runNext != NULL )
				runNext -> addMinPoint( ps );
		}


	// show sample errors for best
	// helper.showSamplesVariance( best.first() );
	// helper.showBestWeights( &bestAfter );
	return( findCountTotal > 0 );
}

bool NNStrategyScanIteration::checkGlobalMin( int id , float searchArea , NNScanPoint *ps )
{
	NNWeights *pw = ps -> getWeights();

	// split remaining (based on axisIndex[]) axes by axisItems
	for( int k = axisItems; k < nVars; k += axisItems )
		{
			// check it is last group
			int count = axisItems;
			if( k + axisItems > nVars )
				count = nVars - k;

			// check it is min across given axes
			if( !checkGlobalMinBySubset( id , k , count , ps -> getVariance() , pw ) )
				return( false );
		}

	return( true );
}

bool NNStrategyScanIteration::checkGlobalMinBySubset( int id , int startIndexPos , int count , float errorMin , NNWeights *pw )
{
	pw -> setToPerceptron();

	MultiIndexIterator mi( count , 3 );
	mi.start();

	float *values = pw -> getData();

	float cwLimitMin , cwLimitMax;
	strategy -> getWeightRange( cwLimitMin , cwLimitMax );

	int countBeyond = 0;
	int countChecked = 0;
	while( mi.next() )
		{
			// set values to pw
			bool beyond = false;
			for( int k = 0; k < count; k++ )
				{
					int index = mi.getAxisIndex( k );
					int axis = axisIndex[ startIndexPos + k ];
					float value = values[ axis ] + searchArea * ( index - 1 );

					if( value < cwLimitMin || value > cwLimitMax )
						{
							beyond = true;
							countBeyond++;
							break;
						}

					float *ptr = pw -> getVarPtrByIndex( axis );
					*ptr = value;
				}

			// helper.onCheckGlobalMinBySubset( id , mi , beyond , 0 , errorMin , countChecked , false , axisIndex , startIndexPos );
			if( beyond )
				continue;
					
			float error = calculateCurrentError();
			countChecked++;

			if( error < errorMin )
				{
					// helper.onCheckGlobalMinBySubset( id , mi , beyond , error , errorMin , countChecked , true , axisIndex , startIndexPos );
					return( false );
				}
		}

	// helper.onCheckGlobalMinBySubset( id , mi , false , 0 , errorMin , countChecked , true , axisIndex , startIndexPos );
	return( true );
}

int NNStrategyScanIteration::getIterationCount()
{
	return( countRuns );
}

void NNStrategyScanIteration::clearIterationCount()
{
	countRuns = 0;
}

void NNStrategyScanIteration::setSearchArea( float value )
{
	searchArea = value;
}

float NNStrategyScanIteration::getSearchArea()
{
	return( searchArea );
}

NNScanPoint *NNStrategyScanIteration::createBestPoint( NNWeights *point )
{
	NNScanPoint *sp = new NNScanPoint( p , ++uniqueID );
	NNWeights *pw = sp -> getWeights();
	pw -> setTo( point );
	
	pw -> setToPerceptron();
	float variance = calculateCurrentError();
	sp -> setVariance( variance );
	
	best.add( sp );
	return( sp );
}

bool NNStrategyScanIteration::checkTheSamePoint( NNWeights *pw , int pos )
{
	float tolerance = searchArea / 100;

	// check before
	if( pos > 0 )
		if( pw -> equals( best[ pos - 1 ] -> getWeights() , tolerance ) )
			return( true );

	// check after
	if( pos < bestMax - 1 && pos < best.count() )
		if( pw -> equals( best[ pos ] -> getWeights() , tolerance ) )
			return( true );

	return( false );
}
