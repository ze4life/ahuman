#include "stdafx.h"
#include "ahumantarget.h"

// #############################################################################
// #############################################################################

class EffectorNeck : public MindEffector {
private:
	bool continueRunFlag;

public:
	EffectorNeck( EffectorArea *area );
	virtual ~EffectorNeck();
	virtual const char *getClass() { return( "EffectorNeck" ); };

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

MindEffector *AHumanTarget::createNeck( EffectorArea *area ) {
	return( new EffectorNeck( area ) );
}

// #############################################################################
// #############################################################################

EffectorNeck::EffectorNeck( EffectorArea *p_area )
:	MindEffector( p_area ) {
	attachLogger();
	continueRunFlag = false;
}

EffectorNeck::~EffectorNeck() {
}

void EffectorNeck::configureEffector( Xml p_config ) {
	config = p_config;
}

void EffectorNeck::createEffector( MindRegionCreateInfo *createInfo ) {
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

void EffectorNeck::createSourceConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkSource *source = new NeuroLinkSource();
	source -> setHandler( ( MindRegion::NeuroLinkSourceHandler )&EffectorNeck::sourceHandler );
	MindEffector::addSourceEntity( connector -> getId() , source );
}

void EffectorNeck::createTargetConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkTarget *target = new NeuroLinkTarget();
	target -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&EffectorNeck::targetHandler );
	MindEffector::addTargetEntity( connector -> getId() , target );
}

NeuroSignal *EffectorNeck::sourceHandler( NeuroLink *link , NeuroLinkSource *point ) {
	return( NULL );
}

NeuroSignalSet *EffectorNeck::targetHandler( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData ) {
	return( NULL );
}
