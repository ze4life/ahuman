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
class MindAreaLinkInfo;
class MindSensor;
class MindEffector;
class CortexRegion;
class NucleiRegion;
class NerveRegion;
class NeuroNet;
class LayeredNet;
class CompactNet;
class SpreadNet;
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
	void addNeuroNet( NeuroNet *net , MindRegion *region );
	void addNeuroLink( NeuroLink *link , NeuroPool *src , NeuroPool *dst );

	// get mind map, specific mind area, region
	MindMap *getMindMap();
	MindArea *getMindArea( String areaId );
	MindRegion *getMindRegion( String regionId );
	  
	// create core items - regions
	CortexRegion *createCortexRegion();
	NucleiRegion *createNucleiRegion();
	NerveRegion *createNerveRegion();

	// create core items - NeuroNet
	LayeredNet *createLayeredNet();
	CompactNet *createCompactNet();
	SpreadNet *createSpreadNet();

	// create core items - neurolinks
	ExcitatoryLink *createExcitatoryLink();
	InhibitoryLink *createInhibitoryLink();
	ModulatoryLink *createModulatoryLink();

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
	RFC_HND lockStructure;
	Xml config;

	MindTarget *target;
	MindSpace *mindSpace;
	MindMap *mindMap;

	MindAreaSet *areaSet;
	MindRegionSet *regionSet;
	MindAreaLinkSet *linkSet;
	MindActiveMemory *activeMemory;

	MessageSession *session;
	int areaIdSeq;
	int regionIdSeq;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDSERVICE_H
