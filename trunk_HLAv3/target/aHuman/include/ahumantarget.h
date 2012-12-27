/*#########################################################################*/
/*#########################################################################*/

#include <mind/include/ah_mind.h>

class AHumanTarget;
class ScenarioPlayer;
class ModelVerifier;
class WikiMaker;

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
	ModelVerifier();
	virtual ~ModelVerifier();
	virtual const char *getClass() { return "ModelVerifier"; };

public:
	void verify( Xml modelArea );
};

/*#########################################################################*/
/*#########################################################################*/

class WikiMaker : public Object {
public:
	WikiMaker();
	virtual ~WikiMaker();
	virtual const char *getClass() { return "WikiMaker"; };

public:
	void createPages( Xml wiki );

private:
	void updateHierarchyPage( Xml wiki , Xml hmind );
	void updateHierarchyPage_walkTree( Xml wiki , Xml hmind , int level , StringList& lines , MindArea *parentArea , MindRegion *parentRegion );
	void updateHierarchyPage_walkNeocortex( Xml wiki , Xml neocortexDivision , String wikiDir , String wikiPage );
	void updateHierarchyPage_getNeocortexLobeLines( Xml wiki , Xml neocortexLobe , StringList& lines );
	String updateHierarchyPage_getElementString( Xml wiki , Xml item , MindArea *parentArea , MindRegion *parentRegion , MindArea *ownArea , MindRegion *ownRegion );
	MindArea *updateHierarchyPage_getArea( Xml item );
	MindRegion *updateHierarchyPage_getRegion( Xml item );
	String updateHierarchyPage_getNeocortexBrodmannLine( Xml wiki , Xml neocortexDivision , String banum );
	void updateHierarchyPage_walkNeocortexBrodmannLine( Xml wiki , Xml item , String banum , StringList& items );

	void createAreaPages( Xml wiki , Xml hmind );
	void createAreaPages_makeAreaPageFile( Xml wiki , Xml hmind , String wikiDir , String wikiPage , MindAreaDef *areaDef );
	String createAreaPages_getRegionTableRow( Xml wiki , Xml hmind , MindRegionDef *regionDef );
	String createAreaPages_getTableCellAttribute( Xml wiki , Xml regionXml , String attribute , bool required , int columnWidth );

	void createComponentPages( Xml wiki , Xml hmind );

	void updateFileSection( String wikiDir , String wikiPage , String section , StringList& lines );
	Xml findHMindRegion( Xml hmind , String regionId );
	Xml findHMindRegionElement( Xml hmind , String regionId );
};

/*#########################################################################*/
/*#########################################################################*/
