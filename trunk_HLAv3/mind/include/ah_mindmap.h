#ifndef	INCLUDE_AH_MINDMAP_H
#define INCLUDE_AH_MINDMAP_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindMap;
class MindRegionTypeDef;
class MindRegionDef;
class MindRegionConnectorDef;
class MindGlobalCircuitDef;
class MindGlobalCircuitRegionDef;
class MindLocalCircuitDef;
class MindLocalCircuitConnectionDef;
class MindServiceDef;
class MindAreaDef;
class MindConnectionTypeDef;
class MindConnectionLinkTypeDef;

class TargetAreaDef;
class TargetRegionDef;
class TargetRegionTypeDef;
class TargetRegionConnectorDef;
class TargetCircuitDef;
class TargetCircuitConnectionDef;
class TargetConnectionTypeDef;
class TargetConnectionLinkTypeDef;

/*#########################################################################*/
/*#########################################################################*/

class NeuroLink;
class NeuroLinkSource;
class NeuroLinkTarget;

/*#########################################################################*/
/*#########################################################################*/

// set of mind areas is a mind map
// topology of mind map is pre-defined , including size and inter-area connections
// mind map is defined statically (at least until invention of artificial genetics), in configuration files
class MindMap : public Object {
public:
	MindMap();
	virtual ~MindMap();
	virtual const char *getClass() { return( "MindMap" ); };

// operations
public:
	void createFromXml( Xml xml );
	void createTargetMeta( Xml xml );

	ClassList<MindGlobalCircuitDef>& getMindGlobalCircuits() { return( mindGlobalCircuitSet ); };
	ClassList<MindLocalCircuitDef>& getMindLocalCircuits() { return( mindLocalCircuitSet ); };
	ClassList<MindAreaDef>& getMindAreas() { return( mindAreaSet ); };

	MindRegionTypeDef *getRegionTypeDefByName( String regionTypeName );
	MindRegionDef *getRegionDefById( String regionId );
	MindGlobalCircuitDef *getGlobalCircuitDefByName( String circuitName );
	MindAreaDef *getAreaDefById( String areaId );
	MindConnectionTypeDef *getConnectionTypeDefByName( String typeName );
	MindServiceDef *getServiceByName( String serviceName );
	void getMapRegions( MapStringToClass<MindRegionDef>& regionMap );

	TargetAreaDef *getSensorAreaDef() { return( sensorAreaInfo ); };
	TargetRegionDef *getTargetRegionDefById( String id );
	TargetAreaDef *getEffectorAreaDef() { return( effectorAreaInfo ); };

private:
	void createRegionTypeDefSet( Xml xml );
	void createAreaDefSet( Xml xml );
	void createConnectionTypeDefSet( Xml xml );
	void createCircuitDefSet( Xml xml );
	void createRegionMap( MindAreaDef *info );
	void createTargetMeta_defineCircuit( Xml xml , TargetAreaDef *areaDef , bool sensors );

private:
// own data
	TargetAreaDef *sensorAreaInfo;
	TargetAreaDef *effectorAreaInfo;

	ClassList<MindRegionTypeDef> regionTypeSet;
	ClassList<MindAreaDef> mindAreaSet;
	ClassList<MindConnectionTypeDef> connectionTypeSet;
	ClassList<MindGlobalCircuitDef> mindGlobalCircuitSet;
	ClassList<MindLocalCircuitDef> mindLocalCircuitSet;

// references
	MapStringToClass<MindRegionTypeDef> regionTypeMap;
	MapStringToClass<MindAreaDef> mindAreaMap;
	MapStringToClass<MindConnectionTypeDef> connectionTypeMap;
	MapStringToClass<MindGlobalCircuitDef> mindGlobalCircuitMap;
	MapStringToClass<MindLocalCircuitDef> mindLocalCircuitMap;
	MapStringToClass<MindRegionDef> mindRegionMap;
	MapStringToClass<MindServiceDef> mindServiceMap;
};

/*#########################################################################*/
/*#########################################################################*/

class MindRegionTypeDef : public Object {
public:
	MindRegionTypeDef();
	virtual ~MindRegionTypeDef();
	virtual const char *getClass() { return( "MindRegionTypeDef" ); };

// operations
public:
	void createFromXml( Xml xml );
	void resolveReferences( MindMap *map );

	String getName() { return( name ); };
	String getImplementation() { return( implementation ); };
	MindRegionTypeDef *getOriginalTypeDef() { return( originalTypeDef ); };

	ClassList<MindRegionConnectorDef>& getConnectors() { return( connectorSet ); };
	MindRegionConnectorDef *getConnector( String id );

private:
	void createConnectorSetFromXml( Xml xml );

protected:
// utilities
	String name;
	String implementation;

// own data
	ClassList<MindRegionConnectorDef> connectorSet;

// references
	MapStringToClass<MindRegionConnectorDef> connectorMap;
	MindRegionTypeDef *originalTypeDef;
};

/*#########################################################################*/
/*#########################################################################*/

typedef enum {
	MIND_REGION_ROLE_NONE = 0,				// not initialized
	MIND_REGION_ROLE_PROCESSOR = 1,			// complex processing
	MIND_REGION_ROLE_RELAY = 2,				// single-target or multiplexing relay
	MIND_REGION_ROLE_SENSORY = 3,			// sensory ganglion
	MIND_REGION_ROLE_SYMPATHETIC = 4,		// sympathetic ganglion/nucleus
	MIND_REGION_ROLE_PARASYMPATHETIC = 5,	// parasympathetic ganglion/nucleus
	MIND_REGION_ROLE_FLEXOR = 6,			// flexor somatic motor
	MIND_REGION_ROLE_EXTENSOR = 7,			// extensor somatic motor
	MIND_REGION_ROLE_TARGETSENSOR = 8,		// target sensor
	MIND_REGION_ROLE_TARGETEFFECTOR = 9		// target motor
} MindRegionRoleEnum;

class MindRegionDef : public Object {
public:
	MindRegionDef( MindAreaDef *area , MindLocalCircuitDef *circuit );
	virtual ~MindRegionDef();
	virtual const char *getClass() { return( "MindRegionDef" ); };

// operations
public:
	void createFromXml( Xml xml );
	void resolveReferences( MindMap *map );

	MindAreaDef *getArea() { return( area ); };
	MindLocalCircuitDef *getCircuit() { return( circuit ); };

	String getId() { return( id ); };
	String getTypeName() { return( typeName ); };
	String getServiceName() { return( serviceName ); };
	MindRegionTypeDef *getType() { return( type ); };
	MindServiceDef *getService() { return( service ); };
	MindRegionRoleEnum getRole() { return( role ); };
	int getSize() { return( size ); };

	String getRoleName();

	bool isTarget() { return( target == true ); };
	bool isTargetSensor() { return( target == true && sensor == true ); };
	bool isTargetEffector() { return( target == true && sensor == false ); };

protected:
// utilities
	String id;
	String typeName;
	String serviceName;
	MindRegionRoleEnum role;
	int size;
	bool target;
	bool sensor;

// references
	MindAreaDef *area;
	MindLocalCircuitDef *circuit;
	MindServiceDef *service;
	MindRegionTypeDef *type;
};

/*#########################################################################*/
/*#########################################################################*/

class MindRegionConnectorDef : public Object {
public:
	MindRegionConnectorDef();
	virtual ~MindRegionConnectorDef() {};
	virtual const char *getClass() { return( "MindRegionConnectorDef" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getId() { return( id ); };
	String getType() { return( type ); };

	bool isTarget();
	
protected:
// utilities
	String id;
	String type;
};

/*#########################################################################*/
/*#########################################################################*/

class MindGlobalCircuitRegionDef : public Object {
public:
	MindGlobalCircuitRegionDef( MindGlobalCircuitDef *circuit );
	virtual ~MindGlobalCircuitRegionDef() {};
	virtual const char *getClass() { return( "MindGlobalCircuitRegionDef" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getId() { return( id ); };
	String getRole() { return( role ); };

protected:
// utilities
	String id;
	String role;

// references
	MindGlobalCircuitDef *circuit;
};

/*#########################################################################*/
/*#########################################################################*/

class MindGlobalCircuitDef : public Object {
public:
	MindGlobalCircuitDef();
	virtual ~MindGlobalCircuitDef();
	virtual const char *getClass() { return( "MindGlobalCircuitDef" ); };

// operations
public:
	void createFromXml( Xml xml );
	void resolveReferences( MindMap *map );

	String getId() { return( id ); };
	String getName() { return( name ); };
	bool runEnabled() { return( enabled ); };
	ClassList<MindLocalCircuitConnectionDef>& getConnections() { return( connections ); };

private:
	void addConnectons( MindMap *map , String region );

// data
public:
// utility
	String id;
	String name;
	bool enabled;

// references
	MapStringToClass<MindGlobalCircuitRegionDef> regionMap;
	ClassList<MindLocalCircuitConnectionDef> connections;
};

/*#########################################################################*/
/*#########################################################################*/

class MindServiceDef : public Object {
public:
	MindServiceDef( MindAreaDef *areaDef );
	virtual ~MindServiceDef();
	virtual const char *getClass() { return( "MindServiceDef" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getServiceId() { return( serviceId ); };
	String getServiceName() { return( serviceName ); };
	MindAreaDef *getAreaDef() { return( area ); };
	MapStringToClass<MindRegionDef>& getRegions() { return( regionMap ); };

protected:
// utility
	String serviceId;
	String serviceName;

// references
	MindAreaDef *area;
	MapStringToClass<MindRegionDef> regionMap;
};

/*#########################################################################*/
/*#########################################################################*/

class MindLocalCircuitDef : public Object {
public:
	MindLocalCircuitDef( MindAreaDef *areaDef );
	virtual ~MindLocalCircuitDef();
	virtual const char *getClass() { return( "MindLocalCircuitDef" ); };

// operations
public:
	void createFromXml( Xml xml );
	void resolveReferences( MindMap *map );

	String getId() { return( id ); };
	String getName() { return( name ); };
	String getImgHeight() { return( imgheight ); };

	MindAreaDef *getAreaDef() { return( area ); };
	MapStringToClass<MindRegionDef>& getRegions() { return( regionMap ); };
	MapStringToClass<MindLocalCircuitConnectionDef>& getConnections() { return( connections ); };

	void getInternalConnections( ClassList<MindLocalCircuitConnectionDef>& links );
	void getExternalConnections( ClassList<MindLocalCircuitConnectionDef>& links , bool isin );

protected:
// utility
	String id;
	String name;
	bool enabled;
	String imgheight;

// references
	MindAreaDef *area;
	MapStringToClass<MindRegionDef> regionMap;
	MapStringToClass<MindLocalCircuitConnectionDef> connections;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaDef : public Object {
public:
	MindAreaDef();
	virtual ~MindAreaDef();
	virtual const char *getClass() { return( "MindAreaDef" ); };

// operations
public:
	void createFromXml( Xml xml );
	void resolveReferences( MindMap *map );

	String getAreaId() { return( areaId ); };
	String getAreaType() { return( areaType ); };
	String getAreaName() { return( areaName ); };
	String getAreaFunction() { return( areaFunction ); };
	bool runEnabled() { return( enabled ); };

	MapStringToClass<MindServiceDef>& getServices() { return( serviceMap ); };
	ClassList<MindRegionDef>& getRegions() { return( regions ); };
	ClassList<MindLocalCircuitConnectionDef>& getConnections() { return( connections ); };
	MapStringToClass<MindLocalCircuitDef>& getCircuits() { return( circuitMap ); };

	void addRegion( MindRegionDef *region );
	void addCircuit( MindLocalCircuitDef *circuit );
	void addConnection( MindLocalCircuitConnectionDef *connection );
	MindRegionDef *findRegion( String region );

protected:
// utility
	String areaId;
	String areaType;
	String areaName;
	String areaFunction;
	bool enabled;

// own data
	ClassList<MindServiceDef> services;
	ClassList<MindLocalCircuitDef> circuits;
	ClassList<MindRegionDef> regions;
	ClassList<MindLocalCircuitConnectionDef> connections;

// references
	MapStringToClass<MindServiceDef> serviceMap;
	MapStringToClass<MindRegionDef> regionMap;
	MapStringToClass<MindLocalCircuitDef> circuitMap;
};

/*#########################################################################*/
/*#########################################################################*/

class MindConnectionTypeDef : public Object {
public:
	MindConnectionTypeDef();
	virtual ~MindConnectionTypeDef();
	virtual const char *getClass() { return( "MindConnectionTypeDef" ); };

// operations
public:
	void createFromXml( Xml xml );
	void resolveReferences( MindMap *map );

	String getName() { return( name ); };
	String getSrcRegionType() { return( srcRegionType ); };
	String getDstRegionType() { return( dstRegionType ); };
	ClassList<MindConnectionLinkTypeDef>& getLinks() { return( links ); };
	MindConnectionLinkTypeDef *getPrimaryLink() { return( links.get( 0 ) ); };

protected:
// utilities
	String name;
	String srcRegionType;
	String dstRegionType;

// own data
	ClassList<MindConnectionLinkTypeDef> links;

// references
	MapStringToClass<MindConnectionLinkTypeDef> linkMap;
};

/*#########################################################################*/
/*#########################################################################*/

class MindConnectionLinkTypeDef : public Object {
public:
	MindConnectionLinkTypeDef( MindConnectionTypeDef *connectionDef );
	virtual ~MindConnectionLinkTypeDef();
	virtual const char *getClass() { return( "MindConnectionLinkTypeDef" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getName() { return( name ); };
	String getImplementation() { return( implementation ); };
	String getType() { return( type ); };
	String getNeurotransmitter() { return( neurotransmitter ); };
	String getSrcConnector() { return( srcConnector ); };
	String getDstConnector() { return( dstConnector ); };
	bool isBackward() { return( back ); };
	MindConnectionTypeDef *getConnectionDef() { return( connectionDef ); };

protected:
// utilities
	String name;
	String implementation;
	String type;
	String neurotransmitter;
	String srcConnector;
	String dstConnector;
	bool back;

// references
	MindConnectionTypeDef *connectionDef;
};

/*#########################################################################*/
/*#########################################################################*/

class MindLocalCircuitConnectionDef : public Object {
public:
	MindLocalCircuitConnectionDef( MindLocalCircuitDef *circuitInfo );
	virtual ~MindLocalCircuitConnectionDef() {};
	virtual const char *getClass() { return( "MindLocalCircuitConnectionDef" ); };

// operations
public:
	void createFromXml( Xml xml );
	void resolveReferences( MindMap *map );

	String getTypeName() { return( typeName ); };
	bool isPrimary() { return( primary ); };
	String getSrcRegion() { return( srcRegion ); };
	String getDstRegion() { return( dstRegion ); };

	MindLocalCircuitDef *getCircuitDef() { return( circuitDef ); };
	MindConnectionTypeDef *getType() { return( type ); };
	MindConnectionLinkTypeDef *getPrimaryLinkType();
	String getId();

// data
protected:
// utility
	String typeName;
	bool primary;
	String srcRegion;
	String dstRegion;

// references
	MindLocalCircuitDef *circuitDef;
	MindConnectionTypeDef *type;
};

// #############################################################################
// #############################################################################

class TargetAreaDef : public MindAreaDef {
public:
	TargetAreaDef();
	virtual ~TargetAreaDef();
	virtual const char *getClass() { return( "TargetAreaDef" ); };

public:
	void defineSensorArea();
	void defineEffectorArea();

	void addRegion( TargetRegionDef *regionDef );
};

// #############################################################################
// #############################################################################

class TargetRegionDef : public MindRegionDef {
public:
	TargetRegionDef( TargetAreaDef *areaInfo );
	virtual ~TargetRegionDef();
	virtual const char *getClass() { return( "TargetRegionDef" ); };

public:
	void defineSensorRegion( Xml xml );
	void defineEffectorRegion( Xml xml );

	void setCircuitDef( TargetCircuitDef *info ) { circuitInfo = info; };
	TargetCircuitDef *getCircuitDef() { return( circuitInfo ); };
	TargetAreaDef *getTargetArea() { return( areaInfo ); };

private:
// references
	TargetAreaDef *areaInfo;
	TargetCircuitDef *circuitInfo;
};

// #############################################################################
// #############################################################################

class TargetRegionTypeDef : public MindRegionTypeDef {
public:
	TargetRegionTypeDef();
	virtual ~TargetRegionTypeDef();
	virtual const char *getClass() { return( "TargetRegionTypeDef" ); };

public:
	void defineSensorRegionType( TargetRegionDef *regionInfo , Xml xml );
	void defineEffectorRegionType( TargetRegionDef *regionInfo , Xml xml );

	void defineRegionType( TargetRegionDef *regionInfo , bool sensor , Xml xml );
	void defineConnectorSet( Xml xml );

	TargetCircuitDef *getCircuitInfo() { return( circuitInfo ); };

private:
	// own data
	TargetCircuitDef *circuitInfo;
};

// #############################################################################
// #############################################################################

class TargetRegionConnectorDef : public MindRegionConnectorDef {
public:
	TargetRegionConnectorDef();
	virtual ~TargetRegionConnectorDef();
	virtual const char *getClass() { return( "TargetRegionConnectorDef" ); };

public:
	void defineRegionConnectorDef( Xml xml , TargetCircuitDef *circuitInfo );

	String getRegion() { return ( region ); };
	String getConnector() { return ( connector ); };

private:
	String region;
	String connector;
};

// #############################################################################
// #############################################################################

class TargetCircuitDef : public MindLocalCircuitDef {
public:
	TargetCircuitDef( TargetAreaDef *areaDef , TargetRegionDef *regionDef );
	virtual ~TargetCircuitDef();
	virtual const char *getClass() { return( "TargetCircuitDef" ); };

public:
	void defineCircuit( bool sensor , Xml xmlRegion );
	void defineCircuitConnection( TargetRegionConnectorDef *regionConnection , Xml xml );

	String getActuatorId() { return( actuatorId ); };
	bool isSensor() { return( isSensorOption ); };

private:
	// utilities
	bool isSensorOption;
	String actuatorId;

	// references
	TargetRegionDef *regionInfo;
};

/*#########################################################################*/
/*#########################################################################*/

class TargetCircuitConnectionDef : public MindLocalCircuitConnectionDef {
public:
	TargetCircuitConnectionDef( TargetCircuitDef *circuitInfo );
	virtual ~TargetCircuitConnectionDef();
	virtual const char *getClass() { return( "TargetCircuitConnectionDef" ); };

public:
	void defineCircuitConnectorDef( TargetRegionConnectorDef *regionConnection , Xml xml );

private:
// references
	TargetRegionConnectorDef *regionConnection;

// own data
	TargetConnectionTypeDef *connectionTypeDef;
};

/*#########################################################################*/
/*#########################################################################*/

class TargetConnectionTypeDef : public MindConnectionTypeDef {
public:
	TargetConnectionTypeDef();
	virtual ~TargetConnectionTypeDef();
	virtual const char *getClass() { return( "TargetConnectionTypeDef" ); };

public:
	void defineConnectionTypeDef( TargetCircuitDef *circuitInfoTarget , TargetRegionConnectorDef *regionConnection , Xml xml );

private:
// references
	TargetConnectionLinkTypeDef *linkInfo;
};

/*#########################################################################*/
/*#########################################################################*/

class TargetConnectionLinkTypeDef : public MindConnectionLinkTypeDef {
public:
	TargetConnectionLinkTypeDef( TargetConnectionTypeDef *p_connectionDef );
	virtual ~TargetConnectionLinkTypeDef();
	virtual const char *getClass() { return( "TargetConnectionLinkTypeDef" ); };

public:
	void defineConnectionLinkTypeDef( TargetCircuitDef *circuitInfoTarget , TargetRegionConnectorDef *regionConnection , TargetConnectionTypeDef *connectionType , Xml xml );
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDMAP_H
