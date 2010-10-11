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
Object *NeoCortexCustomLibBN::createBeliefNetwork( unsigned sourceSizeX , unsigned sourceSizeY , unsigned nHistory , unsigned nClasses , unsigned neuronCount , unsigned maxRegionSequenceLength )
{
	// create hippo
	int nRegions = 3;
	XNeoCortex *neo = new XNeoCortex( nRegions , sourceSizeY , sourceSizeY , nClasses );
	neo -> bestMatchPrecision = 0.95;
	neo -> overlapSubRegions = 0;
	neo -> regionCount = nRegions;

	// bottom
	int compressionX = ( int )( log( ( double )sourceSizeX ) / log( ( double )2 ) );
	int compressionY = ( int )( log( ( double )sourceSizeY ) / log( ( double )2 ) );
	double lSideX = ( double( sourceSizeX - neo -> overlapSubRegions ) / double( compressionX - neo -> overlapSubRegions ) );
	neo -> bottomSizeX = ( unsigned )lSideX;
	double lSideY = ( double( sourceSizeY - neo -> overlapSubRegions ) / double( compressionY - neo -> overlapSubRegions ) );
	neo -> bottomSizeY = ( unsigned )lSideY;

	// delete a percentage of memories/delete memories below threshold
	neo -> deletionByPercentage = false;
	neo -> predictionCount = nClasses;

	// derived: whole number of overlapping subregions that fit into NeoParameters::ImageSide
	// image side covered by hierarchy. May not cover whole bitmap due to overlap
	for( int k = 0; k < nRegions; k++ ) {
		double threshold = ( k == 0 )? 0.05 : 5;
		neo -> regionForgetThreshold.add( threshold );
		neo -> regionMemorySize.add( neuronCount * 10 / nRegions );
		neo -> regionLowUsageThreshold.add( 2 );
		neo -> regionSideXCompression.add( compressionX );
		neo -> regionSideYCompression.add( compressionY );
		neo -> maxSequenceLength.add( maxRegionSequenceLength );
	}

	// create bitmap sense
	XBitmapVision *sense = new XBitmapVision( *neo , sourceSizeX , sourceSizeY );
	neo -> setSense( sense );

	// create regions - default sense
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
	XBitmapVision *sense = ( XBitmapVision * )libobj -> getSense();
	TwoIndexArray<unsigned>& data = sense -> getBitmap();
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
