#include "stdafx.h"

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
	void getIdentifiedElements( String parentNode , StringList& elements );
	const XmlHMindElementInfo& getElementInfo( String node );
	String getMappedRegion( String node );
	void getChildRegions( String node , StringList& regions );
	String getDotDef( String node );

	bool checkAbstractLinkCoveredByRegionLink( String compSrc , String compDst , String linkRegionSrc , String linkRegionDst );

private:
	String createDivisionElement( Xml item );
	String createRegionElement( Xml item );
	void scanChildItems( Xml xmlChild );
	void scanChildRegions( Xml xmlChild , StringList& regions );
	void createElementInfo( String mapId , Xml item , XmlHMindElementInfo& info );
	String getRegionMapId( Xml item );

private:
	Xml xml;
	MapStringToClass<XmlHMindElementInfo> nodeInfo;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlHMindElementInfo {
public:
	String mapId;
	Xml xml;

	bool ignore;
	String id;
	String name;
	bool mapped;
	String refs;
	String comment;
	String brodmannid;
	String type;
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
	Xml getNerveXml( String id );
	XmlNerveInfo& getNerveInfo( String nerve );

private:
	Xml getNerveCategoryXml( Xml categoryItem );
	void addChilds( Xml division , Xml parent );

private:
	MapStringToClass<Xml> nodes;
	MapStringToClass<XmlNerveInfo> nerves;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlNerveInfo {
public:
	~XmlNerveInfo();

	Xml xml;

	String name;
	String synonyms;
	String origin;
	String branches;
	String distribution;
	String imginfo;
	String modality;
	ClassList<XmlNerveFiberInfo> fibers;
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
