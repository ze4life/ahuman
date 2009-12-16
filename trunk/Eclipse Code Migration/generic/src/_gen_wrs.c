/*#######################################################*/
/*#######################################################*/
/* windows operations */

/* standard headers */
#include <windows.h>

#include <__gen.h>

/*#######################################################*/
/*#######################################################*/
/* library resources */

/* accelerator resource */
RFC_HND
	rfc_res_accel( RFC_HND p_inst , const char *p_name )
{
	return( LoadAccelerators( p_inst , p_name ) );
}

/* accelerator resource */
RFC_HND
	rfc_dlp_res_accel( rfc_dllpool *p_dlp , int p_lib , const char *p_name )
{
	rfc_lib_info *l_lib;

	if( p_lib < 0 || 
		p_lib >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( NULL );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_lib );
	if( l_lib == NULL )
		return( NULL );

	if( l_lib -> s_lib == NULL )
		return( NULL );

	return( LoadAccelerators( l_lib -> s_lib , p_name ) );
}

/* image resource (IMAGE_BITMAP, IMAGE_CURSOR, IMAGE_ICON) */
RFC_HND
	rfc_res_image( RFC_HND p_inst , 
		const char *p_name , 
		UINT p_type ,
		int p_cx ,
		int p_cy ,
		UINT p_load )
{
	return( LoadImage( p_inst , p_name , p_type , p_cx , p_cy , p_load ) );
}

/* image resource (IMAGE_BITMAP, IMAGE_CURSOR, IMAGE_ICON) */
RFC_HND
	rfc_dlp_res_image( rfc_dllpool *p_dlp , int p_lib , 
		const char *p_name , 
		UINT p_type ,
		int p_cx ,
		int p_cy ,
		UINT p_load )
{
	rfc_lib_info *l_lib;

	if( p_lib < 0 || 
		p_lib >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( NULL );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_lib );
	if( l_lib == NULL )
		return( NULL );

	if( l_lib -> s_lib == NULL )
		return( NULL );

	return( LoadImage( l_lib -> s_lib , p_name , p_type , p_cx , p_cy , p_load ) );
}

/* menu resource */
RFC_HND
	rfc_res_menu( RFC_HND p_inst , const char *p_name )
{
	return( LoadMenu( p_inst , p_name ) );
}

/* menu resource */
RFC_HND
	rfc_dlp_res_menu( rfc_dllpool *p_dlp , int p_lib , const char *p_name )
{
	rfc_lib_info *l_lib;

	if( p_lib < 0 || 
		p_lib >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( NULL );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_lib );
	if( l_lib == NULL )
		return( NULL );

	if( l_lib -> s_lib == NULL )
		return( NULL );

	return( LoadMenu( l_lib -> s_lib , p_name ) );
}

/* string resource */
const char *
	rfc_res_string( RFC_HND p_inst , int p_id )
{
	static char l_buf[ 1024 + 1 ];
	int l_len;

	*l_buf = 0;

	l_len = LoadString( p_inst , p_id , l_buf , 1024 );
	l_buf[ l_len ] = 0;

	return( l_buf );
}

/* string resource */
const char *
	rfc_dlp_res_string( rfc_dllpool *p_dlp , int p_lib , int p_id )
{
	static char l_buf[ 1024 + 1 ];
	rfc_lib_info *l_lib;
	int l_len;

	*l_buf = 0;

	if( p_lib < 0 || 
		p_lib >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( NULL );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_lib );
	if( l_lib == NULL )
		return( NULL );

	if( l_lib -> s_lib == NULL )
		return( NULL );

	l_len = LoadString( l_lib -> s_lib , p_id , l_buf , 1024 );
	l_buf[ l_len ] = 0;

	return( l_buf );
}

/* dialog resource */
RFC_HND
	rfc_res_dialog( RFC_HND p_inst , const char *p_name )
{
	HRSRC l_res;

	l_res = FindResource( p_inst , p_name , RT_DIALOG );
	if( l_res == NULL )
		return( NULL );

	return( LoadResource( p_inst , l_res ) );
}

/* dialog resource */
RFC_HND
	rfc_dlp_res_dialog( rfc_dllpool *p_dlp , int p_lib , const char *p_name )
{
	rfc_lib_info *l_lib;
	HRSRC l_res;

	if( p_lib < 0 || 
		p_lib >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( NULL );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_lib );
	if( l_lib == NULL )
		return( NULL );

	if( l_lib -> s_lib == NULL )
		return( NULL );

	l_res = FindResource( l_lib -> s_lib , p_name , RT_DIALOG );
	if( l_res == NULL )
		return( NULL );

	return( LoadResource( l_lib -> s_lib , l_res ) );
}

/* custom resource */
RFC_HND
	rfc_res_custom( RFC_HND p_inst , const char *p_name , const char *p_type )
{
	HRSRC l_res;

	l_res = FindResource( p_inst , p_name , p_type );
	if( l_res == NULL )
		return( NULL );

	return( LoadResource( p_inst , l_res ) );
}

/*#######################################################*/
/*#######################################################*/
/* window function */

void
	rfc_wnd_enable( RFC_HND p_wnd , short p_enable )
{
	EnableWindow( ( HWND ) p_wnd , p_enable );
}

short
	rfc_wnd_isenabled( RFC_HND p_wnd )
{
	return IsWindowEnabled( ( HWND )p_wnd );
}

void
	rfc_wnd_show( RFC_HND p_wnd , short p_show )
{
	ShowWindow( ( HWND )p_wnd , p_show ? SW_SHOW : SW_HIDE );
}

short
	rfc_wnd_isshow( RFC_HND p_wnd )
{
	return IsWindowVisible( ( HWND )p_wnd );
}

void
	rfc_wnd_focus( RFC_HND p_wnd )
{
	SetFocus( ( HWND )p_wnd );
}

/*#######################################################*/
/*#######################################################*/