#include "stdafx.h"

#ifndef	INCLUDE_XMLHUMAN_H
#define INCLUDE_XMLHUMAN_H

/*#########################################################################*/
/*#########################################################################*/

class XmlHMind;
class XmlBrainCategory;
class XmlHMindElementInfo;
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
class XmlTracts;
class XmlSpinalCord;
class XmlBrainTractSet;
class XmlBrainTract;
class XmlBrainTractPath;
class XmlBrainFiber;
class XmlBrainEndingSet;
class XmlBrainEnding;

/*#########################################################################*/
/*#########################################################################*/

class XmlHMind : public Object {
public:
	XmlHMind();
	virtual ~XmlHMind();
	virtual const char *getClass() { return "XmlHMind"; };

public:
	void load();
	void loadCategories( Xml xml );

	Xml getNodeXml( String node );
	bool isComponent( String node );

	XmlBrainCategory *getCategory( String category );
	void getDivisions( StringList& divisions );
	void getElements( String parentNode , StringList& elements );
	void getConnectors( String parentNode , StringList& elements );
	void getIdentifiedElements( String parentNode , StringList& elements );
	XmlHMindElementInfo& getElementInfo( String node );
	const XmlHMindElementInfo *getConnectorInfo( String name );
	XmlTracts *getTracts() { return( tracts ); };
	XmlSpinalCord *getSpinalCord() { return( spinalCord ); };
	XmlHMindElementInfo *getIndexedElement( String index );

	String getMappedRegion( String node );
	void getChildRegions( String node , StringList& regions );
	String getDotDef( String node );

	bool checkAbstractLinkCoveredByRegionLink( String compSrc , String compDst , String linkRegionSrc , String linkRegionDst );

private:
	void createDivisionElement( Xml item );
	XmlHMindElementInfo *createRegionElement( Xml item , XmlHMindElementInfo *parent );
	void scanChildItems( Xml xmlChild , XmlHMindElementInfo *parent );
	void scanChildRegions( Xml xmlChild , StringList& regions );
	void createElementInfo( String mapId , Xml item , XmlHMindElementInfo& info );
	String getRegionMapId( Xml item );

private:
	Xml xml;
	MapStringToClass<XmlHMindElementInfo> divs;
	MapStringToClass<XmlHMindElementInfo> nodeInfo;
	MapStringToClass<XmlHMindElementInfo> connectorInfo;
	XmlTracts *tracts;
	XmlSpinalCord *spinalCord;
	MapStringToClass<XmlHMindElementInfo> mapIndex;
	MapStringToClass<XmlBrainCategory> categories;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlBrainCategory {
public:
	XmlBrainCategory( XmlHMind *hmind );

	String getId() { return( id ); };
	String getName() { return( name ); };
	MapStringToClass<XmlHMindElementInfo>& getMappedElements() { return( mappedElements ); };

	void load( Xml xml );
	void addElement( XmlHMindElementInfo *item );
	void getMappedItems( StringList& items );

private:
	XmlHMind *hmind;
	String id;
	String name;
	MapStringToClass<XmlHMindElementInfo> mappedElements;
};

/*#########################################################################*/
/*#########################################################################*/

typedef enum {
	HMIND_ELEMENT_NOTYPE = 0,
	HMIND_ELEMENT_CONNECTOR = 1,
	HMIND_ELEMENT_SENSOR = 2,
	HMIND_ELEMENT_EFFECTOR = 3,
	HMIND_ELEMENT_GANGLION_SENSORY = 4,
	HMIND_ELEMENT_GANGLION_SYMP = 5,
	HMIND_ELEMENT_GANGLION_PSYMP = 6,
	HMIND_ELEMENT_CORTEX = 7,
	HMIND_ELEMENT_NUCLEUS = 8,
	HMIND_ELEMENT_GLAND = 9
} XmlHMindElementInfoType;

class XmlHMindElementInfo {
public:
	XmlHMindElementInfo( XmlHMindElementInfo *p_parent ) { parent = p_parent; ignore = true; mapped = false; };

	XmlHMindElementInfo *getParent() { return( parent ); };
	bool isConnector() const { return( eltype == HMIND_ELEMENT_CONNECTOR ); };
	bool isTarget() const { return( eltype == HMIND_ELEMENT_SENSOR || eltype == HMIND_ELEMENT_EFFECTOR ); };
	bool isGanglion() const { return( eltype == HMIND_ELEMENT_GANGLION_SENSORY || eltype == HMIND_ELEMENT_GANGLION_SYMP || eltype == HMIND_ELEMENT_GANGLION_PSYMP ); };

public:
	String mapId;
	Xml xml;
	XmlHMindElementInfo *parent;

	bool ignore;
	String id;
	String category;
	String index;
	String name;
	bool mapped;
	String refs;
	String comment;
	String brodmannid;
	XmlHMindElementInfoType eltype;
	String eltypename;
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

class XmlTracts {
public:
	XmlTracts( XmlHMind *hmind );
	~XmlTracts();

	void load( Xml xml );
	void getRegionTracts( String region , StringList& tracts );

	MapStringToClass<XmlBrainEndingSet>& getEndings() { return( endings ); };
	MapStringToClass<XmlBrainFiber>& getFibers() { return( fibers ); };
	MapStringToClass<XmlBrainTractSet>& getTracts() { return( tractsets ); };

	MapStringToClass<XmlBrainEnding>& getEndingMap() { return( endingMap ); };
	MapStringToClass<XmlBrainFiber>& getFiberMap() { return( fiberMap ); };
	MapStringToClass<XmlBrainTract>& getTractMap() { return( tractMap ); };
	MapStringToClass<XmlBrainTractPath>& getTractPathMap() { return( pathMap ); };

	XmlBrainEnding& getEnding( String id );
	XmlBrainFiber& getFiber( String id );

	XmlBrainEnding *findEnding( String id );
	XmlBrainFiber *findFiber( String id );

	void addEnding( XmlBrainEnding *ending );
	void addFiber( XmlBrainFiber *fiber );
	void addTract( XmlBrainTract *tract );
	void addPath( XmlBrainTractPath *path );

private:
	void loadFibers( Xml xmlDiv );
	void loadEndings( Xml xmlDiv );
	void loadTracts( Xml xmlDiv );
	void linkFibers();
	void linkTracts();
	void linkTractPaths( XmlBrainTract& tract , MapStringToClass<XmlBrainTractPath>& paths );

private:
	XmlHMind *hmind;
	String imgSrc;
	String imgHeight;
	MapStringToClass<XmlBrainTractSet> tractsets;
	MapStringToClass<XmlBrainFiber> fibers;
	MapStringToClass<XmlBrainEndingSet> endings;

	MapStringToClass<XmlBrainEnding> endingMap;
	MapStringToClass<XmlBrainFiber> fiberMap;
	MapStringToClass<XmlBrainTract> tractMap;
	MapStringToClass<XmlBrainTractPath> pathMap;
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

private:
	void loadLayout( Xml xmlDiv );
	void loadLayoutLevel( Xml xmlLevel , MapStringToClass<StringList>& levelData );

private:
	XmlHMind *hmind;
	String imgSrc;
	String imgHeight;
	MapStringToClass<MapStringToClass<StringList> > data;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlBrainTractSet {
public:
	XmlBrainTractSet( XmlTracts& sc );
	~XmlBrainTractSet();

	void load( Xml xml );

public:
	XmlTracts& sc;

	String id;
	String name;
	String imgsrc;
	String imgheight;
	MapStringToClass<XmlBrainTract> tracts;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlBrainTract {
public:
	XmlBrainTract( XmlBrainTractSet& ts , XmlBrainTract *parent );
	~XmlBrainTract();

	void load( Xml xml );
	void addPath( XmlBrainTractPath *path );
	bool referencesRegion( String region );

public:
	XmlBrainTractSet& ts;
	XmlBrainTract *parent;

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
	MapStringToClass<XmlBrainTract> childs;
	MapStringToClass<XmlBrainTractPath> paths;
	MapStringToClass<XmlBrainTractPath> allpaths;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlBrainTractPath {
public:
	XmlBrainTractPath( XmlBrainTract& tract , XmlBrainTractPath *parent );
	~XmlBrainTractPath();

	void load( Xml xml );

public:
	XmlBrainTract& tract;
	XmlBrainTractPath *parent;

	String id;
	String type;
	String function;
	String pathway;
	StringList endings;
	StringList fibers;
	StringList items;
	MapStringToClass<XmlBrainTractPath> childs;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlBrainFiber {
public:
	XmlBrainFiber( XmlTracts& sc , XmlBrainFiber *parent );
	~XmlBrainFiber();

	void load( Xml xml );
	void addTract( XmlBrainTract *tract );

public:
	XmlTracts& sc;
	XmlBrainFiber *parent;

	String id;
	String name;
	String type;
	String mcm;
	String msec;
	StringList endings;
	String function;
	String notes;
	MapStringToClass<XmlBrainFiber> childs;

	MapStringToClass<XmlBrainTract> tracts;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlBrainEndingSet {
public:
	XmlBrainEndingSet( XmlTracts& sc );
	~XmlBrainEndingSet();

	void load( Xml xml );

public:
	XmlTracts& sc;

	String name;
	String type;
	String imgsrc;
	String imgheight;
	MapStringToClass<XmlBrainEnding> childs;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlBrainEnding {
public:
	XmlBrainEnding( XmlBrainEndingSet& es , XmlBrainEnding *parent );
	~XmlBrainEnding();

	void load( Xml xml , String element );
	void addFiber( XmlBrainFiber *fiber );
	void addTract( XmlBrainTract *tract );

public:
	XmlBrainEndingSet& es;
	XmlBrainEnding *parent;

	String id;
	String type;
	String name;
	String function;
	String notes;
	MapStringToClass<XmlBrainEnding> childs;

	StringList fibers;
	MapStringToClass<XmlBrainTract> tracts;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_XMLHUMAN_H
