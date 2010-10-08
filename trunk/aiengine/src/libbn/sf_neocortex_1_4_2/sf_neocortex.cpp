#include "sf_neocortex.h"
#include "..\libbn_impl.h"
#include "Hippo.h"

#include <math.h>

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


class SFNeoCortexLib : public AILibBNVariant {
public:
	SFNeoCortexLib() : AILibBNVariant( "SFNeoCortex" ) {
	};

	// create neocortex with the same inputs as outputs of given cortex and 
	// probability destribution across given number of labels
	virtual Cortex *createNeoCortex( MindArea *area , Cortex *inputs , int nOutputs ) {
		const BrainLocation& sourcePlace = inputs -> getLocation();
		BrainLocation outputsPlace = sourcePlace.getOutputLocation();

		// get sizes
		int sa , sb;
		outputsPlace.get2Dsizes( sa , sb );

		// create hippo
		SFNeoCortex *neo = new SFNeoCortex( area , sa , sb );
		return( neo );
	}


};

SFNeoCortex::SFNeoCortex( MindArea *area , unsigned bottomSideV, unsigned bottomSideH ) : Cortex( area , bottomSideV * bottomSideH , 1 ) {
	/* Update the local variables */
	sideV = bottomSideV;
	sideH = bottomSideH;
	/* Create a complete new cortex here depending upon the dimensions of the input*/
	logger.attach( "NeoCortex" );
}

void SFNeoCortex::validateInputs(){
	ASSERT(regionCount > 0);
	ASSERT(sequenceLength.count() == regionCount);
	ASSERT(regionSideCompression.count() == regionCount);
	ASSERT(sideH > 0);
	ASSERT(sideV > 0);
}

bool SFNeoCortex::createCortexNetwork(){
	/* Validate that we have everything before creating network */
	validateInputs();
	int sideVer = sideV;
	int sideHor = sideH;
	regions = new NeoRegion* [regionCount];
	for( int k = 0; k < regionCount; k++ )	{
		if(k != 0){
			sideVer /= regionSideCompression[k];
			sideHor /= regionSideCompression[k];
		}
		regions[k] = new NeoRegion(*this,sideHor, sideVer, sequenceLength[k], regionSideCompression[k], k);
		 if(k > 0){
			 regions[k]->setChild(regions[k - 1]);
		 }
	}
	for(int i = 0; i < regionCount-1; i++){
		/* Set parents of every region */
		regions[i]->setParent(regions[i + 1]);
	}
	int maxSide = (sideHor > sideVer) ? sideHor : sideVer;
	hippo = new Hippocampus(*this, maxSide);
	regions[regionCount - 1]->setParent(hippo);
	return true;
}

void SFNeoCortex::setSense(PatternSource* sense){
	regions[0] -> setChild(sense);
	sense->setParent( regions[0] );	
}

void SFNeoCortex::setSideH(int size){
	sideH = size;
}
void SFNeoCortex::setSideV(int size){
	sideV = size;
}
void SFNeoCortex::setSideCompression(int size){
	sideCompression = size;
}
void SFNeoCortex::setRegionCount(int count){
	regionCount = count;
}
SFNeoCortex::~SFNeoCortex() {
	logger.logDebug( "Exiting NeoCortex..." );
}
/*#########################################################################*/
/*#########################################################################*/
AILibBNVariant *AILibBNImpl::createSFNeoCortex() {
	return( new SFNeoCortexLib() );
}
