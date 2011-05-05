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

class NeuroLink : public Object {
public:
	const char *getClass() { return( "NeuroLink" ); };

public:
	NeuroPool *src;
	NeuroPool *dst;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLinkSet : public Object {
public:
	const char *getClass() { return( "NeuroLinkSet" ); };

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
	virtual const char *getClass() { return( "ExcitatoryLink" ); };
};

/*#########################################################################*/
/*#########################################################################*/

class InhibitoryLink : public NeuroLink {
public:
	virtual const char *getClass() { return( "InhibitoryLink" ); };
};

/*#########################################################################*/
/*#########################################################################*/

class ModulatoryLink : public NeuroLink {
public:
	virtual const char *getClass() { return( "ModulatoryLink" ); };
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDMATTER_H
