#ifndef	INCLUDE_AIMIND_IMPL_H
#define INCLUDE_AIMIND_IMPL_H

#include <aiengine.h>
#include <aimind.h>
#include <aiio.h>
#include <aiknowledge.h>

/*#########################################################################*/
/*#########################################################################*/

// patterns to possible actions translator
class AIMindImpl : public AIMind , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Mind" ); };

// external interface
public:

	// AIObject interface

public:
	AIMindImpl();
	void startIndependentThinking();
	void stopIndependentThinking();

	bool canContinue() { return( enabled ); };

// internals
public:
	void performIndependentThinking();

// internals
private:
	AIEngine& engine;

	bool enabled;
	RFC_THREAD independentThreadID;
};

#endif	// INCLUDE_AIMIND_IMPL_H
