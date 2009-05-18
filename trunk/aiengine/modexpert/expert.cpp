
#include <aiexpert_impl.h>

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
	tokenParser = NULL;
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

	setupTokens();

	// load expert factory
	expertRegressionFactory.init();
	expertFinderFactory.init();

	// test able to create new expertFinder by samples
	// testCreateBySamples();

	// play/train with finder
	// expertFinderFactory.testPlay();
	// expertFinderFactory.testFactory();

	db.save( vc , "main" );
}

void AIExpertImpl::testCreateBySamples()
{
	// create samples to check factory
	float inputN = -1;
	float inputY = 1;
	float inputMin[2] = { inputN , inputN };
	float inputMax[2] = { inputY , inputY };
	int classCount = 1;
	int sensorCount = 2;
	NNSamples *samplesLearn = expertFinderFactory.createSamples( sensorCount , classCount );

	// fill samples
	Random rnd;
	rnd.createRangeRandomsFloat( inputN , inputY );
	float vi[2];

	for( int z1 = 100; z1--; )
		{
			vi[0] = rnd.getRandomFloat();
			vi[1] = rnd.getRandomFloat();
			int clusterID = ( vi[0] < 0 || vi[1] < 0 )? 0 : 1;
			expertFinderFactory.addSample( samplesLearn , vi , clusterID );
		}

	// create finder
	NNFinder *ef = expertFinderFactory.create( samplesLearn );
	
	delete ef;
	delete samplesLearn;
}

void AIExpertImpl::exitService()
{
	/* nothing to do */
}

void AIExpertImpl::destroyService()
{
	if( tokenParser != NULL )
		delete tokenParser;

	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

void AIExpertImpl::setupTokens()
{
	tokenParser = new AITokenParser();
}

void AIExpertImpl::processMediaMessage( AIMessage *msg , AISession *session )
{
	// split into token sentenses
	ClassList<AISentense> text;
	tokenParser -> splitToSentenses( msg , text );

	for( int k = 0; k < text.count(); k++ )
		{
			AISentense *s = text.get( k );
			processSentense( session , s );
		}

	text.destroy();
}

void AIExpertImpl::processSentense( AISession *session , AISentense *st )
{
	// handle by token pairs
	ClassList<AIToken>& tokens = st -> getTokens();

	AIKnowledge knowledge;
	for( int k = 1; k < tokens.count(); k++ )
		{
			AIToken *left = tokens[ k - 1 ];
			AIToken *right = tokens[ k ];

			// associate
			knowledge.associate( session , left , right );
		}
}
