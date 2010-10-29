#include <Windows.h>
#include "knowledge_impl.h"
#include "../svcio/io_impl.h"

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

/**
This is the default constructor and can be used to add any initialization
functionality 
*/

ImageQueryProcessor::ImageQueryProcessor():engine(AIEngine::getInstance()){
		/* Create socket */
	WSADATA l_wsa;
	LPHOSTENT  hostEntry;
	memset( &l_wsa, 0 , sizeof( WSADATA ) );
	WSAStartup( MAKEWORD( 2 , 2 ) , &l_wsa );
	sock = socket(AF_INET,SOCK_STREAM, 0);
	if(sock == SOCKET_ERROR){
		logger.logDebug( "ImageQueryProcessor::processQuery - Could not create socket.");
		return;	
	}
	memset(&add, 0, sizeof(SOCKADDR_IN));
	hostEntry = gethostbyname("localhost");
	add.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	add.sin_family = AF_INET;
	add.sin_port = htons(9000);
}

/**
Function called when we get message in the queue 
*/
void ImageQueryProcessor::onMessage( Message *msg ) {
	logger.logDebug( "ImageQueryProcessor::onMessage - Got message to be processed.");
	/* Get results from internet and feed the channel */
	if(sock != SOCKET_ERROR){
		processQuery(msg);
	}
}

/**
Function responsible to fetch image data from image knowledge base server 
*/
void ImageQueryProcessor::processQuery(Message* msg){
	
	AIIOImpl *srv = (AIIOImpl*)engine.getService("IO");
	Publisher *pub = srv->createPublisher( msg->getSession() , "imagekbrsp" , "ImageQueryResults" , "IMGRES" );
	if(connect(sock,(LPSOCKADDR)&add,sizeof(SOCKADDR_IN)) == SOCKET_ERROR){
		logger.logDebug( "ImageQueryProcessor::processQuery - Could not connect to data source.");
		return;
	}
	/* Get the query from the message */
	TextMessage *tmsg = (TextMessage*)msg;
	const char *query = tmsg->getText();
	char * qu = new char[strlen(query)];
	strcpy(qu, query);
	send(sock, query, strlen(query), 0);
	char* q = strtok(qu,";");
	int x = atoi(strtok(NULL,";"));
	int y = atoi(strtok(NULL,";"));
	int samples = atoi(strtok(NULL,";"));
	char *ch = new char[x * y];
	for(int i = 0; i < samples; i++){
		int res = recv(sock, ch, x * y, 0);
		if(res <= 0) break;
		/* publish results to the channel */
		pub->publish(msg->getSession(), ch);
	}
}

/********************************************************************************/
/********************************************************************************/
ImageKnowledgeBase* ImageKnowledgeBase::instance = NULL;

ImageKnowledgeBase::ImageKnowledgeBase():engine(AIEngine::getInstance()){
		
}
void ImageKnowledgeBase::startKnowledgeSource(){
	AIIOImpl *srv = (AIIOImpl*)engine.getService("IO");
	/* Create a subscriber to process the messages */
	ImageQueryProcessor *sub = new ImageQueryProcessor();
	Session *session = srv->createSession(); 
	srv->subscribe(NULL,"imagekbcmd","ImageQueryProcessor", sub);
	logger.logDebug( "ImageKnowledgeBase::startKnowledgeSource - Source started");
}

void ImageKnowledgeBase::stopKnowledgeSource(){
	
}
