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
	void updateHierarchyPage_WalkTree( Xml wiki , Xml hmind , int level , StringList& lines , bool mapRegion );
	String updateHierarchyPage_getElementString( Xml wiki , Xml item , MindRegion *region );

	void createAreaPages( Xml wiki , Xml hmind );
	void createComponentPages( Xml wiki , Xml hmind );

	void updateFileSection( String fileName , String section , StringList& lines );
};

/*#########################################################################*/
/*#########################################################################*/
