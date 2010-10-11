#include "../brain_impl.h"
#include "ailibbn.h"

/*#########################################################################*/
/*#########################################################################*/

class NeoCortexCustomAdapter : public Cortex {
private:
	NeoCortexCustomLibBN *lib;
	Object *libobj;
	unsigned *libInputs;
	cortexvt *cortexInputs;
	int nInputs;

public:
NeoCortexCustomAdapter( MindArea *area , const CortexIOSizeInfo& io )
:	Cortex( "NeoCortexCustomAdapter" , area , io )
{
}

~NeoCortexCustomAdapter()
{
	if( lib != NULL )
		lib -> deleteObject( libobj );
}

void setObject( NeoCortexCustomLibBN *p_lib , Object *p_libobj )
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
	NeoCortexCustomLibBN *lib = libbn.getNeoCortexCustomLib();

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
	NeoCortexCustomAdapter *libcortex = new NeoCortexCustomAdapter( area , CortexIOSizeInfo( inputAreaSize , nClasses * 2 ) );
	// create library object
	Object *libobj = lib -> createBeliefNetwork( sizeX , sizeY , nRegions , nClasses , neuronCount , maxSequenceLength );
	// attach
	libcortex -> setObject( lib , libobj );
	return( libcortex );
}
