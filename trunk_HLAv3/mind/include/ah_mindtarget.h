#ifndef	INCLUDE_AH_MINDTARGET_H
#define INCLUDE_AH_MINDTARGET_H

/*#########################################################################*/
/*#########################################################################*/

#include <platform/include/ah_services.h>
#include "ah_mindarea.h"
#include "ah_mindregion.h"
#include "ah_mindmatter.h"

class MindTarget;
class MindSensorSet;
class MindEffectorSet;
class MindSensor;
class MindEffector;
class SensorArea;
class EffectorArea;

/*#########################################################################*/
/*#########################################################################*/

class MindSensorSetTracker;
class MindArea;
class NeuroVector;

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

private:
	// target areas
	SensorArea *createSensorArea();
	EffectorArea *createEffectorArea();

public:
	void configureSensors( Xml xml );
	void addSensor( MindSensor *sensor );
	void startSensors();
	void stopSensors();
	MindSensorSet *getSensorSet();
	MindSensor *getSensor( String name );

	void configureEffectors( Xml xml );
	void addEffector( MindEffector *effector );

private:
// utility
	Xml configSensors;
	Xml configEffectors;

// own data
	MindSensorSet *sensors;
	MindEffectorSet *effectors;
	SensorArea *sensorArea;
	EffectorArea *effectorArea;

// references
	MindSensorSet *sensorsOffline;
	MindSensorSetTracker *sensorTracker;
};

/*#########################################################################*/
/*#########################################################################*/

class MindSensorSet : public Object {
public:
	MindSensorSet();
	virtual const char *getClass() { return( "MindSensorSet" ); };

public:
	int getCount();
	MindSensor *getSetItem( int k );
	void addSetItem( MindSensor *sensor );

	void createSensorSet( MindArea *area );
	void startSensorSet();
	void stopSensorSet();
	void pollSensorSet( int timeNowMs , int *minPollNextMs );
	MindSensor *getSensor( String name );

private:
// own data
	ClassList<MindSensor> list;

// references
	MapStringToClass<MindSensor> map;
};

/*#########################################################################*/
/*#########################################################################*/

class MindEffectorSet : public Object {
public:
	MindEffectorSet();
	virtual const char *getClass() { return( "MindEffectorSet" ); };

public:
	void addEffector( MindEffector *effector );

private:
// own data
	ClassList<MindEffector> list;

// references
	MapStringToClass<MindEffector> map;
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
	virtual void produceSensorData() = 0;
	virtual void pollSensor() = 0;

private:
	// MindRegion
	virtual void createRegion();
	virtual void exitRegion();
	virtual void destroyRegion();

	// NeuroLink support
	virtual NeuroLinkSource *getNeuroLinkSource( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );
	virtual NeuroLinkTarget *getNeuroLinkTarget( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );

public:
	// memory allocation
	NeuroVector *createSensoryData( int sizeX , int sizeY );
	NeuroVector *createSensoryControlState( int sizeX , int sizeY );
	NeuroVector *createControlFeedbackData( int sizeX , int sizeY );
	NeuroVector *getSensoryData();

	// capture data and and send via NeuroLink
	void processSensorData();
	void applySensorControl( NeuroLink *link , NeuroVector *srcData );

	// poll handling
	void setPollState( bool state );
	bool getPollState();
	int getPollIntervalMs( int timeNowMs );

private:
// utility
	// auto-polling
	bool pollState;
	int pollNextMs;
	int pollIntervalMs;

// own data
	// memory
	NeuroVector *memorySensoryData;
	NeuroVector *memorySensoryControlState;
	NeuroVector *memorySensoryControlFeedback;
	NeuroLinkSource sourceSensoryData;
	NeuroLinkSource sourceSensoryControlFeedback;
	NeuroLinkTarget targetSensoryControl;
};

/*#########################################################################*/
/*#########################################################################*/

class MindEffector : public MindRegion {
public:
	virtual const char *getClass() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class MindRegion;
class MindRegionLink;
class MindAreaNet;

class SensorArea : public MindArea {
public:
	SensorArea();
	virtual ~SensorArea();
	virtual const char *getClass() { return( "SensorArea" ); };

public:
	// own functions
	void initSensorArea();
	MindTarget *getTarget();

	// MindArea lifecycle
	virtual void initRegionsInArea( MindTarget *target );
	virtual void wakeupArea( MindActiveMemory *activeMemory );
	virtual void suspendArea();

private:
	void createSensoryNetwork( MindSensor *sensor );

private:
// references
	MindTarget *target;
};

/*#########################################################################*/
/*#########################################################################*/

class EffectorArea : public MindArea {
public:
	EffectorArea();
	virtual ~EffectorArea();
	virtual const char *getClass() { return( "EffectorArea" ); };

public:
	// own functions
	void createEffectorArea( MindTarget *target );
	void initEffectorArea();
	MindTarget *getTarget();

	// mind area lifecycle
	virtual void initRegionsInArea( MindTarget *target );
	virtual void wakeupArea( MindActiveMemory *activeMemory );
	virtual void suspendArea();

private:
// references
	MindTarget *target;
};

// #############################################################################
// #############################################################################

#endif // INCLUDE_AH_MINDTARGET_H
