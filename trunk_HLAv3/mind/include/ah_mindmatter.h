#ifndef	INCLUDE_AH_MINDMATTER_H
#define INCLUDE_AH_MINDMATTER_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class Neuron;
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

class Neuron : public Object {
public:
	virtual const char *getClass() { return( "Neuron" ); };
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroPool : public Object {
public:
	virtual const char *getClass() { return( "NeuroPool" ); };

private:
	ClassList<Neuron> list;
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

	virtual void createNeuroLink( MindRegionLink *regionLink ) = 0;
	virtual void projectData( neurovt *data , int size ) = 0;

public:
	MindRegionLink *regionLink;
	NeuroPool *src;
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

	virtual void createNeuroLink( MindRegionLink *regionLink );
	virtual void projectData( neurovt *data , int size );
};

/*#########################################################################*/
/*#########################################################################*/

class InhibitoryLink : public NeuroLink {
public:
	InhibitoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "InhibitoryLink" ); };

	virtual void createNeuroLink( MindRegionLink *regionLink );
	virtual void projectData( neurovt *data , int size );
};

/*#########################################################################*/
/*#########################################################################*/

class ModulatoryLink : public NeuroLink {
public:
	ModulatoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "ModulatoryLink" ); };

	virtual void createNeuroLink( MindRegionLink *regionLink );
	virtual void projectData( neurovt *data , int size );
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDMATTER_H
