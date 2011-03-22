#include "fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

AILibNNVariant *AILibNNVariant::createFannCustom() {
	LibFannCustom *lib = new LibFannCustom();
	lib -> init();
	return( lib );
}

/*#########################################################################*/
/*#########################################################################*/

void LibFannCustom::init() {
	// register serialisable classes
	NNVariable::createSerializeObject();
	NNVariableSimple::createSerializeObject();
	NNVariableCategory::createSerializeObject();
	NNVariables::createSerializeObject();
	NNVariablesContainer::createSerializeObject();
	NNSample::createSerializeObject();
	NNSamples::createSerializeObject();
	NNWeights::createSerializeObject();

	NNErrorFunction::createSerializeObject();
	NNInductionFunction::createSerializeObject();
	NNActivationFunction::createSerializeObject();
	NNValidateFunction::createSerializeObject();
	NNStopFunction::createSerializeObject();

	NNNeuron::createSerializeObject();
	NNLayer::createSerializeObject();
	NN::createSerializeObject();

	NNStrategyBackPropagation::createSerializeObject();
	NNStrategyScan::createSerializeObject();

	NNRegression::createSerializeObject();
	NNRegressionFactory::createSerializeObject();
	NNFinder::createSerializeObject();
	NNFinderFactory::createSerializeObject();
}
