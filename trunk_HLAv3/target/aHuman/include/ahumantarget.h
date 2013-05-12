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
	void ensureFileExists( String wikiDir , String wikiPage , StringList& sections );
	void updateFileHeading( String wikiDir , String wikiPage , StringList& lines );
	void updateFileSection( String wikiDir , String wikiPage , String section , StringList& lines );
	void createFileContent( String fileName , StringList& lines );
	String setSpecialCharacters( String data );
	String findReference( MindCircuitConnectionDef *link );
	String getDotColor( String dotdef );

	String getAreaPage( String area );
	String getRegionPage( String region );
	String getAreaReference( String area );
	String getRegionReference( String region );

	void clearRepeats1( String& value1 );
	void clearRepeats2( String& value1 , String& value2 );

private:
	void createMainPage();
	void createCircuitPages();
	void updateHierarchyPage();
	void createAreaPages();
	void createComponentPages();

	bool findReferenceCircuitLink( MindCircuitConnectionDef *link , XmlCircuitInfo& info , String& circuitLink , bool directOnly );

public:
	Xml wiki;
	String saveRepeats1;
	String saveRepeats2;
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
	void createAreaPages_createRegionTableSection( String wikiDir , MindAreaDef *areaDef );
	void createAreaPages_createConnectivityTableSection( String wikiDir , MindAreaDef *areaDef );
	void createAreaPages_createCircuitsAndReferencesTableSection( String wikiDir , MindAreaDef *areaDef );
	void createAreaPages_createRegionPages( String wikiDir , MindAreaDef *areaDef );
	void createAreaPages_addExternalConnections( MindAreaDef *areaDef , StringList& lines , MapStringToClass<MindCircuitConnectionDef>& connections , bool p_inputs );
	String createAreaPages_getCircuitKey( MindAreaDef *areaDef , XmlCircuitInfo& info );
	void createAreaPages_getCircuitLines( XmlCircuitInfo& info , StringList& lines );
	String createAreaPages_getRegionTableRow( MindRegionDef *regionDef );
	String createAreaPages_getTableCellAttribute( const XmlHMindElementInfo& info , String attribute , String value , bool required , int columnWidth );
	void createAreaPages_getInternalConnections( MindAreaDef *areaDef , MapStringToClass<MindCircuitConnectionDef>& connections );
	void createAreaPages_getInternalConnectionTableLine( MindAreaDef *areaDef , MindCircuitConnectionDef *link , StringList& lines );
	void createAreaPages_getExternalConnections( MindAreaDef *areaDef , MapStringToClass<MindCircuitConnectionDef>& connections , bool isin );
	void createAreaPages_getExternalConnectionTableLine( MindAreaDef *areaDef , MindCircuitConnectionDef *link , StringList& lines , bool isin , const char *areaType );
	void createDotFile( MindAreaDef *areaDef , MapStringToClass<MindCircuitConnectionDef>& internals , MapStringToClass<MindCircuitConnectionDef>& inputs , MapStringToClass<MindCircuitConnectionDef>& outputs );
	void createDotFile_subgraph( MindAreaDef *areaDef , bool p_inputs , MapStringToClass<MindCircuitConnectionDef>& connections , StringList& text , String& linkItem );
	String createDotFile_getRegionLabel( MindRegionDef *region , MapStringToClass<MindCircuitConnectionDef>& inputs , MapStringToClass<MindCircuitConnectionDef>& outputs );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiRegionPage : public Object {
public:
	WikiRegionPage( WikiMaker *wm , String wikiDir , MindRegionDef *region );
	virtual ~WikiRegionPage();
	virtual const char *getClass() { return "WikiRegionPage"; };

public:
	void execute();

private:
	void createHeading();

	void createChildTableSection();
	void createChildTableSection_addChilds( Xml node , String prefix , StringList& lines );

	void createConnectivitySection();
	void createConnectivitySection_getExternalConnections( MapStringToClass<MindCircuitConnectionDef>& connections , bool isin );
	void createConnectivitySection_getExternalConnectionTableLine( MindCircuitConnectionDef *link , StringList& lines , bool isin );
	void createDotFile( MapStringToClass<MindRegion>& regions , MapStringToClass<MindCircuitConnectionDef>& connectionsTotal );

	void createThirdpartyAndReferencesSection();
	String createThirdpartyAndReferencesSection_getCircuitKey( MindAreaDef *areaDef , XmlCircuitInfo& info );
	void createThirdpartyAndReferencesSection_getCircuitLines( XmlCircuitInfo& info , StringList& lines );

private:
	WikiMaker *wm;
	String wikiDir;
	MindRegionDef *region;
	const XmlHMindElementInfo& info;
};

/*#########################################################################*/
/*#########################################################################*/
