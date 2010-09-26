// understanding the meaning

#ifndef	INCLUDE_AILIBNN_H
#define INCLUDE_AILIBNN_H

#include <aiengine.h>

class AILibNNVariant;

/*#########################################################################*/
/*#########################################################################*/

class AILibNN
{
public:

// engine helpers
public:
	static Service *newService();
	AILibNN *thisPtr;
	AILibNN();

	virtual void addLibVariant( AILibNNVariant *lib ) {
		thisPtr -> addLibVariant( lib );
	};
	virtual AILibNNVariant *getLibVariant( String name ) {
		return( thisPtr -> getLibVariant( name ) );
	}
};

/*#########################################################################*/
/*#########################################################################*/

class AILibNNVariant
{
public:
	static AILibNNVariant *createFannCustom();
	
	AILibNNVariant( String p_name ) { 
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

#endif	// INCLUDE_AILIBNN_H
