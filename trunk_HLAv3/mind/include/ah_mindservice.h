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
class MindCircuitDef;
class MindCircuitConnectionDef;
class MindConnectionTypeDef;
class MindConnectionLinkTypeDef;
class MindRegionInfo;
class NeuroLinkSource;
class NeuroLinkTarget;
class NeuroLinkInfo;

// factory and lifecycle support for mind components
class MindService : public Service {
// interface
public:
	void setMindTarget( MindTarget *target );

	// get mind map, specific mind area, region, network
	MindActiveMemory *getActiveMemory();
	MindMap *getMindMap();
	MindArea *getMindArea( String areaId );
	MindRegion *getMindRegion( String regionId );
	bool isMindRegion( String regionId );
	  
	// create core items
	MindRegion *createRegion( String implementation , String type , MindArea *area , MindRegionInfo *info );
	NeuroLink *createNeuroLink( String implementation , String type , NeuroLinkSource *src , NeuroLinkTarget *dst , NeuroLinkInfo *info );

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
	void createAreas();
	void createArea( MindAreaDef *areaInfo );
	void establishAreaLinks();
	void addCircuitLinks( MindCircuitDef *circuitDef );
	void addCircuitConnection( MindCircuitDef *circuitDef , MindCircuitConnectionDef *connectionDef );
	void createRegionConnection( MindConnectionTypeDef *connectionType , MindRegion *srcRegion , MindRegion *dstRegion );
	NeuroLink *createNeuroLink( MindConnectionLinkTypeDef *linkDef , MindRegion *srcRegion , MindRegion *dstRegion );
	MindRegionLink *createRegionLink( MindRegion *srcRegion , MindRegion *dstRegion );
	MindAreaLink *createAreaLink( MindArea *masterArea , MindArea *slaveArea );

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
	MapStringToClass<MindConnectionTypeDef> regionConnectionMap;
	MapStringToClass<NeuroLink> regionNeuroLinkMap;
	MapStringToClass<MindAreaLink> areaLinkMap;
	MapStringToClass<MindRegionLink> regionLinkMap;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDSERVICE_H
