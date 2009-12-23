#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

NNVariables::NNVariables()
{
	newId = 0;
	minId = maxId = 0;
	local = true;
}

NNVariables::~NNVariables()
{
	clear();
}

void NNVariables::clear()
{
	if( !local )
		{
			NNVariablesContainer *vc = NNVariablesContainer::getInstance();
			vc -> unregisterVariables( this );
			local = true;
		}

	data.destroy();
}

// ID range
void NNVariables::create( int size )
{
	ASSERT( maxId == 0 );

	NNVariablesContainer *vc = NNVariablesContainer::getInstance();
	vc -> allocateVarRange( size , &minId , &maxId );
	local = false;
	newId = minId;

	vc -> registerVariables( this );
}

void NNVariables::createLocal()
{
	newId = minId = 1;
	maxId = 2000000000;
	local = true;
}

int NNVariables::getMinId()
{
	return( minId );
}

int NNVariables::getMaxId()
{
	return( maxId );
}

NNVariable *NNVariables::getVarById( int p_id )
{
	return( data.get( p_id ) );
}

int NNVariables::getRepresentationSize( ClassList<NNVariable>& vars )
{
	int total = 0;
	for( int k = 0; k < vars.count(); k++ )
		total += vars[ k ] -> getRepresentationSize();
	return( total );
}

NNVariable *NNVariables::addCommonBool()
{
	NNVariableSimple *nv = new NNVariableSimple;
	
	Scale& scale = nv -> getScale();
	scale.setRangeFrom( -1 , 1 );
	scale.setRangeTo( 0 , 1 );

	addVar( nv );
	return( nv );
}

NNVariable *NNVariables::addCommonNumber( bool limitLeft , float valueLeft , bool limitRight , float valueRight )
{
	NNVariableSimple *nv = new NNVariableSimple;
	
	Scale& scale = nv -> getScale();
	scale.setRangeFrom( -1 , 1 );
	if( !limitLeft )
		valueLeft = -1000000000;
	if( !limitRight )
		valueRight = 1000000000;
	scale.setRangeTo( valueLeft , valueRight );

	addVar( nv );
	return( nv );
}

NNVariable *NNVariables::addCommonNumberDerivative()
{
	NNVariableSimple *nv = new NNVariableSimple;
	
	Scale& scale = nv -> getScale();
	scale.setRangeFrom( -1 , 1 );
	scale.setRangeTo( -100 , 100 );

	addVar( nv );
	return( nv );
}

NNVariable *NNVariables::addCommonCategory( int count )
{
	NNVariableCategory *nv = new NNVariableCategory;
	nv -> setCategoryCount( count );

	addVar( nv );
	return( nv );
}

void NNVariables::addVar( NNVariable *nv )
{
	ASSERT( newId <= maxId );

	nv -> setId( newId++ );
	data.add( nv -> getId() , nv );
}

/*#########################################################################*/
/*#########################################################################*/

const char *NNVariables::NAME = "NNVariables";

void NNVariables::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNVariables::onCreate );

	// add own fields
	so -> addFieldObjectList( "variables" , NULL );
	so -> addFieldInt( "minId" );
	so -> addFieldInt( "maxId" );
	so -> addFieldInt( "newId" );
	so -> addFieldBool( "local" );
}

void NNVariables::serialize( SerializeObject& so )
{
	ClassList<NNVariable> list;
	data.copyTo( list );
	so.setPropObjectList( ( ClassList<Object>& )list , "variables" , false );
	so.setPropInt( minId , "minId" );
	so.setPropInt( maxId , "maxId" );
	so.setPropInt( newId , "newId" );
	so.setPropBool( local , "local" );
}

void NNVariables::deserialize( Object *parent , SerializeObject& so )
{
	clear();

	minId = so.getPropInt( "minId" );
	maxId = so.getPropInt( "maxId" );
	newId = so.getPropInt( "newId" );
	local = so.getPropBool( "local" );

	ClassList<NNVariable> list;
	so.getPropObjectList( ( ClassList<Object>& )list , "variables" , true );
	for( int k = 0; k < list.count(); k++ )
		{
			NNVariable *nv = list[ k ];
			data.add( nv -> getId() , nv );
		}

	if( !local )
		{
			NNVariablesContainer *vc = NNVariablesContainer::getInstance();
			vc -> registerVariables( this );
		}
}
