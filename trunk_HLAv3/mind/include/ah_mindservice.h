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
class MindRegion;
class MindRegionSet;
class MindMap;
class MindActiveMemory;
class MindAreaLink;
class MindAreaLinkSet;
class MindAreaLinkInfo;
class MindSensor;
class MindEffector;
class CortexRegion;
class NucleiRegion;
class NerveRegion;
class MindRegionLink;
class NeuroLink;
class NeuroPool;
class ExcitatoryLink;
class InhibitoryLink;
class ModulatoryLink;

// factory and lifecycle support for mind components
class MindService : public Service {
// interface
public:
	// let mind know about created core items
	void setMindTarget( MindTarget *target );
	void addMindArea( MindArea *area );
	void addMindRegion( MindRegion *region , String regionId , MindArea *area , MindLocation& areaLocation );
	void addNeuroLink( NeuroLink *link , NeuroPool *src , NeuroPool *dst );

	// get mind map, specific mind area, region
	MindMap *getMindMap();
	MindArea *getMindArea( String areaId );
	MindRegion *getMindRegion( String regionId );
	  
	// create core items - regions
	CortexRegion *createCortexRegion( MindArea *area );
	NucleiRegion *createNucleiRegion( MindArea *area );
	NerveRegion *createNerveRegion( MindArea *area );

	// create core items - neurolinks
	ExcitatoryLink *createExcitatoryLink( MindRegionLink *link );
	InhibitoryLink *createInhibitoryLink( MindRegionLink *link );
	ModulatoryLink *createModulatoryLink( MindRegionLink *link );

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
	// create core items - areas
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
	void createAreas();
	void establishAreaLinks();

	void createArea( String areaId , MindArea *(MindService::*pfn)() );
	MindAreaLink *createMindLink( MindAreaLinkInfo *linkInfo , MindArea *masterArea , MindArea *slaveArea );
	void addMindRegion( String regionId , MindRegion *region , const MindLocation& relativeLocation );

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

class MindNet : public Object {
public:
	MindNet();
	virtual ~MindNet();
	virtual const char *getClass() { return( "MindNet" ); };
};

/*#########################################################################*/
/*#########################################################################*/

class MindNetSet : public Object {
public:
	MindNetSet();
	virtual ~MindNetSet();
	virtual const char *getClass() { return( "MindNetSet" ); };

private:
// own data
	ClassList<MindNet> list;

// references
	MapStringToClass<MindNet> map;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDSERVICE_H
