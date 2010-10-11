#include "libbn_impl.h"
#include "neocortex_custom/XNeoCortex.h"

/*#########################################################################*/
/*#########################################################################*/

// class hierarchy
//		ContextSource (parent)
//		PatternSource (child)
//		Hippo - ContextSource
//		NeoRegion - ContextSource, PatternSource : LearnedSequence[max], SubRegion[sizeX,sizeY]
//		Sense - PatternSource
//		BitmapVision - Sense
//		SubRegion : belief matrix
//		Sequence : unsigned[SequenceLength (time) x InputCount (spatial)]
//		LearnedSequence - Sequence : frequency
//
// problems found:
//		fixed-length sequences
//		square region - to be addressed
//		memory requirements seems high
//		sequence length is 1 in examples
//		one output
//		temporal pooler and spatial pooler are not delimited
//		there is offline learning
//
// interesting features:
//		subregions overlapping

NeoCortexCustomLibBN::NeoCortexCustomLibBN()
:	AILibBNVariant( "NeoCortexCustom" )
{
}

NeoCortexCustomLibBN::~NeoCortexCustomLibBN()
{
}

// create neocortex with the same inputs as outputs of given cortex and 
// probability destribution across given number of labels
//		sourceSizeX, sourceSizeY: sensor size
Object *NeoCortexCustomLibBN::createBeliefNetwork( unsigned sourceSizeX , unsigned sourceSizeY , unsigned nHistory , 
	unsigned nHippoOutputX , unsigned nHippoOutputY , unsigned neuronCount )
{
	// calculate number of regions required to hold given number of spacial and temporal inputs
	// first region is pure spacial pooler with overlap and with initial compression factor (compression=4x4, overlap=compression/2, maxSequenceLength=1, memory=neuronCount/2)
	// next region is pure temporal pooler and implements all history coverage (compression=1, overlap=0, maxSequenceLength=nHistory, memory=neuronCount/4)
	// finally Hippo should scale spacial size to 1 (compression=2, maxSequenceLength=1, memory=neuronCount/4/(nRegions-2)) an provide final sequence distribution

	// create sense with own data array
	XOwnedSense *sense = new XOwnedSense( sourceSizeX , sourceSizeY );

	// create cortex
	unsigned regionPatchX = 4;
	unsigned regionPatchY = 4;
	unsigned hippoPatchX = sourceSizeX / regionPatchX;
	if( hippoPatchX * regionPatchX < sourceSizeX )
		hippoPatchX++;
	unsigned hippoPatchY = sourceSizeY / regionPatchY;
	if( hippoPatchY * regionPatchY < sourceSizeY )
		hippoPatchY++;
	XNeoCortex *neo = new XNeoCortex( sense , sourceSizeX , sourceSizeY , hippoPatchX , hippoPatchY , nHippoOutputX , nHippoOutputY , neuronCount / 4 );
	
	neo -> setBestMatchPrecision( 0.95 );
	neo -> setDeletionByPercentage( false );

	// regions
	neo -> addRegion( regionPatchX , regionPatchY , 2 , neuronCount / 2 , 0.05 , 2 , 1 ); 
	neo -> addRegion( 1 , 1 , 0 , neuronCount / 4 , 5 , 2 , nHistory );

	// compolete creation of regions
	neo -> createCortexNetwork();
	return( neo );
}

void NeoCortexCustomLibBN::deleteObject( Object *object )
{
	XNeoCortex *libobj = ( XNeoCortex * )object;
	delete libobj;
}

unsigned *NeoCortexCustomLibBN::getInputsBuffer( Object *object )
{
	XNeoCortex *libobj = ( XNeoCortex * )object;
	XOwnedSense *sense = ( XOwnedSense * )libobj -> getSense();
	TwoIndexArray<unsigned>& data = sense -> getData();
	return( data.getData() );
}

void NeoCortexCustomLibBN::feedForward( Object *object , unsigned learningRegion, bool feedbackStage )
{
	// objects
	XNeoCortex *libobj = ( XNeoCortex * )object;
	XSense *sense = libobj -> getSense();
	sense -> feedForward( learningRegion , feedbackStage );
}

/*#########################################################################*/
/*#########################################################################*/

AILibBNVariant *AILibBNImpl::createNeoCortexCustomLib() {
	return( new NeoCortexCustomLibBN() );
}
