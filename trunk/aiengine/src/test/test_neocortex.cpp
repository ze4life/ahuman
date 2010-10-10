#include "aibrain.h"
#include "ailibbn.h"
#include "../libbn/sf_neocortex_1_4_2/sf_neocortex.h"

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
		SFNeoCortex ct( 3 , 32 , 32 , 10 );
		ct.bestMatchPrecision = 0.95;
		ct.overlapSubRegions = 0;
		// Delete a Percentage of memories/Delete memories below threshold
		ct.deletionByPercentage = false;
		//derived: whole number of overlapping subregions that fit into NeoParameters::ImageSide
		//image side covered by hierarchy. May not cover whole bitmap due to overlap
		ct.regionForgetThreshold.add( 0.07 ); ct.regionForgetThreshold.add( 3.5 ); ct.regionForgetThreshold.add( 0.25 );
		ct.regionMemorySize.add( 3 , 30000 );
		ct.regionLowUsageThreshold.add( 3 , 2 );
		ct.regionSideXCompression.add( 4 ); ct.regionSideXCompression.add( 2 ); ct.regionSideXCompression.add( 2 );
		ct.regionSideYCompression.add( 4 ); ct.regionSideYCompression.add( 2 ); ct.regionSideYCompression.add( 2 );
		ct.maxSequenceLength.add( 3 , 1 );
		// derived: whole number of overlapping subregions that fit into ImageSide
		//double lSide = ( double(ct.areaSide - ct.overlapSubRegions ) / double(ct.regionSideCompression[0] - ct.overlapSubRegions ) );
		//ct.bottomRegionSide = ( unsigned )lSide;

		BitmapVision *eye = new BitmapVision( ct , 40 , 40 );
		ct.setSense( eye );

		// create cortex
		ct.createCortexNetwork();

		// test inputs
		TwoIndexArray<unsigned>& arr = eye -> getBitmap();
		arr.setAllValues(2);
		Hippocampus* hippo = ct.getHippo();
		hippo->setTextOutput("test"); //add name to be learned to Mem

		eye -> feedForward(0, false); //cascading through 
		hippo->displayAllMemories();
		hippo->displayResults(true, false);
	}
};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createNeoCortexTest() {
	return( new TestNeoCortex );
}
