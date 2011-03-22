#include "fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

NNFinderFactorySample::NNFinderFactorySample( NNSample *p_fs , NNSample *p_fe )
{
	fs = p_fs;
	fe = p_fe;

	// set fe dimensions
	if( fe != NULL )
		{
			setSysVar( SYS_SA , SA_COUNT );
			setSysVar( SYS_SB , SB_COUNT );
		}
}

void NNFinderFactorySample::adjustDimensions( NNSamples *ss )
{
	int oldSensors = ss -> sizeIn();
	int newSensors = SA_COUNT + SB_COUNT + SYS_COUNT;

	ASSERT( newSensors >= oldSensors );
	if( newSensors <= oldSensors )
		return;

	ss -> addSensors( newSensors - oldSensors , 0 );

	// move sensor data
	for( int k = 0; k < ss -> count(); k++ )
		{
			NNSample *s = ss -> getByPos( k );
			float *sv = s -> getSensors();

			// reposition system vars
			memmove( sv + oldSensors - SYS_COUNT , sv + newSensors - SYS_COUNT , sizeof( float ) * SYS_COUNT );

			// reposition
			int nSAold = ( int )sv[ newSensors - 1 - SYS_SA ];
			int nSBold = ( int )sv[ newSensors - 1 - SYS_SB ];
			ASSERT( nSAold <= SA_COUNT );
			ASSERT( nSBold <= SB_COUNT );

			// clear resize SB area
			if( nSBold < SB_COUNT )
				memset( sv + newSensors - SYS_COUNT - ( SB_COUNT - nSBold ) , 0 , sizeof( float ) * ( SB_COUNT - nSBold ) );

			// move SB area
			if( SA_COUNT > nSAold )
				memmove( sv + nSAold , sv + SA_COUNT , sizeof( float ) * ( SA_COUNT - nSAold ) );

			// clear resize SA area
			if( SA_COUNT > nSAold )
				memset( sv + nSAold , 0 , sizeof( float ) * ( SA_COUNT - nSAold ) );
		}
}

void NNFinderFactorySample::setSA( NNFinderFactorySample::FieldSA field , float v )
{
	fe -> getSensors()[ field ] = v;
}

void NNFinderFactorySample::setSB( NNFinderFactorySample::FieldSB field , float v )
{
	fe -> getSensors()[ field + SA_COUNT ] = v;
}

void NNFinderFactorySample::setST( NNFinderFactorySample::FieldST field , float v )
{
	fe -> getTargets()[ field ] = v;
}

float NNFinderFactorySample::getSA( NNFinderFactorySample::FieldSA field )
{
	return( fe -> getSensors()[ field ] );
}

float NNFinderFactorySample::getSB( NNFinderFactorySample::FieldSB field )
{
	return( fe -> getSensors()[ field + SA_COUNT ] );
}

float NNFinderFactorySample::getST( NNFinderFactorySample::FieldST field )
{
	return( fe -> getTargets()[ field ] );
}

float NNFinderFactorySample::p2TargetFunction( NN *pp )
{
	return( 0 );
}

float NNFinderFactorySample::p2TargetFunction( const float *t )
{
	// scale unlimited to 0-1 (use ratio: 50 epochs=0.02 restarts=500 execute stats)
	float v1 = t[ ST_avgEpochs ]; 
	v1 = 1 - 1 / ( 1 + 0.02f * v1 );

	float v2 = t[ ST_avgRestarts ]; 
	v2 = 1 - 1 / ( 1 + 50 * v2 );

	float v3 = t[ ST_avgExecuteStat ];
	v3 = 1 - 1 / ( 1 + 0.002f * v3 );

	float v4 = t[ ST_avgValidateError ];

	// weighted sum
	float v = ( v1 + v2 + v3 + v4 ) / 4;

	return( v );
}

void NNFinderFactorySample::setSysVar( FieldSYS field , float value )
{
	fe -> getSensors()[ fe -> getNSensors() - 1 - field ] = value;
}

float NNFinderFactorySample::getSysVar( FieldSYS field )
{
	return( fe -> getSensors()[ fe -> getNSensors() - 1 - field ] );
}

// set all at once
void NNFinderFactorySample::setStat( NNSamples *samplesLearn , NNSamples *samplesValidate , NNFinder::StatParams *sp , NNFinder::StatResults& res )
{
	setSA( SA_nSensors , ( float )samplesLearn -> sizeIn() );
	setSA( SA_nTargets , ( float )samplesLearn -> sizeOut() );
	setSB( SB_algorithm , ( float )sp -> algorithm );
	setSB( SB_nHiddenNeurons1 , ( float )sp -> hiddenLayerSize );
	setSB( SB_learnRate , sp -> gradientRate );

	setST( ST_avgEpochs , ( float )res.avgEpochCount );
	setST( ST_avgRestarts , ( float )res.restartsTotal );
	setST( ST_avgExecuteStat , ( float )res.setSensorsTotal );
	setST( ST_avgValidateError , ( float )res.validationFailures );
}

int NNFinderFactorySample::getStatSampleSensors( NNVariables *vars , ClassList<NNVariable>& sensors )
{
	sensors.add( vars -> addCommonNumber( true , 1 , true , 100 ) ); // SA_nSensors
	sensors.add( vars -> addCommonNumber( true , 1 , true , 100 ) ); // SA_nTargets
	sensors.add( vars -> addCommonCategory( 4 ) ); // SB_algorithm
	sensors.add( vars -> addCommonNumber( true , 1 , true , 100 ) ); // SB_nHiddenNeurons1
	sensors.add( vars -> addCommonNumber( true , 0.1f , true , 10 ) ); // SB_learnRate
	return( SA_COUNT + SB_COUNT + SYS_COUNT );
}

int NNFinderFactorySample::getStatSampleTargets( NNVariables *vars , ClassList<NNVariable>& targets )
{
	targets.add( vars -> addCommonNumber( true , 1 , true , 1000 ) ); // ST_avgEpochs
	targets.add( vars -> addCommonNumber( true , 0 , true , 1000 ) ); // ST_avgRestarts
	targets.add( vars -> addCommonNumber( true , 0 , true , 1000000 ) ); // ST_avgExecuteStat
	targets.add( vars -> addCommonNumber( true , 0 , true , 1 ) ); // ST_avgValidateError
	return( ST_COUNT );
}

int NNFinderFactorySample::getTrainSampleSensors( NNVariables *vars , ClassList<NNVariable>& sensors )
{
	sensors.add( vars -> addCommonNumber( true , 1 , true , 100 ) ); // SA_nSensors
	sensors.add( vars -> addCommonNumber( true , 1 , true , 100 ) ); // SA_nTargets
	sensors.add( vars -> addCommonNumber( true , 0 , true , 1 ) ); // SC_errorLevel
	return( SA_COUNT + 1 );
}

int NNFinderFactorySample::getTrainSampleTargets( NNVariables *vars , ClassList<NNVariable>& targets )
{
	targets.add( vars -> addCommonCategory( 4 ) ); // SB_algorithm
	targets.add( vars -> addCommonNumber( true , 1 , true , 100 ) ); // SB_nHiddenNeurons1
	targets.add( vars -> addCommonNumber( true , 0.1f , true , 10 ) ); // SB_learnRate
	return( SB_COUNT );
}

void NNFinderFactorySample::completeFS( NN *nfe )
{
	float *fss = fs -> getSensors();
	float *fst = fs -> getTargets();
	float *fes = fe -> getSensors();
	float *fet = fe -> getTargets();

	// sensors
	memcpy( fss , fes , sizeof( float ) * SA_COUNT );
	fss[ SC_errorLevel ] = p2TargetFunction( fet );

	// targets
	memcpy( fst , fes + SA_COUNT , sizeof( float ) * SB_COUNT );
}

