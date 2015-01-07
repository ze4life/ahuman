/*#######################################################*/
/*#######################################################*/

/* std headers */
#include <__gen.h>
#include <ctype.h>

/* internal string buffer granularity */
#define RFC_STRING_GRANULARITY		64

/*#######################################################*/
/*#######################################################*/
/* construction */

/* create string */
rfc_string
	rfc_str_create( const char *p_s , int p_len , int p_allocate )
{
	char *l_p;

	if( p_s == NULL )
		p_len = 0;
	else
	if( p_len < 0 )
		p_len = strlen( p_s );

	if( p_allocate < 0 )
		p_allocate = p_len + RFC_STRING_GRANULARITY - ( p_len % RFC_STRING_GRANULARITY );
	else
	if( p_allocate < p_len )
		p_allocate = p_len;

	l_p = ( char * )malloc( sizeof( int ) + p_allocate + 1 );
	*( int * )l_p = p_allocate;
	l_p += sizeof( int );

	if( p_len )
		memcpy( l_p , p_s , p_len );

	l_p[ p_len ] = 0;
	return( l_p );
}

/* reallocate buffer if needed */
rfc_string
	rfc_str_allocate( rfc_string p_str , int p_size )
{
	int l_size;

	if( p_str == NULL )
		return( rfc_str_create( NULL , 0 , p_size ) );

	l_size = *( int * )( p_str - sizeof( int ) );
	if( p_size <= 0 )
		{
			p_size = strlen( p_str );
			
			/* allocate to granularity */
			if( p_size % RFC_STRING_GRANULARITY )
				p_size = p_size + RFC_STRING_GRANULARITY - ( p_size % RFC_STRING_GRANULARITY );
			else
				p_size += RFC_STRING_GRANULARITY;

		}
	if( p_size <= l_size )
		return( p_str );

	/* reallocate */
	p_str -= sizeof( int );
	p_str = ( char * )realloc( p_str , p_size + sizeof( int ) + 1 );
	*( int * )p_str = p_size;
	p_str += sizeof( int );

	return( p_str );
}

/* destroy string */
void
	rfc_str_drop( rfc_string p_str )
{
	if( p_str == NULL )
		return;

	free( p_str - sizeof( int ) );
}

/* append string */
rfc_string
	rfc_str_append( rfc_string p_str , int p_pos , const char *p_s , int p_slen )
{
	int l_len;

	if( p_s == NULL ||
		p_slen == 0 )
		return( p_str );

	if( p_slen < 0 )
		{
			p_slen = strlen( p_s );
			if( !p_slen )
				return( p_str );
		}

	l_len = ( p_str )? strlen( p_str ) : 0;
	if( p_pos < 0 )
		p_pos = l_len;
	else
		{
			if( p_pos > l_len )
				return( p_str );
		}

	/* check allocation */
	p_str = rfc_str_allocate( p_str , l_len + p_slen );

	/* shift tail */
	if( p_pos < l_len )
		memmove( p_str + p_pos + p_slen , p_str + p_pos , l_len - p_pos + 1 );
	else
		p_str[ p_pos + p_slen ] = 0;

	/* copy source */
	memcpy( p_str + p_pos , p_s , p_slen );

	return( p_str );
}

/* add char to string */
rfc_string
	rfc_str_addchar( rfc_string p_str , int p_pos , char p_c )
{
	int l_len;

	if( p_c == 0 )
		return( p_str );

	l_len = strlen( p_str );
	if( p_pos < 0 )
		p_pos = l_len;
	else
	if( p_pos > l_len )
		return( p_str );

	/* ensure sizes */
	p_str = rfc_str_allocate( p_str , 0 );

	/* shift tail */
	if( p_pos < l_len )
		memmove( p_str + p_pos + 1 , p_str + p_pos , l_len - p_pos + 1 );
	else
		p_str[ l_len + 1 ] = 0;

	/* set char */
	p_str[ p_pos ] = p_c;

	return( p_str );
}

/* remove part of string */
void
	rfc_str_remove( rfc_string p_str , int p_pos , int p_len )
{
	int l_len;

	if( p_len <= 0 )
		return;

	l_len = strlen( p_str );
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
	memmove( p_str + p_pos , p_str + p_pos + p_len , l_len - p_pos - p_len + 1 );
}

/* clear string */
void
	rfc_str_clear( rfc_string p_str )
{
	*p_str = 0;
}

/* extract left part of string */
rfc_string
	rfc_str_extract_left( const char *p_s , int p_count )
{
	int l_len;

	if( p_count < 0 )
		{
			p_count = -p_count;
			l_len = ( p_s == NULL )? 0 : strlen( p_s );
			if( p_count > l_len )
				p_count = l_len;
		}
	return( rfc_str_create( p_s , p_count , 0 ) );
}

/* extract right part of string */
rfc_string
	rfc_str_extract_right( const char *p_s , int p_count )
{
	int l_len;

	l_len = ( p_s == NULL )? 0 : strlen( p_s );
	if( p_count > l_len )
		p_count = l_len;

	return( rfc_str_create( p_s + l_len - p_count , p_count , 0 ) );
}

/* extract middle part of string */
rfc_string
	rfc_str_extract_middle( const char *p_s , int p_start , int p_count )
{
	int l_len;

	if( p_start < 0 )
		{
			p_start = -p_start;
			l_len = ( p_s == NULL )? 0 : strlen( p_s );
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

	return( rfc_str_create( p_s + p_start , p_count , 0 ) );
}

/* get char by pos from end */
char
	rfc_str_rchar( const char *p_s , int p_rpos )
{
	if( p_s == NULL ||
		p_rpos <= 0 )
		return( 0 );

	p_rpos = strlen( p_s ) - p_rpos;
	if( p_rpos < 0 )
		return( 0 );

	return( p_s[ p_rpos ] );
}

/* set string */
rfc_string
	rfc_str_set( rfc_string p_str , const char *p_s , int p_len )
{
	if( p_str == NULL )
		return( rfc_str_create( p_s , p_len , 0 ) );

	rfc_str_clear( p_str );
	return( rfc_str_append( p_str , 0 , p_s , p_len ) );
}

/*#######################################################*/
/*#######################################################*/

/* make format string */
rfc_string
	rfc_str_format( rfc_string p_str , const char *p_format , ... )
{
	va_list l_va;

	va_start( l_va , p_format );

	p_str = rfc_str_format_va( p_str , p_format , l_va );
	va_end( l_va );

	return( p_str );
}

/* make format string with valist*/
rfc_string
	rfc_str_format_va( rfc_string p_str , const char *p_format , va_list p_va )
{
	const char *l_format;
	va_list l_va;
	int l_max;
	int l_len;
	int l_width;
	int l_prec;
	int l_mod;
	const char *l_next_arg;
	RFC_TYPE x;

	l_format = p_format;
	l_va = p_va;
	l_max = 0;

	/* make a guess at the maximum length of the resulting string */
	for( ; *l_format != '\0'; l_format++ )
		{
			/* handle '%' character, but watch out for '%%' */
			if( *l_format != '%' )
				{
					l_max++;
					continue;
				}

			if( *++l_format == '%' )
				{
					l_max++;
					continue;
				}

			l_len = 0;

			/* handle '%' character with format */
			l_width = 0;
			for( ; *l_format != '\0'; l_format++ )
				{
					/* check for valid flags */
					if( *l_format == '#' )
						l_max += 2;   /* for '0x' */
					else
					if( *l_format == '*' )
						l_width = va_arg( l_va , int );
					else
					if( *l_format == '-' || 
						*l_format == '+' || 
						*l_format == '0' ||
						*l_format == ' ')
						x.u_d = 0;
					else /* hit non-flag character */
						break;
				}

			/* get width and skip it */
			if( l_width == 0 )
				{
					/* width indicated by */
					l_width = atoi( l_format );
					for( ; *l_format != '\0' && isdigit( *l_format ); )
						l_format++;
				}

			/* precesion */
			l_prec = 0;
			if( *l_format == '.' )
				{
					/* skip past '.' separator (width.precision) */
					l_format++;

					/* get precision and skip it */
					if( *l_format == '*' )
						{
							l_prec = va_arg( l_va , int );
							l_format++;
						}
					else
						{
							l_prec = atoi( l_format );
							for( ; *l_format != '\0' && isdigit( *l_format ); )
								l_format++;
						}
				}

			/* should be on type modifier or specifier */
			l_mod = 0;
			if( !strncmp( l_format , RFC_INT64FMTBASE , strlen( RFC_INT64FMTBASE ) ) )
				{
					l_format += strlen( RFC_INT64FMTBASE );
					l_mod = 1;
				}
			else
				{
					switch( *l_format )
						{
							/* modifiers that affect size */
							case 'h':
								l_mod = 2;
								l_format++;
								break;
							case 'l':
								l_mod = 3;
								l_format++;
								break;

							/* modifiers that do not affect size */
							case 'F':
							case 'N':
							case 'L':
								l_format++;
								break;
						}
				}

			/* now should be on specifier */
			switch( *l_format | l_mod )
				{
					/* single characters */
					case 'c':
						l_len = 2;
						x.u_l = va_arg( l_va , int /*char*/ );
						break;

					/* strings */
					case 's':
						l_next_arg = va_arg( l_va , const char * );

						/* check error */
						if( l_next_arg == NULL )
							return( p_str );

						l_len = strlen( l_next_arg );
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
							case 'd':
							case 'i':
							case 'u':
							case 'x':
							case 'X':
							case 'o':
								if( l_mod == 1 )
									x.u_m = va_arg( l_va , RFC_INT64 );
								else
									x.u_l = va_arg( l_va , int );
								l_len = 32;
								l_len = max( l_len , l_width + l_prec );
								break;

							case 'e':
							case 'g':
							case 'G':
								x.u_f = va_arg( l_va , double );
								l_len = 128;
								l_len = max( l_len , l_width + l_prec );
								break;

							case 'f':
								x.u_f = va_arg( l_va , double );
								l_len = 128; /* width isn't truncated */
								/* 312 == strlen("-1+(309 zeroes).") */
								/* 309 zeroes == max precision of a double */
								l_len = max( l_len , 312 + l_prec );
								break;

							case 'p':
								x.u_p = va_arg( l_va , void * );
								l_len = 32;
								l_len = max( l_len , l_width + l_prec );
								break;

							// no output
							case 'n':
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
	p_str = rfc_str_allocate( p_str , l_max );

	vsprintf( p_str , p_format , p_va );
	return( p_str );
}

/* parse format string */
void
	rfc_str_format_parse( const char *p_format , va_list p_va , rfc_string_format *p_fi , int p_opts )
{
	const char *l_format;
	va_list l_va;
	int l_len;
	int l_width;
	int l_prec;
	int l_mod;
	const char *l_next_arg;
	const unsigned short *l_next_arg_w;
	rfc_string_format_el *l_fi;
	RFC_TYPE x;

	p_fi -> s_n = 0;
	l_fi = p_fi -> s_parts;
	l_format = p_format;
	l_va = p_va;

	/* check empty */
	if( l_format == NULL ||
		*l_format == 0 )
		return;

	/* set first format part */
	l_fi -> s_from = 0;

	/* make a guess at the maximum length of the resulting string */
	for( ; *l_format; l_format++ )
		{
			/* handle '%' character, but watch out for '%%' */
			if( *l_format != '%' )
				continue;

			if( *++l_format == '%' )
				continue;

			/* complete text segment */
			l_fi -> s_to = l_format - p_format;
			l_fi -> s_to--;

			/* check not empty text segment */
			if( l_fi -> s_to != l_fi -> s_from )
				{
					l_fi -> s_isarg = 0;
					l_fi++;
					p_fi -> s_n++;
				}

			/* set arg segment */
			l_fi -> s_from = l_format - p_format;
			l_fi -> s_from--;
			l_fi -> s_isarg = 1;
			l_fi -> s_arg_w = -1;
			l_fi -> s_arg_p = -1;
			l_fi -> s_arg_s = 0;

			l_len = 0;

			/* handle '%' character with format */
			l_width = 0;
			for( ; *l_format != '\0'; l_format++ )
				{
					/* check for valid flags */
					if( *l_format == '#' )
						l_fi -> s_arg_s += 2;   /* for '0x' */
					else
					if( *l_format == '*' )
						{
							l_width = va_arg( l_va , int );
							l_fi -> s_arg_w = l_width;
						}
					else
					if( *l_format == '-' || 
						*l_format == '+' || 
						*l_format == '0' ||
						*l_format == ' ')
						x.u_d = 0;
					else /* hit non-flag character */
						break;
				}

			/* get width and skip it */
			if( l_width == 0 )
				{
					/* width indicated by */
					l_width = atoi( l_format );
					for( ; *l_format != '\0' && isdigit( *l_format ); )
						l_format++;
				}

			/* precesion */
			l_prec = 0;
			if( *l_format == '.' )
				{
					/* skip past '.' separator (width.precision) */
					l_format++;

					/* get precision and skip it */
					if( *l_format == '*' )
						{
							l_prec = va_arg( l_va , int );
							l_fi -> s_arg_p = l_prec;
							l_format++;
						}
					else
						{
							l_prec = atoi( l_format );
							for( ; *l_format != '\0' && isdigit( *l_format ); )
								l_format++;
						}
				}

			/* should be on type modifier or specifier */
			l_mod = 0;
			if( !strncmp( l_format , RFC_INT64FMTBASE , strlen( RFC_INT64FMTBASE ) ) )
				{
					l_format += strlen( RFC_INT64FMTBASE );
					l_mod = 1;
				}
			else
				{
					switch( *l_format )
						{
							/* modifiers that affect size */
							case 'h':
								l_mod = 2;
								l_format++;
								break;
							case 'l':
								l_mod = 3;
								l_format++;
								break;

							/* modifiers that do not affect size */
							case 'F':
							case 'N':
							case 'L':
								l_format++;
								break;
						}
				}

			/* now should be on specifier */
			switch( *l_format | l_mod )
				{
					/* single characters */
					case 'c':
						l_len = 2;
						l_fi -> s_arg_v.u_d = va_arg( l_va , int /*short*/ );
						break;

					case 'C':
						l_len = 2;
						l_fi -> s_arg_v.u_b = va_arg( l_va , int /*char*/ );
						break;

					/* strings */
					case 'S':
						if( p_opts & RFC_STR_FPOPT_NOWSTR )
							l_next_arg_w = NULL;
						else
							l_next_arg_w = va_arg( l_va , const unsigned short * );
						l_fi -> s_arg_v.u_wc = l_next_arg_w;

						/* check error */
						if( l_next_arg_w != NULL )
							l_len = rfc_wstr_len( l_next_arg_w );
						else
							l_len = 0;

						l_len = max( 1 , l_len );
						break;
					case 's':
						l_next_arg = va_arg( l_va , const char * );
						l_fi -> s_arg_v.u_c = l_next_arg;

						/* check error */
						if( l_next_arg != NULL )
							l_len = strlen( l_next_arg );
						else
							l_len = 0;

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
							case 'd':
							case 'i':
							case 'u':
							case 'x':
							case 'X':
							case 'o':
								if( l_mod == 1 )
									l_fi -> s_arg_v.u_m = va_arg( l_va , RFC_INT64 );
								else
									l_fi -> s_arg_v.u_l = va_arg( l_va , int );
								l_len = 32;
								l_len = max( l_len , l_width + l_prec );
								break;

							case 'e':
							case 'g':
							case 'G':
								l_fi -> s_arg_v.u_f = va_arg( l_va , double );
								l_len = 128;
								l_len = max( l_len , l_width + l_prec );
								break;

							case 'f':
								l_fi -> s_arg_v.u_f = va_arg( l_va , double );
								l_len = 128; /* width isn't truncated */
								/* 312 == strlen("-1+(309 zeroes).") */
								/* 309 zeroes == max precision of a double */
								l_len = max( l_len , 312 + l_prec );
								break;

							case 'p':
								l_fi -> s_arg_v.u_p = va_arg( l_va , void * );
								l_len = 32;
								l_len = max( l_len , l_width + l_prec );
								break;

							// no output
							case 'n':
								l_fi -> s_arg_v.u_p = va_arg( l_va , int * );
								break;
						}
				}

			l_fi -> s_arg_t = *l_format;
			l_fi -> s_to = ( l_format - p_format ) + 1;
			l_fi -> s_arg_s = l_len;

			/* start new text segment */
			l_fi++;
			p_fi -> s_n++;
			l_fi -> s_isarg = 0;
			l_fi -> s_from = ( l_format - p_format ) + 1;
		}

	/* complete text segment */
	l_fi -> s_to = l_format - p_format;

	/* check not empty text segment */
	if( l_fi -> s_to != l_fi -> s_from )
		{
			l_fi -> s_isarg = 0;
			p_fi -> s_n++;
		}
}

/* print parsed element */
int
	rfc_str_format_parse_printf( char *p_s , const char *p_format , rfc_string_format_el *p_fi )
{
	int l_n;
	char l_format[ 128 ];

	/* segment size */
	l_n = p_fi -> s_to - p_fi -> s_from;

	/* non-argument */
	if( !p_fi -> s_isarg )
		{
			memcpy( p_s , p_format + p_fi -> s_from , l_n );
			p_s[ l_n ] = 0;
			return( l_n );
		}

	/* argument */
	memcpy( l_format , p_format + p_fi -> s_from , l_n );
	l_format[ l_n ] = 0;

	/* special considerations for width and precs */
	if( p_fi -> s_arg_w >= 0 )
		{
			if( p_fi -> s_arg_p >= 0 )
				return( sprintf( p_s , l_format , p_fi -> s_arg_w , p_fi -> s_arg_p , p_fi -> s_arg_v.u_m ) );
			return( sprintf( p_s , l_format , p_fi -> s_arg_w , p_fi -> s_arg_v.u_m ) );
		}

	if( p_fi -> s_arg_p >= 0 )
		return( sprintf( p_s , l_format , p_fi -> s_arg_p , p_fi -> s_arg_v.u_m ) );
	return( sprintf( p_s , l_format , p_fi -> s_arg_v.u_m ) );
}

