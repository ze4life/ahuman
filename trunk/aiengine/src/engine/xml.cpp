
#include "engine_impl.h"

/*#########################################################################*/
/*#########################################################################*/

Xml::Xml()
{
	doc = NULL;
	node = NULL;
}

void Xml::attach( void *p_doc , void *p_node )
{
	doc = p_doc;
	node = p_node;
}

String Xml::getName()
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	return( xml -> Value() );
}

String Xml::getValue()
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	return( xml -> GetText() );
}

String Xml::getHeading()
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;

	std::string x;
	xml -> PrintWithoutChilds( &x , 0 );

	String s = x.c_str();
	return( s );
}

Xml Xml::getChildNode( String s )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	TiXmlElement *xmlChild = NULL;
	try {
		xmlChild = xml -> FirstChildElement( s );
	}
	catch( ... ) {
	}

	ASSERTMSG( xmlChild != NULL , String( "child node " ) + s + " not found" );
	Xml x;
	x.attach( doc , xmlChild );

	return( x );
}

String Xml::getAttribute( String a )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	const char *v = xml -> Attribute( a );

	ASSERTMSG( v != NULL , String( "attribute " ) + a + " not found" );
	return( v );
}

String Xml::getAttribute( String a , String defaultValue )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	const char *v = xml -> Attribute( a );

	if( v == NULL )
		return( defaultValue );

	return( v );
}

bool Xml::getBooleanAttribute( String a )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	return( getAttribute( a , "false" ).equals( "true" ) );
}

int Xml::getIntAttribute( String a )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	const char *v = xml -> Attribute( a );

	ASSERTMSG( v != NULL , a + " attribute is NULL" );
	int value = 0;
	ASSERTMSG( sscanf( v , "%d" , &value ) == 1 , "Unable to parse integer in string: " + a );
	return( value );
}

String Xml::getProperty( String name )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	TiXmlElement *xmlChild = xml -> FirstChildElement( "property" );
	while( xmlChild != NULL )
		{
			String nameFound = xmlChild -> Attribute( "name" );
			if( nameFound.equals( name ) )
				break;

			xmlChild = xmlChild -> NextSiblingElement();
		}

	ASSERTMSG( xmlChild != NULL , String( "property " ) + name + " not found" );

	const char *v = xmlChild -> Attribute( "value" );
	ASSERTMSG( v != NULL , String( "property " ) + name + " has no value attribute" );
	return( v );
}

bool Xml::getBooleanProperty( String name )
{
	String prop = getProperty( name , "false" );
	return( prop.equals( "true" ) );
}

int Xml::getIntProperty( String name )
{
	String prop = getProperty( name );
	char c;
	int v;
	ASSERT( sscanf( prop , "%d%c" , &v , &c ) == 1 );
	return( v );
}

int Xml::getIntProperty( String name , int defaultValue )
{
	char buf[ 12 ];
	sprintf( buf , "%d" , defaultValue );
	String prop = getProperty( name , buf );
	char c;
	int v;
	ASSERT( sscanf( prop , "%d%c" , &v , &c ) == 1 );
	return( v );
}

float Xml::getFloatProperty( String name )
{
	String prop = getProperty( name );
	char c;
	float v;
	ASSERT( sscanf( prop , "%f%c" , &v , &c ) == 1 );
	return( v );
}

float Xml::getFloatProperty( String name , float defaultValue )
{
	char buf[ 40 ];
	sprintf( buf , "%f" , defaultValue );
	String prop = getProperty( name , buf );
	char c;
	float v;
	ASSERT( sscanf( prop , "%f%c" , &v , &c ) == 1 );
	return( v );
}

String Xml::getProperty( String name , String defaultValue )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	TiXmlElement *xmlChild = xml -> FirstChildElement( "property" );
	while( xmlChild != NULL )
		{
			String nameFound = xmlChild -> Attribute( "name" );
			if( nameFound.equals( name ) )
				break;

			xmlChild = xmlChild -> NextSiblingElement();
		}

	if( xmlChild == NULL )
		return( defaultValue );

	const char *v = xmlChild -> Attribute( "value" );
	ASSERTMSG( v != NULL , String( "property " ) + name + " has no value attribute" );

	if( *v == 0 )
		return( defaultValue );

	return( v );
}

bool Xml::exists()
{
	return( node != NULL );
}

void Xml::setAttribute( String a , String value )
{
	ASSERT( node != NULL );
	TiXmlElement *xml = ( TiXmlElement * )node;

	xml -> SetAttribute( a , value );
}

void Xml::setBooleanAttribute( String a , bool value )
{
	ASSERT( node != NULL );
	TiXmlElement *xml = ( TiXmlElement * )node;

	const char *valueStr = ( value )? "true" : "false";
	xml -> SetAttribute( a , valueStr );
}

void Xml::setIntAttribute( String a , int value )
{
	ASSERT( node != NULL );
	TiXmlElement *xml = ( TiXmlElement * )node;

	char v[ 15 ];
	sprintf( v , "%d" , value );
	xml -> SetAttribute( a , v );
}

Xml Xml::getFirstChild( String name )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;

	TiXmlElement *xmlChild = NULL;
	try {
		xmlChild = xml -> FirstChildElement( name );
	}
	catch( ... ) {
	}

	Xml item;
	item.attach( doc , xmlChild );
	return( item );
}

Xml Xml::getNextChild( String name )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	TiXmlElement *xmlChild = xml -> NextSiblingElement( name );

	Xml item;
	item.attach( doc , xmlChild );
	return( item );
}

void Xml::getProperties( MapStringToString& map )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	TiXmlElement *xmlChild = xml -> FirstChildElement( "property" );
	while( xmlChild != NULL )
		{
			String name = xmlChild -> Attribute( "name" );
			String value = xmlChild -> Attribute( "value" );
			map.add( name , value );

			xmlChild = xmlChild -> NextSiblingElement();
		}
}

String Xml::serialize()
{
	TiXmlDocument *l_doc = ( TiXmlDocument * )doc;

	std::string x;
	l_doc -> Print( &x , 0 );

	String s = x.c_str();
	return( s );
}

Xml Xml::addTextElement( String name , String value )
{
	ASSERT( node != NULL );

	TiXmlElement *xml = ( TiXmlElement * )node;
	TiXmlText *xmlValue = new TiXmlText( name );
	xml -> LinkEndChild( xmlValue );

	xmlValue -> SetValue( value );

	Xml ret;
	ret.attach( doc , xmlValue );
	return( ret );
}

Xml Xml::addElement( String name )
{
	ASSERT( node != NULL );

	TiXmlNode *xml = ( TiXmlNode * )node;
	TiXmlElement *xmlProp = new TiXmlElement( name );
	xml -> LinkEndChild( xmlProp );

	Xml ret;
	ret.attach( doc , xmlProp );
	return( ret );
}

void Xml::setProperty( String name , String value )
{
	ASSERT( node != NULL );

	TiXmlNode *xml = ( TiXmlNode * )node;
	TiXmlElement *xmlProp = new TiXmlElement( "property" );
	xmlProp -> SetAttribute( "name" , name );
	xmlProp -> SetAttribute( "value" , value );
	xml -> LinkEndChild( xmlProp );
}

void Xml::setBooleanProperty( String name , bool value )
{
	setProperty( name , ( ( value )? "true" : "false" ) );
}

void Xml::setIntProperty( String name , int value )
{
	char l_buf[ 12 ];
	sprintf( l_buf , "%d" , value );
	setProperty( name , l_buf );
}

void Xml::setFloatProperty( String name , float value )
{
	char l_buf[ 40 ];
	sprintf( l_buf , "%f" , value );
	setProperty( name , l_buf );
}

Xml Xml::findChildByPath( String path )
{
	Xml xml = *this;

	const char *p = path;
	while( *p ) {
		const char *np = strchr( p , '/' );

		String key;
		if( np == NULL ) {
			key = p;
			p += strlen( p );
		}
		else {
			key = path.getMid( p - path , np - p );
			p = np + 1;
		}

		xml = xml.getFirstChild( key );
		if( !xml.exists() )
			return( xml );
	}

	return( xml );
}

Xml Xml::findChildByPathAttr( String path , String attr , String value )
{
	Xml xml = findChildByPath( path );
	if( !xml.exists() )
		return( xml );

	String key;
	int index = path.findLast( '/' );
	if( index < 0 )
		key = path;
	else
		key = path.getMid( index + 1 );

	while( xml.exists() ) {
		if( xml.getAttribute( attr , "" ).equals( value ) )
			return( xml );

		xml = xml.getNextChild( key );
	}
	return( xml );
}

