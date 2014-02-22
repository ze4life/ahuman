#include "stdafx.h"
#include "ahumantarget.h"

// #############################################################################
// #############################################################################

class EffectorMouth : public MindEffector {
private:
	bool continueRunFlag;

public:
	EffectorMouth( EffectorArea *area );
	virtual ~EffectorMouth();
	virtual const char *getClass() { return( "EffectorMouth" ); };

public:
	// effector lifecycle
	virtual void createEffector( MindRegionCreateInfo *createInfo );
	virtual void configureEffector( Xml config );
	virtual void startEffector() {};
	virtual void stopEffector() {};
	virtual void processEffectorControl( NeuroLink *link , NeuroSignal *signal ) {};

private:
	void createSourceConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector );
	void createTargetConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector );

	NeuroSignal *sourceHandler( NeuroLink *link , NeuroLinkSource *point );
	NeuroSignalSet *targetHandler( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData );

private:
	Xml config;
};

MindEffector *AHumanTarget::createMouth( EffectorArea *area ) {
	return( new EffectorMouth( area ) );
}

// #############################################################################
// #############################################################################

EffectorMouth::EffectorMouth( EffectorArea *p_area )
:	MindEffector( p_area ) {
	attachLogger();
	continueRunFlag = false;
}

EffectorMouth::~EffectorMouth() {
}

void EffectorMouth::configureEffector( Xml p_config ) {
	config = p_config;
}

void EffectorMouth::createEffector( MindRegionCreateInfo *createInfo ) {
	// set connectors
	TargetRegionDef *info = MindEffector::getEffectorInfo();
	MindRegionTypeDef *type = info -> getType();
	ClassList<MindRegionConnectorDef>& connectors = type -> getConnectors();
	for( int k = 0; k < connectors.count(); k++ ) {
		MindRegionConnectorDef *connector = connectors.get( k );
		if( connector -> isTarget() )
			createTargetConnector( createInfo , connector );
		else
			createSourceConnector( createInfo , connector );
	}
}

void EffectorMouth::createSourceConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkSource *source = new NeuroLinkSource();
	source -> create( this , connector -> getId() );
	source -> setHandler( ( MindRegion::NeuroLinkSourceHandler )&EffectorMouth::sourceHandler );
}

void EffectorMouth::createTargetConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkTarget *target = new NeuroLinkTarget();
	target -> create( this , connector -> getId() );
	target -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&EffectorMouth::targetHandler );
}

NeuroSignal *EffectorMouth::sourceHandler( NeuroLink *link , NeuroLinkSource *point ) {
	return( NULL );
}

NeuroSignalSet *EffectorMouth::targetHandler( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData ) {
	return( NULL );
}
