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
class MindCircuitConnectionTypeDef;
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
	MindCircuitConnectionTypeDef *getConnectionTypeDefByName( String typeName );

private:
	void createRegionTypeDefSet( Xml xml );
	void createAreaDefSet( Xml xml );
	void createCircuitLinkTypeDefSet( Xml xml );
	void createCircuitDefSet( Xml xml );
	void createRegionMap( MindAreaDef *info );

private:
// own data
	ClassList<MindRegionTypeDef> regionTypeSet;
	ClassList<MindAreaDef> mindAreaSet;
	ClassList<MindCircuitConnectionTypeDef> linkTypeSet;
	ClassList<MindCircuitDef> mindCircuitSet;

// references
	MapStringToClass<MindRegionTypeDef> regionTypeMap;
	MapStringToClass<MindAreaDef> mindAreaMap;
	MapStringToClass<MindCircuitConnectionTypeDef> linkTypeMap;
	MapStringToClass<MindCircuitDef> mindCircuitMap;
	MapStringToClass<MindRegionDef> mindRegionMap;
};

/*#########################################################################*/
/*#########################################################################*/

class MindRegionTypeDef : public Object {
public:
	virtual ~MindRegionTypeDef();
	virtual const char *getClass() { return( "MindRegionTypeDef" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getName();
	MindRegionConnectorDef *getConnector( String id );

private:
	void createConnectorSetFromXml( Xml xml );

private:
// utilities
	String name;

// own data
	ClassList<MindRegionConnectorDef> connectorSet;

// references
	MapStringToClass<MindRegionConnectorDef> connectorMap;
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

	String getName();
	String getTypeName();

	void setType( MindRegionTypeDef *type );
	MindRegionTypeDef *getType();

private:
// utilities
	String name;
	String typeName;

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

	String getId();

private:
// utilities
	String id;
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

	String getName();
	bool runEnabled();

// data
public:
// utility
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

	String getAreaId() { return( areaId ); };
	bool runEnabled();

	ClassList<MindRegionDef>& getRegions();
	String getChannelId();

private:
// utility
	String areaId;
	bool enabled;
	String channelId;

// own data
	ClassList<MindRegionDef> regions;

// references
	MapStringToClass<MindRegionDef> regionMap;
};

/*#########################################################################*/
/*#########################################################################*/

class MindCircuitConnectionTypeDef : public Object {
public:
	MindCircuitConnectionTypeDef();
	virtual ~MindCircuitConnectionTypeDef();
	virtual const char *getClass() { return( "MindCircuitConnectionTypeDef" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getName() { return( name ); };
	String getNeurotransmitter() { return( neurotransmitter ); };
	bool isExcitatory();
	bool isInhibitory();
	bool isModulatory();

private:
// utilities
	String name;
	String neurotransmitter;
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

	String getTypeName() { return( typeName ); };
	String getSrcRegion() { return( srcRegion ); };
	String getDstRegion() { return( dstRegion ); };

// data
public:
// utility
	String typeName;
	String srcRegion;
	String dstRegion;

// references
	MindCircuitDef *circuitInfo;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDMAP_H
