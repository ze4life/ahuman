#ifndef	INCLUDE_AIHTMLIB_IMPL_H
#define INCLUDE_AIHTMLIB_IMPL_H

#include <aiengine.h>
#include <aihtmlib.h>
#include <aiio.h>
#include <aidb.h>

/*#########################################################################*/
/*#########################################################################*/

class AIHtmLibImpl : public AIHtmLib , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "HtmLib" ); };

// external interface
public:
	AIHtmLibImpl();
	static AIHtmLibImpl *getServiceImpl();

	void addLibVariant( AIHtmLibVariant *lib );
	AIHtmLibVariant *getLibVariant( String name );

// internals
private:
	AIEngine& engine;
	
	MapStringToClass<AIHtmLibVariant> variants;
};

#endif	// INCLUDE_AIHTMLIB_IMPL_H
