
#include "aiengine_impl.h"

// #############################################################################
// #############################################################################

typedef struct {
	int size;
} StringData;

static StringData *getData( char *p )
{
	return( ( StringData * )( p - sizeof( StringData ) ) );
}

static StringData *ensureFreeSpace( char *& p , int space )
{
	// create new
	if( p == NULL )
		{
			StringData *d = ( StringData * )malloc( sizeof( StringData ) + space + 1 );
			p = ( char * )( d + 1 );
			*p = 0;

			d -> size = space;
			return( d );
		}
				
	// if space already exists
	StringData *d = getData( p );
	if( d -> size - strlen( p ) >= space )
		return( d );

	// reallocation
	if( space < 16 )
		space = 16;

	int sizeNew = strlen( p ) + space;
	d = ( StringData * )realloc( d , sizeof( StringData ) + sizeNew + 1 );
	d -> size = sizeNew;

	p = ( char * )( d + 1 );
	return( d );
}

// class String
String::String()
{
	v = NULL;
}

String::~String()
{
	if( v != NULL )
		free( getData( v ) );
}

String::String( const char *s )
{
	v = NULL;
	if( s != NULL )
		assign( s , strlen( s ) );
}

void String::createFromString( const char *s )
{
	assign( s , strlen( s ) );
}

String::String( const String& s )
{
	v = NULL;
	assign( s , s.length() );
}

bool String::equals( const char *s )
{
	if( v == NULL )
		return( s == NULL || *s == 0 );
	if( s == NULL )
		return( *v == 0 );

	return( strcmp( s , v ) == 0 );
}

String& String::operator +=( const char *s )
{
	if( s == NULL )
		return( *this );

	if( v == NULL )
		return( assign( s , strlen( s ) ) );

	return( append( s , strlen( s ) ) );
}

String& String::append( const char *s ,  int n2 )
{
	if( s == NULL )
		return( *this );

	if( v == NULL )
		return( assign( s , n2 ) );

	StringData *d = ensureFreeSpace( v , n2 );

	int len = strlen( v );
	memcpy( v + len , s , n2 );
	v[ len + n2 ] = 0;

	return( *this );
}

String& String::operator +=( char c )
{
	return( append( &c , 1 ) );
}

String& String::operator +=( int v )
{
	char l_buf[ 12 ];
	sprintf( l_buf , "%d" , v );
	return( append( l_buf , strlen( l_buf ) ) );
}

String& String::operator +=( float v )
{
	char l_buf[ 30 ];
	sprintf( l_buf , "%g" , v );
	return( append( l_buf , strlen( l_buf ) ) );
}

String::operator const char *() const
{
	return( v );
}

String& String::operator =( const char *s )
{
	if( s == NULL )
		return( *this );

	return( assign( s , strlen( s ) ) );
}

String& String::operator =( String& s )
{
	if( s == NULL )
		return( *this );

	return( assign( s , strlen( s ) ) );
}

void String::clear()
{
	if( v == NULL )
		return;

	*v = 0;
}

String& String::assign( const char *s ,  int n2 )
{
	if( v != NULL )
		*v = 0;

	StringData *d = ensureFreeSpace( v , n2 );
	memcpy( v , s , n2 );
	v[ n2 ] = 0;

	return( *this );
}

String& String::append( int count , char c )
{
	StringData *d = ensureFreeSpace( v , count );

	int len = strlen( v );
	memset( v + len , c , count );
	v[ len + count ] = 0;

	return( *this );
}

void String::resize( int nn )
{
	if( v == NULL )
		{
			ensureFreeSpace( v , nn );
			return;
		}
			
	ensureFreeSpace( v , nn - length() );
}

char *String::getBuffer()
{
	return( v );
}

int String::size() const
{
	if( v == NULL )
		return( 0 );

	StringData *d = getData( v );
	return( d -> size );
}

int String::length() const
{
	if( v == NULL )
		return( 0 );

	return( strlen( v ) );
}

bool String::isEmpty() const
{
	return( v == NULL || *v == 0 );
}

int String::findLastAny( const char *chars )
{
	if( v == NULL )
		return( -1 );

	char c;
	char *pBest = NULL;
	while( c = *chars++ )
		{
			char *p = strrchr( v , c );
			if( p != NULL )
				if( pBest == NULL || p > pBest )
					pBest = p;
		}

	if( pBest != NULL )
		return( pBest - v );

	return( -1 );
}

int String::findLast( char c )
{
	if( v == NULL )
		return( -1 );

	char *p = strrchr( v , c );
	if( p == NULL )
		return( -1 );

	return( p - v );
}

String String::getMid( int from , int n )
{
	if( v == NULL )
		return( "" );

	int len = length();
	if( from >= len )
		return( "" );

	String s;
	if( n > len - from )
		n = len - from;
	s.assign( v + from  , n );
	return( s );
}

// #############################################################################
// #############################################################################

String operator +( String& s1 , const char *s2 )
{
	String s = s1;
	s += s2;
	return( s );
}

String operator +( const String& s1 , int value )
{
	char l_buf[ 12 ];
	sprintf( l_buf , "%d" , value );

	String s = s1;
	s += l_buf;
	return( s );
}

String operator +( const String& s1 , float value )
{
	char l_buf[ 30 ];
	sprintf( l_buf , "%g" , value );

	String s = s1;
	s += l_buf;
	return( s );
}

String operator +( const String& s1 , const char *s2 )
{
	String s = s1;
	s += s2;
	return( s );
}

String operator +( const String& s1 , char value )
{
	String s = s1;
	s += value;
	return( s );
}

String operator +( const String& s1 , bool value )
{
	String s = s1;
	s += ( value )? "true" : "false";
	return( s );
}
