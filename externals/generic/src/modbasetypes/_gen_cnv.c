/*#######################################################*/
/*#######################################################*/
/* physical types convertion */

/* std headers */
#include <math.h>
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/
/* routines */

static short
	_rfc_cnv_short( short *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen );
static short
	_rfc_cnv_long( int *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen );
static short
	_rfc_cnv_moment( int *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen );
static short
	_rfc_cnv_timet( time_t *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen );
static short
	_rfc_cnv_money( RFC_INT64 *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen );
static short
	_rfc_cnv_double( double *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen );
static short
	_rfc_cnv_float( float *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen );
static short
	_rfc_cnv_string( rfc_string *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen , void * p_fmt );
static short
	_rfc_cnv_char( char **p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen , void * p_fmt );

/* days from 1900 to 1970 (starting time_t) */
static int
	g_rfc_timet_start = 0;

/*#######################################################*/
/*#######################################################*/

/* convert phys type to phys type */
short
	rfc_type_cnv( const void *p_vfrom , int p_typefrom , void *p_vto , int p_typeto , int *p_tolen , void * p_fmt )
{
	/* for equal types - copy */
	if( p_typefrom == p_typeto )
		{
			rfc_type_set( p_typeto , ( RFC_TYPE * )p_vto , p_vfrom , p_tolen );
			return( 1 );
		}

	/* switch by destination */
	switch( p_typeto )
		{
			case RFC_EXT_TYPESHORT :
				return( _rfc_cnv_short( ( short * )p_vto , p_typefrom , p_vfrom , p_tolen ) );
			case RFC_EXT_TYPELONG :
				return( _rfc_cnv_long( ( int * )p_vto , p_typefrom , p_vfrom , p_tolen ) );
			case RFC_EXT_TYPEMOMENT :
				return( _rfc_cnv_moment( ( int * )p_vto , p_typefrom , p_vfrom , p_tolen ) );
			case RFC_EXT_TYPETIMET :
				return( _rfc_cnv_timet( ( time_t * )p_vto , p_typefrom , p_vfrom , p_tolen ) );
			case RFC_EXT_TYPEMONEY :
				return( _rfc_cnv_money( ( RFC_INT64 * )p_vto , p_typefrom , p_vfrom , p_tolen ) );
			case RFC_EXT_TYPEDOUBLE :
				return( _rfc_cnv_double( ( double * )p_vto , p_typefrom , p_vfrom , p_tolen ) );
			case RFC_EXT_TYPEFLOAT :
				return( _rfc_cnv_float( ( float * )p_vto , p_typefrom , p_vfrom , p_tolen ) );
			case RFC_EXT_TYPESTRING :
				return( _rfc_cnv_string( ( rfc_string * )p_vto , p_typefrom , p_vfrom , p_tolen , p_fmt ) );
			case RFC_EXT_TYPECHAR :
				return( _rfc_cnv_char( ( char ** )p_vto , p_typefrom , p_vfrom , p_tolen , p_fmt ) );
		}

	/* cannot convert to others */
	return( 0 );
}

/* set type value */
short
	rfc_type_set( int p_type , RFC_TYPE *p_data , const void *p_value , int *p_tolen )
{
	switch( p_type )
		{
			case RFC_EXT_TYPESHORT :
				p_data -> u_d = *( const short * )p_value;
				break;
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				p_data -> u_l = *( const int * )p_value;
				break;
			case RFC_EXT_TYPEMONEY :
				p_data -> u_m = *( const RFC_INT64 * )p_value;
				break;
			case RFC_EXT_TYPEDOUBLE :
				p_data -> u_f = *( const double * )p_value;
				break;
			case RFC_EXT_TYPEFLOAT :
				p_data -> u_r = *( const float * )p_value;
				break;
			case RFC_EXT_TYPESTRING :
				if( p_data -> u_s == NULL )
					p_data -> u_s = rfc_str_create( *( const char ** )p_value , -1 , 0 );
				else
					p_data -> u_s = rfc_str_set( p_data -> u_s , *( const char ** )p_value , -1 );
				break;
			case RFC_EXT_TYPECHAR :
				if( p_tolen != NULL )
					return( rfc_copy_char( p_data -> u_s , *( char ** )p_value , p_tolen ) );
				p_data -> u_s = *( char ** )p_value;
				break;
			case RFC_EXT_TYPEPTR :
				p_data -> u_p = *( void * const * )p_value;
				break;
			case RFC_EXT_TYPEBYTE :
				p_data -> u_b = **( const char ** )p_value;
				break;
			case RFC_EXT_TYPEBLOB :
				rfc_blob_copy( &p_data -> u_o , ( const rfc_blob *)p_value );
				break;

			default :
				return( 0 );
		}

	return( 1 );
}

/* compare type values */
int
	rfc_type_cmp( int p_type , const void *p_v1 , const void *p_v2 )
{
	RFC_TYPE l_v1;
	RFC_TYPE l_v2;

	if( p_v1 == NULL )
		{
			/* NULL equal to NULL */
			if( p_v2 == NULL )
				return( 0 );
			/* NULL more than not NULL */
			return( 1 );
		}
	/* not NULL less than NULL */
	if( p_v2 == NULL )
		return( -1 );

	switch( p_type )
		{
			case RFC_EXT_TYPEBYTE :
				l_v1.u_b = *( const char * )p_v1;
				l_v2.u_b = *( const char * )p_v2;
				if( l_v1.u_b > l_v2.u_b )
					return( 1 );
				if( l_v1.u_b < l_v2.u_b )
					return( -1 );
				return( 0 );
			case RFC_EXT_TYPESHORT :
				l_v1.u_d = *( const short * )p_v1;
				l_v2.u_d = *( const short * )p_v2;
				if( l_v1.u_d > l_v2.u_d )
					return( 1 );
				if( l_v1.u_d < l_v2.u_d )
					return( -1 );
				return( 0 );
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				l_v1.u_l = *( const int * )p_v1;
				l_v2.u_l = *( const int * )p_v2;
				if( l_v1.u_l > l_v2.u_l )
					return( 1 );
				if( l_v1.u_l < l_v2.u_l )
					return( -1 );
				return( 0 );
			case RFC_EXT_TYPEMONEY :
				l_v1.u_m = *( const RFC_INT64 * )p_v1;
				l_v2.u_m = *( const RFC_INT64 * )p_v2;
				if( l_v1.u_m > l_v2.u_m )
					return( 1 );
				if( l_v1.u_m < l_v2.u_m )
					return( -1 );
				return( 0 );
			case RFC_EXT_TYPEDOUBLE :
				l_v1.u_f = *( const double * )p_v1;
				l_v2.u_f = *( const double * )p_v2;
				if( l_v1.u_f > l_v2.u_f )
					return( 1 );
				if( l_v1.u_f < l_v2.u_f )
					return( -1 );
				return( 0 );
			case RFC_EXT_TYPEFLOAT :
				l_v1.u_r = *( const float * )p_v1;
				l_v2.u_r = *( const float * )p_v2;
				if( l_v1.u_r > l_v2.u_r )
					return( 1 );
				if( l_v1.u_r < l_v2.u_r )
					return( -1 );
				return( 0 );
			case RFC_EXT_TYPESTRING :
			case RFC_EXT_TYPECHAR :
				l_v1.u_s = *( char * const * )p_v1;
				l_v2.u_s = *( char * const * )p_v2;
				if( l_v1.u_s == NULL )
					{
						if( l_v2.u_s == NULL )
							return( 0 );
						return( 1 );
					}
				if( l_v2.u_s == NULL )
					return( -1 );
				return( strcmp( l_v1.u_s , l_v2.u_s ) );
			case RFC_EXT_TYPEPTR :
				l_v1.u_p = *( void * const * )p_v1;
				l_v2.u_p = *( void * const * )p_v2;
				if( l_v1.u_p > l_v2.u_p )
					return( 1 );
				if( l_v1.u_p < l_v2.u_p )
					return( -1 );
				return( 0 );
		}
	return( 0 );
}

short
	rfc_copy_char( char *p_to , const char *p_from , int *p_tolen )
{
	int l_len;

	if( p_from == NULL )
		{
			*p_to = 0;
			*p_tolen = 0;
		}
	else
		{
			l_len = strlen( p_from );
			if( l_len > *p_tolen )
				return( 0 );
			strcpy( p_to , p_from );
			*p_tolen = l_len;
		}
	
	return( 1 );
}

/*#######################################################*/
/*#######################################################*/

static short
	_rfc_cnv_short( short *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen )
{
	int l_i;

	/* switch by source */
	switch( p_typefrom )
		{
			case RFC_EXT_TYPELONG :
				l_i = *( int * )p_vfrom;
				if( l_i < 0 )
					{
						l_i = -l_i;
						if( l_i & 0xFFFF0000 )
							return( 0 );
						*p_vto = -( l_i & 0x0000FFFF );
					}
				else
					{
						if( l_i & 0xFFFF0000 )
							return( 0 );
						*p_vto = l_i & 0x0000FFFF;
					}
				return( 1 );
			case RFC_EXT_TYPECHAR :
			case RFC_EXT_TYPESTRING :
				if( *( const char ** )p_vfrom == NULL )
					return( 0 );
				l_i = atoi( *( const char ** )p_vfrom );
				return( _rfc_cnv_short( p_vto , RFC_EXT_TYPELONG , &l_i , NULL ) );
		}

	return( 0 );
}

static short
	_rfc_cnv_long( int *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen )
{
	/* switch by source */
	switch( p_typefrom )
		{
			case RFC_EXT_TYPESHORT :
				*p_vto = *( short * )p_vfrom;
				return( 1 );
			case RFC_EXT_TYPECHAR :
			case RFC_EXT_TYPESTRING :
				if( *( const char ** )p_vfrom == NULL )
					return( 0 );
				*p_vto = atoi( *( const char ** )p_vfrom );
				return( 1 );
		}
	return( 0 );
}

static short
	_rfc_cnv_moment( int *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen )
{
	int l_sec;
	int l_m;
	const char *l_s;

	/* switch by source */
	switch( p_typefrom )
		{
			case RFC_EXT_TYPELONG :
				rfc_type_set( RFC_EXT_TYPEMOMENT , ( RFC_TYPE * )p_vto , p_vfrom , p_tolen );
				return( 1 );
			case RFC_EXT_TYPETIMET :
				if( !g_rfc_timet_start )
					g_rfc_timet_start = rfc_dtm_get_days( 700101 );
				l_sec = *( int * )p_vfrom;
				l_m = 100 * rfc_dtm_get_moment( g_rfc_timet_start + ( l_sec / ( 24 * 3600 ) ) );
				l_m += ( l_sec % ( 24 * 3600 ) ) / ( 15 * 60 );
				*p_vto = l_m;
				return( 1 );
			case RFC_EXT_TYPECHAR :
			case RFC_EXT_TYPESTRING :
				l_s = *( const char ** )p_vfrom;
				if( l_s == NULL )
					return( 0 );
				/* convert as d.m.y */
				l_m = rfc_dtm_format_get( l_s );
				*p_vto = l_m + 95;
				return( 1 );
		}

	return( 0 );
}

static short
	_rfc_cnv_timet( time_t *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen )
{
	int l_m;
	int l_days;

	/* switch by source */
	switch( p_typefrom )
		{
			case RFC_EXT_TYPELONG :
				rfc_type_set( RFC_EXT_TYPETIMET , ( RFC_TYPE * )p_vto , p_vfrom , p_tolen );
				return( 1 );
			case RFC_EXT_TYPEMOMENT :
				if( !g_rfc_timet_start )
					g_rfc_timet_start = rfc_dtm_get_days( 700101 );
				l_m = *( int * )p_vfrom;
				l_days = rfc_dtm_get_days( l_m / 100 ) - g_rfc_timet_start;
				*p_vto = l_days * 24 * 3600 + ( l_m % 100 ) * 15 * 60;
				return( 1 );
			case RFC_EXT_TYPECHAR :
			case RFC_EXT_TYPESTRING :
				if( !_rfc_cnv_moment( &l_m , RFC_EXT_TYPESTRING , p_vfrom , NULL ) )
					return( 0 );
				return( _rfc_cnv_timet( p_vto , RFC_EXT_TYPEMOMENT , &l_m , NULL ) );
		}

	return( 0 );
}

static short
	_rfc_cnv_money( RFC_INT64 *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen )
{
	double l_df , l_di;
	const char *l_s;

	/* switch by source */
	switch( p_typefrom )
		{
			case RFC_EXT_TYPESHORT :
				*p_vto = *( short * )p_vfrom * 10000;
				return( 1 );
			case RFC_EXT_TYPELONG :
				*p_vto = *( int * )p_vfrom * 10000;
				return( 1 );
			case RFC_EXT_TYPEDOUBLE :
				l_df = modf( *( double * )p_vfrom , &l_di );
				*p_vto = ( ( RFC_INT64 )l_di ) * 10000 + ( RFC_INT64 )( l_df * 10000 );
				return( 1 );
			case RFC_EXT_TYPEFLOAT :
				l_df = modf( *( float * )p_vfrom , &l_di );
				*p_vto = ( ( RFC_INT64 )l_di ) * 10000 + ( RFC_INT64 )( l_df * 10000 );
				return( 1 );
			case RFC_EXT_TYPECHAR :
			case RFC_EXT_TYPESTRING :
				l_s = *( const char ** )p_vfrom;
				if( l_s == NULL )
					return( 0 );
				*p_vto = rfc_money_string2money( l_s );
				return( 1 );
		}

	return( 0 );
}

static short
	_rfc_cnv_double( double *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen )
{
	RFC_INT64 l_m;
	double l_d;
	const char *l_s;

	/* switch by source */
	switch( p_typefrom )
		{
			case RFC_EXT_TYPEFLOAT :
				*p_vto = *( float * )p_vfrom;
				return( 1 );
			case RFC_EXT_TYPESHORT :
				*p_vto = *( short * )p_vfrom;
				return( 1 );
			case RFC_EXT_TYPELONG :
				*p_vto = *( int * )p_vfrom;
				return( 1 );
			case RFC_EXT_TYPEMONEY :
				l_m = *( RFC_INT64 * )p_vfrom;
				if( l_m < 0 )
					{
						l_m = -l_m;
						l_d = ( double )( l_m / 10000 );
						l_m %= 10000;
						l_d += ( ( double )l_m ) / 10000;
						*p_vto = -l_d;
					}
				else
					{
						l_d = ( double )( l_m / 10000 );
						l_m %= 10000;
						l_d += ( ( double )l_m ) / 10000;
						*p_vto = l_d;
					}
				return( 1 );
			case RFC_EXT_TYPECHAR :
			case RFC_EXT_TYPESTRING :
				l_s = *( const char ** )p_vfrom;
				if( l_s == NULL )
					return( 0 );
				*p_vto = atof( l_s );
				return( 1 );
		}

	return( 0 );
}

static short
	_rfc_cnv_float( float *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen )
{
	RFC_INT64 l_m;
	float l_d;
	const char *l_s;

	/* switch by source */
	switch( p_typefrom )
		{
			case RFC_EXT_TYPEDOUBLE :
				*p_vto = ( float )*( double * )p_vfrom;
				return( 1 );
			case RFC_EXT_TYPESHORT :
				*p_vto = *( short * )p_vfrom;
				return( 1 );
			case RFC_EXT_TYPELONG :
				*p_vto = ( float )*( int * )p_vfrom;
				return( 1 );
			case RFC_EXT_TYPEMONEY :
				l_m = *( RFC_INT64 * )p_vfrom;
				if( l_m < 0 )
					{
						l_m = -l_m;
						l_d = ( float )( l_m / 10000 );
						l_m %= 10000;
						l_d += ( ( float )l_m ) / 10000;
						*p_vto = -l_d;
					}
				else
					{
						l_d = ( float )( l_m / 10000 );
						l_m %= 10000;
						l_d += ( ( float )l_m ) / 10000;
						*p_vto = l_d;
					}
				return( 1 );
			case RFC_EXT_TYPECHAR :
			case RFC_EXT_TYPESTRING :
				l_s = *( const char ** )p_vfrom;
				if( l_s == NULL )
					return( 0 );
				*p_vto = ( float )atof( l_s );
				return( 1 );
		}

	return( 0 );
}

static short
	_rfc_cnv_string( rfc_string *p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen , void * p_fmt )
{
	rfc_string l_s;
	int l_m;

	/* switch by source */
	switch( p_typefrom )
		{
			case RFC_EXT_TYPESHORT :
				*p_vto = l_s = rfc_str_create( NULL , 0 , 6 );
				sprintf( l_s , "%d" , ( int )*( short * )p_vfrom );
				return( 1 );
			case RFC_EXT_TYPELONG :
				*p_vto = l_s = rfc_str_create( NULL , 0 , 11 );
				sprintf( l_s , "%d" , ( int )*( int * )p_vfrom );
				return( 1 );
			case RFC_EXT_TYPEMOMENT :
				*p_vto = l_s = rfc_str_create( NULL , 0 , 11 );
				rfc_dtm_moment2string ( *( int * )p_vfrom, ( rfc_fmt_date * )p_fmt , l_s);
				return( 1 );
			case RFC_EXT_TYPETIMET :
				if( !_rfc_cnv_moment( &l_m , RFC_EXT_TYPETIMET , p_vfrom , NULL ) )
					return( 0 );
				return( _rfc_cnv_string( p_vto , RFC_EXT_TYPEMOMENT , &l_m , NULL , p_fmt ) );
			case RFC_EXT_TYPEMONEY :
				*p_vto = l_s = rfc_str_create( NULL , 0 , 21 );
				rfc_money_money2string( *( RFC_INT64 * )p_vfrom , ( rfc_fmt_money * )p_fmt , l_s );
				return( 1 );
			case RFC_EXT_TYPEDOUBLE :
				*p_vto = l_s = rfc_str_create( NULL , 0 , 64 );
				sprintf( l_s , "%lf" , *( double * )p_vfrom );
				return( 1 );
			case RFC_EXT_TYPEFLOAT :
				*p_vto = l_s = rfc_str_create( NULL , 0 , 32 );
				sprintf( l_s , "%f" , *( double * )p_vfrom );
				return( 1 );
			case RFC_EXT_TYPECHAR :
				*p_vto = l_s = rfc_str_create( *( const char ** )p_vfrom , -1 , 0 );
				return( 1 );
		}

	return( 0 );
}

static short
	_rfc_cnv_char( char **p_vto , int p_typefrom , const void *p_vfrom , int *p_tolen , void * p_fmt )
{
	int l_m;
	char l_buf[ 64 ];
	int l_len;

	/* switch by source */
	switch( p_typefrom )
		{
			case RFC_EXT_TYPEBYTE :
				if( p_tolen == NULL )
					return( 0 );
				l_len = sprintf( l_buf , "%c" , *( char * )p_vfrom );
				break;
			case RFC_EXT_TYPESHORT :
				if( p_tolen == NULL )
					return( 0 );
				l_len = sprintf( l_buf , "%d" , ( int )*( short * )p_vfrom );
				break;
			case RFC_EXT_TYPELONG :
				if( p_tolen == NULL )
					return( 0 );
				l_len = sprintf( l_buf , "%d" , ( int )*( int * )p_vfrom );
				break;
			case RFC_EXT_TYPEMOMENT :
				if( p_tolen == NULL )
					return( 0 );
				if ( *(int*)p_vfrom >= 2000123100  )
					 l_buf[ 0 ] = 0;
				else
					rfc_dtm_moment2string( *( int * )p_vfrom , ( rfc_fmt_date * )p_fmt , l_buf );
				l_len = strlen( l_buf );
				break;
			case RFC_EXT_TYPETIMET :
				if( p_tolen == NULL )
					return( 0 );
				if( !_rfc_cnv_moment( &l_m , RFC_EXT_TYPETIMET , p_vfrom , NULL ) )
					return( 0 );
				return( _rfc_cnv_char( p_vto , RFC_EXT_TYPEMOMENT , &l_m , p_tolen , p_fmt ) );
			case RFC_EXT_TYPEMONEY :
				if( p_tolen == NULL )
					return( 0 );
				rfc_money_money2string( *( RFC_INT64 * )p_vfrom , (rfc_fmt_money *) p_fmt, l_buf );
				l_len = strlen( l_buf );
				break;
			case RFC_EXT_TYPEDOUBLE :
				if( p_tolen == NULL )
					return( 0 );
				l_len = sprintf( l_buf , "%lf" , *( double * )p_vfrom );
				break;
			case RFC_EXT_TYPEFLOAT :
				if( p_tolen == NULL )
					return( 0 );
				l_len = sprintf( l_buf , "%f" , *( float * )p_vfrom );
				break;
			case RFC_EXT_TYPESTRING :
				if( p_tolen != NULL )
					return( rfc_copy_char( *p_vto , *( char ** )p_vfrom , p_tolen ) );
				*p_vto = *( char ** )p_vfrom;
				return( 1 );
		}

	if( p_tolen == NULL || l_len > *p_tolen )
		return( 0 );
	strcpy( *p_vto , l_buf );
	*p_tolen = l_len;

	return( 1 );
}

/*#######################################################*/
/*#######################################################*/

