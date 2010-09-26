#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include <math.h>

#include "aiengine.h"
#include "aibrain.h"

class SFNeoCortex : public Cortex
{
public:
	Logger logger;
	static const int OUTPUT_NONE = -1;
	
	unsigned regionCount;
	unsigned areaSide;
	unsigned bottomRegionSide;

	FlatList<unsigned> regionSideCompression;
	FlatList<unsigned> sequenceLength;
	FlatList<unsigned> regionMemorySize;
	FlatList<double> regionForgetThreshold;
	FlatList<unsigned> regionLowUsageThreshold;

	// number of pixels overlapping between adjacent sub-regions
	unsigned overlapSubRegions;

	double bestMatchPrecision; // 0.95
	unsigned predictionCount;
	bool deletionByPercentage;

public:
	SFNeoCortex( MindArea *area , unsigned bottomSide ) : Cortex( area , bottomSide * bottomSide , 1 ) {
		logger.attach( "NeoCortex" );
	};

public:
	void log( const char *s ) { logger.logDebug( s ); };
};

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
//		memory requirements seems high
//		sequence length is 1 in examples
//		one output
//		temporal pooler and spatial pooler are not delimited
//		there is offline learning
//
// interesting features:
//		subregions overlapping

#include "Source.h"
#include "Hippo.h"
#include "Sequence.h"
#include "SparseArray.h"
#include "SubRegion.h"
#include "Source.h"
#include "NeoRegion.h"
#include "Sense.h"
