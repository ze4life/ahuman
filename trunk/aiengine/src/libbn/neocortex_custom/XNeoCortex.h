#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <math.h>

#include "aiengine.h"

/*#########################################################################*/
/*#########################################################################*/

class XNeoCortex;

class XPatternSource;
class XContextSource;
class XHippocampus;
class XSequence;
class XLearnedSequence;
class XAccessKey;
class XSubRegion;
class XNeoRegion;
class XSense;
class XDirectInputSense;
class XBitmapVision;

/*#########################################################################*/
/*#########################################################################*/

class XNeoCortex : public Object
{
public:
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
	XHippocampus *hippo;
	XSense *sensor;
	ClassList<XNeoRegion> regions;

public:
	// cortex inputs are sensor data rectangle
	// cortex outputs are set of class/probability pairs - reflecting probability distribution used
	XNeoCortex( unsigned nRegions , unsigned sourceSizeX , unsigned sourceSizeY , unsigned nClasses );
	virtual ~XNeoCortex();
	virtual const char *getClass() { return( "XNeoCortex" ); };

public:
	void setOverlapSubRegions( unsigned p_v );
	void setBestMatchPrecision( double p_v ) { bestMatchPrecision = p_v; };
	void setDeletionByPercentage( bool p_v ) { deletionByPercentage = p_v; };

	void createCortexNetwork();

private:
	XNeoRegion *addRegion( unsigned sideCompression , unsigned memorySize , double forgetThreshold , unsigned lowUsageThreshold , unsigned sequenceLength );

public:
	void log( const char *s ) { logger.logDebug( s ); };
	XHippocampus* getHippo() { return hippo; }
	void setSideCompression( int comp );
	void setSense( XSense *sense ) { sensor = sense; };
	XSense *getSense() { return( sensor ); };

private:
	void validateInputs(void);
};

/*#########################################################################*/
/*#########################################################################*/

using namespace std;

#include "XSource.h"
#include "XHippo.h"
#include "XSequence.h"
#include "XSparseArray.h"
#include "XSubRegion.h"
#include "XNeoRegion.h"
#include "XSense.h"

