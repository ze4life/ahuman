// aistudy.cpp : Defines the entry point for the console application.
//

#include "engine_impl.h"

// #############################################################################
// #############################################################################

const char *Object::getClass() 
{ 
	throw RuntimeError( "Object::getClass: virtual function undefined for class" );
}

String Object::getObjectName()
{
	if( name.getBuffer() != NULL )
		return( name );

	if( instance.getBuffer() != NULL ) {
		name = instance;
		return( instance );
	}

	return( getClass() );
}

void Object::serialize( SerializeObject& so ) 
{
	throw RuntimeError( "Object::serialize: virtual function undefined for class" );
}

void Object::deserialize( Object *parent , SerializeObject& so ) 
{
	throw RuntimeError( "Object::deserialize: virtual function undefined for class" );
}

String Object::getPK() 
{ 
	throw RuntimeError( "Object::getPK: virtual function undefined for class" );
}

const char *Object::getInstance()
{
	return( instance );
}

void Object::setInstance( const char *p_instance )
{
	instance = p_instance;
	logger.attach( this );
}

Object *Object::createObject( const char *className )
{
	SerializeObject *so = AIEngine::getInstance().getSerializeObject( className );
	return( so -> createObject() );
}

SerializeObject *Object::getSerializeObject()
{
	return( AIEngine::getInstance().getSerializeObject( getClass() ) );
}

void Object::serialize( Object *o , SerializeObject& so )
{
	so.clearData();
	so.setEffectiveObjectClass( o -> getClass() );

	o -> serialize( so );
}

void Object::deserialize( Object *parent , Object *o , SerializeObject& so )
{
	if( strcmp( so.getEffectiveObjectClass() , o -> getClass() ) )
		throw RuntimeError( "Object::deserialize: different object and so classes" );

	o -> deserialize( parent , so );
}

