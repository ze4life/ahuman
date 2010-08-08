// understanding the meaning

#ifndef	INCLUDE_AILIBBN_H
#define INCLUDE_AILIBBN_H

#include <aisvcio.h>

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
	static AILibBNVariant *createHtmCustom();
	
	AILibBNVariant( String p_name ) { 
		name = p_name; 
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
