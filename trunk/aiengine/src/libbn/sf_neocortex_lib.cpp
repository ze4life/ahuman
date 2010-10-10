#include "libbn_impl.h"
#include "sf_neocortex_1_4_2/sf_neocortex.h"

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

SFNeoCortexLibBN::SFNeoCortexLibBN()
:	AILibBNVariant( "SFNeoCortex" )
{
}

SFNeoCortexLibBN::~SFNeoCortexLibBN()
{
}

// create neocortex with the same inputs as outputs of given cortex and 
// probability destribution across given number of labels
Object *SFNeoCortexLibBN::createBeliefNetwork( int sizeX , int sizeY , int nRegions , int nClasses , int neuronCount , int maxSequenceLength )
{
	// create hippo
	SFNeoCortex *neo = new SFNeoCortex( nRegions , sizeX , sizeY , nClasses );
	neo -> bestMatchPrecision = 0.95;
	neo -> overlapSubRegions = 0;
	neo -> regionCount = nRegions;

	// bottom
	int compressionX = ( int )( log( ( double )sizeX ) / log( ( double )2 ) );
	int compressionY = ( int )( log( ( double )sizeY ) / log( ( double )2 ) );
	double lSideX = ( double( sizeX - neo -> overlapSubRegions ) / double( compressionX - neo -> overlapSubRegions ) );
	neo -> bottomSizeX = ( unsigned )lSideX;
	double lSideY = ( double( sizeY - neo -> overlapSubRegions ) / double( compressionY - neo -> overlapSubRegions ) );
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
		neo -> maxSequenceLength.add( maxSequenceLength );
	}

	// create bitmap sense
	BitmapVision *sense = new BitmapVision( *neo , sizeX , sizeY );
	neo -> setSense( sense );

	// create regions - default sense
	neo -> createCortexNetwork();
	return( neo );
}

void SFNeoCortexLibBN::deleteObject( Object *object )
{
	SFNeoCortex *libobj = ( SFNeoCortex * )object;
	delete libobj;
}

unsigned *SFNeoCortexLibBN::getInputsBuffer( Object *object )
{
	SFNeoCortex *libobj = ( SFNeoCortex * )object;
	BitmapVision *sense = ( BitmapVision * )libobj -> getSense();
	TwoIndexArray<unsigned>& data = sense -> getBitmap();
	return( data.getData() );
}

void SFNeoCortexLibBN::feedForward( Object *object , unsigned learningRegion, bool feedbackStage )
{
	// objects
	SFNeoCortex *libobj = ( SFNeoCortex * )object;
	Sense *sense = libobj -> getSense();
	sense -> feedForward( learningRegion , feedbackStage );
}

/*#########################################################################*/
/*#########################################################################*/

AILibBNVariant *AILibBNImpl::createSFNeoCortexLib() {
	return( new SFNeoCortexLibBN() );
}
