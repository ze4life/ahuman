#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include <math.h>

#include "aiengine.h"

class SFNeoCortex
{
public:
	static const int OutputNone = 0;
	
	double BestMatchPrecision; // 0.95
	unsigned PredictionCount;
	int *RegionLevelMemorySize;
	int *RegionLevelForgetThreshold;
	int *RegionLowUsageThreshold;
	bool DeletionByPercentage;
};

#include "Source.h"
#include "Hippo.h"
#include "Sequence.h"
#include "SparseArray.h"
#include "SubRegion.h"
#include "Source.h"
#include "NeoRegion.h"
#include "Sense.h"
