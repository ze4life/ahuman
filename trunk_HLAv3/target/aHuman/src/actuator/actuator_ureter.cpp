#include "stdafx.h"
#include "ahumantarget.h"

// #############################################################################
// #############################################################################

class EffectorUreter : public MindEffector {
private:
	bool continueRunFlag;

public:
	EffectorUreter( EffectorArea *area );
	virtual ~EffectorUreter();
	virtual const char *getClass() { return( "EffectorUreter" ); };

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

MindEffector *AHumanTarget::createUreter( EffectorArea *area ) {
	return( new EffectorUreter( area ) );
}

// #############################################################################
// #############################################################################

EffectorUreter::EffectorUreter( EffectorArea *p_area )
:	MindEffector( p_area ) {
	attachLogger();
	continueRunFlag = false;
}

EffectorUreter::~EffectorUreter() {
}

void EffectorUreter::configureEffector( Xml p_config ) {
	config = p_config;
}

void EffectorUreter::createEffector( MindRegionCreateInfo *createInfo ) {
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

void EffectorUreter::createSourceConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkSource *source = new NeuroLinkSource();
	source -> create( this , connector -> getId() );
	source -> setHandler( ( MindRegion::NeuroLinkSourceHandler )&EffectorUreter::sourceHandler );
}

void EffectorUreter::createTargetConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkTarget *target = new NeuroLinkTarget();
	target -> create( this , connector -> getId() );
	target -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&EffectorUreter::targetHandler );
}

NeuroSignal *EffectorUreter::sourceHandler( NeuroLink *link , NeuroLinkSource *point ) {
	return( NULL );
}

NeuroSignalSet *EffectorUreter::targetHandler( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData ) {
	return( NULL );
}
