#include "stdafx.h"
#include "ahumantarget.h"

// #############################################################################
// #############################################################################

class SensorMindCover : public MindSensor {
private:
	bool continueRunFlag;

public:
	SensorMindCover( SensorArea *area );
	virtual ~SensorMindCover();
	virtual const char *getClass() { return( "SensorMindCover" ); };

public:
	// sensor lifecycle
	virtual void createSensor( MindRegionCreateInfo *createInfo );
	virtual void configureSensor( Xml config );
	virtual void startSensor() {};
	virtual void stopSensor() {};
	virtual void processSensorControl( NeuroLink *link , NeuroSignal *signal ) {};
	virtual void produceSensorData() {};
	virtual void pollSensor() {};

private:
	bool executeSensorControl( NeuroSignal *signal );
	void sendSignal( int action , String value );

	void createSourceConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector );
	void createTargetConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector );

	NeuroSignal *sourceHandler( NeuroLink *link , NeuroLinkSource *point );
	NeuroSignalSet *targetHandler( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData );

private:
	Xml config;
};

MindSensor *AHumanTarget::createMindCover( SensorArea *area ) {
	return( new SensorMindCover( area ) );
}

// #############################################################################
// #############################################################################

SensorMindCover::SensorMindCover( SensorArea *p_area )
:	MindSensor( p_area ) {
	attachLogger();
	continueRunFlag = false;

	// autonomous, polling is not required
	MindSensor::setPollState( false );
}

SensorMindCover::~SensorMindCover() {
}

void SensorMindCover::configureSensor( Xml p_config ) {
	config = p_config;
}

void SensorMindCover::createSensor( MindRegionCreateInfo *createInfo ) {
	// set connectors
	TargetRegionDef *info = MindSensor::getSensorInfo();
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

void SensorMindCover::createSourceConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkSource *source = new NeuroLinkSource();
	source -> setHandler( ( MindRegion::NeuroLinkSourceHandler )&SensorMindCover::sourceHandler );
	MindSensor::addSourceEntity( connector -> getId() , source );
}

void SensorMindCover::createTargetConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkTarget *target = new NeuroLinkTarget();
	target -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&SensorMindCover::targetHandler );
	MindSensor::addTargetEntity( connector -> getId() , target );
}

NeuroSignal *SensorMindCover::sourceHandler( NeuroLink *link , NeuroLinkSource *point ) {
	return( NULL );
}

NeuroSignalSet *SensorMindCover::targetHandler( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData ) {
	return( NULL );
}
