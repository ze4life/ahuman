#include "body_impl.h"

class Sensors : public Object , public MindArea
{
	AIEngine& engine;
	RFC_HND threadSensesTracker;
	bool runSensesTracker;
	ClassList<Attractor> sensors;

// construction
public:
	Sensors()
	:	engine( AIEngine::getInstance() ) {

		// init variables
		threadSensesTracker = ( RFC_HND )NULL;
		runSensesTracker = true;
	};

	const char *getClass() { return( "Sensors" ); };

// MindArea events
public:
	virtual void onCreateArea() {
		createAttractors();
	};
	virtual void onLoadArea() {
		// for body areas create and load are the same
		onCreateArea();
	}
	virtual void onBrainStart() {
		startTracker();
	}
	virtual void onBrainStop() {
		runSensesTracker = false;
		if( threadSensesTracker != NULL ) {
			engine.waitThreadExited( threadSensesTracker );
			threadSensesTracker = ( RFC_HND )NULL;
		}
	};

private:
	void createAttractors() {
		addSensor( Attractor::createFileSysWalker( this ) );
	}

	void addSensor( Attractor *att ) {
		sensors.add( att );
	}

	void startTracker() {
		// start tracking thread
		threadSensesTracker = engine.runThread( "SensesTracker" , this , ( ObjectThreadFunction )&Sensors::onRunSensesTracker , NULL );
	}

	void onRunSensesTracker( void *p_arg ) {
		logger.attach( "SensesTracker" );

		// run until stop signal
		int sleepRemained = 0;
		while( runSensesTracker ) {
			pollIteration( sleepRemained );
		}
	}

	void pollIteration( int& sleepRemained ) {
		int timeNow = Timer::timeNow();

		// iterate sensors and find sleep time required
		int minMs = 0;
		for( int k = sensors.count() - 1; k >= 0; k-- ) {
			Attractor *att = sensors.get( k );

			// get poll status and time to next poll
			bool poll = att -> getPollState();
			int ms;
			if( poll )
				ms = att -> getPollInterval( timeNow );

			// run all in poll state
			if( poll && ms <= 0 )
				att -> runPoll();

			if( minMs == 0 || ( ms > 0 && ms < minMs ) )
				minMs = ms;
		}

		// check need sleep
		if( minMs == 0 )
			rfc_thr_sleep( 1 );
		else {
			// buffered sleep time
			sleepRemained += minMs;
			int sleepSeconds = sleepRemained / 1000;
			if( sleepSeconds > 0 ) {
				rfc_thr_sleep( sleepSeconds );
				sleepRemained %= 1000;
			}
		}
	}
};

MindArea *AIBodyImpl::createSensors()
{
	Sensors *area = new Sensors();
	return( area );
}
