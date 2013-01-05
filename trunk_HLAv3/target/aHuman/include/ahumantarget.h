#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

class AHumanTarget;
class ScenarioPlayer;
class ModelVerifier;
class WikiMaker;

/*#########################################################################*/
/*#########################################################################*/

class MindRegionDef;
class XmlHMind;
class XmlCircuits;

/*#########################################################################*/
/*#########################################################################*/

class AHumanTarget : public MindTarget , public MessageSubscriber {
public:
	AHumanTarget();

	// target lifecycle
	virtual void configureTarget( Xml config );
	virtual void createTarget( SensorArea *sensorArea , EffectorArea *effectorArea );
	virtual void initSensorsTarget( SensorArea *sensorArea );
	virtual void initEffectorsTarget( EffectorArea *effectorArea );
	virtual void runTarget();
	virtual void stopTarget();
	virtual void exitTarget();
	virtual void destroyTarget();

protected:
	// commands
	void onXmlMessage( XmlMessage *msg );
	void cmdPlayCircuit( Xml scenario );
	void cmdVerifyModel( Xml modelArea );
	void cmdCreateWikiPages( Xml wiki );
};

/*#########################################################################*/
/*#########################################################################*/

class ScenarioPlayer : public Object {
public:
	ScenarioPlayer();
	virtual ~ScenarioPlayer();
	virtual const char *getClass() { return "ScenarioPlayer"; };

public:
	void play( Xml scenario );

private:
	void playSignal( Xml cmd );
};

/*#########################################################################*/
/*#########################################################################*/

class ModelVerifier : public Object {
public:
	ModelVerifier( Xml modelArea );
	virtual ~ModelVerifier();
	virtual const char *getClass() { return "ModelVerifier"; };

public:
	void verify();

private:
	void checkHierarchy();
	void checkCircuits();
	void checkMindModel();

	bool checkHierarchy_verifyChild( String node , bool checkMapping );
	bool checkCircuits_verifyComponents( String circuit );
	bool checkCircuits_verifyLinks( String circuit );
	bool checkCircuits_verifyCircuitLink( XmlCircuitInfo& circuit , XmlCircuitLinkInfo& link );
	bool checkMindModel_verifyRegion( MindRegionDef *regionDef );
	bool checkMindModel_verifyLinkedConnectors( MindRegionDef *regionDef , MindRegion *region );

private:
	Xml modelArea;
	XmlHMind hmindxml;
	XmlCircuits circuitsxml;

	MapStringToClass<MindRegionDef> regionMap;
	MapStringToClass<MindRegionDef> hierarchyMap;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiMaker : public Object {
public:
	WikiMaker( Xml wiki );
	virtual ~WikiMaker();
	virtual const char *getClass() { return "WikiMaker"; };

public:
	void createPages();

private:
	void updateHierarchyPage();
	void updateHierarchyPage_walkTree( String parentNode , int level , StringList& lines , MindArea *parentArea , MindRegion *parentRegion );
	void updateHierarchyPage_walkNeocortex( String neocortexDivision , String wikiDir , String wikiPage );
	void updateHierarchyPage_getNeocortexLobeLines( String neocortexLobe , StringList& lines );
	String updateHierarchyPage_getElementString( String node , MindArea *parentArea , MindRegion *parentRegion , MindArea *ownArea , MindRegion *ownRegion );
	MindArea *updateHierarchyPage_getArea( String node );
	MindRegion *updateHierarchyPage_getRegion( String node );
	String updateHierarchyPage_getNeocortexBrodmannLine( String neocortexDivision , String banum );
	void updateHierarchyPage_walkNeocortexBrodmannLine( String node , String banum , StringList& items );

	void createAreaPages();
	void createAreaPages_createRegionTableSection( String wikiDir , String wikiPage , MindAreaDef *areaDef );
	void createAreaPages_createCircuitsSection( String wikiDir , String wikiPage , MindAreaDef *areaDef );
	void createAreaPages_createReferencesSection( String wikiDir , String wikiPage , MindAreaDef *areaDef );
	String createAreaPages_getRegionTableRow( MindRegionDef *regionDef );
	String createAreaPages_getTableCellAttribute( XmlHMindElementInfo& info , String attribute , String value , bool required , int columnWidth );

	void createComponentPages();

	void updateFileSection( String wikiDir , String wikiPage , String section , StringList& lines );

private:
	Xml wiki;
	XmlHMind hmindxml;
};

/*#########################################################################*/
/*#########################################################################*/
