/*#######################################################*/
/*#######################################################*/

/* std headers */
#include <math.h>
#include "__gen.h"

/* SIGN macro definition */
#define SIGN( x )			( x < 0 ? -1 : 1 )

/* operations */
/* money (int64) to string convertion. p_mstr - destination buffer */
void
	rfc_money_money2string( RFC_INT64 p_val, const rfc_fmt_money * p_fmt , char * p_mstr )
{
	char	l_buf[ 80 ];
	RFC_INT64	l_int;
	int			l_dig , l_pos , l_len , i, l_k;
	double		l_fract;
	short		l_sign = SIGN( p_val );
	rfc_fmt_money l_fmtdef;

	memset( ( void * )l_buf, '\0', sizeof( l_buf ) );

	if ( p_fmt == NULL )
	{
		rfc_money_get_deformat( &l_fmtdef );
		p_fmt = &l_fmtdef;
	}

	l_int	= l_sign * p_val / 10000;
	l_fract = ( double )( l_sign * p_val % 10000 );

	if( p_fmt -> s_prec . s_ndig < 4 )
	{
		for( i = 0 , l_dig = 10000; i < p_fmt -> s_prec . s_ndig; i++ ) 
			l_dig /= 10;
		l_fract /= l_dig;
		l_k = ( int )l_fract;
		if ( p_fmt -> s_rndtype != RFC_FMT_MONEY_ROUNDTRUNC )
			l_fract = ( l_fract - l_k ) < 0.5 ? l_k : l_k + 1;
		else
			l_fract = l_k;
		if( l_fract * l_dig == 10000 )	{ l_int ++; l_fract = 0; }
	}
	/* before decimal */
	l_len = strlen( p_fmt -> s_group . s_chdiv );
	l_pos = 0;
	l_k = 1;
	strcpy( l_buf + 29 , "0" );
	if( l_int == 0 )
		l_buf[ 30 - l_pos ++ ] = '0';
	else
		while( l_int )
		{
			l_dig  = ( int )( l_int % 10 ); 
			l_int /= 10;

			l_buf[ 30 - l_pos ++ ] = '0' + l_dig;
			if( l_k++  % p_fmt -> s_group . s_ndig == 0 && l_int != 0 )
			{
				for( i = 0; i < l_len; i ++ )	
					l_buf[ 30 - l_pos ++ ] = p_fmt -> s_group . s_chdiv[ i ];
				l_k = 1;
			}
		}

	if ( l_sign == -1  &&  
		 p_fmt -> s_neg_fmt != RFC_FMT_MONEY_NEGCOLORUNSIGNED )
		l_buf[ 30 - l_pos++] = '-';

	/* after decimal */
	if( p_fmt -> s_prec . s_ndig != 0 )
	{
		strcat( l_buf + 30 , p_fmt -> s_prec . s_chdiv );
		l_len = strlen( p_fmt -> s_prec . s_chdiv );
		if( p_fmt -> s_prec . s_ndig < 4 )
			sprintf( l_buf + 30 + l_len + 1, "%.*d" , p_fmt -> s_prec . s_ndig , ( int )l_fract );
		else
			sprintf( l_buf + 30 + l_len + 1, "%.4d%.*d" , ( int )l_fract , p_fmt -> s_prec . s_ndig - 4 , ( int )0 );
	}

	strcpy( p_mstr , l_buf + ( 30 - l_pos + 1 ) );
	/* return( l_buf + ( 30 - l_pos + 1 ) ); */
}

/* get default format */
void
	rfc_money_get_deformat( rfc_fmt_money * p_fmt )
{
	*p_fmt -> s_group.s_chdiv = 0;
	p_fmt -> s_group.s_ndig  = 3;
	*p_fmt -> s_prec.s_chdiv = '.';
	*( p_fmt -> s_prec.s_chdiv + 1 ) = 0;
	p_fmt -> s_prec.s_ndig	 = 2;
}

/* double to money (int64) convertion */
RFC_INT64 
	rfc_money_double2money( double p_val )
{
	double l_val = p_val * 10000;
	double l_int;

	modf( l_val, &l_int );
	return( ( RFC_INT64 )l_int );
}

/* money (int64) to double convertion */
double 
	rfc_money_money2double( RFC_INT64 p_val )
{
	RFC_INT64 l_int, l_fract;
	double l_val = 0;

	l_int = p_val / 10000;
	l_fract = p_val % 10000;

	l_val = l_int + ( double )l_fract / 10000;
	return( l_val );
}

/* money multiply "p_first" and "p_second" */
RFC_INT64 
	rfc_money_mul( RFC_INT64 p_first, RFC_INT64 p_second )
{
	RFC_INT64 l_first_int, l_first_frac;
	RFC_INT64 l_second_int, l_second_frac;
	short l_sign1, l_sign2;
	RFC_INT64 l_res;

	l_sign1 = SIGN( p_first );
	l_sign2 = SIGN( p_second );
	p_first *= l_sign1;
	p_second *= l_sign2;
	l_sign1 *= l_sign2;

	l_first_int = p_first / 10000;
	l_first_frac = p_first % 10000;

	l_second_int = p_second / 10000;
	l_second_frac = p_second % 10000;

	l_res = 10000 * l_first_int * l_second_int + 
		l_first_int * l_second_frac + l_first_frac * l_second_int + 
		l_first_frac * l_second_frac / 10000;

	l_res *= l_sign1;

	return( l_res );
}

/* money division "p_first" and "p_second" */
RFC_INT64 
	rfc_money_div( RFC_INT64 p_first, RFC_INT64 p_second )
{
	short l_sign1 = SIGN( p_first );
	short l_sign2 = SIGN( p_second );
	RFC_INT64 l_res;

	p_first *= l_sign1;
	p_second *= l_sign2;

	l_res = ( p_first / p_second ) * 10000 + 
		p_first % p_second * 10000 / p_second;

	l_res *= l_sign1 * l_sign2;

	return( l_res );
}

/* string to money (int64) convertion. p_buf - destination buffer */
RFC_INT64
	rfc_money_string2money( const char *p_buf )
{
	RFC_INT64 l_i;
	int l_f;
	short l_c;
	int l_r;
	short l_neg;

	if( *p_buf == '-' )
		{
			l_neg = 1;
			p_buf++;
		}
	else
		l_neg = 0;

	if( *p_buf == '.' )
		{
			l_i = 0;
			sscanf( p_buf + 1 , "%4u" , &l_f );
			l_c = 2;
		}
	else
		{
			l_c = sscanf( p_buf , RFC_INT64FMT ".%4u" , &l_i , &l_f );
			if( l_c == 0 )
				return( ( RFC_INT64 )0 );
		}
			
	if( l_c == 2 )
		{
			if( l_f >= 1000 )
				l_r = l_f;
			else
			if( l_f >= 100 )
				l_r = l_f * 10;
			else
			if( l_f >= 10 )
				l_r = l_f * 100;
			else
			if( l_f > 0 )
				l_r = l_f * 1000;
			else
				l_r = 0;
		}
	else
		l_r = 0;
	l_i = l_i * 10000 + l_r;
	if( l_neg )
		l_i = -l_i;

	return( l_i );
}

/*#######################################################*/
/*#######################################################*/
