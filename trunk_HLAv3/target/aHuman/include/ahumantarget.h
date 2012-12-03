/*#########################################################################*/
/*#########################################################################*/

#include <mind/include/ah_mind.h>

class AHumanTarget : public MindTarget {
public:
	AHumanTarget();

	// target lifecycle
	virtual void configureTarget( Xml config );
	virtual void createTarget( SensorArea *sensorArea , EffectorArea *effectorArea );
	virtual void initSensorsTarget( SensorArea *sensorArea );
	virtual void initEffectorsTarget( EffectorArea *effectorArea );
	virtual void runTarget();
	virtual void stopTarget();
	virtual void exitTarget();
	virtual void destroyTarget();

public:
};

/*#########################################################################*/
/*#########################################################################*/
