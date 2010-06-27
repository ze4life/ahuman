// understanding the meaning

#ifndef	INCLUDE_AIHTMLIB_H
#define INCLUDE_AIHTMLIB_H

#include <aiio.h>

class AIHtmLibVariant;

/*#########################################################################*/
/*#########################################################################*/

class AIHtmLib
{
public:

// engine helpers
public:
	static Service *createService();
	AIHtmLib *thisPtr;
	AIHtmLib();

	virtual void addLibVariant( AIHtmLibVariant *lib ) {
		thisPtr -> addLibVariant( lib );
	};
	virtual AIHtmLibVariant *getLibVariant( String name ) {
		return( thisPtr -> getLibVariant( name ) );
	}
};

/*#########################################################################*/
/*#########################################################################*/

class AIHtmLibVariant
{
public:
	static AIHtmLibVariant *createHtmCustom();
	
	AIHtmLibVariant( String p_name ) { 
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

#endif	// INCLUDE_AIHTMLIB_H
