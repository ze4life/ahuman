#ifndef	INCLUDE_AILIBNN_IMPL_H
#define INCLUDE_AILIBNN_IMPL_H

#include <math.h>

#include <aiengine.h>
#include <ailibnn.h>
#include <aiknowledge.h>
#include <aisvcio.h>
#include <aisvcdb.h>

// neuro networks
#include "fann_custom_implfunc.h"
#include "fann_custom_implnn.h"
#include "fann_custom_implstrategy.h"
#include "fann_custom_implnet.h"

/*#########################################################################*/
/*#########################################################################*/

class NNFinderFactory;

class LibFannCustom : public AILibNNVariant
{
public:
	LibFannCustom() : AILibNNVariant( "LibFannCustom" ), engine( AIEngine::getInstance() ) {
		finderFactory = NULL;
		regressionFactory = NULL;
	};
	void init();
	
	static LibFannCustom *getInstance() {
		AILibNN nnlib;
		return( ( LibFannCustom * )nnlib.getLibVariant( "LibFannCustom" ) );
	}
	
	NNFinderFactory *getFinderFactory() {
		return( finderFactory );
	}
	NNRegressionFactory *getRegressionFactory() {
		return( regressionFactory );
	}
	
private:
	AIEngine& engine;
	NNFinderFactory *finderFactory;
	NNRegressionFactory *regressionFactory;
};

#endif	// INCLUDE_AILIBNN_IMPL_H
