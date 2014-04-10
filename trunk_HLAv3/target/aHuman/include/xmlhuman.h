#include "stdafx.h"

#ifndef	INCLUDE_XMLHUMAN_H
#define INCLUDE_XMLHUMAN_H

/*#########################################################################*/
/*#########################################################################*/

class XmlHMindElementInfo;
class XmlHMind;
class XmlCircuits;
class XmlCircuitInfo;
class XmlCircuitLinkInfo;
class XmlCircuitFind;
class XmlNerves;
class XmlNerveInfo;
class XmlNerveFiberInfo;
class XmlMuscles;
class XmlMuscleInfo;
class XmlMuscleDivision;
class XmlSpinalCord;
class XmlSpinalTractSet;
class XmlSpinalTract;
class XmlSpinalTractPath;
class XmlSpinalFiber;
class XmlSpinalEndingSet;
class XmlSpinalEnding;

/*#########################################################################*/
/*#########################################################################*/

class XmlHMind : public Object {
public:
	XmlHMind();
	virtual ~XmlHMind();
	virtual const char *getClass() { return "XmlHMind"; };

public:
	void load();

	Xml getNodeXml( String node );
	bool isComponent( String node );

	void getDivisions( StringList& divisions );
	void getElements( String parentNode , StringList& elements );
	void getConnectors( String parentNode , StringList& elements );
	void getIdentifiedElements( String parentNode , StringList& elements );
	const XmlHMindElementInfo& getElementInfo( String node );
	const XmlHMindElementInfo *getConnectorInfo( String name );
	XmlSpinalCord *getSpinalCord() { return( spinalCord ); };
	XmlHMindElementInfo *getIndexedElement( String index );

	String getMappedRegion( String node );
	void getChildRegions( String node , StringList& regions );
	String getDotDef( String node );

	bool checkAbstractLinkCoveredByRegionLink( String compSrc , String compDst , String linkRegionSrc , String linkRegionDst );

private:
	void createDivisionElement( Xml item );
	String createRegionElement( Xml item );
	void scanChildItems( Xml xmlChild );
	void scanChildRegions( Xml xmlChild , StringList& regions );
	void createElementInfo( String mapId , Xml item , XmlHMindElementInfo& info );
	String getRegionMapId( Xml item );

private:
	Xml xml;
	MapStringToClass<XmlHMindElementInfo> nodeInfo;
	MapStringToClass<XmlHMindElementInfo> connectorInfo;
	XmlSpinalCord *spinalCord;
	MapStringToClass<XmlHMindElementInfo> mapIndex;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlHMindElementInfo {
public:
	bool isConnector() const { return( type.equals( "connector" ) ); };

public:
	String mapId;
	Xml xml;

	bool ignore;
	String id;
	String index;
	String name;
	bool mapped;
	String refs;
	String comment;
	String brodmannid;
	String type;
	String fgroup;
	String function;
	String notes;
	String dotdef;

	String batype;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlCircuits {
public:
	XmlCircuits();
	virtual ~XmlCircuits();
	virtual const char *getClass() { return "XmlCircuits"; };

public:
	void load();

	void getCircuitList( StringList& circuits );
	XmlCircuitInfo& getCircuitInfo( String circuit );
	void getCircuitLinks( String circuit , FlatList<Xml>& links );
	void getCircuitLinkInfo( Xml link , XmlCircuitLinkInfo& info );
	String mapComponent( XmlCircuitInfo& circuit , String circuitComponent );
	bool checkRegionUsedByCircuit( String region , String circuit );
	void getCircuitComponents( XmlCircuitInfo& circuit , StringList& components );

	bool findReferenceLink( XmlHMind& hmindxml , String srcRegion , String dstRegion , XmlCircuitFind& find );
	bool findReferenceCircuitLink( XmlHMind& hmindxml , String checkSrcRegion , String checkDstRegion , XmlCircuitInfo& info , XmlCircuitFind *find , bool directOnly );

private:
	Xml getCircuitXml( String id );
	Xml getCircuitFromFile( String id , String file );

private:
	Xml xml;
	MapStringToClass<Xml> nodes;
	MapStringToClass<XmlCircuitInfo> circuits;
	MapStringToClass<XmlCircuitFind> referenceMap;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlCircuitInfo {
public:
	Xml xml;

	String id;
	bool ignore;

	String name;
	String image;
	String reference;
	MapStringToString componentMapping;

	int imageHeight;
	int imageWidth;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlCircuitLinkInfo {
public:
	String compSrc;
	String compDst;
	String function;
};

class XmlCircuitFind {
public:
	XmlCircuitInfo *circuit;
	XmlCircuitLinkInfo link;
	bool isAbstractLink;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlNerves {
public:
	XmlNerves();
	virtual ~XmlNerves();
	virtual const char *getClass() { return "XmlNerves"; };

public:
	void load();

	void getNerveList( StringList& list );
	bool checkNerve( String nerve );
	Xml getNerveXml( String id );
	XmlNerveInfo& getNerveInfo( String nerve );

	ClassList<XmlNerveInfo>& getDivisions() { return( divisions ); };
	XmlNerveInfo& getNerveDivision( String nerve );

private:
	Xml getNerveCategoryXml( Xml categoryItem );
	XmlNerveInfo *createNerveInfo( String nerve , Xml xmlitem , XmlNerveInfo *div );
	void addChilds( XmlNerveInfo *division , XmlNerveInfo *parent );

private:
	MapStringToClass<Xml> nodes;
	MapStringToClass<XmlNerveInfo> nerves;
	ClassList<XmlNerveInfo> divisions;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlNerveInfo {
public:
	XmlNerveInfo() { tree = false; };
	~XmlNerveInfo() { fibers.destroy(); };

	Xml xml;

public:
	void getMotorNuclei( StringList& items );
	void getSensoryNuclei( StringList& items );

	void getFiberMotorNuclei( XmlNerveFiberInfo& fiber , StringList& items );
	void getFiberSensoryNuclei( XmlNerveFiberInfo& fiber , StringList& items );
	void getNervesByComponent( String item , StringList& nerves );

public:
	XmlNerveInfo *div;
	String name;
	String type;
	String synonyms;
	String origin;		// page in division
	String branches;
	String distribution;
	String imgsrc;
	String imgheight;
	String modality;
	StringList mods;
	String action;
	bool tree;

	ClassList<XmlNerveFiberInfo> fibers;
	MapStringToClass<XmlNerveInfo> childs;
	StringList rootNerves;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlNerveFiberInfo {
public:
	String type;
	String src;
	String dst;
	StringList mids;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlMuscles {
public:
	XmlMuscles();
	virtual ~XmlMuscles();
	virtual const char *getClass() { return "XmlMuscles"; };

public:
	void load();

	void getMuscleList( StringList& list );
	Xml getMuscleXml( String id );
	XmlMuscleInfo& getMuscleInfo( String muscle );
	void getMusclesByNerve( String nerve , StringList& muscles );
	XmlMuscleInfo *findByConnector( String name );

	void getCategories( StringList& categories );
	MapStringToClass<XmlMuscleDivision>& getDivisions() { return( divisions ); };

private:
	Xml getMuscleCategoryXml( Xml categoryItem );
	XmlMuscleInfo *createMuscleInfo( XmlMuscleDivision *division , String muscle , Xml xmlitem );
	void addChilds( XmlMuscleDivision *division , Xml parent , MapStringToClass<XmlMuscleInfo>& list );
	void addNerveMuscles( XmlMuscleInfo *muscle );

private:
	MapStringToClass<XmlMuscleInfo> muscles;
	MapStringToClass<XmlMuscleDivision> divisions;
	MapStringToClass<StringList> nerveMuscles;
	MapStringToClass<XmlMuscleInfo> muscleConnectors;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlMuscleInfo {
public:
	~XmlMuscleInfo() {};

	Xml xml;

	XmlMuscleDivision *division;
	String name;
	String type;
	String link;
	MapStringToString nerves;
	String action;
	String imgsrc;
	String imgheight;

	MapStringToClass<XmlMuscleInfo> childs;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlMuscleDivision {
public:
	~XmlMuscleDivision() {};

	Xml xml;

	String name;
	String category;
	String page;

	String divc;
	String divgroup;

	MapStringToClass<XmlMuscleInfo> childs;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlSpinalCord {
public:
	XmlSpinalCord( XmlHMind *hmind );
	~XmlSpinalCord();

	void load( Xml xmlDiv );
	String getImageSrc() { return( imgSrc ); };
	String getImageHeight() { return( imgHeight ); };
	const char **getLayoutLevels();
	const char **getLayoutLaminas();
	StringList& getLayoutCellItems( String level , String lamina );
	void getLayoutItems( StringList& items );
	void getLayoutItemLayers( String item , StringList& items );
	void getLayoutItemLaminas( String item , StringList& items );
	void getRegionTracts( String region , StringList& tracts );

	MapStringToClass<XmlSpinalEndingSet>& getEndings() { return( endings ); };
	MapStringToClass<XmlSpinalFiber>& getFibers() { return( fibers ); };
	MapStringToClass<XmlSpinalTractSet>& getTracts() { return( tractsets ); };

	MapStringToClass<XmlSpinalEnding>& getEndingMap() { return( endingMap ); };
	MapStringToClass<XmlSpinalFiber>& getFiberMap() { return( fiberMap ); };
	MapStringToClass<XmlSpinalTract>& getTractMap() { return( tractMap ); };

	XmlSpinalEnding& getEnding( String id );
	XmlSpinalFiber& getFiber( String id );

	XmlSpinalEnding *findEnding( String id );
	XmlSpinalFiber *findFiber( String id );

	void addEnding( XmlSpinalEnding *ending );
	void addFiber( XmlSpinalFiber *fiber );
	void addTract( XmlSpinalTract *tract );
	void addPath( XmlSpinalTractPath *path );

private:
	void loadFibers( Xml xmlDiv );
	void loadEndings( Xml xmlDiv );
	void loadLayout( Xml xmlDiv );
	void loadLayoutLevel( Xml xmlLevel , MapStringToClass<StringList>& levelData );
	void loadTracts( Xml xmlDiv );
	void linkFibers();
	void linkTracts();
	void linkTractPaths( XmlSpinalTract& tract , MapStringToClass<XmlSpinalTractPath>& paths );

private:
	XmlHMind *hmind;
	String imgSrc;
	String imgHeight;
	MapStringToClass<MapStringToClass<StringList> > data;
	MapStringToClass<XmlSpinalTractSet> tractsets;
	MapStringToClass<XmlSpinalFiber> fibers;
	MapStringToClass<XmlSpinalEndingSet> endings;

	MapStringToClass<XmlSpinalEnding> endingMap;
	MapStringToClass<XmlSpinalFiber> fiberMap;
	MapStringToClass<XmlSpinalTract> tractMap;
	MapStringToClass<XmlSpinalTractPath> pathMap;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlSpinalTractSet {
public:
	XmlSpinalTractSet( XmlSpinalCord& sc );
	~XmlSpinalTractSet();

	void load( Xml xml );

public:
	XmlSpinalCord& sc;

	String name;
	String imgsrc;
	String imgheight;
	MapStringToClass<XmlSpinalTract> tracts;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlSpinalTract {
public:
	XmlSpinalTract( XmlSpinalTractSet& ts , XmlSpinalTract *parent );
	~XmlSpinalTract();

	void load( Xml xml );
	void addPath( XmlSpinalTractPath *path );
	bool referencesRegion( String region );

public:
	XmlSpinalTractSet& ts;
	XmlSpinalTract *parent;

	String index;
	String brief;
	String name;
	String link;
	String synonyms;
	String function;
	String source;
	String target;
	String notes;
	String imgsrc;
	String imgheight;
	MapStringToClass<XmlSpinalTract> childs;
	MapStringToClass<XmlSpinalTractPath> paths;
	MapStringToClass<XmlSpinalTractPath> allpaths;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlSpinalTractPath {
public:
	XmlSpinalTractPath( XmlSpinalTract& tract , XmlSpinalTractPath *parent );
	~XmlSpinalTractPath();

	void load( Xml xml );

public:
	XmlSpinalTract& tract;
	XmlSpinalTractPath *parent;

	String id;
	String function;
	String pathway;
	StringList endings;
	StringList fibers;
	StringList items;
	MapStringToClass<XmlSpinalTractPath> childs;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlSpinalFiber {
public:
	XmlSpinalFiber( XmlSpinalCord& sc , XmlSpinalFiber *parent );
	~XmlSpinalFiber();

	void load( Xml xml );
	void addTract( XmlSpinalTract *tract );

public:
	XmlSpinalCord& sc;
	XmlSpinalFiber *parent;

	String id;
	String name;
	String type;
	String mcm;
	String msec;
	StringList endings;
	String function;
	String notes;
	MapStringToClass<XmlSpinalFiber> childs;

	MapStringToClass<XmlSpinalTract> tracts;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlSpinalEndingSet {
public:
	XmlSpinalEndingSet( XmlSpinalCord& sc );
	~XmlSpinalEndingSet();

	void load( Xml xml );

public:
	XmlSpinalCord& sc;

	String name;
	String type;
	String imgsrc;
	String imgheight;
	MapStringToClass<XmlSpinalEnding> childs;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlSpinalEnding {
public:
	XmlSpinalEnding( XmlSpinalEndingSet& es , XmlSpinalEnding *parent );
	~XmlSpinalEnding();

	void load( Xml xml , String element );
	void addFiber( XmlSpinalFiber *fiber );
	void addTract( XmlSpinalTract *tract );

public:
	XmlSpinalEndingSet& es;
	XmlSpinalEnding *parent;

	String id;
	String type;
	String name;
	String function;
	String notes;
	MapStringToClass<XmlSpinalEnding> childs;

	StringList fibers;
	MapStringToClass<XmlSpinalTract> tracts;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_XMLHUMAN_H
