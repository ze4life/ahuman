#include "sf_neocortex.h"
#include "..\libbn_impl.h"

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
		SFNeoCortex *neo = new SFNeoCortex( area , sa * sb );
		return( neo );
	}
};

/*#########################################################################*/
/*#########################################################################*/

AILibBNVariant *AILibBNImpl::createSFNeoCortex() {
	return( new SFNeoCortexLib() );
}
