#include "XNeoCortex.h"

/*#########################################################################*/
/*#########################################################################*/

XNeoCortex::XNeoCortex( XSense *p_sense , unsigned p_sensorSizeX , unsigned p_sensorSizeY , unsigned p_hippoPatchSizeX , unsigned p_hippoPatchSizeY , 
		unsigned p_hippoOutputSizeX , unsigned p_hippoOutputSizeY , unsigned p_hippoMemorySize )
{
	sensor = p_sense;

	sensorSizeX = p_sensorSizeX;
	sensorSizeY = p_sensorSizeY;
	hippoPatchSizeX = p_hippoPatchSizeX;
	hippoPatchSizeY = p_hippoPatchSizeY;
	hippoOutputSizeX = p_hippoOutputSizeX;
	hippoOutputSizeY = p_hippoOutputSizeY;
	hippoMemorySize = p_hippoMemorySize;

	bestMatchPrecision = 0;
	deletionByPercentage = false;

	hippo = NULL;

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

XNeoRegion *XNeoCortex::addRegion( unsigned srcSizeX , unsigned srcSizeY , unsigned overlapSubRegions , unsigned memorySize , 
	double forgetThreshold , unsigned lowUsageThreshold , unsigned maxSequenceLength )
{
	// calculate size of region
	// regionSizeX * srcSizeX = upperregionSizeX + ( regionSizeX - 1 ) * overlapSubRegions
	// regionSizeX = ( upperregionSizeX - overlapSubRegions ) / ( srcSizeX - overlapSubRegions );
	// upper region is last region in already added or sensor size
	unsigned upperregionSizeX = ( regions.count() > 0 )? regions.last() -> getRegionSizeX() : sensorSizeX;
	unsigned upperregionSizeY = ( regions.count() > 0 )? regions.last() -> getRegionSizeY() : sensorSizeY;
	
	unsigned regionSizeX = ( upperregionSizeX - overlapSubRegions ) / ( srcSizeX - overlapSubRegions );
	unsigned regionSizeY = ( upperregionSizeY - overlapSubRegions ) / ( srcSizeY - overlapSubRegions );

	XNeoRegion *region = new XNeoRegion( *this , regions.count() , srcSizeX , srcSizeY , overlapSubRegions , regionSizeX , regionSizeY ,
		memorySize , forgetThreshold , lowUsageThreshold , maxSequenceLength );
	regions.add( region );

	return( region );
}

void XNeoCortex::createCortexNetwork()
{
	logger.logDebug( String( "XNeoCortex - create neocortex with sensorSizeX=" ) + sensorSizeX + ", sensorSizeY=" + sensorSizeY , Logger::LogStart );

	for( int k = 0; k < regions.count(); k++ ) {
		XNeoRegion *region = regions[ k ];
		logger.logDebug( String( "\tXNeoCortex - create region with srcPatchSizeX=" ) + region -> srcPatchSizeX + 
			", srcPatchSizeY=" + region -> srcPatchSizeY + 
			", regionSizeX=" + region -> getRegionSizeX() +
			", regionSizeY=" + region -> getRegionSizeY() +
			", maxSequenceLength=" + region -> maxSequenceLength +
			", maxMemorySize=" + region -> maxMemorySize +
			", overlapSubRegions=" + region -> overlapSubRegions , Logger::LogLine );

		if( k > 0 ) {
			regions[k] -> setChild( regions[k-1] );
			regions[k-1] -> setParent( regions[k] );
		}
	}

	// create default sensor if not created before
	if( sensor == NULL )
		sensor = new XSense( sensorSizeX , sensorSizeY );

	regions.first() -> setChild( sensor );
	sensor -> setParent( regions.first() );

	hippo = new XHippocampus( *this , hippoPatchSizeX , hippoPatchSizeY , hippoOutputSizeX , hippoOutputSizeY , hippoMemorySize ); //side of top region == side compression of hippocampus to give '1'
	hippo -> setChild( regions.last() );
	regions.last() -> setParent( hippo );

	logger.logDebug( String( "\tXNeoCortex - create Hippo with hippoPatchSizeX=" ) + hippoPatchSizeX + 
		", hippoPatchSizeY=" + hippoPatchSizeY +
		", hippoOutputSizeX=" + hippoOutputSizeX +
		", hippoOutputSizeY=" + hippoOutputSizeY +
		", hippoMemorySize=" + hippoMemorySize , Logger::LogStop );
}

void XNeoCortex::showRegionMemories()
{
	logger.logDebug( "NeoCortex regions:" , Logger::LogStart );
	for( int k = 0; k < regions.count(); k++ ) {
		XNeoRegion *region = regions.get( k );
		logger.logDebug( String( "\tRegion " ) + k + ": memories=" + region -> getMemCount() , Logger::LogLine );
	}
	logger.logDebug( "." , Logger::LogStop );
}

/*#########################################################################*/
/*#########################################################################*/
