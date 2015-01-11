/*#######################################################*/
/*#######################################################*/
/* windows operations */

/* standard headers */
#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <signal.h>
#include "__gen.h"

#define MIN_CPU_LOAD_TICKS 100

static RFC_THREADDATA *main_thread = NULL;
static unsigned long tlsIndex = 0;

/*#######################################################*/
/*#######################################################*/
/* module handle */
RFC_HND
	rfc_hmodule = ( RFC_HND )NULL;

/* semaphore & event operations */

/* lock semaphore */
int rfc_hnd_semlock( RFC_HND p_hnd ) {
	if( WaitForSingleObject( p_hnd , INFINITE ) != WAIT_OBJECT_0 )
		return( -1 );

	return( 0 );
}

/* release semaphore */
void rfc_hnd_semunlock( RFC_HND p_hnd ) {
	ReleaseSemaphore( p_hnd , 1 , NULL );
}

/* create semaphore */
RFC_HND rfc_hnd_semcreate() {
	return( CreateSemaphore( NULL , 1 , 1 , NULL ) );
}

/* destroy semaphore */
void rfc_hnd_semdestroy( RFC_HND p_hnd ) {
	CancelIoEx( p_hnd , NULL );
	CloseHandle( p_hnd );
}

/* wait to event signaled */
short rfc_hnd_waitevent( RFC_HND p_hnd , int p_timeout_ms ) {
	DWORD waitParam = p_timeout_ms;
	if( p_timeout_ms < 0 )
		waitParam = INFINITE;
	if( WaitForSingleObject( p_hnd , waitParam ) == WAIT_OBJECT_0 )
		return( 1 );

	return( 0 );
}

/* create event */
RFC_HND rfc_hnd_evcreate() {
	return( CreateEvent( NULL , TRUE , FALSE , NULL ) );
}

/* destroy event */
void rfc_hnd_evdestroy( RFC_HND p_hnd ) {
	CancelIoEx( p_hnd , NULL );
	CloseHandle( p_hnd );
}

/* set signaled state to event */
void rfc_hnd_evsignal( RFC_HND p_hnd ) {
	SetEvent( p_hnd );
}

/* clear signaled state of event */
void rfc_hnd_evreset( RFC_HND p_hnd ) {
	ResetEvent( p_hnd );
}

/* create mutex */
RFC_HND		rfc_hnd_mutcreate( void ) {
	return( CreateMutex( NULL , FALSE , NULL ) );
}

/* destroy mutex */
void		rfc_hnd_mutdestroy( RFC_HND p_hnd ) {
	CancelIoEx( p_hnd , NULL );
	CloseHandle( p_hnd );
}

/* lock mutex */
void		rfc_hnd_mutlock( RFC_HND p_hnd ) {
	WaitForSingleObject( p_hnd , INFINITE );
}

/* unlock mutex */
void		rfc_hnd_mutunlock( RFC_HND p_hnd ) {
	ReleaseMutex( p_hnd );
}

/*#######################################################*/
/*#######################################################*/
/* threads */

static void on_exit( int p_sig ) {
	if( main_thread != NULL )
		if( main_thread -> signal_translator != NULL )
			main_thread -> signal_translator( main_thread , p_sig );

	signal( SIGABRT , on_exit );
	signal( SIGINT , on_exit );
	signal( SIGTERM , on_exit );
	signal( SIGFPE , on_exit );
	signal( SIGILL , on_exit );
	signal( SIGSEGV , on_exit );
}

void rfc_thr_initmain( RFC_THREADDATA *p_data ) {
	main_thread = p_data;

	rfc_thr_initstackhandle();
	tlsIndex = TlsAlloc();

	if( p_data -> signal_translator != NULL ) {
		signal( SIGABRT , on_exit );
		signal( SIGINT , on_exit );
		signal( SIGTERM , on_exit );
		signal( SIGFPE , on_exit );
		signal( SIGILL , on_exit );
		signal( SIGSEGV , on_exit );
	}
}

void rfc_thr_setsignals( RFC_THREADDATA *p_data ) {
}

void rfc_thr_initthread( RFC_THREADDATA *rd ) {
	TlsSetValue( tlsIndex , rd );
	rd -> threadId = GetCurrentThreadId();
}

RFC_THREADDATA *rfc_thr_getdata() {
	return( ( RFC_THREADDATA * )TlsGetValue( tlsIndex ) );
}

void rfc_thr_exitthread() {
	// to be no more used
	TlsSetValue( tlsIndex , NULL );
}

/* wait to exit thread */
int rfc_thr_waitexit( RFC_THREAD *p_hnd ) {
	if( WaitForSingleObject( p_hnd -> s_ih , INFINITE ) != WAIT_OBJECT_0 )
		return( -1 );

	return( 0 );
}

/* close thread handle */
void rfc_thr_closehandle( RFC_THREAD *p_hnd ) {
	CloseHandle( p_hnd -> s_ih );
}

/* execution thread */
int rfc_thr_process( RFC_THREAD *p_thread , void *p_arg , RFC_THRFUNC p_action ) {
	p_thread -> s_ih = ( RFC_HND )_beginthreadex( NULL , 0 , p_action , p_arg , 1 , &p_thread -> s_ip );
	if( p_thread -> s_ih == 0 )
		return( -1 );
	return( 0 );
}

/* exit thread */
void rfc_thr_threxit( int p_exitcode ) {
	_endthreadex( p_exitcode );
}

/* sleep current thread */
void rfc_thr_sleep( int p_sec ) {
	Sleep( p_sec * 1000 );
}

int rfc_thr_increment( int *pv ) {
	return( ( int )InterlockedIncrement( ( LPLONG )pv ) );
}

void rfc_thr_register( RFC_THREADDATA *p_data ) {
	p_data -> threadExtId.s_ih = OpenThread( THREAD_ALL_ACCESS , FALSE , GetCurrentThreadId() );
	p_data -> threadExtId.s_ip = 0;
}

unsigned long rfc_thr_getcurrentid() {
	return( GetCurrentThreadId() );
}

void rfc_thr_suspend( RFC_THREAD *p_hnd ) {
	RFC_HND handle = p_hnd -> s_ih;
	SuspendThread( handle );
}

void rfc_thr_resume( RFC_THREAD *p_hnd ) {
	RFC_HND handle = p_hnd -> s_ih;
	ResumeThread( handle );
}

/*#######################################################*/
/*#######################################################*/
/* library management */

RFC_HND rfc_lib_load( const char *p_lib ) {
	return( LoadLibrary( p_lib ) );
}

RFC_PROC rfc_lib_getfunc( RFC_HND p_lib , const char *p_func ) {
	return( ( RFC_PROC )GetProcAddress( ( HINSTANCE )p_lib , p_func ) );
}

void rfc_lib_unload( RFC_HND p_lib ) {
	FreeLibrary( ( HINSTANCE )p_lib );
}

/*#######################################################*/
/*#######################################################*/
/* environment */

void rfc_env_gethostname( char *p_name , int p_size ) {
	GetComputerName( p_name , ( DWORD * )&p_size );
}

/*#######################################################*/
/*#######################################################*/

/* translate from unicode using codepage */
short rfc_str_setcp( char *p_s , const unsigned short *p_v , int p_cp ) {
	int l_len;

	l_len = rfc_wstr_len( p_v );
	if( !WideCharToMultiByte( p_cp , 0 , ( const WCHAR * )p_v , l_len , p_s , l_len , NULL , NULL ) )
		return( 0 );

	p_s[ l_len ] = 0;
	return( 1 );
}

/* translate from ansi using codepage */
short rfc_wstr_setcp( unsigned short *p_s , const char *p_v , int p_cp ) {
	int l_len;

	l_len = strlen( p_v );
	if( !MultiByteToWideChar( p_cp , 0 , p_v , l_len , ( WCHAR * )p_s , l_len ) )
		return( 0 );

	p_s[ l_len ] = 0;
	return( 1 );
}

/*#######################################################*/
/*#######################################################*/
/* high precision time measurement */

static LARGE_INTEGER hpt_start_ticks;
static long hpt_start_clocks;
static LONGLONG hpt_window_ticks;
static LONGLONG hpt_window_clocks;

void rfc_hpt_startadjustment() {
	QueryPerformanceCounter( &hpt_start_ticks );
	hpt_start_clocks = GetTickCount();
}

void rfc_hpt_stopadjustment() {
	LARGE_INTEGER hpt_stop_ticks;
	long htp_stop_clocks;

	QueryPerformanceCounter( &hpt_stop_ticks );
	htp_stop_clocks = GetTickCount();

	hpt_window_ticks = hpt_stop_ticks.QuadPart - hpt_start_ticks.QuadPart;
	hpt_window_clocks = htp_stop_clocks - hpt_start_clocks;
}

void rfc_hpt_setpoint( RFC_INT64 *pv ) {
	QueryPerformanceCounter( ( LARGE_INTEGER * )pv );
}

RFC_INT64 rfc_hpt_timepassed( RFC_INT64 *pv ) {
	LARGE_INTEGER hpt_stop_ticks;
	QueryPerformanceCounter( &hpt_stop_ticks );
	return( hpt_stop_ticks.QuadPart - *pv );
}

RFC_INT64 rfc_hpt_ticks2ms( RFC_INT64 ticks ) {
	return( ( ticks * hpt_window_clocks ) / hpt_window_ticks );
}

RFC_INT64 rfc_hpt_ms2ticks( RFC_INT64 ms ) {
	return( ( ms * hpt_window_ticks ) / hpt_window_clocks );
}

/*#######################################################*/
/*#######################################################*/

float rfc_sys_getcpuload( CPULOADINFO *info ) {
	double timeFree, timeBusy;
	float cpuLoad;

	/* check initial set */
	if( !info -> initialized ) {
		/* one point */
		info -> clocks = ( int )clock();
		if( !GetSystemTimes( ( LPFILETIME )&info -> pidle , ( LPFILETIME )&info -> pkernel , ( LPFILETIME )&info -> puser ) )
			return( -1 );

		/* copy current point to anchor */
		info -> aidle = info -> pidle;
		info -> akernel = info -> pkernel;
		info -> auser = info -> puser;
		info -> aclocks = info -> pclocks;

		/* timeout 100ms */
		Sleep( 100 );

		/* last point */
		info -> clocks = ( int )clock();
		if( !GetSystemTimes( ( LPFILETIME )&info -> idle , ( LPFILETIME )&info -> kernel , ( LPFILETIME )&info -> user ) )
			return( -1 );

		/* mark as initialized */
		info -> initialized = 1;
	}
	else {
		/* set previous */
		info -> pidle = info -> idle;
		info -> pkernel = info -> kernel;
		info -> puser = info -> user;
		info -> pclocks = info -> clocks;

		/* last point */
		info -> clocks = ( int )clock();
		if( !GetSystemTimes( ( LPFILETIME )&info -> idle , ( LPFILETIME )&info -> kernel , ( LPFILETIME )&info -> user ) )
			return( -1 );

		/* check can use new anchor */
		if( ( info -> clocks - info -> pclocks ) > MIN_CPU_LOAD_TICKS ) {
			info -> aidle = info -> pidle;
			info -> akernel = info -> pkernel;
			info -> auser = info -> puser;
			info -> aclocks = info -> pclocks;
		}
	}

	/* calculate cpu load as last vs anchor */
	timeFree = ( double )( info -> idle - info -> aidle );
	timeBusy = ( double )( info -> user - info -> auser + info -> kernel - info -> akernel );

	cpuLoad = 100.f * ( 1.f - ( float )( timeFree / timeBusy ) );
	return( cpuLoad );
}

short rfc_sys_getfileinfo( const char *path , RFC_FILEINFO *info ) {
	WIN32_FIND_DATA findFileData;
	HANDLE hFind;
	RFC_MONEY value;

	hFind = FindFirstFile( path , &findFileData );
	if( hFind == INVALID_HANDLE_VALUE )
		return( 0 );	

	/* form structure */
	info -> timeCreated = *( RFC_INT64 * )&findFileData.ftCreationTime;
	info -> timeUpdated = *( RFC_INT64 * )&findFileData.ftLastWriteTime;

	value.s_part.s_hi = findFileData.nFileSizeHigh;
	value.s_part.s_low = findFileData.nFileSizeLow;
	info -> size = value.s_int64;

	FindClose( hFind );
	return( 1 );
}

