#ifndef	INCLUDE_AH_MINDSERVICE_H
#define INCLUDE_AH_MINDSERVICE_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindService;

/*#########################################################################*/
/*#########################################################################*/

class MindTarget;
class MindSensor;
class MindEffector;
class MindSpace;
class MindLocation;
class MindArea;
class MindAreaSet;
class MindRegion;
class MindRegionSet;
class MindMap;
class MindActiveMemory;
class MindAreaLink;
class MindAreaLinkSet;
class MindSensor;
class MindEffector;
class MindRegionLink;
class NeuroLink;
class NeuroPool;
class MindAreaDef;
class CortexRegionInfo;
class NucleiRegionInfo;
class NerveRegionInfo;

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
	  
	// create core items - regions
	MindRegion *createCortexRegion( MindArea *area , String id , CortexRegionInfo *info );
	MindRegion *createNucleiRegion( MindArea *area , String id , NucleiRegionInfo *info );
	MindRegion *createNerveRegion( MindArea *area , String id , NerveRegionInfo *info );

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
	// routines
	void createAreas();
	void establishAreaLinks();

	void createArea( MindAreaDef *areaInfo );
	void addMindRegion( String regionId , MindRegion *region , const MindLocation& relativeLocation );
	void createMindAreaLink( MindArea *masterArea , MindArea *slaveArea );

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

// references
	MindTarget *target;
	MindRegionSet *regionSet;
	MessageSession *session;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDSERVICE_H
