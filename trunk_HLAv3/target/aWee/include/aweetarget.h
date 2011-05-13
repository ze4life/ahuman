/*#########################################################################*/
/*#########################################################################*/

#include <mind/include/ah_mind.h>

class AWeeTarget : public MindTarget {
public:
	AWeeTarget();

	// target lifecycle
	virtual void configureTarget( Xml config );
	virtual void createTarget();
	virtual void initSensorsTarget( MindArea *sensorArea );
	virtual void initEffectorsTarget( MindArea *effectorArea );
	virtual void runTarget();
	virtual void stopTarget();
	virtual void exitTarget();
	virtual void destroyTarget();

public:
	MindSensor *createFileSysWalker( MindArea *area );
};

/*#########################################################################*/
/*#########################################################################*/
