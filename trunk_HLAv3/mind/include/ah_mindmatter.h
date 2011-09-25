#ifndef	INCLUDE_AH_MINDMATTER_H
#define INCLUDE_AH_MINDMATTER_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class NeuroVector;
class NeuroPool;
class NeuroPoolSet;
class NeuroLink;
class NeuroLinkSet;
class NeuroNet;
class LayeredNet;
class CompactNet;
class SpreadNet;
class ExcitatoryLink;
class InhibitoryLink;
class ModulatoryLink;

/*#########################################################################*/
/*#########################################################################*/

class NeuroVector : public Object {
public:
	virtual const char *getClass() { return( "NeuroVector" ); };

	NeuroVector( int sizeX , int sizeY );
	NeuroVector( NeuroVector *src );
	~NeuroVector();

public:
	neurovt *getRawData();
	TwoIndexArray<neurovt>& getVectorData();

private:
	TwoIndexArray<neurovt> data;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroPool : public Object {
public:
	virtual const char *getClass() { return( "NeuroPool" ); };

private:
	NeuroVector *output;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroPoolSet : public Object {
public:
	virtual const char *getClass() { return( "NeuroPoolSet" ); };

private:
	ClassList<NeuroPool> list;
};

/*#########################################################################*/
/*#########################################################################*/

class MindRegionLink;

class NeuroLink : public Object {
public:
	NeuroLink( MindRegionLink *regionLink );
	const char *getClass() { return( "NeuroLink" ); };

	void create( NeuroVector *p_src , NeuroPool *p_dst );
	NeuroVector *getSourceData();

	virtual void createNeuroLink() = 0;

public:
	MindRegionLink *regionLink;

	NeuroVector *src;
	NeuroPool *dst;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLinkSet : public Object {
public:
	const char *getClass() { return( "NeuroLinkSet" ); };

	void addSetItem( NeuroLink *link );
	void projectData( neurovt *data , int size );

public:
	ClassList<NeuroLink> list;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroNet : public Object {
public:
	virtual const char *getClass() = 0;

private:
	NeuroPoolSet *pools;
	NeuroLinkSet *links;
};

/*#########################################################################*/
/*#########################################################################*/

class LayeredNet : public NeuroNet {
public:
	virtual const char *getClass() { return( "LayeredNet" ); };
};

/*#########################################################################*/
/*#########################################################################*/

class CompactNet : public NeuroNet {
public:
	virtual const char *getClass() { return( "CompactNet" ); };
};

/*#########################################################################*/
/*#########################################################################*/

class SpreadNet : public NeuroNet {
public:
	virtual const char *getClass() { return( "SpreadNet" ); };
};

/*#########################################################################*/
/*#########################################################################*/

class ExcitatoryLink : public NeuroLink {
public:
	ExcitatoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "ExcitatoryLink" ); };

	virtual void createNeuroLink();
	virtual void projectData( neurovt *data , int size );
};

/*#########################################################################*/
/*#########################################################################*/

class InhibitoryLink : public NeuroLink {
public:
	InhibitoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "InhibitoryLink" ); };

	virtual void createNeuroLink();
	virtual void projectData( neurovt *data , int size );
};

/*#########################################################################*/
/*#########################################################################*/

class ModulatoryLink : public NeuroLink {
public:
	ModulatoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "ModulatoryLink" ); };

	virtual void createNeuroLink();
	virtual void projectData( neurovt *data , int size );
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDMATTER_H
