#include "test_impl.h"

/*#########################################################################*/
/*#########################################################################*/

class TestDirectChannels : public TestUnit , public Subscriber
{
// data
private:
	RFC_HND msgEvent;
	String pageResults;

	Subscription *sub;
	Publisher *pub;

// construction
public:
	TestDirectChannels() : TestUnit( "TestDirectChannels" ) {
		msgEvent = rfc_hnd_evcreate();

		pub = NULL;
		sub = NULL;
	};
	~TestDirectChannels() {
		rfc_hnd_evdestroy( msgEvent );
	};

	virtual void init() {
		ADD_METHOD( TestDirectChannels::testRequestPage );

		AIIO io;
		sub = io.subscribe( NULL , "http.response" , "http.test" , this );
		pub = io.createPublisher( NULL , "http.request" , "http.test" , "text" );
	}
	virtual void exit() {
		rfc_hnd_evsignal( msgEvent );
	}
	
// tests
public:

	void testRequestPage( XmlCall& call ) {
		String page = call.getParam( "page" );
		
		rfc_hnd_evreset( msgEvent );
		pageResults.clear();

		String pageQuery = "GET " + page;
		String msgId = pub -> publish( call.getSession() , pageQuery );

		rfc_hnd_waitevent( msgEvent , 5000 );
		
		ASSERTMSG( !pageResults.isEmpty() , "No response from google page=" + page );
		Xml xml = call.createResponse();
		xml.addTextElement( "request" , page );
		xml.addTextElement( "response" , pageResults );
	}

	virtual void onTextMessage( TextMessage *msg ) {
		pageResults = msg -> getText();
		rfc_hnd_evsignal( msgEvent );
	}
};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createDirectChannelsTest() {
	return( new TestDirectChannels );
}

