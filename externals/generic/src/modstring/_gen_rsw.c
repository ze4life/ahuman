/*#######################################################*/
/*#######################################################*/

/* std headers */
#include <__gen.h>
#include <ctype.h>

/* internal string buffer granularity */
#define RFC_WSTRING_GRANULARITY		64

/*#######################################################*/
/*#######################################################*/
/* construction */

/* create string */
rfc_wstring
	rfc_wstr_create( const unsigned short *p_s , int p_len , int p_allocate )
{
	unsigned short *l_p;

	if( p_s == NULL )
		p_len = 0;
	else
	if( p_len < 0 )
		p_len = rfc_wstr_len( p_s );

	if( p_allocate < 0 )
		p_allocate = p_len + RFC_WSTRING_GRANULARITY - ( p_len % RFC_WSTRING_GRANULARITY );
	else
	if( p_allocate < p_len )
		p_allocate = p_len;

	l_p = ( unsigned short * )malloc( sizeof( int ) + p_allocate * 2 + 2 );
	*( int * )l_p = p_allocate;
	l_p = ( unsigned short * )( ( ( char * )l_p ) + sizeof( int ) );

	if( p_len )
		memcpy( l_p , p_s , p_len * 2 );

	l_p[ p_len ] = 0;
	return( l_p );
}

/* reallocate buffer if needed */
rfc_wstring
	rfc_wstr_allocate( rfc_wstring p_str , int p_size )
{
	int l_size;

	if( p_str == NULL )
		return( rfc_wstr_create( NULL , 0 , p_size ) );

	l_size = *( int * )( ( ( char * )p_str ) - sizeof( int ) );
	if( p_size <= 0 )
		{
			p_size = rfc_wstr_len( p_str );
			
			/* allocate to granularity */
			if( p_size % RFC_WSTRING_GRANULARITY )
				p_size = p_size + RFC_WSTRING_GRANULARITY - ( p_size % RFC_WSTRING_GRANULARITY );
			else
				p_size += RFC_WSTRING_GRANULARITY;

		}
	if( p_size <= l_size )
		return( p_str );

	/* reallocate */
	p_str = ( unsigned short * )( ( ( char * )p_str ) - sizeof( int ) );
	p_str = ( unsigned short * )realloc( p_str , p_size * 2 + sizeof( int ) + 2 );
	*( int * )p_str = p_size;
	p_str = ( unsigned short * )( ( ( char * )p_str ) + sizeof( int ) );

	return( p_str );
}

/* destroy string */
void
	rfc_wstr_drop( rfc_wstring p_str )
{
	if( p_str == NULL )
		return;

	free( ( ( char * )p_str ) - sizeof( int ) );
}

/* append string */
rfc_wstring
	rfc_wstr_append( rfc_wstring p_str , int p_pos , const unsigned short *p_s , int p_slen )
{
	int l_len;

	if( p_s == NULL ||
		p_slen == 0 )
		return( p_str );

	if( p_slen < 0 )
		{
			p_slen = rfc_wstr_len( p_s );
			if( !p_slen )
				return( p_str );
		}

	l_len = ( p_str )? rfc_wstr_len( p_str ) : 0;
	if( p_pos < 0 )
		p_pos = l_len;
	else
		{
			if( p_pos > l_len )
				return( p_str );
		}

	/* check allocation */
	p_str = rfc_wstr_allocate( p_str , l_len + p_slen );

	/* shift tail */
	if( p_pos < l_len )
		memmove( p_str + p_pos + p_slen , p_str + p_pos , ( l_len - p_pos + 1 ) * 2 );
	else
		p_str[ p_pos + p_slen ] = 0;

	/* copy source */
	memcpy( p_str + p_pos , p_s , p_slen * 2 );

	return( p_str );
}

/* add char to string */
rfc_wstring
	rfc_wstr_addchar( rfc_wstring p_str , int p_pos , unsigned short p_c )
{
	int l_len;

	if( p_c == 0 )
		return( p_str );

	l_len = rfc_wstr_len( p_str );
	if( p_pos < 0 )
		p_pos = l_len;
	else
	if( p_pos > l_len )
		return( p_str );

	/* ensure sizes */
	p_str = rfc_wstr_allocate( p_str , 0 );

	/* shift tail */
	if( p_pos < l_len )
		memmove( p_str + p_pos + 1 , p_str + p_pos , ( l_len - p_pos + 1 ) * 2 );
	else
		p_str[ l_len + 1 ] = 0;

	/* set char */
	p_str[ p_pos ] = p_c;

	return( p_str );
}

/* remove part of string */
void
	rfc_wstr_remove( rfc_wstring p_str , int p_pos , int p_len )
{
	int l_len;

	if( p_len <= 0 )
		return;

	l_len = rfc_wstr_len( p_str );
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
	if( p_len >= l_len - p_pos )
		{
			p_str[ p_pos ] = 0;
			return;
		}

	/* shift tail */
	memmove( p_str + p_pos , p_str + p_pos + p_len , ( l_len - p_pos - p_len + 1 ) * 2 );
}

/* clear string */
void
	rfc_wstr_clear( rfc_wstring p_str )
{
	*p_str = 0;
}

/* extract left part of string */
rfc_wstring
	rfc_wstr_extract_left( const unsigned short *p_s , int p_count )
{
	int l_len;

	if( p_count < 0 )
		{
			p_count = -p_count;
			l_len = ( p_s == NULL )? 0 : rfc_wstr_len( p_s );
			if( p_count > l_len )
				p_count = l_len;
		}
	return( rfc_wstr_create( p_s , p_count , 0 ) );
}

/* extract right part of string */
rfc_wstring
	rfc_wstr_extract_right( const unsigned short *p_s , int p_count )
{
	int l_len;

	l_len = ( p_s == NULL )? 0 : rfc_wstr_len( p_s );
	if( p_count > l_len )
		p_count = l_len;

	return( rfc_wstr_create( p_s + l_len - p_count , p_count , 0 ) );
}

/* extract middle part of string */
rfc_wstring
	rfc_wstr_extract_middle( const unsigned short *p_s , int p_start , int p_count )
{
	int l_len;

	if( p_start < 0 )
		{
			p_start = -p_start;
			l_len = ( p_s == NULL )? 0 : rfc_wstr_len( p_s );
			if( p_start >= l_len )
				p_count = 0;
			else
			if( p_count < 0 ||
				p_start + p_count > l_len )
				p_count = l_len - p_start;
		}
	else
	if( p_count < 0 )
		p_count = 0;

	return( rfc_wstr_create( p_s + p_start , p_count , 0 ) );
}

/* get char by pos from end */
unsigned short
	rfc_wstr_rchar( const unsigned short *p_s , int p_rpos )
{
	if( p_s == NULL ||
		p_rpos <= 0 )
		return( 0 );

	p_rpos = rfc_wstr_len( p_s ) - p_rpos;
	if( p_rpos < 0 )
		return( 0 );

	return( p_s[ p_rpos ] );
}

/* set string */
rfc_wstring
	rfc_wstr_set( rfc_wstring p_str , const unsigned short *p_s , int p_len )
{
	if( p_str == NULL )
		return( rfc_wstr_create( p_s , p_len , 0 ) );

	rfc_wstr_clear( p_str );
	return( rfc_wstr_append( p_str , 0 , p_s , p_len ) );
}

/*#######################################################*/
/*#######################################################*/

/* make format string */
rfc_wstring
	rfc_wstr_format( rfc_wstring p_str , const unsigned short *p_format , ... )
{
	va_list l_va;

	va_start( l_va , p_format );

	p_str = rfc_wstr_format_va( p_str , p_format , l_va );
	va_end( l_va );

	return( p_str );
}

/* make format string with valist*/
rfc_wstring
	rfc_wstr_format_va( rfc_wstring p_str , const unsigned short *p_format , va_list p_va )
{
	const unsigned short *l_format;
	va_list l_va;
	int l_max;
	int l_len;
	int l_width;
	int l_prec;
	int l_mod;
	const unsigned short *l_next_arg;
	RFC_TYPE x;

	l_format = p_format;
	l_va = p_va;
	l_max = 0;

	/* make a guess at the maximum length of the resulting string */
	for( ; *l_format; l_format++ )
		{
			/* handle '%' character, but watch out for '%%' */
			if( *l_format != L'%' )
				{
					l_max++;
					continue;
				}

			if( *++l_format == L'%' )
				{
					l_max++;
					continue;
				}

			l_len = 0;

			/* handle '%' character with format */
			l_width = 0;
			for( ; *l_format; l_format++ )
				{
					/* check for valid flags */
					if( *l_format == L'#' )
						l_max += 2;   /* for '0x' */
					else
					if( *l_format == L'*' )
						l_width = va_arg( l_va , int );
					else
					if( *l_format == L'-' || 
						*l_format == L'+' || 
						*l_format == L'0' ||
						*l_format == L' ')
						x.u_l = 0;
					else /* hit non-flag character */
						break;
				}

			/* get width and skip it */
			if( l_width == 0 )
				{
					/* width indicated by */
					l_width = rfc_wstr_atoi( l_format );
					for( ; *l_format && rfc_wstr_isdigit( *l_format ); )
						l_format++;
				}

			/* precesion */
			l_prec = 0;
			if( *l_format == L'.' )
				{
					/* skip past '.' separator (width.precision) */
					l_format++;

					/* get precision and skip it */
					if( *l_format == L'*' )
						{
							l_prec = va_arg( l_va , int );
							l_format++;
						}
					else
						{
							l_prec = rfc_wstr_atoi( l_format );
							for( ; *l_format && rfc_wstr_isdigit( *l_format ); )
								l_format++;
						}
				}

			/* should be on type modifier or specifier */
			l_mod = 0;
			if( !rfc_wstr_ncmp( l_format , ( const unsigned short * )RFC_WINT64FMTBASE , rfc_wstr_len( ( const unsigned short * )RFC_WINT64FMTBASE ) ) )
				{
					l_format += rfc_wstr_len( ( const unsigned short * )RFC_WINT64FMTBASE );
					l_mod = 1;
				}
			else
				{
					switch( *l_format )
						{
							/* modifiers that affect size */
							case L'h':
								l_mod = 2;
								l_format++;
								break;
							case L'l':
								l_mod = 3;
								l_format++;
								break;

							/* modifiers that do not affect size */
							case L'F':
							case L'N':
							case L'L':
								l_format++;
								break;
						}
				}

			/* now should be on specifier */
			switch( *l_format | l_mod )
				{
					/* single characters */
					case L'c':
						l_len = 2;
						x.u_l = va_arg( l_va , int /*unsigned short*/ );
						break;

					/* strings */
					case L's':
						l_next_arg = va_arg( l_va , const unsigned short * );

						/* check error */
						if( l_next_arg == NULL )
							return( p_str );

						l_len = rfc_wstr_len( l_next_arg );
						l_len = max( 1 , l_len );
						break;
				}

			/* adjust nItemLen for strings */
			if( l_len != 0 )
				{
					if( l_prec != 0 )
						l_len = min( l_len , l_prec );
					l_len = max( l_len , l_width );
				}
			else
				{
					switch( *l_format )
						{
							/* integers */
							case L'd':
							case L'i':
							case L'u':
							case L'x':
							case L'X':
							case L'o':
								if( l_mod == 1 )
									x.u_m = va_arg( l_va , RFC_INT64 );
								else
									x.u_l = va_arg( l_va , int );
								l_len = 32;
								l_len = max( l_len , l_width + l_prec );
								break;

							case L'e':
							case L'g':
							case L'G':
								x.u_f = va_arg( l_va , double );
								l_len = 128;
								l_len = max( l_len , l_width + l_prec );
								break;

							case L'f':
								x.u_f = va_arg( l_va , double );
								l_len = 128; /* width isn't truncated */
								/* 312 == rfc_wstr_len("-1+(309 zeroes).") */
								/* 309 zeroes == max precision of a double */
								l_len = max( l_len , 312 + l_prec );
								break;

							// no output
							case L'n':
								x.u_p = va_arg( l_va , int * );
								break;

							default:
								return( p_str );  /* unknown formatting option */
						}
				}

			/* adjust l_max for output l_len */
			l_max += l_len;
		}

	/* allocate */
	p_str = rfc_wstr_allocate( p_str , l_max );

	rfc_wstr_vsprintf( p_str , p_format , p_va );
	return( p_str );
}

/* special */
/* get string length */
int
	rfc_wstr_len( const unsigned short *p_s )
{
	int l_n;

	for( l_n = 0; *p_s; p_s++ )
		l_n++;
	return( l_n );
}

/* convert string to integer */
int
	rfc_wstr_atoi( const unsigned short *p_s )
{
	char l_buf[ 16 ];
	int l_max;
	char *l_p;

	l_max = 10;
	l_p = l_buf;
	while( l_max-- && *p_s && *( ( ( char * )p_s ) + 1 ) == 0 )
		*l_p++ = *( const char * )p_s++;
	*l_p = 0;

	return( atoi( l_buf ) );
}

/* check character is digit */
int
	rfc_wstr_isdigit( const unsigned short p_c )
{
	const char *l_p;

	l_p = ( const char * )&p_c;
	if( l_p[ 1 ] == 0 &&
		isdigit( l_p[ 0 ] ) )
		return( 1 );
	return( 0 );
}

/* compare strings */
int
	rfc_wstr_ncmp( const unsigned short *p_s1 , const unsigned short *p_s2 , int p_n )
{
	int l_v;
	if( p_s1 == NULL || p_s2 == NULL )
		return( p_s2 - p_s1 );

	while( p_n-- && ( *p_s1 || *p_s2 ) )
		{
			if( ( l_v = *p_s2++ - *p_s1++ ) )
				return( l_v );
		}
	return( 0 );
}

/* format string */
int
	rfc_wstr_vsprintf( unsigned short *p_s , const unsigned short *p_fmt , va_list p_va )
{
	const unsigned short *l_format;
	va_list l_va;
	int l_len;
	int l_width;
	int l_prec;
	int l_mod;
	const unsigned short *l_next_arg;
	unsigned short *l_s;
	const unsigned short *l_fs;
	RFC_TYPE l_v;
	char l_fmt[ 128 ];
	char l_buf[ 512 ];
	char *l_fmtp;
	char *l_copy;
	RFC_TYPE x;

	l_format = p_fmt;
	l_va = p_va;
	l_s = p_s;

	/* make a guess at the maximum length of the resulting string */
	for( ; *l_format; l_format++ )
		{
			/* handle '%' character, but watch out for '%%' */
			if( *l_format != L'%' )
				{
					*l_s++ = *l_format;
					continue;
				}

			l_fs = l_format;
			if( *++l_format == L'%' )
				{
					*l_s++ = L'%';
					continue;
				}

			/* handle '%' character with format */
			l_width = 0;
			for( ; *l_format; l_format++ )
				{
					/* check for valid flags */
					if( *l_format == L'*' )
						l_width = va_arg( l_va , int );
					else
					if( *l_format == L'-' || 
						*l_format == L'+' || 
						*l_format == L'0' ||
						*l_format == L' ')
						x.u_l = 0;
					else /* hit non-flag character */
						break;
				}

			/* get width and skip it */
			if( l_width == 0 )
				{
					/* width indicated by */
					l_width = rfc_wstr_atoi( l_format );
					for( ; *l_format && rfc_wstr_isdigit( *l_format ); )
						l_format++;
				}

			/* precesion */
			l_prec = 0;
			if( *l_format == L'.' )
				{
					/* skip past '.' separator (width.precision) */
					l_format++;

					/* get precision and skip it */
					if( *l_format == L'*' )
						{
							l_prec = va_arg( l_va , int );
							l_format++;
						}
					else
						{
							l_prec = rfc_wstr_atoi( l_format );
							for( ; *l_format && rfc_wstr_isdigit( *l_format ); )
								l_format++;
						}
				}

			/* should be on type modifier or specifier */
			l_mod = 0;
			if( !rfc_wstr_ncmp( l_format , ( const unsigned short * )RFC_WINT64FMTBASE , rfc_wstr_len( ( const unsigned short * )RFC_WINT64FMTBASE ) ) )
				{
					l_format += rfc_wstr_len( ( const unsigned short * )RFC_WINT64FMTBASE );
					l_mod = 1;
				}
			else
				{
					switch( *l_format )
						{
							/* modifiers that affect size */
							case L'h':
								l_mod = 2;
								l_format++;
								break;
							case L'l':
								l_mod = 3;
								l_format++;
								break;

							/* modifiers that do not affect size */
							case L'F':
							case L'N':
							case L'L':
								l_format++;
								break;
						}
				}

			if( *l_format != 'c' &&
				*l_format != 's' )
				{
					/* do default formating */
					l_fmtp = l_fmt;
					do
						{
							*l_fmtp = *( const char * )l_fs;
						}
					while( l_fs++ != l_format );
					*l_fmtp = 0;
				}

			/* now should be on specifier */
			switch( *l_format | l_mod )
				{
					/* single characters */
					case L'c':
					case L'C':
						l_len = 2;
						*l_s++ = va_arg( l_va , int /*unsigned short*/ );
						continue;

					/* strings */
					case L'S':
					case L's':
						l_next_arg = va_arg( l_va , const unsigned short * );

						/* check error */
						if( l_next_arg == NULL )
							continue;

						l_len = rfc_wstr_len( l_next_arg );
						if( l_prec != 0 )
							l_len = min( l_len , l_prec );
						l_len = max( l_len , l_width );
						while( l_len-- )
							*l_s++ = *l_next_arg++;
						continue;
					/* integers */
					case L'd':
					case L'i':
					case L'u':
					case L'x':
					case L'X':
					case L'o':
						if( l_mod == 1 )
							{
								l_v.u_m = va_arg( l_va , RFC_INT64 );
								l_len = sprintf( l_buf , l_fmt , l_v.u_m );
							}
						else
							{
								l_v.u_l = va_arg( l_va , int );
								l_len = sprintf( l_buf , l_fmt , l_v.u_l );
							}
						break;

					case L'e':
					case L'g':
					case L'G':
					case L'f':
						l_v.u_f = va_arg( l_va , double );
						l_len = sprintf( l_buf , l_fmt , l_v.u_f );
						break;

					// no output
					case L'n':
						x.u_p = va_arg( l_va , int * );
						continue;

					default:
						*l_s++ = 0;
						return( 0 );  /* unknown formatting option */
				}

			/* copy buffer to wide string */
			l_fmtp = l_buf;
			l_copy = ( char * )l_s;
			l_s += l_len;

			while( l_len-- )
				{
					*l_copy++ = *l_fmtp++;
					*l_copy++ = 0;
				}
		}
	*l_s++ = 0;
	return( l_s - p_s );
}

int
	rfc_wstr_cmp( const unsigned short *p_s1 , const unsigned short *p_s2 )
{
	int l_v;
	if( p_s1 == NULL || p_s2 == NULL )
		return( p_s2 - p_s1 );

	while( *p_s1 || *p_s2 )
		{
			if( ( l_v = *p_s2++ - *p_s1++ ) )
				return( l_v );
		}
	return( 0 );
}

/* copy string */
unsigned short *
	rfc_wstr_cpy( unsigned short *p_dst , const unsigned short *p_src )
{
	unsigned short *l_dst;
	l_dst = p_dst;
	
	do
		{
			*p_dst++ = *p_src++;
		}
	while( *p_src++ );
	return( l_dst );
}

/* find character */
unsigned short *
	rfc_wstr_chr( const unsigned short *p_s , unsigned short p_c )
{
	while( *p_s )
		if( *p_s == p_c )
			return( ( unsigned short * )p_s );
		else
			p_s++;
	return( NULL );
}

/* format string */
int
	rfc_wstr_sprintf( unsigned short *p_s , const unsigned short *p_fmt , ... )
{
	va_list l_va;
	int l_n;

	va_start( l_va , p_fmt );

	l_n = rfc_wstr_vsprintf( p_s , p_fmt , l_va );
	va_end( l_va );

	return( l_n );
}

/* find string */
unsigned short *
	rfc_wstr_str( const unsigned short *p_s , const unsigned short *p_v )
{
	int l_len;
	const unsigned short *l_s;

	l_len = rfc_wstr_len( p_v );
	l_s = p_s;
	while( 1 )
		{
			/* find first character */
			l_s = rfc_wstr_chr( l_s , *p_v );
			if( l_s == NULL )
				return( NULL );

			/* compare strings */
			if( !rfc_wstr_ncmp( l_s , p_v , l_len ) )
				return( ( unsigned short * )l_s );

			/* go next */
			l_s++;
		}

	return( NULL );
}

/* translate from UTF8 */
short
	rfc_wstr_setutf8( rfc_wchar *p_s , const rfc_uchar *p_v )
{
	rfc_uchar l_c;
	rfc_wchar l_w;

	if( p_v == NULL )
		{
			*p_s = 0;
			return( 1 );
		}

	while( ( l_c = *p_v++ ) )
		{
			/* check byte number */
			if( l_c <= 0x7F )
				{
					*p_s++ = l_c;
				}
			else
			if( l_c <= 0xDF )
				{
					/* 1 byte */
					l_w = ( l_c & 0x1F ) << 6;
					/* 2 byte */
					l_c = *p_v++;
					if( l_c & 0x80 )
						{
							l_w |= l_c & 0x3F;
							*p_s++ = l_w;
						}
					else
						return( 0 );
				}
			else
			if( l_c <= 0xEF )
				{
					/* 1 byte */
					l_w = ( l_c & 0x0F ) << 12;
					/* 2 byte */
					l_c = *p_v++;
					if( l_c & 0x80 )
						l_w |= ( l_c & 0x3F ) << 6;
					else
						return( 0 );
					/* 3 byte */
					l_c = *p_v++;
					if( l_c & 0x80 )
						{
							l_w |= l_c & 0x3F;
							*p_s++ = l_w;
						}
					else
						return( 0 );
				}
			else
				return( 0 );
		}

	*p_s = 0;
	return( 1 );
}

