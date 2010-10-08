#include "aibrain.h"
#include "ailibbn.h"
#include "..\libbn\sf_neocortex_1_4_2\sf_neocortex.h"

#include "test_impl.h"

/*#########################################################################*/
/*#########################################################################*/

class TestNeoCortex : public TestUnit {
private:
	bool cInitForInferenceDone;

// construction
public:
	TestNeoCortex() : TestUnit( "TestNeoCortex" ) {};

	virtual void init() {
		ADD_METHOD( TestNeoCortex::testCreateSimple );
	}
	
// tests
public:

	void testCreateSimple( XmlCall& call ) {
		// use libbn sf_neocortex library directly without unified interface
		// set parameters
		SFNeoCortex ct( AIBrain::getNeoCortexArea() , 32, 32 );
		ct.bestMatchPrecision = 0.95;
		ct.overlapSubRegions = 0;
		// Delete a Percentage of memories/Delete memories below threshold
		ct.deletionByPercentage = false;
		ct.predictionCount = 10;
		//derived: whole number of overlapping subregions that fit into NeoParameters::ImageSide
		//image side covered by hierarchy. May not cover whole bitmap due to overlap
		ct.setRegionCount(3);
		ct.regionForgetThreshold.add( 0.07 ); ct.regionForgetThreshold.add( 3.5 ); ct.regionForgetThreshold.add( 0.25 );
		ct.regionMemorySize.add( 3 , 30000 );
		ct.regionLowUsageThreshold.add( 3 , 2 );
		ct.regionSideCompression.add( 4 ); ct.regionSideCompression.add( 2 ); ct.regionSideCompression.add( 2 );
		ct.sequenceLength.add( 3 , 1 );
		// derived: whole number of overlapping subregions that fit into ImageSide
		//double lSide = ( double(ct.areaSide - ct.overlapSubRegions ) / double(ct.regionSideCompression[0] - ct.overlapSubRegions ) );
		//ct.bottomRegionSide = ( unsigned )lSide;

		// create cortex
		BitmapVision eye( ct );
		ct.createCortexNetwork();
		ct.setSense(&eye);
	}
};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createNeoCortexTest() {
	return( new TestNeoCortex );
}
