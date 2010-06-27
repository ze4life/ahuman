// understanding the meaning

#ifndef	INCLUDE_AINNLIB_H
#define INCLUDE_AINNLIB_H

#include <aiio.h>

class AINNLibVariant;

/*#########################################################################*/
/*#########################################################################*/

class AINNLib
{
public:

// engine helpers
public:
	static Service *createService();
	AINNLib *thisPtr;
	AINNLib();

	virtual void addLibVariant( AINNLibVariant *lib ) {
		thisPtr -> addLibVariant( lib );
	};
	virtual AINNLibVariant *getLibVariant( String name ) {
		return( thisPtr -> getLibVariant( name ) );
	}
};

/*#########################################################################*/
/*#########################################################################*/

class AINNLibVariant
{
public:
	static AINNLibVariant *createFannCustom();
	
	AINNLibVariant( String p_name ) { 
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

#endif	// INCLUDE_AINNLIB_H
