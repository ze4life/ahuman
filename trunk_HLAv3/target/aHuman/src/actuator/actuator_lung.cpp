#include "stdafx.h"
#include "ahumantarget.h"

// #############################################################################
// #############################################################################

class EffectorLung : public MindEffector {
private:
	bool continueRunFlag;

public:
	EffectorLung( EffectorArea *area );
	virtual ~EffectorLung();
	virtual const char *getClass() { return( "EffectorLung" ); };

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

MindEffector *AHumanTarget::createLung( EffectorArea *area ) {
	return( new EffectorLung( area ) );
}

// #############################################################################
// #############################################################################

EffectorLung::EffectorLung( EffectorArea *p_area )
:	MindEffector( p_area ) {
	attachLogger();
	continueRunFlag = false;
}

EffectorLung::~EffectorLung() {
}

void EffectorLung::configureEffector( Xml p_config ) {
	config = p_config;
}

void EffectorLung::createEffector( MindRegionCreateInfo *createInfo ) {
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

void EffectorLung::createSourceConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkSource *source = new NeuroLinkSource();
	source -> setHandler( ( MindRegion::NeuroLinkSourceHandler )&EffectorLung::sourceHandler );
	MindEffector::addSourceEntity( connector -> getId() , source );
}

void EffectorLung::createTargetConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkTarget *target = new NeuroLinkTarget();
	target -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&EffectorLung::targetHandler );
	MindEffector::addTargetEntity( connector -> getId() , target );
}

NeuroSignal *EffectorLung::sourceHandler( NeuroLink *link , NeuroLinkSource *point ) {
	return( NULL );
}

NeuroSignalSet *EffectorLung::targetHandler( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData ) {
	return( NULL );
}
