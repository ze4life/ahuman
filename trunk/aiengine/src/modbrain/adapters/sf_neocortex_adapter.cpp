#include "../brain_impl.h"
#include "ailibbn.h"

/*#########################################################################*/
/*#########################################################################*/

class SFNeoCortexAdapter : public Cortex {
private:
	SFNeoCortexLibBN *lib;
	Object *libobj;

public:
SFNeoCortexAdapter( SFNeoCortexLibBN *p_lib , Object *p_libobj , MindArea *area , const CortexIOSizeInfo& io )
:	lib( p_lib ) ,
	libobj( p_libobj ) ,
	Cortex( "SFNeoCortex" , area , io )
{
}

~SFNeoCortexAdapter()
{
	lib -> deleteObject( libobj );
}

};

/*#########################################################################*/
/*#########################################################################*/

Cortex *AIBrainImpl::createSFNeoCortexAdapter( MindArea *area , BrainLocation& relativeLocation , Cortex *sensorCortex )
{
	// use Source Forge neocortex library
	AILibBN libbn;
	SFNeoCortexLibBN *lib = libbn.getSFNeoCortexLib();

	// create belief network
	// inputs - given cortex
	// outputs - twice size as inputs, each pair represents most probable pattern
	int sizeX, sizeY;
	BrainLocation connectors = sensorCortex -> getOutputsSurface();
	connectors.get2Dsizes( sizeX , sizeY );

	int inputAreaSize = sizeX * sizeY;
	int nRegions = 3;
	int nClasses = 10;
	int neuronCount = nRegions * inputAreaSize;
	int maxSequenceLength = 10;
	Object *libobj = lib -> createBeliefNetwork( sizeX , sizeY , nRegions , nClasses , neuronCount , maxSequenceLength );

	// create cortex
	SFNeoCortexAdapter *libcortex = new SFNeoCortexAdapter( lib , libobj , area , CortexIOSizeInfo( inputAreaSize , nClasses * 2 ) );
	return( libcortex );
}
