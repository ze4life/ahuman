#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

NNVariablesContainer *NNVariablesContainer::singlton = NULL;

// class NNVariablesContainer : public Object
NNVariablesContainer::NNVariablesContainer()
{
	lastVarId = 0;
}

NNVariablesContainer::~NNVariablesContainer()
{
}

// instance handling
NNVariablesContainer *NNVariablesContainer::getInstance()
{
	if( singlton == NULL )
		singlton = new NNVariablesContainer();

	return( singlton );
}

void NNVariablesContainer::destroy()
{
	if( singlton == NULL )
		return;

	delete singlton;
	singlton = NULL;
}

// handling variables
void NNVariablesContainer::registerVariables( NNVariables *vars )
{
	ASSERT( varsMap.get( vars -> getMinId() ) == NULL );
	varsMap.add( vars -> getMinId() , vars );
}

void NNVariablesContainer::unregisterVariables( NNVariables *vars )
{
	varsMap.removeByKey( vars -> getMinId() );
}

NNVariable *NNVariablesContainer::getVarById( int id )
{
	int index = varsMap.getInsertPos( id );
	
	// can be equal to returned
	NNVariables *vars = NULL;
	if( index < varsMap.count() )
		{
			int value = varsMap.getKeyByIndex( index );
			if( id == value )
				vars = varsMap.getClassByIndex( index );
		}

	// should be greater than previous if any
	if( vars == NULL )
		{
			ASSERT( index > 0 );
			index--;
			vars = varsMap.getClassByIndex( index );
		}

	return( vars -> getVarById( id ) );
}

void NNVariablesContainer::allocateVarRange( int size , int *minId , int *maxId )
{
	*minId = lastVarId + 1;

	lastVarId += size;
	*maxId = lastVarId;
}

/*#########################################################################*/
/*#########################################################################*/

// Object interface
const char *NNVariablesContainer::NAME = "NNVariablesContainer";

void NNVariablesContainer::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );

	// add own fields
	so -> addFieldInt( "lastVarId" );
}

void NNVariablesContainer::serialize( SerializeObject& so )
{
	so.setPropInt( lastVarId , "lastVarId" );
}

void NNVariablesContainer::deserialize( Object *parent , SerializeObject& so )
{
	lastVarId = so.getPropInt( "lastVarId" );
	varsMap.clear();
}
