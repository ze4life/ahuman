#include "stdafx.h"

/*#########################################################################*/
/*#########################################################################*/

class XmlHMindElementInfo;
class XmlHMind;
class XmlCircuits;
class XmlCircuitInfo;
class XmlCircuitLinkInfo;

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
	void getElementInfo( String node , XmlHMindElementInfo& info );
	String getMappedRegion( String node );

private:
	void scanChildItems( Xml xmlChild );

private:
	Xml xml;
	MapStringToPtr nodes;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlHMindElementInfo {
public:
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
	void getCircuitInfo( String circuit , XmlCircuitInfo& info );
	void getCircuitLinks( String circuit , FlatList<Xml>& links );
	void getCircuitLinkInfo( Xml link , XmlCircuitLinkInfo& info );
	String mapComponent( XmlCircuitInfo& circuit , String circuitComponent );

private:
	Xml getCircuitXml( String id );
	Xml getCircuitFromFile( String id , String file );

private:
	Xml xml;
	MapStringToClass<Xml> nodes;
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
};

/*#########################################################################*/
/*#########################################################################*/

class XmlCircuitLinkInfo {
public:
	String compSrc;
	String compDst;
	String function;
};

/*#########################################################################*/
/*#########################################################################*/
