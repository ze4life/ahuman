#include  "../body_impl.h"

#include <rebecca/all.h>
#include <rebecca/network_all.h>
#include "lyrnx.h"
using namespace rebecca;

// #############################################################################
// #############################################################################

class RebeccaChat : public PhysioControl , public Subscriber {
private:
	String inTopic;
	String outTopic;

	Publisher *pub;
	Subscription *sub;
	GraphBuilder *builder;
	AimlFacade aiml;

public:

RebeccaChat()
:	PhysioControl( "RebeccaChat" )
{
	pub = NULL;
	sub = NULL;
	builder = NULL;
};

virtual const char *getClass()
{
	return( "RebeccaChat" );
}

// physiology overridables
virtual void create( Xml config )
{
	inTopic = config.getProperty( "ear-listner-topic" );
	outTopic = config.getProperty( "mouth-speaker-topic" );
}

virtual void start()
{
	AIIO io;
	pub = io.createPublisher( NULL , outTopic , "MOUTHRES" , "TALK" );

	/* Create a subscriber to process the messages */
	sub = io.subscribe( NULL , inTopic , "EarListener" , this );

	logger.logInfo( "start rebecca chat engine..." ); 
	builder = &aiml.getGraphBuilder();

	AIEngine& engine = AIEngine::getInstance();
	builder -> setAIMLSchema( ( const char * )engine.getConfigurationPath( "rebecca/xsd/AIML.xsd" ) );
	builder -> setCommonTypesSchema( ( const char * )engine.getConfigurationPath( "rebecca/xsd/common-types.xsd" ) );
	builder -> setBotConfigurationSchema( ( const char * )engine.getConfigurationPath( "rebecca/xsd/bot-configuration.xsd" ) );

	// set to true that we want to do XML validation    
	builder -> setAIMLValidation();
	builder -> setBotConfigurationValidation();

	// parse the substitutions file
	builder -> parseSubstitutionFile( ( const char * )engine.getConfigurationPath( "rebecca/substitutions.xml" ) );

	// parse sentence splitters
	builder -> parseSentenceSplitterFile( ( const char * )engine.getConfigurationPath( "rebecca/sentence-splitters.xml" ) );

	// parse bot properties    
	builder -> parsePropertiesFile( ( const char * )engine.getConfigurationPath( "rebecca/properties.xml" ) );

	// add the AIML directory unless its already added    
	builder -> addDirectoryUnlessAlreadyAdded( ( const char * )engine.getConfigurationPath( "rebecca/aiml" ) );

	logger.logInfo( "prepare rebecca chat engine database..." ); 
	builder -> createGraph();
	logger.logInfo( "rebecca chat engine started" ); 

	string botName = builder -> getBotPredicate( "name" ).c_str();
	StringPimpl response = builder -> getResponse( "connect" );
}

virtual void stop()
{
	AIIO io;
	io.unsubscribe( sub);
	io.destroyPublisher( pub );
	sub = NULL;
	pub = NULL;
}

virtual void onTextMessage( TextMessage * msg )
{
	TextMessage* resmsg = new TextMessage();
	String s = msg->getText();
	char *ch = s.getBuffer();
	StringPimpl response = builder->getResponse(ch);
	const char* res = response.c_str();
	// Call the lyrnx body part for creating voice
	lyrnx::play((char*)res);
	resmsg->setText(res);
	pub->publish(NULL, resmsg);
}

};

// #############################################################################
// #############################################################################

PhysioControl *PhysioControl::createRebeccaChat()
{
	return( new RebeccaChat() );
}
