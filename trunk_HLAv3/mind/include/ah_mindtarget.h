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
	Xml configSensors;
	SensorArea *sensorArea;
	MindSensorSet *sensors;
	MindSensorSet *sensorsOffline;
	MindSensorSetTracker *sensorTracker;

	Xml configEffectors;
	EffectorArea *effectorArea;
	MindEffectorSet *effectors;
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
	ClassList<MindSensor> list;
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
	ClassList<MindEffector> list;
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
	virtual bool executeSensorControl() = 0;
	virtual void produceSensorData() = 0;
	virtual void pollSensor() = 0;

private:
	// MindRegion
	virtual void createRegion();
	virtual void exitRegion();
	virtual void destroyRegion();

	// link creation
	virtual void createNeuroLinks( MindRegionLink *link , MindRegion *dst );
	virtual void createNeuroLinksFromCortexRegion( MindRegionLink *link , CortexRegion *src );
	virtual void createNeuroLinksFromNucleiRegion( MindRegionLink *link , NucleiRegion *src );
	virtual void createNeuroLinksFromNerveRegion( MindRegionLink *link , NerveRegion *src );
	virtual void createNeuroLinksFromSensorRegion( MindRegionLink *link , MindSensor *src );

	// access to pools
	virtual NeuroPool *getFeedForwardInputPool() { return( NULL ); };

public:
	// memory allocation
	NeuroVector *createSensoryData( int sizeX , int sizeY );
	NeuroVector *createSensoryControlState( int sizeX , int sizeY );
	NeuroVector *getSensoryData();

	// sensor operations
	void setFeedForwardLink( NeuroLink *link );
	// capture data and and send via NeuroLink
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
	NeuroVector *memorySensoryData;
	NeuroVector *memorySensoryControlState;

	// links
	NeuroLink *linkFeedForward;
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
	virtual void initMasterLinkToArea( MindAreaLink *link , String slaveAreaId );
	virtual void initSlaveLinkToArea( MindAreaLink *link , String masterAreaId );
	virtual void wakeupArea( MindActiveMemory *activeMemory );
	virtual void asleepArea();

private:
	void initLinksToPerceptionArea( MindAreaLink *link );
	void createPerceptionNeuroLinks( MindRegionLink *regionLink , MindRegion *srcRegion , MindRegion *dstRegion , MindSensor *sensor );

private:
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
	virtual void initMasterLinkToArea( MindAreaLink *link , String slaveAreaId );
	virtual void initSlaveLinkToArea( MindAreaLink *link , String masterAreaId );
	virtual void wakeupArea( MindActiveMemory *activeMemory );
	virtual void asleepArea();

private:
	MindTarget *target;
};

// #############################################################################
// #############################################################################

#endif // INCLUDE_AH_MINDTARGET_H
