#include "fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

NNVariableCategory::NNVariableCategory()
:	NNVariable( NNVariable::VarCategory )
{
	categoryCount = 0;
	value = 0;
}

NNVariableCategory::~NNVariableCategory()
{
}

// value
void NNVariableCategory::clearValue()
{
	value = 0;
}

float NNVariableCategory::getValue()
{
	return( value );
}

// attach to NN
NNVariable::Mapping *NNVariableCategory::attachAsSensor( NN *nn , float * const *values )
{
	NNVariableCategory::Mapping *vm = sensorMapping.add();
	vm -> objs.var = this;
	vm -> objs.p = nn;
	vm -> pv = new FlatList<float *>;
	vm -> pv -> set( values , categoryCount - 1 );
	vm -> pvBack = NULL;

	return( ( NNVariable::Mapping * )vm );
}

NNVariable::Mapping *NNVariableCategory::attachAsTarget( NN *nn , float **values , float * const *valuesBack )
{
	NNVariableCategory::Mapping *vm = targetMapping.add();
	vm -> objs.var = this;
	vm -> objs.p = nn;
	vm -> pv = new FlatList<float *>;
	vm -> pv -> set( values , categoryCount - 1 );
	vm -> pvBack = new FlatList<float *>;
	vm -> pvBack -> set( valuesBack , categoryCount - 1 );

	return( ( NNVariable::Mapping * )vm );
}

// representation
int NNVariableCategory::getRepresentationSize()
{
	// total N-1 booleans: false=-1, true=1
	// if all outputs < -0.6 then category N
	// if all outputs < -0.6 except k-th which is > 0.6, then it is category (k+1)
	// else it is unknown category = 0
	return( categoryCount - 1 );
}

void NNVariableCategory::setValueAndCalculateRepresentation( float p_value , NNVariable::Mapping *vm )
{
	value = ( int )p_value;
	float **pv = ( ( NNVariableCategory::Mapping * )vm ) -> pv -> getAll();
	for( int k = 0; k < categoryCount - 1; k++ )
		*( pv[ k ] ) = ( value == (k+1) )? 1 : -1;
}

void NNVariableCategory::calculateBackRepresentation( float p_value , NNVariable::Mapping *vm )
{
	int x_value = ( int )p_value;
	float **pv = ( ( NNVariableCategory::Mapping * )vm ) -> pvBack -> getAll();
	for( int k = 0; k < categoryCount - 1; k++ )
		*( pv[ k ] ) = ( x_value == (k+1) )? 1 : -1;
}

void NNVariableCategory::calculateValueFromRepresentation( NNVariable::Mapping *vm )
{
	// make most probable response
	float **pv = ( ( NNVariableCategory::Mapping * )vm ) -> pv -> getAll();
	int maxClass = 0;
	for( int k = 0; k < categoryCount - 1; k++ )
		{
			float v = *( pv[ k ] );
			if( v >= 0.6 )
				{
					if( maxClass > 0 )
						{
							// more than one output is actioned - no class assigned
							value = 0;
							return;
						}

					maxClass = k + 1;
				}
			else
			if( v > -0.6 )
				{
					// unclassified signal
					value = 0;
					return;
				}
		}

	// no output means last class
	if( maxClass == 0 )
		value = categoryCount - 1;
	else
		value = maxClass;
}

/*#########################################################################*/
/*#########################################################################*/

const char *NNVariableCategory::NAME = "NNVariableCategory";

void NNVariableCategory::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNVariableCategory::onCreate );

	// add own fields
	so -> addFieldInt( "id" );
	so -> addFieldInt( "domain" );
	so -> addFieldInt( "type" );
	so -> addFieldInt( "categoryCount" );
}

void NNVariableCategory::serialize( SerializeObject& so )
{
	so.setPropInt( id , "id" );
	so.setPropInt( domain , "domain" );
	so.setPropInt( type , "type" );
	so.setPropInt( categoryCount , "categoryCount" );
}

void NNVariableCategory::deserialize( Object *parent , SerializeObject& so )
{
	id = so.getPropInt( "id" );
	domain = so.getPropInt( "domain" );
	type = ( NNVariable::VariableType )so.getPropInt( "type" );
	categoryCount = so.getPropInt( "categoryCount" );
}
