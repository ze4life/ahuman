#include <ah_platform.h>

// #############################################################################
// #############################################################################

SchedulerTask::SchedulerTask( MessagePublisher *p_notifyPublisher ) {
	attachLogger();

	notifyPublisher = p_notifyPublisher;
	intervalSec = 0;
	taskThread = ( RFC_HND )NULL;
	stopEvent = ( RFC_HND )NULL;
	stopSignal = false;
}

SchedulerTask::~SchedulerTask() {
	ASSERTMSG( taskThread == ( RFC_HND )NULL , "thread is running for task name=" + name );
}

void SchedulerTask::setName( String p_name ) {
	name = p_name;
}

void SchedulerTask::setIntervalSec( int nSec ) {
	intervalSec = nSec;
}

void SchedulerTask::setStopSignal() {
	stopSignal = true;
}

void SchedulerTask::start( RFC_HND stopEvent ) {
	ASSERTMSG( taskThread == ( RFC_HND )NULL , "thread is running for task name=" + name );
	ThreadService *ts = ThreadService::getService();
	stopSignal = false;
	taskThread = ts -> runThread( "scheduler." + name , this , ( ObjectThreadFunction )&SchedulerTask::runThreadTask , NULL );
}

void SchedulerTask::stop() {
	if( taskThread == ( RFC_HND )NULL )
		return;

	stopSignal = true;
	ThreadService *ts = ThreadService::getService();
	ts -> waitThreadExited( taskThread );
}

void SchedulerTask::runThreadTask( void *p_arg ) {
	TextMessage *msg = notifyPublisher -> createTextMessage();
	msg -> setProperty( "TASK" , name );
	notifyPublisher -> publish( NULL , msg );
}
