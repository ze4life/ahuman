class String;
class Xml;
class AIApi;

class AIApiImpl;

// #############################################################################
// #############################################################################

class String
{
public:
	String();
	~String();
	String( const char *s );
	String( const String& s );

	String& operator +=( const char *v );
	String& operator +=( char v );
	String& operator +=( int v );
	String& operator +=( float v );
	operator const char *() const;
	String& operator =( const char *s );
	String& operator =( String& s );

	bool equals( const char *s );
	void clear();
	String& append( int count , char c );
	String& append( const char *s , int nChars );
	String& assign( const char *s , int nChars );

	void resize( int length );
	char *getBuffer();
	int size() const;
	int length() const;
	bool isEmpty() const;

	int findLastAny( const char *chars );
	int findLast( char c );
	String getMid( int from , int n );

private:
	void createFromString( const char *s );
private:
	char *v;
};

String operator +( const String& s1 , const char *s2 );
String operator +( const String& s1 , int value );
String operator +( const String& s1 , float value );
String operator +( const String& s1 , char value );
String operator +( const String& s1 , bool value );

/*#########################################################################*/
/*#########################################################################*/

class Xml
{
	friend class AIApi;

public:
	Xml();
	void attach( void *doc , void *node );
	bool exists();

	// direct data
	String getName();
	String getValue();
	String serialize();

	// navigation
	Xml getChildNode( String s );
	Xml getFirstChild( String name );
	Xml getNextChild( String name );

	// attributes
	String getAttribute( String a );
	String getAttribute( String a , String defaultValue );
	bool getBooleanAttribute( String a );
	void setAttribute( String a , String value );
	void setBooleanAttribute( String a , bool value );

	// properties
	String getProperty( String name );
	String getProperty( String name , String defaultValue );
	bool getBooleanProperty( String name );
	int getIntProperty( String name );
	int getIntProperty( String name , int defaultValue );
	float getFloatProperty( String name );
	float getFloatProperty( String name , float defaultValue );

	// elements
	Xml addTextElement( String name , String value );

public:
	void *doc;
	void *node;
};

/*#########################################################################*/
/*#########################################################################*/

class AIApi
{
public:
	AIApi();
	~AIApi();

public:
	void initThread();
	void exitThread();

	void connect( String url );
	void disconnect();
	bool isConnected();

	Xml execute();

	Xml createXmlRequest();
	Xml loadXmlRequest( String fileName );
	Xml readXmlRequest( const char *data );

private:
	AIApiImpl *api;
	Xml lastRequest;
	Xml lastResponse;
};

/*#########################################################################*/
/*#########################################################################*/
