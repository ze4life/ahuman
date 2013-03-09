#ifndef	INCLUDE_AH_MINDMAP_H
#define INCLUDE_AH_MINDMAP_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindMap;
class MindRegionTypeDef;
class MindRegionDef;
class MindRegionConnectorDef;
class MindCircuitDef;
class MindAreaDef;
class MindConnectionTypeDef;
class MindConnectionLinkTypeDef;
class MindCircuitConnectionDef;

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
	MindMap() {};
	virtual ~MindMap();
	virtual const char *getClass() { return( "MindMap" ); };

// operations
public:
	void createFromXml( Xml xml );

	ClassList<MindCircuitDef>& getMindCircuits() { return( mindCircuitSet ); };
	ClassList<MindAreaDef>& getMindAreas() { return( mindAreaSet ); };

	MindRegionTypeDef *getRegionTypeDefByName( String regionTypeName );
	MindCircuitDef *getCircuitDefByName( String circuitName );
	MindAreaDef *getAreaDefById( String areaId );
	MindConnectionTypeDef *getConnectionTypeDefByName( String typeName );
	void getMapRegions( MapStringToClass<MindRegionDef>& regionMap );

private:
	void createRegionTypeDefSet( Xml xml );
	void createAreaDefSet( Xml xml );
	void createConnectionTypeDefSet( Xml xml );
	void createCircuitDefSet( Xml xml );
	void createRegionMap( MindAreaDef *info );

private:
// own data
	ClassList<MindRegionTypeDef> regionTypeSet;
	ClassList<MindAreaDef> mindAreaSet;
	ClassList<MindConnectionTypeDef> connectionTypeSet;
	ClassList<MindCircuitDef> mindCircuitSet;

// references
	MapStringToClass<MindRegionTypeDef> regionTypeMap;
	MapStringToClass<MindAreaDef> mindAreaMap;
	MapStringToClass<MindConnectionTypeDef> connectionTypeMap;
	MapStringToClass<MindCircuitDef> mindCircuitMap;
	MapStringToClass<MindRegionDef> mindRegionMap;
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

private:
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

class MindRegionDef : public Object {
public:
	MindRegionDef( MindAreaDef *area );
	virtual ~MindRegionDef();
	virtual const char *getClass() { return( "MindRegionDef" ); };

// operations
public:
	void createFromXml( Xml xml );
	void resolveReferences( MindMap *map );

	MindAreaDef *getArea() { return( area ); };
	String getName() { return( name ); };
	String getTypeName() { return( typeName ); };
	MindRegionTypeDef *getType() { return( type ); };
	int getSize() { return( size ); };

private:
// utilities
	String name;
	String typeName;
	int size;

// references
	MindAreaDef *area;
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

private:
// utilities
	String id;
	String type;
};

/*#########################################################################*/
/*#########################################################################*/

class MindCircuitDef : public Object {
public:
	MindCircuitDef();
	virtual ~MindCircuitDef();
	virtual const char *getClass() { return( "MindCircuitDef" ); };

// operations
public:
	void createFromXml( Xml xml );
	void resolveReferences( MindMap *map );

	String getId() { return( id ); };
	String getName() { return( name ); };
	bool runEnabled() { return( enabled ); };
	ClassList<MindCircuitConnectionDef>& getConnections() { return( connections ); };

// data
public:
// utility
	String id;
	String name;
	bool enabled;

// own data
	ClassList<MindCircuitConnectionDef> connections;
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
	bool runEnabled() { return( enabled ); };
	ClassList<MindRegionDef>& getRegions() { return( regions ); };

	MindRegionDef *findRegion( String region );

private:
// utility
	String areaId;
	bool enabled;

// own data
	ClassList<MindRegionDef> regions;

// references
	MapStringToClass<MindRegionDef> regionMap;
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
	ClassList<MindConnectionLinkTypeDef>& getLinks() { return( links ); };

private:
// utilities
	String name;

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

private:
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

class MindCircuitConnectionDef : public Object {
public:
	MindCircuitConnectionDef( MindCircuitDef *circuitInfo );
	virtual ~MindCircuitConnectionDef() {};
	virtual const char *getClass() { return( "MindCircuitConnectionDef" ); };

// operations
public:
	void createFromXml( Xml xml );
	void resolveReferences( MindMap *map );

	String getTypeName() { return( typeName ); };
	String getSrcRegion() { return( srcRegion ); };
	String getDstRegion() { return( dstRegion ); };

	MindCircuitDef *getCircuitDef() { return( circuitDef ); };
	MindConnectionTypeDef *getType() { return( type ); };

// data
public:
// utility
	String typeName;
	String srcRegion;
	String dstRegion;

// references
	MindCircuitDef *circuitDef;
	MindConnectionTypeDef *type;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDMAP_H
