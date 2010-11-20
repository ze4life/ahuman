#include "knowledge_impl.h"

/*************************************************************************************
The logic for getting information is that the module will get the command
using a IO channel which is hardcoded to 'imagekbcmd' for now and it will add
subscriber which will be responsible to get information from the ImageKnowledgeBase
server which is presently implemented in JAVA and uses bing search API to fetch 
images.

On getting the information from web it will publich the results in the IO channel
which is hardcoded to 'imagekbrsp' for now.

Anymodule who is interested in the image data can subscribe to the channel and can
get results. Any module can publish to the 'imagekbcmd' to activate the search process

***************************************************************************************/

class ImageKnowledgeBase : public KnowledgeController , public Subscriber
{
private:
	AIEngine& engine;
	RFC_HND thread;

	String externalChannel;
	String commandChannel;
	String responseChannel;

	Publisher *publisher;
	Subscription *subscription;

public:

ImageKnowledgeBase()
:	KnowledgeController( getClass() ) , 
	engine( AIEngine::getInstance() )
{
}

const char *getClass() { return( "ImageKnowledgeBase" ); };

public:

virtual void onTextMessage( TextMessage *msg )
{
	logger.logDebug( "onTextMessage: got message to be processed");
	processQuery( msg -> getText() );
}

virtual void createController( Xml config )
{
	externalChannel = config.getProperty( "external-channel" );
	commandChannel = config.getProperty( "command-topic" );
	responseChannel = config.getProperty( "response-topic" );
}

virtual void startController()
{
	// create publisher
	AIIO io;
	publisher = io.createPublisher( NULL , responseChannel , "ImageQueryResults" , "IMGRES" );

	/* Create a subscriber to process the messages */
	subscription = io.subscribe( NULL , commandChannel , "ImageQueryProcessor" , this );
	logger.logDebug( "startKnowledgeSource: Source started");
}

virtual void stopController()
{
	AIIO io;
	io.unsubscribe( subscription );
	io.destroyPublisher( publisher );

	subscription = NULL;
	publisher = NULL;
}

private:

/**
Function responsible to fetch image data from image knowledge base server 
*/
void processQuery( String query )
{
	AIMedia media;

	/* Get the query from the message */
	media.sendTextToDirectChannel( externalChannel , query );

	StringList list;
	query.split( list , ";" );

	ASSERTMSG( list.count() == 4 , "Invalid query - expecting 4 tokens, query=" + query );

	String q = list.get( 0 );
	int x = atoi( list.get( 1 ) );
	int y = atoi( list.get( 2 ) );
	int samples = atoi( list.get( 3 ) );

	for( int i = 0; i < samples; i++ ) {
		// read and publish to channel
		String data = media.receiveFixedSizeTextFromDirectChannel( externalChannel , x * y );
		publisher -> publish( NULL , data );
	}
}

}; // class

KnowledgeController *KnowledgeController::createImageKnowledgeBase()
{
	return( new ImageKnowledgeBase() );
}

