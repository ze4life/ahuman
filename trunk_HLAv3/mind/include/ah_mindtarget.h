#ifndef	INCLUDE_AH_MINDTARGET_H
#define INCLUDE_AH_MINDTARGET_H

/*#########################################################################*/
/*#########################################################################*/

class MindTarget;
class MindActuatorSet;
class MindActuator;
class MindSensor;
class MindEffector;

/*#########################################################################*/
/*#########################################################################*/

class MindTarget : public Object {
public:
	virtual const char *getClass() = 0;

public:
	void addSensor( MindSensor *sensor );
	void addEffector( MindEffector *effector );

private:
	MindActuatorSet *sensors;
	MindActuatorSet *effectors;
};

/*#########################################################################*/
/*#########################################################################*/

class MindActuatorSet : public Object {
public:
	virtual const char *getClass() { return( "MindActuatorSet" ); };

public:
	void addActuator( MindActuator *actuator );

private:
	ClassList<MindActuator> list;
	MapStringToClass<MindActuator> map;
};

/*#########################################################################*/
/*#########################################################################*/

class MindActuator : public Object {
public:
	virtual const char *getClass() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class MindSensor : public MindActuator {
public:
	virtual const char *getClass() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class MindEffector : public MindActuator {
public:
	virtual const char *getClass() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDTARGET_H
