#include "body_impl.h"

class Sensors : public Object , public MindArea
{
	AIEngine& engine;
	RFC_HND threadSensesTracker;
	bool runSensesTracker;

// construction
public:
	Sensors()
	:	engine( AIEngine::getInstance() ) {

		// init variables
		threadSensesTracker = ( RFC_HND )NULL;
		runSensesTracker = true;
	};

	void createAttractors() {
		Attractor::createFileSysWalker( this );
	}

	const char *getClass() { return( "Sensors" ); };

// MindArea events
public:
	virtual void onCreateArea() {
		createAttractors();
		startTracker();
	};
	virtual void onLoadArea() {
		// for body areas create and load are the same
		onCreateArea();
	}
	virtual void onBrainStop() {
		runSensesTracker = false;
		if( threadSensesTracker != NULL ) {
			engine.waitThreadExited( threadSensesTracker );
			threadSensesTracker = ( RFC_HND )NULL;
		}
	};

private:
	void startTracker() {
		// start tracking thread
		threadSensesTracker = engine.runThread( "SensesTracker" , this , ( ObjectThreadFunction )&Sensors::onRunSensesTracker , NULL );
	}

	void onRunSensesTracker( void *p_arg ) {
		// run until stop signal
		while( runSensesTracker ) {
			pollIteration();
		}
	}

	void pollIteration() {
		// iterate sensors and find sleep time required
		ClassList<Cortex>& list = MindArea::getCortexList();
		for( int k = list.count() - 1; k >= 0; k-- ) {
			Cortex *attractor = list.get( k );
		}
	}
};

MindArea *AIBodyImpl::createSensors()
{
	Sensors *area = new Sensors();
	return( area );
}
