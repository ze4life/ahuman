#include <aiengine.h>
#include <aisvcio.h>
#include <rebecca/all.h>
using namespace rebecca;

#include  "body_impl.h"

ChatInterface::ChatInterface(){}

void ChatInterface::onTextMessage(TextMessage *msg ){
	TextMessage* resmsg = new TextMessage();
	String s = msg->getText();
	char *ch = s.getBuffer();
	StringPimpl response = builder->getResponse(ch);
	const char* res = response.c_str();
	resmsg->setText(res);
	pub->publish(NULL, resmsg);
}

void ChatInterface::createService(Xml config){
	inTopic = config.getProperty( "ear-listner-topic" );
	outTopic = config.getProperty( "mouth-speaker-topic" );
}

void ChatInterface::initService(){
	AIIO io;
	pub = io.createPublisher( NULL , outTopic , "MOUTHRES" , "TALK" );
	/* Create a subscriber to process the messages */
	sub = io.subscribe( NULL , inTopic , "EarListener" , this );
	builder = &aiml.getGraphBuilder();
	builder->setAIMLSchema("resources\\schema\\AIML.xsd");
	builder->setCommonTypesSchema("resources\\schema\\common-types.xsd");
	builder->setBotConfigurationSchema("resources\\schema\\bot-configuration.xsd");
	//set to true that we want to do XML validation    
	builder->setAIMLValidation();
	builder->setBotConfigurationValidation();
	//parse the substitutions file
	builder->parseSubstitutionFile("conf\\substitutions.xml");
	//parse sentence splitters
	builder->parseSentenceSplitterFile("conf\\sentence-splitters.xml");
	//parse bot properties    
	builder->parsePropertiesFile("conf\\properties.xml");
	//add the AIML directory unless its already added    
	builder->addDirectoryUnlessAlreadyAdded("aiml\\annotated_alice");
	builder->createGraph();
	string botName = builder->getBotPredicate("name").c_str();
	StringPimpl response = builder->getResponse("connect");		
}

void ChatInterface::runService(){


}

void ChatInterface::exitService(){

}

void ChatInterface::destroyService(){
	AIIO io;
	io.unsubscribe( sub);
	io.destroyPublisher( pub );
	sub = NULL;
	pub = NULL;
}
