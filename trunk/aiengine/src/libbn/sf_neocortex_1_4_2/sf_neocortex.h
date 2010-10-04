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
	SFNeoCortex( MindArea *area , unsigned bottomSide );
	virtual ~SFNeoCortex();

public:
	void log( const char *s ) { logger.logDebug( s ); };
};

#include "Source.h"
#include "Hippo.h"
#include "Sequence.h"
#include "SparseArray.h"
#include "SubRegion.h"
#include "Source.h"
#include "NeoRegion.h"
#include "Sense.h"
