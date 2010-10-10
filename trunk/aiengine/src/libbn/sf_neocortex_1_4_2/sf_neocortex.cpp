#include "sf_neocortex.h"
#include "Hippo.h"

/*#########################################################################*/
/*#########################################################################*/

SFNeoCortex::~SFNeoCortex()
{
	logger.logDebug( "Exiting NeoCortex..." );

	// delete classes
	regions.destroy();
	delete sensor;
	delete hippo;
}

void SFNeoCortex::createCortexNetwork()
{
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

		NeoRegion *region = new NeoRegion( *this , sideX , sideY , maxSequenceLength[i] , regionSideXCompression[i] , regionSideYCompression[i] , i );
		regions.add( region );

		if(i > 0)
			regions[i] -> setChild(regions[i-1]);
	}

	for(i = 0; i < regionCount-1; i++)
		regions[i] -> setParent( regions[i+1] );

	sensor = new Sense( sensorAreaSideX , sensorAreaSideY , overlapSubRegions );
	regions[0] -> setChild( sensor );
	sensor -> setParent( regions[0] );

	hippo = new Hippocampus( *this , sideX , sideY ); //side of top region == side compression of hippocampus to give '1'
	hippo -> setChild( regions[regionCount-1] );
	regions[regionCount-1] -> setParent( hippo );
}

void SFNeoCortex::setOverlapSubRegions( unsigned p_v ) {
}

/*#########################################################################*/
/*#########################################################################*/
