#include "stdafx.h"
#include "ahumantarget.h"

// #############################################################################
// #############################################################################

class EffectorLeg : public MindEffector {
private:
	bool continueRunFlag;

public:
	EffectorLeg( EffectorArea *area );
	virtual ~EffectorLeg();
	virtual const char *getClass() { return( "EffectorLeg" ); };

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

MindEffector *AHumanTarget::createLeg( EffectorArea *area ) {
	return( new EffectorLeg( area ) );
}

// #############################################################################
// #############################################################################

EffectorLeg::EffectorLeg( EffectorArea *p_area )
:	MindEffector( p_area ) {
	attachLogger();
	continueRunFlag = false;
}

EffectorLeg::~EffectorLeg() {
}

void EffectorLeg::configureEffector( Xml p_config ) {
	config = p_config;
}

void EffectorLeg::createEffector( MindRegionCreateInfo *createInfo ) {
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

void EffectorLeg::createSourceConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkSource *source = new NeuroLinkSource();
	source -> setHandler( ( MindRegion::NeuroLinkSourceHandler )&EffectorLeg::sourceHandler );
	MindEffector::addSourceEntity( connector -> getId() , source );
}

void EffectorLeg::createTargetConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkTarget *target = new NeuroLinkTarget();
	target -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&EffectorLeg::targetHandler );
	MindEffector::addTargetEntity( connector -> getId() , target );
}

NeuroSignal *EffectorLeg::sourceHandler( NeuroLink *link , NeuroLinkSource *point ) {
	return( NULL );
}

NeuroSignalSet *EffectorLeg::targetHandler( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData ) {
	return( NULL );
}
