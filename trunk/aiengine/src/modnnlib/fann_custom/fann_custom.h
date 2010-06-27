#ifndef	INCLUDE_AINNLIB_IMPL_H
#define INCLUDE_AINNLIB_IMPL_H

#include <math.h>

#include <aiengine.h>
#include <ainnlib.h>
#include <aiknowledge.h>
#include <aiio.h>
#include <aidb.h>

// neuro networks
#include "fann_custom_implfunc.h"
#include "fann_custom_implnn.h"
#include "fann_custom_implstrategy.h"
#include "fann_custom_implnet.h"

/*#########################################################################*/
/*#########################################################################*/

class NNFinderFactory;

class LibFannCustom : public AINNLibVariant
{
public:
	LibFannCustom() : AINNLibVariant( "LibFannCustom" ) {};
	void init();
	
	static LibFannCustom *getInstance() {
		AINNLib nnlib;
		return( ( LibFannCustom * )nnlib.getLibVariant( "LibFannCustom" ) );
	}
	
	NNFinderFactory *getFinderFactory() {
		return( finderFactory );
	}
	NNRegressionFactory *getRegressionFactory() {
		return( regressionFactory );
	}
	
private:
	NNFinderFactory *finderFactory;
	NNRegressionFactory *regressionFactory;
};

#endif	// INCLUDE_AINNLIB_IMPL_H
