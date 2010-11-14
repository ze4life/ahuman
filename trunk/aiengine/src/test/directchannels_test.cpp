#include "test_impl.h"

/*#########################################################################*/
/*#########################################################################*/

class TestDirectChannels : public TestUnit , public Subscriber
{
// data
private:
	RFC_HND msgEvent;
	String pageResults;

// construction
public:
	TestDirectChannels() : TestUnit( "TestDirectChannels" ) {
		msgEvent = rfc_hnd_evcreate();
	};
	~TestDirectChannels() {
		rfc_hnd_evdestroy( msgEvent );
	};

	virtual void init() {
		ADD_METHOD( TestDirectChannels::testRequestPage );
	}
	virtual void exit() {
		rfc_hnd_evsignal( msgEvent );
	}
	
// tests
public:

	void testRequestPage( XmlCall& call ) {
		String page = call.getParam( "page" );
		
		AIIO io;
		Subscription *sub = io.subscribe( call.getSession() , "http.response" , "http.test" , this );
		Publisher *pub = io.createPublisher( call.getSession() , "http.request" , "http.test" , "text" );

		rfc_hnd_evreset( msgEvent );
		pageResults.clear();

		String pageQuery = "GET " + page;
		String msgId = pub -> publish( call.getSession() , pageQuery );

		rfc_hnd_waitevent( msgEvent );
		
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

