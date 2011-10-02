#ifndef	INCLUDE_AH_MINDSPACE_H
#define INCLUDE_AH_MINDSPACE_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindSpace;
class MindLocation;
class MindMap;
class MindNetInfo;
class MindAreaInfo;
class MindAreaLinkInfo;
class MindNetworkType;

/*#########################################################################*/
/*#########################################################################*/

// every mind area and cortex have exact location in brain 3D space
// location is parallelogramm, centered in given absolute point, and having X, Y, Z dimentions
// brain has no limits
// mind area has pre-configured location in brain space
// inter-area connections between neurons are established within specific mind link, all mind links are pre-configured
// inter-cortex connections between neurons are established within specific cortex link, all cortex links are dynamic
// connections evolve all the time
// probability of establishing inter-area and inter-cortex connections depends on distance between neurons
// to diminish rough shapes of mind areas and cortexes, distances are adjusted by factor equal to distance between cortex/area centers
// brain controls that areas/cortexes do not overlap
class MindLocation : public Object {
public:
	MindLocation() {
		x = y = z = 0;
		dx = dy = dz = 0;
	};
	virtual const char *getClass() { return( "MindLocation" ); };

	void setPosition( int p_x , int p_y , int p_z ) { x = p_x; y = p_y; z = p_z; };
	void setDimensions( int p_dx , int p_dy , int p_dz ) { dx = p_dx; dy = p_dy; dz = p_dz; };
	int getSize() const { return( dx * dy * dz ); };

	// relative is counted from lower corner
	MindLocation getAbsoluteLocation( const MindLocation& relativeLocation ) const;
	MindLocation getRelativeLocation( const MindLocation& absoluteLocation ) const;
	bool placeLocation( MindLocation& cover , MindLocation& add ) const;
	void getCenter( int& cx , int& cy , int& cz ) const;
	void movePosition( int cx , int cy , int cz );
	void resize( int cx , int cy , int cz );
	void setSurfaceDimensions( int d1 , int d2 );
	void center( const MindLocation& parent );
	void moveInside( MindLocation& relativePosition ) const;

	// get inputs/outputs surface
	int getSurfaceSize() const;

private:
	bool placeLocationFirst( MindLocation& cover , MindLocation& add ) const;

private:
// utility
	// lower corner position (relative to parent)
	int x;
	int y;
	int z;

	// dimensions
	int dx;
	int dy;
	int dz;
};

/*#########################################################################*/
/*#########################################################################*/

class MindSpace : public Object {
public:
	MindSpace();
	~MindSpace() {};
	virtual const char *getClass() { return( "MindSpace" ); };

// operations
public:
	void createFromXml( Xml xml );
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

class MindNetworkType : public Object {
public:
	virtual const char *getClass() { return( "MindNetworkType" ); };

// operations
public:
	void createFromXml( Xml xml );
	String getName();

private:
	String name;
};

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

#endif // INCLUDE_AH_MINDSPACE_H
