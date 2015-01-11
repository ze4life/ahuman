#include <ah_platform.h>
#include <ah_threads_impl.h>

/*#########################################################################*/
/*#########################################################################*/

#ifdef _WIN32

#include <windows.h>

static void UnhandledExceptionTranslator( unsigned int exceptionCode , struct _EXCEPTION_POINTERS *exceptionInfo ) {
	throw RuntimeException( exceptionCode , 3 , exceptionInfo -> ExceptionRecord -> ExceptionAddress );
}

#else
#endif

ThreadData::ThreadData() {
	memset( &data , 0 , sizeof( RFC_THREADDATA ) );

	object = NULL;
	objectFunction = NULL;
	objectFunctionArg = NULL;
	sleepEvent = rfc_hnd_evcreate();
	stopped = false;

	data.userdata = this;
}

ThreadData::~ThreadData() {
	rfc_hnd_evdestroy( sleepEvent );
}

void ThreadData::stopThread() {
	stopped = true;
	rfc_hnd_evsignal( sleepEvent );
}

bool ThreadData::checkStopped() {
	return( stopped );
}

void ThreadData::setHandleExceptions() {
#ifdef _WIN32
	oldhandler = _set_se_translator( UnhandledExceptionTranslator );
#else
#endif
}
