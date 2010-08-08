#include <aiengine.h>
#include <aisvcio.h>
#include <test.h>

// core classes
class TestUnit;
class TestMethod;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AITestPoolImpl : public AITestPool , public Service , public Subscriber
{
public:
	// service
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "TestPool" ); };

	// subscriber
	virtual void onXmlCall( XmlCall *msg );

// external interface
public:
	AITestPoolImpl();
	static AITestPoolImpl *getServiceImpl();

// internals
private:
	void addTestUnit( TestUnit *p_unit );

private:
	AIEngine& engine;

	Publisher *callPub;
	Subscription *callSub;
	MapStringToClass<TestUnit> units;
};

/*#########################################################################*/
/*#########################################################################*/

typedef void ( TestUnit::*TestUnitMethodType )( XmlCall& );
#define ADD_METHOD( method ) TestUnit::addMethod( #method , ( TestUnitMethodType )&method )

class TestMethod
{
public:
	TestMethod( String p_name , TestUnitMethodType p_fptr ) {
		name = p_name;
		fptr = p_fptr;
	}
	
	String name;
	TestUnitMethodType fptr;
};

/*#########################################################################*/
/*#########################################################################*/

class TestUnit
{
// test units
public:
	static TestUnit *createFannCustom();
	static TestUnit *createHtmViewCustom();

// generic
public:
	TestUnit( String p_name ) {
		name = p_name;
	}
	~TestUnit() {
		methods.destroy();
	}

	String getName() {
		return( name );
	}

	void create() {
		logger.attach( name );
		init();
	}

	TestMethod *getMethod( String methodName ) {
		return( methods.get( methodName ) );
	}
	
	void callMethod( TestMethod *method , XmlCall& call ) {
		( *this.*(method->fptr) )( call );
	}
	
	virtual void init() = 0;
	
protected:
	void addMethod( String methodName , TestUnitMethodType methodFunction ) {
		methods.add( methodName , new TestMethod( methodName , methodFunction ) );
	}

// virtuals
public:
	Logger logger;
	
	String name;
	MapStringToClass<TestMethod> methods;
};

/*#########################################################################*/
/*#########################################################################*/
