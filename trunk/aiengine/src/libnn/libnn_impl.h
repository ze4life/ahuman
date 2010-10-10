#ifndef	INCLUDE_AINNLIB_IMPL_H
#define INCLUDE_AINNLIB_IMPL_H

#include <math.h>

#include <aiengine.h>
#include <ailibnn.h>
#include <aiknowledge.h>
#include <aisvcio.h>
#include <aisvcdb.h>

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AILibNNImpl : public AILibNN , public Service
{
private:
	AIEngine& engine;
	MapStringToClass<AILibNNVariant> variants;

public:
	// service
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "LibNN" ); };

// external interface
public:
	AILibNNImpl();
	static AILibNNImpl *getServiceImpl();

	AILibNNVariant *getLibVariant( String name );

// internals
private:
	void addLibVariant( AILibNNVariant *lib );
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AINNLIB_IMPL_H
