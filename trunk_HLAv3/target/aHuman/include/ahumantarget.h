#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

class AHumanTarget;
class MindModel;
class ScenarioPlayer;
class ModelVerifier;
class WikiMaker;
class WikiMainPage;
class WikiCircuitPages;
class WikiHierarchyPage;
class WikiAreaPages;

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

class MindModel : public Object {
public:
	MindModel();
	virtual ~MindModel();
	virtual const char *getClass() { return "MindModel"; };

public:
	void load();

	bool checkCircuitCoveredByModel( String compSrc , String compDst );
	bool checkCircuitCoveredByModelLink( String compSrc , String compDst , String linkRegionSrc , String linkRegionDst );

public:
	XmlHMind hmindxml;
	XmlCircuits circuitsxml;
};

/*#########################################################################*/
/*#########################################################################*/

class ScenarioPlayer : public MindModel {
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

class ModelVerifier : public MindModel {
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
	bool checkMindModel_verifyRegionCircuits( MindRegionDef *regionDef , MindRegion *region );

private:
	Xml modelArea;

	MapStringToClass<MindRegionDef> regionMap;
	MapStringToClass<MindRegionDef> hierarchyMap;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiMaker : public MindModel {
public:
	WikiMaker( Xml wiki );
	virtual ~WikiMaker();
	virtual const char *getClass() { return "WikiMaker"; };

public:
	void createPages();
	void updateFileHeading( String wikiDir , String wikiPage , StringList& lines );
	void updateFileSection( String wikiDir , String wikiPage , String section , StringList& lines );
	void createFileContent( String fileName , StringList& lines );
	String setSpecialCharacters( String data );
	String findReference( MindCircuitConnectionDef *link );

private:
	void createMainPage();
	void createCircuitPages();
	void updateHierarchyPage();
	void createAreaPages();
	void createComponentPages();

	bool findReferenceCircuitLink( MindCircuitConnectionDef *link , XmlCircuitInfo& info , String& circuitLink , bool directOnly );

public:
	Xml wiki;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiMainPage : public Object {
public:
	WikiMainPage( WikiMaker *wm );
	virtual ~WikiMainPage();
	virtual const char *getClass() { return "WikiMainPage"; };

public:
	void execute();

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiCircuitPages : public Object {
public:
	WikiCircuitPages( WikiMaker *wm );
	virtual ~WikiCircuitPages();
	virtual const char *getClass() { return "WikiMainPage"; };

public:
	void execute();

private:
	void createCircuitPage( String wikiDir , String wikiPage , MindCircuitDef *cd );
	void createCircuitPage_getHeading( String wikiPage , MindCircuitDef *cd , StringList& lines );
	void createCircuitPage_getLinkList( MindCircuitDef *cd , MapStringToClass<MindCircuitConnectionDef>& links );
	void createCircuitPage_getLinkSection( MindCircuitDef *cd , MapStringToClass<MindCircuitConnectionDef>& links , StringList& lines );
	void createCircuitPage_getLinksRow( MindCircuitDef *cd , MindCircuitConnectionDef *link , StringList& lines );
	void createCircuitPage_getDiagram( MindCircuitDef *cd , MapStringToClass<MindRegion>& nodes , MapStringToClass<MindCircuitConnectionDef>& links , StringList& lines );
	void createCircuitPage_getNodeList( MindCircuitDef *cd , MapStringToClass<MindRegion>& nodes );
	void createCircuitPage_getNodeSection( MindCircuitDef *cd , MapStringToClass<MindRegion>& nodes , StringList& lines );
	void createCircuitPage_getNodesRow( MindCircuitDef *cd , MindRegion *region , StringList& lines );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiHierarchyPage : public Object {
public:
	WikiHierarchyPage( WikiMaker *wm );
	virtual ~WikiHierarchyPage();
	virtual const char *getClass() { return "WikiHierarchyPage"; };

public:
	void execute();

private:
	void updateHierarchyPage_walkTree( String parentNode , int level , StringList& lines , MindArea *parentArea , MindRegion *parentRegion );
	void updateHierarchyPage_walkNeocortex( String neocortexDivision , String wikiDir , String wikiPage );
	void updateHierarchyPage_getNeocortexLobeLines( String neocortexLobe , StringList& lines );
	String updateHierarchyPage_getElementString( String node , MindArea *parentArea , MindRegion *parentRegion , MindArea *ownArea , MindRegion *ownRegion );
	MindArea *updateHierarchyPage_getArea( String node );
	MindRegion *updateHierarchyPage_getRegion( String node );
	String updateHierarchyPage_getNeocortexBrodmannLine( String neocortexDivision , String banum );
	void updateHierarchyPage_walkNeocortexBrodmannLine( String node , String banum , StringList& items );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiAreaPages : public Object {
public:
	WikiAreaPages( WikiMaker *wm );
	virtual ~WikiAreaPages();
	virtual const char *getClass() { return "WikiAreaPages"; };

public:
	void execute();

private:
	void createAreaPages_createRegionTableSection( String wikiDir , String wikiPage , MindAreaDef *areaDef );
	void createAreaPages_createConnectivityTableSection( String wikiDir , String wikiPage , MindAreaDef *areaDef );
	void createAreaPages_createCircuitsAndReferencesTableSection( String wikiDir , String wikiPage , MindAreaDef *areaDef );
	String createAreaPages_getCircuitKey( MindAreaDef *areaDef , XmlCircuitInfo& info );
	void createAreaPages_getCircuitLines( XmlCircuitInfo& info , StringList& lines );
	String createAreaPages_getRegionTableRow( MindRegionDef *regionDef );
	String createAreaPages_getTableCellAttribute( XmlHMindElementInfo& info , String attribute , String value , bool required , int columnWidth );
	void createAreaPages_getInternalConnections( MindAreaDef *areaDef , MapStringToClass<MindCircuitConnectionDef>& connections );
	void createAreaPages_getInternalConnectionTableLine( MindAreaDef *areaDef , MindCircuitConnectionDef *link , StringList& lines );
	void createAreaPages_getExternalConnections( MindAreaDef *areaDef , MapStringToClass<MindCircuitConnectionDef>& connections , bool isin );
	void createAreaPages_getExternalConnectionTableLine( MindAreaDef *areaDef , MindCircuitConnectionDef *link , StringList& lines , bool isin );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/
