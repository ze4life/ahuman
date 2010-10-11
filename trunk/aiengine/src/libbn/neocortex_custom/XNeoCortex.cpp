#include "XNeoCortex.h"

/*#########################################################################*/
/*#########################################################################*/

XNeoCortex::XNeoCortex( unsigned nRegions , unsigned sourceSizeX , unsigned sourceSizeY , unsigned nClasses )
{
	sensorAreaSideX = sourceSizeX;
	sensorAreaSideY = sourceSizeY;
	predictionCount = nClasses;

	overlapSubRegions = 0;
	bestMatchPrecision = 0;
	deletionByPercentage = false;

	regionCount = nRegions;
	bottomSizeX = 0;
	bottomSizeY = 0;

	hippo = NULL;
	sensor = NULL;

	logger.attach( this );
}

XNeoCortex::~XNeoCortex()
{
	logger.logDebug( "Exiting NeoCortex..." );

	// delete classes
	regions.destroy();

	if( sensor != NULL )
		delete sensor;

	if( hippo != NULL )
		delete hippo;
}

void XNeoCortex::createCortexNetwork()
{
	logger.logDebug( String( "SFNeoCortex::createCortexNetwork - create neocortex with bottomSizeX=" ) + bottomSizeX + ", bottomSizeY=" + bottomSizeY + ":" , Logger::LogStart );

	unsigned i, sideX = 0, sideY = 0;
	for(i = 0; i < regionCount; i++) {
		if(i == 0) {
			sideX = bottomSizeX;
			sideY = bottomSizeY;
		}
		else {
			sideX /= regionSideXCompression[i];
			sideY /= regionSideYCompression[i];
		}

		XNeoRegion *region = new XNeoRegion( *this , sideX , sideY , maxSequenceLength[i] , regionSideXCompression[i] , regionSideYCompression[i] , i );
		regions.add( region );

		logger.logDebug( String( "\tSFNeoCortex::createCortexNetwork - create region with sideX=" ) + sideX + ", sideY=" + sideY , Logger::LogLine );

		if(i > 0)
			regions[i] -> setChild(regions[i-1]);
	}

	for(i = 0; i < regionCount-1; i++)
		regions[i] -> setParent( regions[i+1] );

	// create default sensor if not created before
	if( sensor == NULL )
		sensor = new XSense( sensorAreaSideX , sensorAreaSideY , overlapSubRegions );

	regions[0] -> setChild( sensor );
	sensor -> setParent( regions[0] );

	hippo = new XHippocampus( *this , sideX , sideY ); //side of top region == side compression of hippocampus to give '1'
	hippo -> setChild( regions[regionCount-1] );
	regions[regionCount-1] -> setParent( hippo );

	logger.logDebug( String( "\tSFNeoCortex::createCortexNetwork - create Hippo with sideX=" ) + sideX + ", sideY=" + sideY , Logger::LogStop );
}

void XNeoCortex::setOverlapSubRegions( unsigned p_v ) {
}

/*#########################################################################*/
/*#########################################################################*/
