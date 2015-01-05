/*#######################################################*/
/*#######################################################*/

/* std headers */
#include <__gen.h>
#include <ctype.h>

/*#######################################################*/
/*#######################################################*/
/* UNICODE UTF-8 string functions */

/* create string */
rfc_ustring
	rfc_ustr_create( const rfc_uchar *p_s , int p_len , int p_allocate )
{
	char *l_p;
	int l_size;

	if( p_s == NULL )
		p_len = 0;
	else
	if( p_len < 0 )
		p_len = rfc_ustr_len( p_s );

	if( p_allocate < p_len )
		l_size = strlen( ( const char * )p_s );
	else
		l_size = p_allocate * 3;

	l_p = ( char * )malloc( sizeof( int ) + l_size + 1 );
	*( int * )l_p = l_size;
	l_p += sizeof( int );

	if( p_len )
		strcpy( l_p , ( char * )p_s );
	else
		*l_p = 0;
	return( ( rfc_ustring )l_p );
}

/* reallocate buffer if needed */
rfc_ustring
	rfc_ustr_allocate( rfc_ustring p_str , int p_size )
{
	int l_size;

	if( p_str == NULL )
		return( rfc_ustr_create( NULL , 0 , p_size ) );

	l_size = *( int * )( p_str - sizeof( int ) );
	if( p_size * 3 <= l_size )
		return( p_str );

	/* reallocate */
	p_str -= sizeof( int );
	p_str = ( rfc_ustring )realloc( p_str , p_size * 3 + sizeof( int ) + 1 );
	*( int * )p_str = p_size * 3;
	p_str += sizeof( int );

	return( p_str );
}

rfc_ustring
	rfc_ustr_allocate_internal( int p_size )
{
	rfc_ustring l_s;

	/* reallocate */
	l_s = ( rfc_ustring )malloc( p_size + sizeof( int ) + 1 );
	l_s -= sizeof( int );
	*( int * )l_s = p_size;
	l_s += sizeof( int );

	return( l_s );
}

/* destroy string */
void
	rfc_ustr_drop( rfc_ustring p_str )
{
	if( p_str == NULL )
		return;

	free( p_str - sizeof( int ) );
}

/* append string */
rfc_ustring
	rfc_ustr_append( rfc_ustring p_str , int p_pos , const rfc_uchar *p_s , int p_slen )
{
	int l_len;
	int l_size;
	int l_size_pos;
	int l_size_slen;

	if( p_s == NULL ||
		p_slen == 0 )
		return( p_str );

	if( p_slen < 0 )
		{
			p_slen = rfc_ustr_len( p_s );
			if( !p_slen )
				return( p_str );
		}

	l_len = ( p_str )? rfc_ustr_len( p_str ) : 0;
	if( p_pos < 0 )
		p_pos = l_len;
	else
		{
			if( p_pos > l_len )
				return( p_str );
		}

	/* check allocation */
	p_str = ( rfc_ustring )rfc_str_allocate( ( char * )p_str , l_len + p_slen );

	/* shift tail */
	l_size = ( p_str )? strlen( ( char * )p_str ) : 0;
	l_size_pos = rfc_ustr_size( p_str , p_pos );
	l_size_slen = rfc_ustr_size( p_s , p_slen );
	if( p_pos < l_len )
		memmove( p_str + l_size_pos + l_size_slen , p_str + l_size_pos , l_size - l_size_pos + 1 );
	else
		p_str[ l_size_pos + l_size_slen ] = 0;

	/* copy source */
	memcpy( p_str + l_size_pos , p_s , l_size_slen );

	return( p_str );
}

/* remove part of string */
void
	rfc_ustr_remove( rfc_ustring p_str , int p_pos , int p_len )
{
	int l_len;
	int l_size_pos;
	int l_size_len;

	if( p_len <= 0 )
		return;

	l_len = rfc_ustr_len( p_str );
	if( p_pos < 0 )
		{
			p_pos = l_len + p_pos;
			if( p_pos < 0 )
				return;
		}
	else
	if( p_pos >= l_len )
		return;

	/* remove tail from pos */
	l_size_pos = rfc_ustr_size( p_str , p_pos );
	if( p_len >= l_len - p_pos )
		{
			p_str[ l_size_pos ] = 0;
			return;
		}

	/* shift tail */
	l_size_len = rfc_ustr_size( p_str , p_len );
	memmove( p_str + l_size_pos , p_str + l_size_pos + l_size_len , l_len - l_size_pos - l_size_len + 1 );
}

/* clear string */
void
	rfc_ustr_clear( rfc_ustring p_str )
{
	*p_str = 0;
}

/* set string */
rfc_ustring
	rfc_ustr_set( rfc_ustring p_str , const rfc_uchar *p_s , int p_len )
{
	if( p_str == NULL )
		return( rfc_ustr_create( p_s , p_len , 0 ) );

	rfc_ustr_clear( p_str );
	return( rfc_ustr_append( p_str , 0 , p_s , p_len ) );
}

/* extract left part of string */
rfc_ustring
	rfc_ustr_extract_left( const rfc_uchar *p_s , int p_count )
{
	return( rfc_ustr_create( p_s , p_count , 0 ) );
}

/* extract right part of string */
rfc_ustring
	rfc_ustr_extract_right( const rfc_uchar *p_s , int p_count )
{
	int l_size_count;
	int l_len;
	rfc_ustring l_s;

	if( p_s == NULL || p_count <= 0 || *p_s == 0 )
		return( NULL );

	l_len = rfc_ustr_len( p_s );
	if( p_count >= l_len )
		return( rfc_ustr_create( p_s , -1 , 0 ) );

	l_size_count = rfc_ustr_size( p_s , l_len - p_count );
	l_s = rfc_ustr_allocate_internal( l_size_count );
	memcpy( l_s , p_s , l_size_count );
	l_s[ l_size_count ] = 0;

	return( l_s );
}

/* extract middle part of string */
rfc_ustring
	rfc_ustr_extract_middle( const rfc_uchar *p_s , int p_start , int p_count )
{
	if( p_start < 0 || p_s == NULL || p_count == 0 )
		return( NULL );

	if( p_count < 0 )
		{
			p_count = rfc_ustr_len( p_s ) - p_start;
			if( p_count < 0 )
				return( NULL );
		}

	return( rfc_ustr_create( p_s + rfc_ustr_size( p_s , p_start ) , p_count , 0 ) );
}

/* make format string */
rfc_ustring
	rfc_ustr_format( rfc_ustring p_str , const rfc_uchar *p_format , ... )
{
	va_list l_va;

	va_start( l_va , p_format );

	p_str = rfc_ustr_format_va( p_str , p_format , l_va );
	va_end( l_va );

	return( p_str );
}

/* make format string with valist*/
rfc_ustring
	rfc_ustr_format_va( rfc_ustring p_str , const rfc_uchar *p_format , va_list p_va )
{
	/* the same as for rfc_string */
	return( ( rfc_ustring )rfc_str_format_va( ( rfc_string )p_str , ( const char * )p_format , p_va ) );
}

/* special */
/* get string length */
int
	rfc_ustr_len( const rfc_uchar *p_s )
{
	int l_len;

	l_len = 0;
	while( *p_s )
		{
			p_s = rfc_ustr_next( p_s );
			l_len++;
		}

	return( l_len );
}

/* get string size for first p_n characters */
int
	rfc_ustr_size( const rfc_uchar *p_s , int p_n )
{
	const rfc_uchar *l_s;

	if( p_n <= 0 || p_s == NULL )
		return( 0 );

	l_s = p_s;
	for( ; *l_s && p_n; p_n-- )
		l_s = rfc_ustr_next( l_s );

	return( l_s - p_s );
}

/* compare strings */
int
	rfc_ustr_ncmp( const rfc_uchar *p_s1 , const rfc_uchar *p_s2 , int p_n )
{
	int l_size1;
	int l_size2;

	if( p_s1 == NULL || p_s2 == NULL )
		return( p_s1 - p_s2 );

	l_size1 = rfc_ustr_size( p_s1 , p_n );
	l_size2 = rfc_ustr_size( p_s2 , p_n );
	if( l_size1 != l_size2 )
		return( strcmp( ( const char * )p_s1 , ( const char * )p_s2 ) );

	return( strncmp( ( const char * )p_s1 , ( const char * )p_s2 , l_size1 ) );			
}

/* get next character pointer */
rfc_uchar *
	rfc_ustr_next( const rfc_uchar *p_s )
{
	rfc_uchar l_c;

	l_c = *p_s;
	if( l_c )
		{
			/* UTF-8 specs */
			if( l_c <= 0x7F )
				return( ( rfc_uchar * )( p_s + 1 ) );

			if( l_c <= 0xDF )
				return( ( rfc_uchar * )( p_s + 2 ) );

			return( ( rfc_uchar * )( p_s + 3 ) );
		}

	return( ( rfc_uchar * )p_s );
}

/* translate from USC-2 using codepage */
short
	rfc_ustr_setusc2( rfc_uchar *p_s , const rfc_wchar *p_v )
{
	rfc_wchar l_c;

	if( p_v == NULL )
		{
			*p_s = 0;
			return( 1 );
		}

	for( ;; ) {
		l_c = *p_v++;
		if( !l_c )
			break;

		if( l_c <= 0x7F ) {
			/* equal to ASCII */
			*p_s++ = ( rfc_uchar )l_c;
		}
		else if( l_c <= 0x7FF ) {
			/* 1 byte */
			*p_s++ = 0xC0 | ( l_c >> 6 );
			/* 2 byte */
			*p_s++ = 0x80 | ( l_c & 0x3F );
		}
		else {
			/* 1 byte */
			*p_s++ = 0xE0 | ( l_c >> 12 );
			/* 2 byte */
			*p_s++ = 0x80 | ( ( l_c >> 6 ) & 0x3F );
			/* 3 byte */
			*p_s++ = 0x80 | ( l_c & 0x3F );
		}
	}
	*p_s++ = 0;

	return( 1 );
}

/* calculate UTF8 string size by USC-2 string */
int
	rfc_ustr_usc2size( const rfc_wchar *p_v )
{
	int l_size;
	rfc_wchar l_c;

	if( p_v == NULL )
		return( 0 );

	l_size = 0;
	for( ;; ) {
		l_c = *p_v++;
		if( !l_c )
			break;

		if( l_c <= 0x7F )
			l_size++;
		else
		if( l_c <= 0x7FF )
			l_size += 2;
		else
			l_size += 3;
	}
	return( l_size );			
}
