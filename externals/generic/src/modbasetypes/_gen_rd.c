/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

#include <time.h>

/*#######################################################*/
/*#######################################################*/

/* monthes */
static int g_dtm_month[ 12 ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


const char * months[] = 
{ 	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October" , "November", "December" };

const char * mon[] = 
{ 	"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
	"JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

const char * week[] = 
{	"sunday" ,"monday", "tuesday", "wednesday", "thursday",
	"friday", "saturday" };

const char * wk[] = 
{ 	"sn", "mn", "tu", "wd", "th", "fr", "st" };


/*#######################################################*/
/*#######################################################*/
/* datetime functions */

/* get date from format */
rfc_moment
	rfc_dtm_format_get( const char *p_date )
{
	int l_year , l_month , l_day;
	sscanf( p_date , "%d.%d.%d" , &l_day , &l_month , &l_year );
	return( ( l_year - 1900 ) * 1000000 + l_month * 10000 + l_day * 100 );
}

void 
	_rfc_dtm_stm2string( struct tm * p_tm , rfc_fmt_date * p_fmt , char * p_tmstr )
{
	const char * l_dtdiv = "  ";
	int		year, month, day ,
			hour, min  , sec ,
			i ;
	char	l_sss[ 11 ] ,
			l_str[ 28 ] ;

	year	= p_tm -> tm_year + 1900;
	day		= p_tm -> tm_mday;
	month	= p_tm -> tm_mon;
	hour	= p_tm -> tm_hour;
	min		= p_tm -> tm_min;
	sec		= p_tm -> tm_sec;

	l_str[ 0 ] = '\0';

	for ( i = 0; i < 4; i++ ) {
		switch( p_fmt -> s_el[ i ].s_type  ) {
			case 'Y':
				if ( p_fmt -> s_el[ i ].s_fmt != RFC_FMT_NOT ) {
					if ( p_fmt -> s_el[ i ].s_fmt == RFC_FMT_YEAR_SHORTDIG )
						year %= 100;

					sprintf( l_sss , "%0*d" , p_fmt -> s_el[ i ].s_fmt , year );
					strcat( l_str , l_sss );
					if ( i < 3 && p_fmt -> s_el[ i + 1 ].s_type != 'T' &&
							p_fmt -> s_el[ i + 1 ].s_fmt != RFC_FMT_NOT )
						strcat( l_str , p_fmt -> s_ddiv );
					else
						strcat( l_str , l_dtdiv );
				}
				break;

			case 'M':
				if ( p_fmt -> s_el [ i ] . s_fmt != RFC_FMT_NOT ) {
					if ( p_fmt -> s_el [ i ] . s_fmt == RFC_FMT_MONTH_LONGSTR ) {
						sprintf( l_sss , "%s" , months[ month ] );
						strcat( l_str , l_sss );
					}
					else if ( p_fmt -> s_el [ i ].s_fmt == RFC_FMT_MONTH_SHORTSTR ) {
						sprintf( l_sss , "%s" , mon[ month ] );
						strcat( l_str , l_sss );
					}
					else {
						sprintf( l_sss , "%.*d" , p_fmt -> s_el[ i ].s_fmt , month );
						strcat( l_str , l_sss );
					}

					if ( i < 3 && p_fmt -> s_el[ i + 1 ] . s_type != 'T' &&
							p_fmt -> s_el[ i + 1 ] .s_fmt != RFC_FMT_NOT)
						strcat( l_str , p_fmt -> s_ddiv );
					else
						strcat( l_str , l_dtdiv );
				}
			break;

			case 'D':
				if ( p_fmt -> s_el[ i ] . s_fmt  != RFC_FMT_NOT ) {
					if ( p_fmt -> s_el[ i ] . s_fmt  == RFC_FMT_DAY_SHORTSTR ) {
						sprintf( l_sss , "%s" ,	wk[ p_tm -> tm_wday ] );
						l_str[ 0 ] = '\0';
						strcat( l_str , l_sss );
						strcpy( p_tmstr , l_str );
						return;
					}
					else if ( p_fmt -> s_el[ i ] . s_fmt  == RFC_FMT_DAY_LONGSTR ) {
						sprintf( l_sss , "%s" , week[ p_tm -> tm_wday ] );
						l_str[ 0 ] = '\0';
						strcat( l_str , l_sss );
						strcpy( p_tmstr , l_str );
						return;
					}
					else {
						sprintf( l_sss , "%.*d" , p_fmt -> s_el[ i ] . s_fmt , day );
						strcat( l_str , l_sss );
						if ( i < 3 && p_fmt -> s_el[ i + 1 ] . s_type != 'T' &&
								p_fmt -> s_el[ i + 1 ] .s_fmt != RFC_FMT_NOT)
							strcat( l_str , p_fmt -> s_ddiv );
						else
							strcat( l_str , l_dtdiv ); 
					}
				}
				break;

			case 'T':
				if ( p_fmt -> s_el[ i ] . s_fmt  != RFC_FMT_NOT ) {
					sprintf( l_sss , "%02d" , hour );
					strcat( l_str , l_sss );
					strcat( l_str , p_fmt -> s_tdiv );
					sprintf( l_sss , "%02d" , min );
					strcat( l_str , l_sss );

					if ( p_fmt -> s_el[ i ] . s_fmt == RFC_FMT_TIME_LONGDIG ) {
						strcat( l_str , p_fmt -> s_tdiv );
						sprintf( l_sss , "%02d" , sec );
						strcat( l_str , l_sss );
					}

					if ( i < 3 )
						strcat( l_str , l_dtdiv ); 
				}
				break;
		}
	}

	strcpy( p_tmstr , l_str );
}

/* convert time_t date/time to formated string */
void 
	rfc_dtm_time2string( time_t p_time , const rfc_fmt_date *p_fmt , char *p_tmstr ) {

	struct tm		l_s_tm;
	rfc_fmt_date	l_fmt;

	if ( p_fmt == NULL ) {
		l_fmt.s_el[ 0 ].s_type	= 'D';
		l_fmt.s_el[ 0 ].s_fmt	= RFC_FMT_DAY_LONGDIG;
		l_fmt.s_el[ 1 ].s_type	= 'M';
		l_fmt.s_el[ 1 ].s_fmt	= RFC_FMT_MONTH_LONGDIG;
		l_fmt.s_el[ 2 ].s_type	= 'Y';
		l_fmt.s_el[ 2 ].s_fmt	= RFC_FMT_YEAR_LONGDIG;
		l_fmt.s_el[ 3 ].s_type	= 'T';
		l_fmt.s_el[ 3 ].s_fmt	= RFC_FMT_TIME_SHORTDIG;
		strcpy( l_fmt.s_ddiv , "." );
		strcpy( l_fmt.s_tdiv , ":" );
	}
	else
		memcpy( &l_fmt , p_fmt , sizeof( rfc_fmt_date ) );

	localtime_r( &p_time , &l_s_tm );
	_rfc_dtm_stm2string( &l_s_tm , &l_fmt , p_tmstr );
}

rfc_moment rfc_dtm_moment( short p_prec )
{
	time_t		t		= time( NULL );
	struct tm	l_tms;

	char l_buf[9+1];
	int l_min = 0;

	localtime_r( &t, &l_tms );
	switch( p_prec ) {
		case 0:	l_min = 95;	break;
		case 1:	l_min = ( l_tms.tm_min + 60 * l_tms.tm_hour ) / 15 ; break;
	}
			
	sprintf( l_buf , "%03d%02d%02d%02d" , l_tms.tm_year , l_tms.tm_mon + 1 , l_tms.tm_mday , (int)l_min );

	return (rfc_moment) atoi( l_buf );
}

/* get default format */
void
	rfc_dtm_get_deformat( rfc_fmt_date * p_fmt )
{
	p_fmt -> s_el[ 0 ] . s_type	= 'D';
	p_fmt -> s_el[ 0 ] . s_fmt	= RFC_FMT_DAY_LONGDIG;
	p_fmt -> s_el[ 1 ] . s_type	= 'M';
	p_fmt -> s_el[ 1 ] . s_fmt	= RFC_FMT_MONTH_LONGDIG;
	p_fmt -> s_el[ 2 ] . s_type	= 'Y';
	p_fmt -> s_el[ 2 ] . s_fmt	= RFC_FMT_YEAR_LONGDIG;
	p_fmt -> s_el[ 3 ] . s_type	= 'T';
	p_fmt -> s_el[ 3 ] . s_fmt	= RFC_FMT_NOT;
	strcpy( p_fmt -> s_ddiv , "." );
	strcpy( p_fmt -> s_tdiv , ":" );
}

/* convert rfc_moment date/time to formated string */
void 
	rfc_dtm_moment2string ( rfc_moment p_mmt, const rfc_fmt_date * p_fmt , char * p_mmtstr )
{
	rfc_fmt_date	l_fmt;
	struct tm		l_tms;
	int				year, day, month, i;

	if( p_mmt == 0 ) {
		p_mmtstr[ 0 ] = '\0';
		return;
	}

	year  = ( p_mmt / 1000000 );
	month = ( p_mmt / 10000 ) % 100;
	day   = ( p_mmt / 100 ) % 100;

	if ( p_fmt != NULL ) {
		memcpy( &l_fmt , p_fmt , sizeof( rfc_fmt_date ) );
		i = 0;

		while ( l_fmt . s_el[ i++ ] . s_type != 'T' && i < 4 ) ;
		if ( --i < 4 ) 
			l_fmt . s_el[ i ] . s_fmt = RFC_FMT_NOT;
	}
	else
		rfc_dtm_get_deformat( &l_fmt );

	l_tms . tm_hour	= l_tms.tm_min = l_tms.tm_sec = 0;
 
	l_tms . tm_mday	= day;
	l_tms . tm_mon	= month;
	l_tms . tm_year	= year;
	/* corect 0 -> 01.01.1900 is We, week[0] set for Su */
	l_tms . tm_wday = ( rfc_dtm_get_weekday( p_mmt ) + 4 ) % 7;

	_rfc_dtm_stm2string( &l_tms , &l_fmt , p_mmtstr );
}

/* get moment from days since 01.01.1900 */
rfc_moment
	rfc_dtm_get_moment( int p_days )
{
	int l_year;
	int l_month;
	int l_x;

	int l_early;
	int l_yeardays;
	int l_remdays;

	/* get fixed early margin */
	l_year = 1900;
	l_year += ( int )( p_days / 366 );
	/* get early year 01.01 date */
	l_early = ( l_year - 1900 ) * 365;
	/* plus count of %4 */
	l_early += ( l_year / 4 ) - ( 1900 / 4 );
	/* minus count of %100 */
	l_early -= ( l_year / 100 ) - ( 1900 / 100 );
	/* plus count of %400 */
	l_early += ( l_year / 400 ) - ( 1900 / 400 );

	/* remainder */
	l_remdays = p_days - l_early;

	/* calc year */
	while( 1 )
		{
			/* calc days of this year */
			l_yeardays = 366;
			if( l_year % 4 )
				l_yeardays--;
			else
			if( ( l_year % 100 ) == 0 &&
				( l_year % 400 ) != 0 )
				l_yeardays--;
			if( l_remdays < l_yeardays )
				break;
			l_remdays -= l_yeardays;
			l_year++;
		}

	/* calc month */
	for( l_month = 0; l_month < 12; l_month++ )
		{
			l_x = g_dtm_month[ l_month ];
			/* set febrary days */
			if( l_month == 1 &&
				l_yeardays == 366 )
				l_x++;
			if( l_remdays < l_x )
				break;
			l_remdays -= l_x;
		}

	/* return value */
	return( ( ( l_year - 1900 ) * 100 + ( l_month + 1 ) 
			) * 100 + ( l_remdays + 1 )
		  );
}

/* get days from 1900.01.01 */
int
	rfc_dtm_get_days( rfc_moment p_moment )
{
	int l_year;
	int l_month;

	int l_early;

	l_year = p_moment / 10000;
	l_year += 1900;
	/* get year 01.01 date */
	l_early = ( l_year - 1900 ) * 365;
	/* plus count of %4 */
	l_early += ( l_year / 4 ) - ( 1900 / 4 );
	/* minus count of %100 */
	l_early -= ( l_year / 100 ) - ( 1900 / 100 );
	/* plus count of %400 */
	l_early += ( l_year / 400 ) - ( 1900 / 400 );

	/* get month */
	l_month = ( p_moment / 100 ) % 100;
	while( --l_month )
		{
			l_early += g_dtm_month[ l_month ];
			if( l_month == 1 )
				if( ( ( l_year % 4 ) == 0 ) &&
					    ( ( ( l_year % 100 ) != 0 ) ||
					      ( ( l_year % 400 ) == 0 ) 
					    )
			      )
					l_early++;
		}

	/* plus days */
	l_early += p_moment % 100;
	l_early--;

	return( l_early );
}

/* get day of the week (monday=0) */
int
	rfc_dtm_get_weekday( rfc_moment p_moment )
{
	/* 00000101 is 2 */
	return( rfc_dtm_get_days( p_moment ) % 7 );
}

rfc_moment
	rfc_dtm_add_days( rfc_moment p_moment, int p_days )
{
	int l_all_days = p_moment / 100;
	l_all_days = rfc_dtm_get_days( l_all_days );
	l_all_days += p_days;
	l_all_days = rfc_dtm_get_moment( l_all_days );
	p_moment = l_all_days * 100 + p_moment % 100;

	return( p_moment );
}

/*#######################################################*/
/*#######################################################*/
