// understanding the meaning

#ifndef	INCLUDE_AILIBBN_H
#define INCLUDE_AILIBBN_H

#include <aiengine.h>

class AILibBNVariant;

/*#########################################################################*/
/*#########################################################################*/

class AILibBN
{
public:

// engine helpers
public:
	static Service *newService();
	AILibBN *thisPtr;
	AILibBN();

	virtual void addLibVariant( AILibBNVariant *lib ) {
		thisPtr -> addLibVariant( lib );
	};
	virtual AILibBNVariant *getLibVariant( String name ) {
		return( thisPtr -> getLibVariant( name ) );
	}
};

/*#########################################################################*/
/*#########################################################################*/

class AILibBNVariant
{
public:
	AILibBNVariant( String p_name ) { 
		name = p_name; 
	};
	virtual ~AILibBNVariant() {
	};

	String getName() { 
		return( name ); 
	};

private:	
	String name;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AILIBBN_H
