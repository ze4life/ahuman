#include "stdafx.h"
#include "xmlhuman.h"
#include "ahumanmodel.h"

/*#########################################################################*/
/*#########################################################################*/

class WikiMaker;
class WikiMainPage;
class WikiCircuitPages;
class WikiHierarchyPage;
class WikiAreaPages;
class WikiRegionPage;
class WikiNerveMainPage;
class WikiNerveSpecPages;
class WikiMuscleMainPage;
class WikiMuscleSpecPages;
class WikiSpinalCordPage;
class WikiCategoryPage;
class WikiTractsPages;

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
	String findReference( MindLocalCircuitConnectionDef *link );
	String findReference( String srcRegion , String dstRegion );
	String getDotColor( String dotdef );

	bool checkCreateMainPages();
	bool checkCreateNervePages();
	bool checkCreateMusclePages();
	bool checkCreateOverallHierarchyPage();
	bool checkCreateCircuitPages();
	bool checkCreateRegionPages();
	bool checkCreateAreaPages();

	String getWikiPath();
	String getWikiImagePath();
	String getWikiDotPath();

	String getDefaultDotSetup();
	String getDefaultDotRegionSetup();

	String getMainPage();
	String getOverallHierarchyPage();
	String getSpinalCordPage();
	String getSpinalCordPageLayoutSection();
	String getMainTractPage();
	String getMainTractLocationSection();
	String getMainTractPageListSection();
	String getMainTractPageNeuronsSection();
	String getMainNervePage();
	String getMainNervePageListSection();
	String getMainMusclePage();
	String getMainMusclePageListSection();

	String getPeripheralPage();
	String getCategoryPageRegionSection();
	String getCategoryPageSensoryLinkSection();
	String getCategoryPageMotorLinkSection();
	String getCategoryPageReciprocalLinkSection();
	String getCategoryPageGangliaLinkSection();

	String getSelectedArea();

	String getAreaPage( String area );
	String getRegionPage( String region );
	String getAreaReference( String area );
	String getRegionReference( String region );
	String getComponentReference( String comp );
	String getAvailableReference( String comp );

	const XmlHMindElementInfo& getComponentReferenceInfo( String comp );
	String getMuscleReference( String name , String text );
	String getImageWikiLink( String imgsrc , String height );
	String getWikiLink( String link , String text );
	String getWikiBold( String text );
	String getTableCellAttribute( const char *id , const char *attribute , String value , bool required , int columnWidth );
	String getCircuitDotPath( MindLocalCircuitDef& circuit );
	String getCircuitImageRef( MindLocalCircuitDef& circuit );

	void clearRepeats1( String& value1 );
	void clearRepeats2( String& value1 , String& value2 );

	String getNerveWikiPage( String nerve );
	String getTractPageLink( String tractSetId );

private:
	void createMainPage();
	void createCircuitPages();
	void updateHierarchyPage();
	void createAreaPages();
	void createNervePages();
	void createMusclePages();
	void createSpinalCordPage();
	void createPeripheralPage();
	void createTractsPages();

private:
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
	void createCircuitPage( String wikiDir , String wikiPage , MindGlobalCircuitDef *cd );
	void createCircuitPage_getHeading( String wikiPage , MindGlobalCircuitDef *cd , StringList& lines );
	void createCircuitPage_getLinkList( MindGlobalCircuitDef *cd , MapStringToClass<MindLocalCircuitConnectionDef>& links );
	void createCircuitPage_getLinkSection( MindGlobalCircuitDef *cd , MapStringToClass<MindLocalCircuitConnectionDef>& links , StringList& lines );
	void createCircuitPage_getLinksRow( MindGlobalCircuitDef *cd , MindLocalCircuitConnectionDef *link , StringList& lines );
	void createCircuitPage_getDiagram( MindGlobalCircuitDef *cd , MapStringToClass<MindRegion>& nodes , MapStringToClass<MindLocalCircuitConnectionDef>& links , StringList& lines );
	void createCircuitPage_getNodeList( MindGlobalCircuitDef *cd , MapStringToClass<MindRegion>& nodes );
	void createCircuitPage_getNodeSection( MindGlobalCircuitDef *cd , MapStringToClass<MindRegion>& nodes , StringList& lines );
	void createCircuitPage_getNodesRow( MindGlobalCircuitDef *cd , MindRegion *region , StringList& lines );

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
	void createAreaPages_createArea( String wikiDir , MindArea *area );
	void createAreaPages_createCircuitsAndReferencesTableSection( String wikiDir , MindArea *area );
	String createAreaPages_getCircuitKey( MindArea *area , XmlCircuitInfo& info );
	void createAreaPages_getCircuitLines( XmlCircuitInfo& info , StringList& lines );
	void createAreaPages_createRegionPages( String wikiDir , MindArea *area );

	void createAreaPages_createAreaCircuit( MindArea *area , MindLocalCircuitDef& circuit , StringList& lines );

	void createAreaPages_createRegionTableSection( MindArea *area , MindLocalCircuitDef& circuit , StringList& lines );
	void createAreaPages_createConnectivityTableSection( MindArea *area , MindLocalCircuitDef& circuit , StringList& lines );
	String createAreaPages_getRegionTableRow( MindRegionDef *region );

	void createAreaPages_getInternalConnections( MindArea *area , MindLocalCircuitDef& circuit , MapStringToClass<MindLocalCircuitConnectionDef>& connections );
	void createAreaPages_addExternalConnections( MindArea *area , MindLocalCircuitDef& circuit , StringList& lines , MapStringToClass<MindLocalCircuitConnectionDef>& connections , bool p_inputs );
	void createAreaPages_getInternalConnectionTableLine( MindArea *area , MindLocalCircuitDef& circuit , MindLocalCircuitConnectionDef *link , StringList& lines );
	void createAreaPages_getExternalConnections( MindArea *area , MindLocalCircuitDef& circuit , MapStringToClass<MindLocalCircuitConnectionDef>& connections , bool isin );
	void createAreaPages_getExternalConnectionTableLine( MindArea *area , MindLocalCircuitDef& circuit , MindLocalCircuitConnectionDef *link , StringList& lines , bool isin , const char *areaType );
	void createDotFile( MindArea *area , MindLocalCircuitDef& circuit , MapStringToClass<MindLocalCircuitConnectionDef>& internals , MapStringToClass<MindLocalCircuitConnectionDef>& inputs , MapStringToClass<MindLocalCircuitConnectionDef>& outputs );
	void createDotFile_subgraph( MindArea *area , MindLocalCircuitDef& circuit , bool p_inputs , MapStringToClass<MindLocalCircuitConnectionDef>& connections , StringList& text , String& linkItem );
	String createDotFile_getRegionLabel( MindRegionDef *region );
	String getRegionColor( String regionId );

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
	String createChildTableSection_getChildDetails( Xml node );
	String createChildTableSection_getChildNameItem( Xml node );
	String createChildTableSection_getChildIdItem( Xml node );

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

class WikiNerveMainPage : public Object {
public:
	WikiNerveMainPage( WikiMaker *wm );
	virtual ~WikiNerveMainPage();
	virtual const char *getClass() { return "WikiNerveMainPage"; };

public:
	void execute();

private:
	void addNerve( int level , XmlNerveInfo& nerve , StringList& lines );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiNerveSpecPages : public Object {
public:
	WikiNerveSpecPages( WikiMaker *wm );
	virtual ~WikiNerveSpecPages();
	virtual const char *getClass() { return "WikiNerveSpecPages"; };

public:
	void execute();

private:
	void addNerveDivision( XmlNerveInfo& div );
	void addNerveList( int level , XmlNerveInfo& div , StringList& lines );
	String getNerveDivision_fibers( ClassList<XmlNerveFiberInfo>& fibers );
	String getNerveDivision_rootNerves( StringList rootNerves );
	String getNerveDivision_fiberchain( XmlNerveFiberInfo& fiber );
	String getNerveDivision_muscles( String name );
	void addNucleiGroup( XmlNerveInfo& div , String group , StringList& nuclei , StringList& lines );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiMuscleMainPage : public Object {
public:
	WikiMuscleMainPage( WikiMaker *wm );
	virtual ~WikiMuscleMainPage();
	virtual const char *getClass() { return "WikiMuscleMainPage"; };

public:
	void execute();

private:
	void addMuscles( int level , XmlMuscleDivision& div , MapStringToClass<XmlMuscleInfo>& items , StringList& lines );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiMuscleSpecPages : public Object {
public:
	WikiMuscleSpecPages( WikiMaker *wm );
	virtual ~WikiMuscleSpecPages();
	virtual const char *getClass() { return "WikiMuscleSpecPages"; };

public:
	void execute();

private:
	void addMuscleDivision( XmlMuscleDivision& div );
	void addMuscleList( int level , XmlMuscleInfo& muscle , StringList& lines );
	String getNerveList( XmlMuscleInfo& muscle );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiCategoryPage : public Object {
public:
	WikiCategoryPage( WikiMaker *wm );
	virtual ~WikiCategoryPage();
	virtual const char *getClass() { return "WikiCategoryPage"; };

public:
	void execute( String category , String wikiPage );

private:
	void createRegions( XmlBrainCategory *braincategory , String page );
	void createConnectivity( XmlBrainCategory *braincategory , String page );
	void createConnectivity_extractNuclei( MapStringToClass<XmlHMindElementInfo>& spinalitems , XmlBrainTractPath& path , MapStringToClass<StringList>& sensoryNuclei , MapStringToClass<StringList>& motorNuclei , MapStringToClass<StringList>& ganglia );
	void createConnectivity_fillSection( String page , String sectionName , MapStringToClass<StringList>& nuclei );
	void createConnectivity_fillSectionTree( MapStringToClass<StringList>& nuclei , int level , XmlHMindElementInfo& item , MapStringToClass<XmlHMindElementInfo>& subtree , StringList& lines );
	void createConnectivity_addTract( MapStringToClass<StringList>& map , XmlHMindElementInfo& comp , XmlBrainTractPath& path );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiSpinalCordPage : public Object {
public:
	WikiSpinalCordPage( WikiMaker *wm );
	virtual ~WikiSpinalCordPage();
	virtual const char *getClass() { return "WikiSpinalCordPage"; };

public:
	void execute();

private:
	void createLayout();

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/

class WikiTractsPages : public Object {
public:
	WikiTractsPages( WikiMaker *wm );
	virtual ~WikiTractsPages();
	virtual const char *getClass() { return "WikiTractsPages"; };

public:
	void execute();

private:
	void createNeurons();
	void createNeurons_addEndings( XmlBrainEndingSet& set , StringList& lines );
	void createNeurons_addEndingItem( int level , XmlBrainEnding& item , StringList& lines );
	void createNeurons_addFibers( int level , MapStringToClass<XmlBrainFiber>& fibers , StringList& lines );
	void createNeurons_addFiberInfo( int level , XmlBrainFiber& fiber , StringList& lines );

	void createTractsMain();
	void createTracts_addTractSetLinks( XmlBrainTractSet& ts , StringList& lines );
	void createTracts_addTractLinks( int level , XmlBrainTract& tract , StringList& lines );

	void createTractsHirarchy();
	void createTracts_addTractTableLines( MapStringToClass<XmlBrainTractSet>& tractsets , StringList& lines );
	void createTracts_addTractSetTableLines( XmlBrainTractSet& ts , StringList& lines );
	void createTracts_addTractTableLines( int level , XmlBrainTract& tract , StringList& lines );
	void createTracts_addTractSetLines( XmlBrainTractSet& ts , StringList& lines );
	void createTracts_addTractLines( int level , XmlBrainTract& tract , StringList& lines );
	void createTracts_addTractPathLines( int level , XmlBrainTractPath& path , StringList& lines );

private:
	WikiMaker *wm;
};

/*#########################################################################*/
/*#########################################################################*/
