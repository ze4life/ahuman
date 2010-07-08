#include "fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

AINNLib::AINNLib() 
{ 
	thisPtr = AINNLibImpl::getServiceImpl(); 
}

AINNLibImpl *AINNLibImpl::getServiceImpl()
{
	return( static_cast<AINNLibImpl *>( AIEngine::getInstance().getService( "AINNLib" ) ) );
}

/* static */ Service *AINNLib::createService()
{
	Service *svc = new AINNLibImpl();
	AIEngine::getInstance().registerService( svc , "AINNLib" );
	return( svc );
}

AINNLibImpl::AINNLibImpl()
:	engine( AIEngine::getInstance() )
{
}

void AINNLibImpl::initService()
{
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

void AINNLibImpl::runService()
{
	// load variables container
	NNVariablesContainer *vc = NNVariablesContainer::getInstance();
	AIDB db;
	db.load( vc , "main" );

	// load factories
	regressionFactory.init();
	finderFactory.init();
	db.save( vc , "main" );

	// register debug call subscriber
	debug.init( config );
}

void AINNLibImpl::exitService()
{
	debug.exit();
}

void AINNLibImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

