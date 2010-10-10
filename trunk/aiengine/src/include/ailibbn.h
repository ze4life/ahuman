// understanding the meaning

#ifndef	INCLUDE_AILIBBN_H
#define INCLUDE_AILIBBN_H

#include <aiengine.h>

class Cortex;

class AILibBNVariant;
class SFNeoCortexLibBN;
class ViewCustomLibBN;

/*#########################################################################*/
/*#########################################################################*/

// provides facade for each library incorporated into engine
class AILibBN
{
public:
	virtual SFNeoCortexLibBN *getSFNeoCortexLib() {
		return( thisPtr -> getSFNeoCortexLib() );
	};
	virtual ViewCustomLibBN *getViewCustomLib() {
		return( thisPtr -> getViewCustomLib() );
	};

// engine helpers
public:
	static Service *newService();
	AILibBN *thisPtr;
	AILibBN();
};

/*#########################################################################*/
/*#########################################################################*/

class AILibBNVariant
{
private:	
	String name;

public:
	AILibBNVariant( String p_name ) { name = p_name; };
	virtual ~AILibBNVariant() {};

	String getName() { return( name ); };
};

/*#########################################################################*/
/*#########################################################################*/

class SFNeoCortexLibBN : public AILibBNVariant
{
public:
	SFNeoCortexLibBN();
	~SFNeoCortexLibBN();

	// create neocortex with the same inputs as outputs of given cortex and 
	// probability destribution across given number of labels
	Object *createBeliefNetwork( int sizeX , int sizeY , int nRegions , int nClasses , int neuronCount , int maxSequenceLength );
	void deleteObject( Object *object );

	unsigned *getInputsBuffer( Object *object );
	void feedForward( Object *object , unsigned learningRegion, bool feedbackStage );
};

/*#########################################################################*/
/*#########################################################################*/

class ViewCustomLibBN : public AILibBNVariant
{
public:
	ViewCustomLibBN();
	~ViewCustomLibBN();

	// create neocortex with the same inputs as outputs of given cortex and 
	// probability destribution across given number of labels
	Object *createBeliefNetwork();
	void deleteObject( Object *object );
};

#endif	// INCLUDE_AILIBBN_H
