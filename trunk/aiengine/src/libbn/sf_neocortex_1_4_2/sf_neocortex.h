#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include <math.h>

#include "aiengine.h"

/*#########################################################################*/
/*#########################################################################*/

class NeoRegion;
class Sense;
class Hippocampus;
class PatternSource;

class SFNeoCortex : public Object
{
public:
	Logger logger;
	static const int OUTPUT_NONE = -1;
	
	// start info
	unsigned sensorAreaSideX;
	unsigned sensorAreaSideY;
	unsigned predictionCount;

	// number of items overlapping between adjacent sub-regions
	unsigned overlapSubRegions;
	double bestMatchPrecision; // 0.95
	bool deletionByPercentage;

	// derived info
	unsigned regionCount;
	unsigned bottomSizeX;
	unsigned bottomSizeY;

	// region parameters
	FlatList<unsigned> regionSideXCompression;
	FlatList<unsigned> regionSideYCompression;
	FlatList<unsigned> regionMemorySize;
	FlatList<double> regionForgetThreshold;
	FlatList<unsigned> regionLowUsageThreshold;
	FlatList<unsigned> maxSequenceLength;

	// classes
private:
	Hippocampus *hippo;
	Sense *sensor;
	ClassList<NeoRegion> regions;

public:
	// cortex inputs are sensor data rectangle
	// cortex outputs are set of class/probability pairs - reflecting probability distribution used
	SFNeoCortex( unsigned nRegions , unsigned sourceSizeX , unsigned sourceSizeY , unsigned nClasses ) {
		sensorAreaSideX = sourceSizeX;
		sensorAreaSideY = sourceSizeY;
		predictionCount = nClasses;

		overlapSubRegions = 0;
		bestMatchPrecision = 0;
		deletionByPercentage = false;

		regionCount = nRegions;
		bottomSizeX = 0;
		bottomSizeY = 0;

		hippo = NULL;
		sensor = NULL;

		logger.attach( "NeoCortex" );
	};
	virtual ~SFNeoCortex();
	virtual const char *getClass() { return( "SFNeoCortex" ); };

public:
	void setOverlapSubRegions( unsigned p_v );
	void setBestMatchPrecision( double p_v ) { bestMatchPrecision = p_v; };
	void setDeletionByPercentage( bool p_v ) { deletionByPercentage = p_v; };

	void createCortexNetwork();

private:
	NeoRegion *addRegion( unsigned sideCompression , unsigned memorySize , double forgetThreshold , unsigned lowUsageThreshold , unsigned sequenceLength );

public:
	void log( const char *s ) { logger.logDebug( s ); };
	Hippocampus* getHippo() { return hippo; }
	void setSideCompression( int comp );
	void setSense( Sense *sense ) { sensor = sense; };
	Sense *getSense() { return( sensor ); };

private:
	void validateInputs(void);
};

/*#########################################################################*/
/*#########################################################################*/

#include "Source.h"
#include "Hippo.h"
#include "Sequence.h"
#include "SparseArray.h"
#include "SubRegion.h"
#include "Source.h"
#include "NeoRegion.h"
#include "Sense.h"

