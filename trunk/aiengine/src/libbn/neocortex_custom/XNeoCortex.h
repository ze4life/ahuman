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
	
	// global settings
	double bestMatchPrecision; // 0.95
	bool deletionByPercentage;

private:
	// start info
	unsigned sensorSizeX;
	unsigned sensorSizeY;
	unsigned hippoPatchSizeX;
	unsigned hippoPatchSizeY;
	unsigned hippoOutputSizeX;
	unsigned hippoOutputSizeY;
	unsigned hippoMemorySize;

	// classes
private:
	XHippocampus *hippo;
	XSense *sensor;
	ClassList<XNeoRegion> regions;

public:
	// cortex inputs are sensor data rectangle
	// cortex outputs are set of class/probability pairs - reflecting probability distribution used
	XNeoCortex( XSense *sense , unsigned sensorSizeX , unsigned sensorSizeY , unsigned hippoPatchSizeX , unsigned hippoPatchSizeY , 
		unsigned hippoOutputSizeX , unsigned hippoOutputSizeY , unsigned hippoMemorySize );
	virtual ~XNeoCortex();
	virtual const char *getClass() { return( "XNeoCortex" ); };

public:
	unsigned getRegionCount() { return( regions.count() ); };
	XNeoRegion *getRegion( int index ) { return( regions.get( index ) ); };

	void setBestMatchPrecision( double p_v ) { bestMatchPrecision = p_v; };
	void setDeletionByPercentage( bool p_v ) { deletionByPercentage = p_v; };

	XNeoRegion *addRegion( unsigned sizeX , unsigned sizeY , unsigned overlapSubRegions , unsigned memorySize , 
		double forgetThreshold , unsigned lowUsageThreshold , unsigned maxSequenceLength );
	void createCortexNetwork();

public:
	XHippocampus* getHippo() { return hippo; }
	XSense *getSense() { return( sensor ); };

	void showRegionMemories();

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

