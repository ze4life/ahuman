#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

NNVariableSimple::NNVariableSimple()
:	NNVariable( NNVariable::VarSimple )
{
	value = 0;
}

NNVariableSimple::~NNVariableSimple()
{
}

void NNVariableSimple::setVariableRange( float minValue , float maxValue )
{
	scale.setRangeTo( minValue , maxValue );
}

void NNVariableSimple::setRepresentationRange( float minValue , float maxValue )
{
	scale.setRangeFrom( minValue , maxValue );
}

Scale& NNVariableSimple::getScale()
{
	return( scale );
}

// value
void NNVariableSimple::clearValue()
{
	value = 0;
}

float NNVariableSimple::getValue()
{
	return( value );
}

// attach to NN
NNVariable::Mapping *NNVariableSimple::attachAsSensor( NN *nn , float * const *values )
{
	NNVariableSimple::Mapping *vm = sensorMapping.add();
	vm -> objs.var = this;
	vm -> objs.p = nn;
	vm -> pv = *values;
	vm -> pvBack = NULL;

	return( ( NNVariable::Mapping * )vm );
}

NNVariable::Mapping *NNVariableSimple::attachAsTarget( NN *nn , float **values , float * const *valuesBack )
{
	NNVariableSimple::Mapping *vm = targetMapping.add();
	vm -> objs.var = this;
	vm -> objs.p = nn;
	vm -> pv = *values;
	vm -> pvBack = *valuesBack;

	return( ( NNVariable::Mapping * )vm );
}

// representation
int NNVariableSimple::getRepresentationSize()
{
	return( 1 );
}

void NNVariableSimple::setValueAndCalculateRepresentation( float p_value , NNVariable::Mapping *vm )
{
	value = p_value;
	*( ( ( NNVariableSimple::Mapping * )vm ) -> pv ) = scale.unscale( value );
}

void NNVariableSimple::calculateBackRepresentation( float value , NNVariable::Mapping *vm )
{
	*( ( ( NNVariableSimple::Mapping * )vm ) -> pvBack ) = scale.unscale( value );
}

void NNVariableSimple::calculateValueFromRepresentation( NNVariable::Mapping *vm )
{
	value = scale.scale( *( ( ( NNVariableSimple::Mapping * )vm ) -> pv ) );
}

/*#########################################################################*/
/*#########################################################################*/

const char *NNVariableSimple::NAME = "NNVariableSimple";

void NNVariableSimple::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNVariableSimple::onCreate );

	// add own fields
	so -> addFieldInt( "id" );
	so -> addFieldInt( "domain" );
	so -> addFieldInt( "type" );
	so -> addFieldObject( "scale" , Scale::getSerializeObject() );
}

void NNVariableSimple::serialize( SerializeObject& so )
{
	so.setPropInt( id , "id" );
	so.setPropInt( domain , "domain" );
	so.setPropInt( type , "type" );
	so.setPropObject( scale , "scale" );
}

void NNVariableSimple::deserialize( Object *parent , SerializeObject& so )
{
	id = so.getPropInt( "id" );
	domain = so.getPropInt( "domain" );
	type = ( NNVariable::VariableType )so.getPropInt( "type" );
	Scale *s = ( Scale * )so.getPropObject( "scale" , false );
	scale.set( *s );
}
