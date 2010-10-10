#ifndef	INCLUDE_AIHTMLIB_IMPL_H
#define INCLUDE_AIHTMLIB_IMPL_H

#include <aiengine.h>
#include <ailibbn.h>
#include <aisvcio.h>
#include <aisvcdb.h>

/*#########################################################################*/
/*#########################################################################*/

class AILibBNImpl : public AILibBN , public Service
{
	// service
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "LibBN" ); };

// external interface
public:
	AILibBNImpl();
	static AILibBNImpl *getServiceImpl();

	virtual SFNeoCortexLibBN *getSFNeoCortexLib() { return( ( SFNeoCortexLibBN * )getLibVariant( "SFNeoCortex" ) ); };
	virtual ViewCustomLibBN *getViewCustomLib() { return( ( ViewCustomLibBN * )getLibVariant( "ViewCustom" ) ); };

private:
	void addLibVariant( AILibBNVariant *lib );
	AILibBNVariant *getLibVariant( String name );

// create library items
public:
	static AILibBNVariant *createViewCustomLib();
	static AILibBNVariant *createSFNeoCortexLib();

// internals
private:
	AIEngine& engine;
	
	MapStringToClass<AILibBNVariant> variants;
};

#endif	// INCLUDE_AIHTMLIB_IMPL_H
