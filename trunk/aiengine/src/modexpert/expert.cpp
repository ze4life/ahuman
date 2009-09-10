
#include "aiexpert_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIExpert::AIExpert() 
{ 
	thisPtr = AIExpertImpl::getServiceImpl(); 
}

AIExpertImpl *AIExpertImpl::getServiceImpl()
{
	return( static_cast<AIExpertImpl *>( AIEngine::getInstance().getService( "AIExpert" ) ) );
}

/* static */ Service *AIExpert::createService()
{
	Service *svc = new AIExpertImpl();
	AIEngine::getInstance().registerService( svc , "AIExpert" );
	return( svc );
}

AIExpertImpl::AIExpertImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIExpertImpl::initService()
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

void AIExpertImpl::runService()
{
	// load variables container
	NNVariablesContainer *vc = NNVariablesContainer::getInstance();
	AIDB db;
	db.load( vc , "main" );

	// load expert factory
	expertRegressionFactory.init();
	expertFinderFactory.init();

	// test able to create new expertFinder by samples
	// testCreateBySamples();

	// play/train with finder
	// expertFinderFactory.testPlay();
	// expertFinderFactory.testFactory();
	db.save( vc , "main" );

	// register debug call subscriber
	debug.init( config );
}

void AIExpertImpl::exitService()
{
	debug.exit();
}

void AIExpertImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

