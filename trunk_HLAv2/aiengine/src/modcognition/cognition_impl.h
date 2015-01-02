#ifndef	INCLUDE_AICOGNITION_IMPL_H
#define INCLUDE_AICOGNITION_IMPL_H

#include <aiengine.h>
#include <aibrain.h>
#include <aisvcdb.h>
#include <aisvcio.h>

#include <aicognition.h>

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AICognitionImpl : public AICognition , public Service
{
	// service
	virtual void createService( Xml config );
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Cognition" ); };

// external interface
public:
	AICognitionImpl();

private:
	static MindArea *createNeoCortex();

// internals
private:
	AIEngine& engine;
};

// #############################################################################
// #############################################################################

class CognitiveProcessor : public Object
{
private:
	Cortex *inputsCortex;
	Cortex *cognitiveCortex;
	int inputAreaSize;

	const char *getClass() { return( "CognitiveProcessor" ); };

public:
	CognitiveProcessor( String name );
	virtual ~CognitiveProcessor() {};

public:
	void createCortexProcessor( MindArea *area , Cortex *inputs );

public:
	virtual void processMessage( CortexMessage *message );
	virtual void stop() {};
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AICOGNITION_IMPL_H
