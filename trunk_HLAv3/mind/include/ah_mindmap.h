#ifndef	INCLUDE_AH_MINDMAP_H
#define INCLUDE_AH_MINDMAP_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindMap;
class MindNetInfo;
class MindAreaInfo;
class MindAreaLinkInfo;
class MindAreaNetInfo;
class MindNetworkType;
class MindLinkType;
class NeuroLinkInfo;

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

	ClassList<MindNetInfo>& getMindNets() { return( mindNetSet ); };
	ClassList<MindAreaInfo>& getMindAreas() { return( mindAreaSet ); };
	ClassList<MindAreaLinkInfo>& getLinks() { return( mindLinkSet ); }
	MindNetInfo *getNetByName( String netName );
	MindAreaInfo *getAreaById( String areaId );
	MindNetworkType *getNetTypeByName( String typeName );
	MindLinkType *getLinkTypeByName( String typeName );

private:
	void createAreaSet( Xml xml );
	void createNetworkTypeSet( Xml xml );
	void createNetworkSet( Xml xml );
	void createLinkTypeSet( Xml xml );
	void createMindLinkSet( Xml xml );
	void linkAreaNet();

private:
// own data
	ClassList<MindNetworkType> netTypeSet;
	ClassList<MindNetInfo> mindNetSet;
	ClassList<MindAreaInfo> mindAreaSet;
	ClassList<MindLinkType> linkTypeSet;
	ClassList<MindAreaLinkInfo> mindLinkSet;

// references
	MapStringToClass<MindNetInfo> mindNetMap;
	MapStringToClass<MindAreaInfo> mindAreaMap;
	MapStringToClass<MindNetworkType> netTypeMap;
	MapStringToClass<MindLinkType> linkTypeMap;
};

/*#########################################################################*/
/*#########################################################################*/

class MindNetInfo : public Object {
public:
	MindNetInfo();
	virtual ~MindNetInfo();
	virtual const char *getClass() { return( "MindNetInfo" ); };

// operations
public:
	void createFromXml( Xml xml );
	String getName();
	String getTypeName();
	bool runEnabled();
	void setNetType( MindNetworkType *netType );
	MindNetworkType *getNetType();

// data
public:
// utility
	String name;
	String typeName;
	bool enabled;
	MindNetworkType *netType;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaInfo : public Object {
public:
	MindAreaInfo();
	virtual ~MindAreaInfo();
	virtual const char *getClass() { return( "MindAreaInfo" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getAreaId() { return( areaId ); };
	bool runEnabled();

	MindLocation *getLocation() { return( location ); };
	ClassList<MindAreaLinkInfo>& getLinkSet() { return( linkSet ); };
	void addLink( MindAreaLinkInfo *link ) { linkSet.add( link );	};
	ClassList<MindAreaNetInfo>& getNetSet() { return( netSet ); };
	MindAreaNetInfo *getNetInfo( String name );

private:
// utility
	String areaId;
	bool enabled;

// own data
	MindLocation *location;
	ClassList<MindAreaNetInfo> netSet;

// references
	MapStringToClass<MindAreaNetInfo> netMap;
	ClassList<MindAreaLinkInfo> linkSet;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaLinkInfo : public Object {
public:
	MindAreaLinkInfo();
	virtual ~MindAreaLinkInfo() {};
	virtual const char *getClass() { return( "MindAreaLinkInfo" ); };

// operations
public:
	void createFromXml( Xml xml );
	bool isEnabled() { return( enabled ); };
	String getTypeName() { return( typeName ); };
	String getMasterAreaId() { return( masterAreaId ); };
	String getSlaveAreaId() { return( slaveAreaId ); };
	String getChannelId() { return( channelId ); };

	void setLinkType( MindLinkType *linkType );
	MindLinkType *getLinkType();

// data
public:
// utility
	bool enabled;
	String typeName;
	String masterAreaId;
	String slaveAreaId;
	String channelId;

// references
	MindLinkType *linkType;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaNetInfo : public Object {
public:
	MindAreaNetInfo();
	virtual ~MindAreaNetInfo();
	virtual const char *getClass() { return( "MindAreaNetInfo" ); };

// operations
public:
	void createFromXml( Xml xml );
	String getNetName();
	String getTransmitters();

	void setNetInfo( MindNetInfo *netInfo );
	MindNetInfo *getNetInfo();

// data
public:
// utility
	String netName;
	String transmitters;

// references
	MindNetInfo *netInfo;
};

/*#########################################################################*/
/*#########################################################################*/

class MindNetworkType : public Object {
public:
	virtual ~MindNetworkType() {};
	virtual const char *getClass() { return( "MindNetworkType" ); };

// operations
public:
	void createFromXml( Xml xml );
	String getName();

private:
// utilities
	String name;
};

/*#########################################################################*/
/*#########################################################################*/

class MindLinkType : public Object {
public:
	MindLinkType();
	virtual ~MindLinkType();
	virtual const char *getClass() { return( "MindLinkType" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getName() { return( name ); };
	int getNeuroLinkCount();
	NeuroLinkInfo *getNeuroLinkInfo( int pos );

private:
// utilities
	String name;

// own
	ClassList<NeuroLinkInfo> neuroLinkSet;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLink;

class NeuroLinkInfo : public Object {
public:
	NeuroLinkInfo( MindLinkType *linkType );
	virtual ~NeuroLinkInfo() {};
	virtual const char *getClass() { return( "NeuroLinkInfo" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getTypeName() { return( type ); };
	String getMasterEntity() { return( masterEntity ); };
	String getSlaveEntity() { return( slaveEntity ); };
	String getTransmitter() { return( transmitter ); };
	bool getForward() { return( forward ); };
	MindLinkType *getLinkType() { return( linkType ); };

	NeuroLink *createNeuroLink( MindRegionLink *regionLink );

// data
public:
// utility
	String type;
	String masterEntity;
	String slaveEntity;
	String transmitter;
	bool forward;

// references
	MindLinkType *linkType;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDMAP_H
