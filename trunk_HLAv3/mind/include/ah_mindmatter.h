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
// utility
	TwoIndexArray<neurovt> data;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroPool : public Object {
public:
	virtual const char *getClass() { return( "NeuroPool" ); };

private:
// own data
	NeuroVector *output;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroPoolSet : public Object {
public:
	virtual const char *getClass() { return( "NeuroPoolSet" ); };

private:
// own data
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
// references
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
// own data
	ClassList<NeuroLink> list;
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
