/*#########################################################################*/
/*#########################################################################*/

#include <mind/include/ah_mind.h>

class AWeeTarget : public MindTarget {
public:
	AWeeTarget();

	// service interface
	virtual const char *getServiceName() { return( "AWeeTarget" ); };
	virtual void configureService( Xml config );
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void stopService();
	virtual void exitService();
	virtual void destroyService();
};

/*#########################################################################*/
/*#########################################################################*/
