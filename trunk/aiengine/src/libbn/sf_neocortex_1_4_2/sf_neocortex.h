#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include <math.h>

#include "aiengine.h"
#include "aibrain.h"


class NeoRegion;
class Hippocampus;
class PatternSource;
class SFNeoCortex : public Cortex
{
private:
	/* Sides of the input layer of the cortex */
	unsigned sideV, sideH;
	/* Layers array in the cortex */
	NeoRegion** regions;
	Hippocampus* hippo;
	unsigned regionCount;
	unsigned sideCompression;
public:
	Logger logger;
	static const int OUTPUT_NONE = -1;
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
	SFNeoCortex( MindArea *area , unsigned bottomSideV, unsigned bottomSideH );
	virtual ~SFNeoCortex();
public:
	void log( const char *s ) { logger.logDebug( s ); };
	bool createCortexNetwork();
	void setSideV(int size);
	void setSideH(int size);
	int  getSideV(){ return sideV; }
	int  getSideH() { return sideH; }
	Hippocampus* getHippo(){ return hippo; }
	void setSideCompression(int comp);
	void setRegionCount(int count);
	void setSense(PatternSource* sense);
private:
	void validateInputs(void);
};

#include "Source.h"
#include "Hippo.h"
#include "Sequence.h"
#include "SparseArray.h"
#include "SubRegion.h"
#include "Source.h"
#include "NeoRegion.h"
#include "Sense.h"

