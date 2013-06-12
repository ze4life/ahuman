#include "stdafx.h"
#include "ahumantarget.h"

// #############################################################################
// #############################################################################

class SensorEar : public MindSensor {
private:
	bool continueRunFlag;

public:
	SensorEar( SensorArea *area );
	virtual ~SensorEar();
	virtual const char *getClass() { return( "SensorEar" ); };

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

MindSensor *AHumanTarget::createEar( SensorArea *area ) {
	return( new SensorEar( area ) );
}

// #############################################################################
// #############################################################################

SensorEar::SensorEar( SensorArea *p_area )
:	MindSensor( p_area ) {
	attachLogger();
	continueRunFlag = false;

	// autonomous, polling is not required
	MindSensor::setPollState( false );
}

SensorEar::~SensorEar() {
}

void SensorEar::configureSensor( Xml p_config ) {
	config = p_config;
}

void SensorEar::createSensor( MindRegionCreateInfo *createInfo ) {
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

void SensorEar::createSourceConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkSource *source = new NeuroLinkSource();
	source -> setHandler( ( MindRegion::NeuroLinkSourceHandler )&SensorEar::sourceHandler );
	MindSensor::addSourceEntity( connector -> getId() , source );
}

void SensorEar::createTargetConnector( MindRegionCreateInfo *createInfo , MindRegionConnectorDef *connector ) {
	NeuroLinkTarget *target = new NeuroLinkTarget();
	target -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&SensorEar::targetHandler );
	MindSensor::addTargetEntity( connector -> getId() , target );
}

NeuroSignal *SensorEar::sourceHandler( NeuroLink *link , NeuroLinkSource *point ) {
	return( NULL );
}

NeuroSignalSet *SensorEar::targetHandler( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData ) {
	return( NULL );
}
