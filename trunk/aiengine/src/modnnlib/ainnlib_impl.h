#ifndef	INCLUDE_AINNLIB_IMPL_H
#define INCLUDE_AINNLIB_IMPL_H

#include <math.h>

#include <aiengine.h>
#include <ainnlib.h>
#include <aiknowledge.h>
#include <aiio.h>
#include <aidb.h>

class AINNLibImpl;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AINNLibImpl : public AINNLib , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "NNLib" ); };

// external interface
public:
	AINNLibImpl();
	static AINNLibImpl *getServiceImpl();

	void addLibVariant( AINNLibVariant *lib );
	AINNLibVariant *getLibVariant( String name );

// internals
private:
	AIEngine& engine;
	
	MapStringToClass<AINNLibVariant> variants;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AINNLIB_IMPL_H
