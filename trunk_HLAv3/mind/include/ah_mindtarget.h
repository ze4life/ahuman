#ifndef	INCLUDE_AH_MINDTARGET_H
#define INCLUDE_AH_MINDTARGET_H

/*#########################################################################*/
/*#########################################################################*/

#include <platform/include/ah_services.h>
#include "ah_mindarea.h"
#include "ah_mindregion.h"

class MindTarget;
class MindSensorSet;
class MindEffectorSet;
class MindSensor;
class MindEffector;

/*#########################################################################*/
/*#########################################################################*/

class MindSensorSetTracker;
class MindArea;

class MindTarget : public Service {
public:
	MindTarget();

	virtual void configureTarget( Xml config ) = 0;
	virtual void createTarget() = 0;
	virtual void initSensorsTarget( MindArea *sensorArea ) = 0;
	virtual void initEffectorsTarget( MindArea *effectorArea ) = 0;
	virtual void runTarget() = 0;
	virtual void stopTarget() = 0;
	virtual void exitTarget() = 0;
	virtual void destroyTarget() = 0;

private:
	// target service virtuals
	virtual const char *getServiceName() { return( "MindTarget" ); };
	virtual void configureService( Xml config );
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void stopService();
	virtual void exitService();
	virtual void destroyService();

public:
	void configureSensors( Xml xml );
	void addSensor( MindSensor *sensor );
	void addEffector( MindEffector *effector );
	void startSensors();
	void stopSensors();
	MindSensor *getSensor( String name );

private:
	Xml configSensors;
	MindArea *sensorArea;
	MindSensorSet *sensors;
	MindSensorSet *sensorsOffline;
	MindSensorSetTracker *sensorTracker;

	MindEffectorSet *effectors;
	MindArea *effectorArea;
};

/*#########################################################################*/
/*#########################################################################*/

class MindSensorSet : public MindArea {
public:
	void addSensor( MindSensor *sensor );
	void startSensorSet();
	void stopSensorSet();
	void pollSensorSet( int timeNowMs , int *minPollNextMs );
	MindSensor *getSensor( String name );

private:
	ClassList<MindSensor> list;
	MapStringToClass<MindSensor> map;
};

/*#########################################################################*/
/*#########################################################################*/

class MindEffectorSet : public MindArea {
public:
	void addSensor( MindEffectorSet *sensor );

private:
	ClassList<MindEffectorSet> list;
	MapStringToClass<MindEffectorSet> map;
};

/*#########################################################################*/
/*#########################################################################*/

class MindSensor : public MindRegion {
public:
	MindSensor();

	// Object
	virtual const char *getClass() = 0;

	// MindSensor
	virtual void startSensor() = 0;
	virtual void stopSensor() = 0;
	virtual void processSensorControl() = 0;
	virtual bool executeSensorControl() = 0;
	virtual void produceSensorData() = 0;
	virtual void pollSensor() = 0;

private:
	// MindRegion
	virtual void exitRegion();
	virtual void destroyRegion();

public:
	// memory allocation
	neurovt *createSensoryDataMemoryNVT( int sizeNVT );
	neurovt *createSensoryControlMemoryNVT( int sizeNVT );

	// sensor operations
	void processSensorData();

	// poll handling
	void setPollState( bool state );
	bool getPollState();
	int getPollIntervalMs( int timeNowMs );

private:
	// auto-polling
	bool pollState;
	int pollNextMs;
	int pollIntervalMs;

	// memory
	neurovt *memorySensoryData;
	neurovt *memorySensoryControl;
};

/*#########################################################################*/
/*#########################################################################*/

class MindEffector : public MindRegion {
public:
	virtual const char *getClass() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDTARGET_H
