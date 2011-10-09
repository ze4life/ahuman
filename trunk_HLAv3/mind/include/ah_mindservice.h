#ifndef	INCLUDE_AH_MINDSERVICE_H
#define INCLUDE_AH_MINDSERVICE_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindService;
class MindNet;
class MindNetSet;

/*#########################################################################*/
/*#########################################################################*/

class MindTarget;
class MindSensor;
class MindEffector;
class MindSpace;
class MindLocation;
class MindArea;
class MindAreaSet;
class MindAreaNet;
class MindRegion;
class MindRegionSet;
class MindMap;
class MindActiveMemory;
class MindAreaLink;
class MindAreaLinkSet;
class MindAreaLinkInfo;
class MindSensor;
class MindEffector;
class MindRegionLink;
class NeuroLink;
class NeuroPool;

// factory and lifecycle support for mind components
class MindService : public Service {
// interface
public:
	// let mind know about created core items
	void setMindTarget( MindTarget *target );
	void addMindArea( MindArea *area );
	void addMindRegion( MindRegion *region , String regionId , MindArea *area , MindLocation& areaLocation );
	void addNeuroLink( NeuroLink *link , NeuroPool *src , NeuroPool *dst );

	// get mind map, specific mind area, region, network
	MindActiveMemory *getActiveMemory();
	MindMap *getMindMap();
	MindArea *getMindArea( String areaId );
	MindRegion *getMindRegion( String regionId );
	MindNet *getMindNet( String net );
	  
	// create core items - regions
	MindRegion *createCortexRegion( MindArea *area );
	MindRegion *createNucleiRegion( MindArea *area );
	MindRegion *createNerveRegion( MindArea *area );

	// create core items - neurolinks
	NeuroLink *createExcitatoryLink( MindRegionLink *link );
	NeuroLink *createInhibitoryLink( MindRegionLink *link );
	NeuroLink *createModulatoryLink( MindRegionLink *link );

// whole mind lifecycle
public:
	virtual const char *getServiceName() { return( "MindService" ); };
	virtual void configureService( Xml config );
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void stopService();
	virtual void exitService();
	virtual void destroyService();

protected:
	MindService();
public:
	static Service *newService();
	static MindService *getService() { return( ( MindService * )ServiceManager::getInstance().getService( "MindService" ) ); };

// internals:
private:
	// create core items
	MindArea *createThalamusArea();
	MindArea *createPerceptionArea();
	MindArea *createHippocampusArea();
	MindArea *createParietalArea();
	MindArea *createPrefrontalCortexArea();
	MindArea *createBasalGangliaArea();
	MindArea *createBrainStemArea();
	MindArea *createCranialNerveArea();
	MindArea *createSpinalCordArea();
	MindArea *createMotorNerveArea();
	MindArea *createBodyFeelingNerveArea();

	// routines
	void createNetworks();
	void createAreas();
	void establishAreaLinks();

	void createArea( String areaId , MindArea *(MindService::*pfn)() );
	void addMindRegion( String regionId , MindRegion *region , const MindLocation& relativeLocation );
	void createMindAreaLink( MindArea *masterArea , MindArea *slaveArea , MindAreaLinkInfo *linkInfo );
	void createMindRegionLinks( MindAreaLink *link , MindNet *net , MindAreaNet *masterNet , MindAreaNet *slaveNet );
	void createMindRegionLink( MindAreaLink *link , MindNet *net , MindRegion *masterRegion , MindRegion *slaveRegion );

	// structure lock
	void lock() { rfc_hnd_semlock( lockStructure );	}
	void unlock() { rfc_hnd_semunlock( lockStructure );	}

private:
// utility
	RFC_HND lockStructure;
	Xml config;
	int areaIdSeq;
	int regionIdSeq;

// own data
	MindSpace *mindSpace;
	MindMap *mindMap;
	MindAreaSet *areaSet;
	MindAreaLinkSet *linkSet;
	MindActiveMemory *activeMemory;
	MindNetSet *netSet;

// references
	MindTarget *target;
	MindRegionSet *regionSet;
	MessageSession *session;
};

/*#########################################################################*/
/*#########################################################################*/

class MindNetInfo;

class MindNet : public Object {
public:
	MindNet();
	virtual ~MindNet();
	virtual const char *getClass() { return( "MindNet" ); };

public:
	void setInfo( MindNetInfo *p_info );
	MindNetInfo *getInfo();
	String getName();

public:
// utilities
	String name;

// references
	MindNetInfo *info;
};

/*#########################################################################*/
/*#########################################################################*/

class MindNetInfo;

class MindNetSet : public Object {
public:
	MindNetSet();
	virtual ~MindNetSet();
	virtual const char *getClass() { return( "MindNetSet" ); };

	MindNet *createMindNet( MindNetInfo *info );
	MindNet *getMindNet( String net );
	
private:
// own data
	ClassList<MindNet> list;

// references
	MapStringToClass<MindNet> map;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDSERVICE_H
