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
class MindLink;
class MindLinkSet;
class MindLinkInfo;
class MindSensor;
class MindEffector;
class CortexRegion;
class NucleiRegion;
class NerveRegion;
class LayeredNet;
class CompactNet;
class SpreadNet;
class ExcitatoryLink;
class InhibitoryLink;
class ModulatoryLink;

// factory and lifecycle support for mind components
class MindService : public Service {
// interface
public:
	// add target-aligned sensor and effector regions
	void setTarget( MindTarget *target );
	void addSensorRegion( String regionId , MindArea *area , MindSensor *region , MindLocation& areaLocation );
	void addEffectorRegion( String regionId , MindArea *area , MindEffector *region , MindLocation& areaLocation );

	// get mind map, specific mind area, region
	MindMap *getMindMap();
	MindArea *getMindArea( String areaId );
	MindRegion *getMindRegion( String regionId );
	  
	// create core items - regions
	CortexRegion *createCortexRegion( String regionId , MindArea *area , MindLocation& areaLocation );
	NucleiRegion *createNucleiRegion( String regionId , MindArea *area , MindLocation& areaLocation );
	NerveRegion *createNerveRegion( String regionId , MindArea *area , MindLocation& areaLocation );

	// create core items - NeuroNet
	LayeredNet *createLayeredNet( MindRegion *region );
	CompactNet *createCompactNet( MindRegion *region );
	SpreadNet *createSpreadNet( MindRegion *region );

	// create core items - neurolinks
	ExcitatoryLink *createExcitatoryLink( MindRegion *regionSrc, MindRegion *regionDst );
	InhibitoryLink *createInhibitoryLink( MindRegion *regionSrc, MindRegion *regionDst );
	ModulatoryLink *createModulatoryLink( MindRegion *regionSrc, MindRegion *regionDst );

	// create core items - areas
	MindArea *createThalamusArea();
	MindArea *createSensoryArea();
	MindArea *createHippocampusArea();
	MindArea *createParietalArea();
	MindArea *createLateralPrefrontalCortexArea();
	MindArea *createOrbitoMedialPrefrontalCortexArea();
	MindArea *createBasalGangliaArea();
	MindArea *createBrainStemArea();
	MindArea *createCranialNerveArea();
	MindArea *createSpinalCordArea();
	MindArea *createMotorNerveArea ();
	MindArea *createBodyFeelingNerveArea();

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
	void addMindArea( String areaId , MindArea *area );
	MindLink *createMindLink( MindLinkInfo *linkInfo , MindArea *masterArea , MindArea *slaveArea );
	void addMindRegion( String regionId , MindRegion *region , const MindLocation& relativeLocation );

	// structure lock
	void lock() { rfc_hnd_semlock( lockStructure );	}
	void unlock() { rfc_hnd_semunlock( lockStructure );	}

private:
	Xml config;
	RFC_HND lockStructure;

	MindMap *mindMap;
	MindSpace *mindSpace;

	MindAreaSet *areaSet;
	MindRegionSet *regionSet;
	MindLinkSet *linkSet;
	MindActiveMemory *activeMemory;

	MessageSession *ioBrainSession;
	int areaIdSeq;
	int regionIdSeq;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDSERVICE_H
