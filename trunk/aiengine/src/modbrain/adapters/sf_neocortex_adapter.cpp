#include "../brain_impl.h"
#include "ailibbn.h"

/*#########################################################################*/
/*#########################################################################*/

class SFNeoCortexAdapter : public Cortex {
private:
	SFNeoCortexLibBN *lib;
	Object *libobj;
	unsigned *libInputs;
	cortexvt *cortexInputs;
	int nInputs;

public:
SFNeoCortexAdapter( MindArea *area , const CortexIOSizeInfo& io )
:	Cortex( "SFNeoCortex" , area , io )
{
}

~SFNeoCortexAdapter()
{
	if( lib != NULL )
		lib -> deleteObject( libobj );
}

void setObject( SFNeoCortexLibBN *p_lib , Object *p_libobj )
{
	lib = p_lib;
	libobj = p_libobj;

	// convert inputs
	libInputs = lib -> getInputsBuffer( libobj );
	cortexInputs = Cortex::getInputs();
	nInputs = Cortex::getNInputs();
}

// handlers
virtual void onCortexRun()
{
	// convert data - [-1,1] -> [0,255]
	for( int k = 0; k < nInputs; k++ )
		libInputs[k] = ( unsigned )( ( 1 + cortexInputs[k] ) * 255 / 2 );

	lib -> feedForward( libobj , 0 , false );
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
	connectors.getSurfaceDimensions( sizeX , sizeY );

	int inputAreaSize = sizeX * sizeY;
	int nRegions = 3;
	int nClasses = 10;
	int neuronCount = nRegions * inputAreaSize;
	int maxSequenceLength = 10;

	// create cortex
	SFNeoCortexAdapter *libcortex = new SFNeoCortexAdapter( area , CortexIOSizeInfo( inputAreaSize , nClasses * 2 ) );
	// create library object
	Object *libobj = lib -> createBeliefNetwork( sizeX , sizeY , nRegions , nClasses , neuronCount , maxSequenceLength );
	// attach
	libcortex -> setObject( lib , libobj );
	return( libcortex );
}
