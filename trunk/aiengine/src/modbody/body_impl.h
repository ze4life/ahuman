#ifndef	INCLUDE_AIBODY_IMPL_H
#define INCLUDE_AIBODY_IMPL_H

#include <aiengine.h>
#include <aibrain.h>
#include <aisvcdb.h>
#include <aisvcio.h>

#include <aibody.h>

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIBodyImpl : public AIBody , public Service
{
	// service
	virtual void createService( Xml config );
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Body" ); };

// external interface
public:
	AIBodyImpl();
	static AIBodyImpl *getInstance();

private:
	static MindArea *createSensors();
	static MindArea *createEffectors();
	static MindArea *createBiology();
	static MindArea *createPhysiology();

// internals
private:
	AIEngine& engine;
};

// #############################################################################
// #############################################################################

// any body element
// each generally has two direction - input and output cortexes
// internal cortex implementation is fully hard-coded
// sensors have actions controlling their focus and other metrics controlling data capture
// effectors have senses with direct feedback from environment to action
// does not have state persisted while AI is not running
// created on AI start
class Sensor : public Cortex
{
	// every sensor should implement:
	//		control state: capture area
	//		control state: capture resolution
	//		deliver captured properties from external world and transfer to sensordata IO channel according to control state
	//		deriver exposed properties from control state and deliver them to external world
	String name;

	// auto-polling
	bool pollState;
	int pollNextMs;
	int pollIntervalMs;

	// dimensions (sensor third size is 2 always)
	unsigned dim1;
	unsigned dim2;

// construction
public:
	Sensor( String p_name , MindArea *area , const CortexIOSizeInfo& ioSizeInfo )
	:	Cortex( "hardcoded" , area , ioSizeInfo ) {
		name = p_name;
		Cortex::setId( name );
		pollState = false;
		pollNextMs = 0;
		pollIntervalMs = 0;
	};
	virtual ~Sensor() {};

	// sensors
	static Sensor *createFileSysWalker( MindArea *area );
	static Sensor *createEye( MindArea *area );
	// cortex overridables
	virtual void onCortexRun() {
		// inpus were updated
		processSensorControl();
	};

	// sensor overridables
	virtual void startSensor() = 0;
	virtual void stopSensor() = 0;
	virtual void processSensorControl() = 0;
	virtual bool executeSensorControl() = 0;
	virtual void produceSensorData() = 0;

// operations
public:
	String getName() { return( name ); };

	// poll setup
	void setPollState( bool state ) { pollState = state; };
	void setPollInterval( int intervalMs ) {
		pollIntervalMs = intervalMs;
	};

	// poll state
	bool getPollState() { return( pollState ); };
	int getPollInterval( int timeNowMs ) {
		return( pollNextMs - timeNowMs );
	};

	// do poll iteration
	void runPoll() {
		ASSERTMSG( pollState , "Unexpected" );

		produceSensorData();
		pollNextMs = Timer::timeNow() + pollIntervalMs;
	};
};

class Sensors : public Object , public MindArea
{
	AIEngine& engine;
	RFC_HND threadSensesTracker;
	bool runSensesTracker;
	MapStringToClass<Sensor> sensors;
	MapStringToClass<Sensor> sensorsOffline;
	BrainLocation coverLocation;

// construction
public:
	Sensors();
	const char *getClass() { return( "Sensors" ); };
	static Sensors *getSensors();

	Sensor *getSensor( String name );

// MindArea events
public:
	virtual void onCreateArea();
	virtual void onLoadArea();
	virtual void onBrainStart();
	virtual void onBrainStop();

private:
	void createSensors();
	void addSensor( Xml configSensors , Sensor *att );

	void startTracker();
	void onRunSensesTracker( void *p_arg );
	void pollIteration( int& sleepRemained );
};

#endif	// INCLUDE_AIBODY_IMPL_H
