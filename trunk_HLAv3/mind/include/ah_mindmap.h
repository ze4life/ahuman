#ifndef	INCLUDE_AH_MINDMAP_H
#define INCLUDE_AH_MINDMAP_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindMap;
class MindRegionTypeDef;
class MindRegionConnectorDef;
class MindCircuitDef;
class MindAreaDef;
class MindCircuitLinkTypeDef;
class MindCircuitLinkDef;

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
	MindCircuitLinkTypeDef *getLinkTypeDefByName( String typeName );

private:
	void createRegionTypeDefSet( Xml xml );
	void createAreaDefSet( Xml xml );
	void createCircuitLinkTypeDefSet( Xml xml );

private:
// own data
	ClassList<MindRegionTypeDef> regionTypeSet;
	ClassList<MindCircuitDef> mindCircuitSet;
	ClassList<MindAreaDef> mindAreaSet;
	ClassList<MindCircuitLinkTypeDef> linkTypeSet;

// references
	MapStringToClass<MindRegionTypeDef> regionTypeMap;
	MapStringToClass<MindAreaDef> mindAreaMap;
	MapStringToClass<MindCircuitDef> mindCircuitMap;
	MapStringToClass<MindCircuitLinkTypeDef> linkTypeMap;
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

class MindRegionConnectorDef : public Object {
public:
	MindRegionConnectorDef();
	virtual ~MindRegionConnectorDef() {};
	virtual const char *getClass() { return( "MindRegionConnectorDef" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getId();
	bool isSourceConnector();

private:
// utilities
	String id;
	bool sourceConnector;
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

	MindLocation *getLocation() { return( location ); };
	String getChannelId();

private:
	void setChannelInfo( Xml xml );

private:
// utility
	String areaId;
	bool enabled;
	String channelId;

// own data
	MindLocation *location;
};

/*#########################################################################*/
/*#########################################################################*/

class MindCircuitLinkTypeDef : public Object {
public:
	MindCircuitLinkTypeDef();
	virtual ~MindCircuitLinkTypeDef();
	virtual const char *getClass() { return( "MindCircuitLinkTypeDef" ); };

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

class MindCircuitLinkDef : public Object {
public:
	MindCircuitLinkDef( MindCircuitDef *circuitInfo );
	virtual ~MindCircuitLinkDef() {};
	virtual const char *getClass() { return( "MindCircuitLinkDef" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getTypeName() { return( typeName ); };
	String getSrcArea() { return( srcArea ); };
	String getSrcRegion() { return( srcRegion ); };
	String getDstArea() { return( dstArea ); };
	String getDstRegion() { return( dstRegion ); };

// data
public:
// utility
	String typeName;
	String srcArea;
	String srcRegion;
	String dstArea;
	String dstRegion;

// references
	MindCircuitDef *circuitInfo;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDMAP_H
