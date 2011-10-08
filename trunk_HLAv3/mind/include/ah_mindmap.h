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
class NeuroLinkInfo;

/*#########################################################################*/
/*#########################################################################*/

// set of mind areas is a mind map
// topology of mind map is pre-defined , including size and inter-area connections
// mind map is defined statically (at least until invention of artificial genetics), in configuration files
class MindMap : public Object {
public:
	MindMap() {};
	~MindMap();
	virtual const char *getClass() { return( "MindMap" ); };

// operations
public:
	void createFromXml( Xml xml );

	ClassList<MindNetInfo>& getMindNets() { return( mindNets ); };
	ClassList<MindAreaInfo>& getMindAreas() { return( mindAreas ); };
	ClassList<MindAreaLinkInfo>& getLinks() { return( mindLinks ); }
	MindNetInfo *getNetByName( String netName );
	MindAreaInfo *getAreaById( String areaId );
	MindNetworkType *getNetTypeByName( String typeName );

private:
	void createAreaSet( Xml xml );
	void createMindLinkSet( Xml xml );
	void createNetworkTypeSet( Xml xml );
	void createNetworkSet( Xml xml );

private:
// own data
	ClassList<MindNetInfo> mindNets;
	ClassList<MindAreaInfo> mindAreas;
	ClassList<MindAreaLinkInfo> mindLinks;
	ClassList<MindNetworkType> netTypes;

// references
	MapStringToClass<MindNetInfo> mindNetMap;
	MapStringToClass<MindAreaInfo> mindAreaMap;
	MapStringToClass<MindNetworkType> netTypeMap;
};

/*#########################################################################*/
/*#########################################################################*/

class MindNetInfo : public Object {
public:
	MindNetInfo();
	~MindNetInfo();
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
	~MindAreaInfo();
	virtual const char *getClass() { return( "MindAreaInfo" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getAreaId() { return( areaId ); };
	bool runEnabled();

	const MindLocation& getLocation() { return( location ); };
	const ClassList<MindAreaLinkInfo>& getLinks() { return( links ); };
	void addLink( MindAreaLinkInfo *link ) { links.add( link );	};

private:
// utility
	String areaId;
	bool enabled;
	StringList transmitters;

// own data
	MindLocation location;

// references
	ClassList<MindAreaNetInfo> netInfoSet;
	ClassList<MindAreaLinkInfo> links;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaLinkInfo : public Object {
public:
	MindAreaLinkInfo();
	~MindAreaLinkInfo() {};
	virtual const char *getClass() { return( "MindAreaLinkInfo" ); };

// operations
public:
	void createFromXml( Xml xml );
	String getMasterAreaId() { return( masterAreaId ); };
	String getSlaveAreaId() { return( slaveAreaId ); };
	String getChannelId() { return( channelId ); };

// data
public:
// utility
	String masterAreaId;
	String slaveAreaId;
	String channelId;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaNetInfo : public Object {
public:
	MindAreaNetInfo();
	~MindAreaNetInfo();
	virtual const char *getClass() { return( "MindAreaNetInfo" ); };

// operations
public:
	void createFromXml( Xml xml );
	String getName();
	void setNetInfo( MindNetInfo *netInfo );
	MindNetInfo *getNetInfo();

// data
public:
// utility
	String netName;
	MindNetInfo *netInfo;
};

/*#########################################################################*/
/*#########################################################################*/

class MindNetworkType : public Object {
public:
	virtual const char *getClass() { return( "MindNetworkType" ); };

// operations
public:
	void createFromXml( Xml xml );
	String getName();
	int getNeuroLinkCount();
	NeuroLinkInfo *getNeuroLinkInfo( int pos );

private:
// utilities
	String name;

// own
	ClassList<NeuroLinkInfo> neuroLinks;

// references
	MapStringToClass<NeuroLinkInfo> neuroLinkMap;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLink;

class NeuroLinkInfo : public Object {
public:
	NeuroLinkInfo( MindNetworkType *netType );
	~NeuroLinkInfo() {};
	virtual const char *getClass() { return( "NeuroLinkInfo" ); };

// operations
public:
	void createFromXml( Xml xml );

	String getName() { return( name ); };
	String getType() { return( type ); };
	String getTransmitter() { return( transmitter ); };
	bool getForward() { return( forward ); };

	NeuroLink *createNeuroLink( MindRegionLink *regionLink );

// data
public:
// utility
	String name;
	String type;
	String transmitter;
	bool forward;

// references
	MindNetworkType *netType;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDMAP_H
