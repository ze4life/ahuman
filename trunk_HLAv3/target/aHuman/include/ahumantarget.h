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
	virtual void initTarget();
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

private:
	MindSensor *createEye( SensorArea *sensorArea );
	MindSensor *createEar( SensorArea *sensorArea );
	MindSensor *createNose( SensorArea *sensorArea );
	MindSensor *createMindCover( SensorArea *sensorArea );
	MindEffector *createHeart( EffectorArea *area );
	MindEffector *createMouth( EffectorArea *area );
	MindEffector *createFace( EffectorArea *area );
	MindEffector *createNeck( EffectorArea *area );
	MindEffector *createLung( EffectorArea *area );
	MindEffector *createLiver( EffectorArea *area );
	MindEffector *createStomach( EffectorArea *area );
	MindEffector *createHand( EffectorArea *area );
	MindEffector *createTrunk( EffectorArea *area );
	MindEffector *createBreast( EffectorArea *area );
	MindEffector *createUreter( EffectorArea *area );
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

	bool checkLinkCoveredByModel( String compSrc , String compDst );

public:
	XmlHMind hmindxml;
	XmlCircuits circuitsxml;
	XmlNerves nervesxml;
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
	void checkNerves();
	void checkMindModel();

	bool checkHierarchy_verifyChild( String node , bool checkMapping );
	bool checkCircuits_verifyComponents( String circuit );
	bool checkCircuits_verifyLinks( String circuit );
	bool checkCircuits_verifyCircuitLink( XmlCircuitInfo& circuit , XmlCircuitLinkInfo& link );
	bool checkNerves_verifyComponents( String nerve );
	bool checkNerves_verifyLinks( XmlNerveInfo& info , XmlNerveFiberInfo& nf );
	bool checkNerves_verifyFiberChain( XmlNerveInfo& info , String regionSrcId , String regionDstId );
	bool checkFiberComp( XmlNerveInfo& info , XmlNerveFiberInfo& nf , String comp );
	bool checkFiberType( XmlNerveInfo& info , XmlNerveFiberInfo& nf , String type );
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
	String findReference( MindRegionLink *link );
	String findReference( MindCircuitConnectionDef *link );
	String findReference( String srcRegion , String dstRegion );
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

public:
	Xml wiki;
	String saveRepeats1;
	String saveRepeats2;
	MapStringToString referenceMap;
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
	void createAreaPages_createRegionTableSection( String wikiDir , MindArea *area );
	void createAreaPages_createConnectivityTableSection( String wikiDir , MindArea *area );
	void createAreaPages_createCircuitsAndReferencesTableSection( String wikiDir , MindArea *area );
	void createAreaPages_createRegionPages( String wikiDir , MindArea *area );
	void createAreaPages_addExternalConnections( MindArea *area , StringList& lines , MapStringToClass<MindRegionLink>& connections , bool p_inputs );
	String createAreaPages_getCircuitKey( MindArea *area , XmlCircuitInfo& info );
	void createAreaPages_getCircuitLines( XmlCircuitInfo& info , StringList& lines );
	String createAreaPages_getRegionTableRow( MindRegion *region );
	String createAreaPages_getTableCellAttribute( const XmlHMindElementInfo& info , String attribute , String value , bool required , int columnWidth );
	void createAreaPages_getInternalConnections( MindArea *area , MapStringToClass<MindRegionLink>& connections );
	void createAreaPages_getInternalConnectionTableLine( MindArea *area , MindRegionLink *link , StringList& lines );
	void createAreaPages_getExternalConnections( MindArea *area , MapStringToClass<MindRegionLink>& connections , bool isin );
	void createAreaPages_getExternalConnectionTableLine( MindArea *area , MindRegionLink *link , StringList& lines , bool isin , const char *areaType );
	void createDotFile( MindArea *area , MapStringToClass<MindRegionLink>& internals , MapStringToClass<MindRegionLink>& inputs , MapStringToClass<MindRegionLink>& outputs );
	void createDotFile_subgraph( MindArea *area , bool p_inputs , MapStringToClass<MindRegionLink>& connections , StringList& text , String& linkItem );
	String createDotFile_getRegionLabel( MindRegion *region , MapStringToClass<MindRegionLink>& inputs , MapStringToClass<MindRegionLink>& outputs );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiRegionPage : public Object {
public:
	WikiRegionPage( WikiMaker *wm , String wikiDir , MindRegion *region );
	virtual ~WikiRegionPage();
	virtual const char *getClass() { return "WikiRegionPage"; };

public:
	void execute();

private:
	void createHeading();

	void createChildTableSection();
	void createChildTableSection_addChilds( Xml node , String prefix , StringList& lines );

	void createConnectivitySection();
	void createConnectivitySection_getExternalConnections( MapStringToClass<MindRegionLink>& connections , bool isin );
	void createConnectivitySection_getExternalConnectionTableLine( MindRegionLink *link , StringList& lines , bool isin );
	void createDotFile( MapStringToClass<MindRegion>& regions , MapStringToClass<MindRegionLink>& connectionsTotal );

	void createThirdpartyAndReferencesSection();
	String createThirdpartyAndReferencesSection_getCircuitKey( MindRegion *region , XmlCircuitInfo& info );
	void createThirdpartyAndReferencesSection_getCircuitLines( XmlCircuitInfo& info , StringList& lines );

private:
	WikiMaker *wm;
	String wikiDir;
	MindRegion *region;
	const XmlHMindElementInfo& info;
};

/*#########################################################################*/
/*#########################################################################*/
