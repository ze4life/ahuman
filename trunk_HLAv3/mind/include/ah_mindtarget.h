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

class MindTarget : public Service {
public:
	// targer service virtuals
	virtual const char *getServiceName() = 0;
	virtual void configureService( Xml config ) = 0;
	virtual void createService() = 0;
	virtual void initService() = 0;
	virtual void runService() = 0;
	virtual void stopService() = 0;
	virtual void exitService() = 0;
	virtual void destroyService() = 0;

public:
	void addSensor( MindSensor *sensor );
	void addEffector( MindEffector *effector );

private:
	MindSensorSet *sensors;
	MindEffectorSet *effectors;
};

/*#########################################################################*/
/*#########################################################################*/

class MindSensorSet : public MindArea {
public:
	void addSensor( MindSensor *sensor );

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
	virtual const char *getClass() = 0;
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
