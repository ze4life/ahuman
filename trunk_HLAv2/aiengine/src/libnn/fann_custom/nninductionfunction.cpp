#include "fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

NNInductionFunction::NNInductionFunction()
{
	functionType = FANN_EMPTY;
}

NNInductionFunction::~NNInductionFunction()
{
}

void NNInductionFunction::setWeightedSum()
{
	functionType = FANN_WEIGHTEDSUM;
}

float NNInductionFunction::getDerivative( float s , NNConnection *ic )
{
	// now the only function type implemented
	return( ic -> weight );
}

float NNInductionFunction::calculate( FixedPtrList<NNConnection>& inputs )
{
	// now the only function type implemented
	float sum = 0;
	NNConnection * const *ic = inputs.getAll();
	for( int k = 0; k < inputs.count(); k++ , ic++ )
		sum += (*ic) -> weight * *( (*ic) -> inputPtr );

	return( sum );
}

void NNInductionFunction::set( const NNInductionFunction *p_f )
{
	functionType = p_f -> functionType;
}

// Object interface
const char *NNInductionFunction::NAME = "NNInductionFunction";

void NNInductionFunction::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNInductionFunction::onCreate );

	so -> addFieldInt( "functionType" );
}

void NNInductionFunction::serialize( SerializeObject& so )
{
	so.setPropInt( functionType , "functionType" );
}

void NNInductionFunction::deserialize( Object *parent , SerializeObject& so )
{
	functionType = ( InductionFunction )so.getPropInt( "functionType" );
}
