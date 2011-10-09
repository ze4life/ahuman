#include "stdafx.h"

// #############################################################################
// #############################################################################

// signals emitted
#define SIGNAL_COMPUTER_NAME	( neurovt )1
#define SIGNAL_DISK_LISTITEM	( neurovt )2
#define SIGNAL_DIR_LISTITEM		( neurovt )3
#define SIGNAL_FILE_NAME		( neurovt )4
#define SIGNAL_FILE_TYPE		( neurovt )5
#define SIGNAL_DISK_NAME		( neurovt )6
#define SIGNAL_DISK_SPACETOTAL	( neurovt )7
#define SIGNAL_DISK_SPACEUSED	( neurovt )8
#define SIGNAL_DISK_SPACEFREE	( neurovt )9

#define FILE_NOTIFY_ACTION_ADDED		( neurovt )11
#define FILE_NOTIFY_ACTION_REMOVED		( neurovt )12
#define FILE_NOTIFY_ACTION_MODIFIED		( neurovt )13
#define FILE_NOTIFY_ACTION_RENAMEDFROM	( neurovt )14
#define FILE_NOTIFY_ACTION_RENAMEDTO	( neurovt )15

#define NUMBER_TO_NEURAL( numMin , numMax , value ) ( ( (value) - (numMin) ) * 2.f / ( (numMax) - (numMin) ) - 1 )
#define NEURAL_TO_NUMBER( numMin , numMax , value ) ( (numMin) + ( (value) + 1 ) * ( (numMax) - (numMin) ) / 2.f )

static const int MAX_FILE_NOTIFY_ACTIONS = 5;
static const int FOCUS_DEPTH_LEVELS = 10;
static const int SENSOR_WIDTH_CONTROL = 2;
static const int SENSOR_WIDTH_DATA = 16;

// #############################################################################
// #############################################################################

class SensorFileSysWalker : public MindSensor {
private:
	// control state: capture area
	String curDisk;
	String curDir;
	String curFile;

	// control state: capture resolution
	enum {
		FOCUS_COMPUTER = 0 ,
		FOCUS_DISK = 1 ,
		FOCUS_DIR = 2 ,
		FOCUS_FILE = 3
	} curFocusType;

	int curFocusDepth;

	// inputs
	// command to be executed
	typedef enum {
		COMMAND_FOCUS_NOCMD = 0 ,

		COMMAND_FOCUS_UP = 1 ,
		COMMAND_FOCUS_DOWN = 2 ,
		COMMAND_FOCUS_INCREASE = 3 ,
		COMMAND_FOCUS_DECREASE = 4 ,
		COMMAND_FOCUS_CHANGEDEPTH = 5 ,

		COMMAND_LAST = 5
	} FOCUS_COMMAND;

	FOCUS_COMMAND curFocusCommand;
	// power of command - 1-100
	int curFocusCommandStrength;

	//		control state: capture resolution
	//		deliver captured properties from external world and transfer to sensordata IO channel according to control state
	//		deriver exposed properties from control state and deliver them to external world

	neurovt actions[ MAX_FILE_NOTIFY_ACTIONS ];

private:
	neurovt *vin;

	neurovt *vout;
	RFC_HND thread;
	RFC_HND commandEvent;
	RFC_HND lockHandle;

	HANDLE changeHandle;
	bool continueRunFlag;

public:
	SensorFileSysWalker( SensorArea *area );
	virtual ~SensorFileSysWalker();
	virtual const char *getClass() { return( "SensorFileSysWalker" ); };

public:
	// sensor lifecycle
	virtual void startSensor();
	virtual void stopSensor();
	virtual void processSensorControl();
	virtual void produceSensorData();
	virtual void pollSensor() {};

private:
	bool executeSensorControl();
	void prepareWaitComputerInfo();
	void prepareWaitDiskInfo();
	void prepareWaitDirectoryInfo();
	void prepareWaitFileInfo();
	void sendNewComputerInfo();
	void sendNewDiskInfo();
	void sendNewDirectoryInfo();
	void sendNewFileInfo();
	bool commandFocusUp();
	bool commandFocusDown();
	bool commandMove( int change );
	bool commandFocusIncrease();
	bool commandFocusDecrease();
	bool commandFocusChangeDepth();
	String getCurFocusArea();
	void sendSignal( neurovt type , String value );

	String getComputerName();
	String getFirstDisk();
	String getRootDiskDirectory( String disk );
	String getFirstDirectoryFile( String directory );
	String getDiskUpDown( String disk , int move );
	String getDiskList();
	String getFileUpDown( String file , int move );

	void lock();
	void unlock();
	void closeWaitHandle();

	bool isDirectory( String file );
	String getDir( String file );
	String getFileOnly( String file );
	void getDirList( String dir , StringList& files );
	String getFileType( String file );
	void getDiskInfo( String disk , float *diskSpaceTotalGB , float *diskSpaceUsedGB , float *diskSpaceFreeGB );
	HANDLE startTracking( String path , bool isDir );
	void continueTracking( HANDLE handle );
	void stopTracking( HANDLE handle );
	void readDirChanges( HANDLE handle , void *buf , DWORD bufLength , int depth );
	void waitChangeEventAndExecute();

	void runThreadReader( void *p_arg );
	void continueRead();
};

// #############################################################################
// #############################################################################

SensorFileSysWalker::SensorFileSysWalker( SensorArea *p_area )
:	MindSensor( p_area ) {
	attachLogger();

	actions[0] = FILE_NOTIFY_ACTION_ADDED; 
	actions[1] = FILE_NOTIFY_ACTION_REMOVED; 
	actions[2] = FILE_NOTIFY_ACTION_MODIFIED; 
	actions[3] = FILE_NOTIFY_ACTION_RENAMEDFROM; 
	actions[4] = FILE_NOTIFY_ACTION_RENAMEDTO;

	// internal data
	NeuroVector *nv = MindSensor::createSensoryData( SENSOR_WIDTH_DATA , 1 );
	vout = nv -> getRawData();

	nv = MindSensor::createSensoryControlState( SENSOR_WIDTH_CONTROL , 1 );
	vin = nv -> getRawData();

	// synchnonization
	commandEvent = rfc_hnd_evcreate();
	lockHandle = rfc_hnd_semcreate();
	continueRunFlag = false;

	// ensure variables are initialised
	changeHandle = NULL;
	thread = NULL;

	// autonomous, polling is not required
	MindSensor::setPollState( false );

	// initialise inputs
	curFocusCommand = COMMAND_FOCUS_NOCMD;
	curFocusCommandStrength = 0;

	// control data: capture area
	curDisk.clear();
	curDir.clear();
	curFile.clear();

	// control data: capture resolution
	curFocusType = FOCUS_COMPUTER;
	curFocusDepth = -1;

	// start capture for first dir tree
	curDisk = getFirstDisk();
	curDir = getRootDiskDirectory( curDisk );
	curFocusType = FOCUS_DIR;
}

SensorFileSysWalker::~SensorFileSysWalker() {
	rfc_hnd_evdestroy( commandEvent );
	rfc_hnd_semdestroy( lockHandle );
};

void SensorFileSysWalker::startSensor() {
	// start reading thread
	continueRunFlag = true;
	ThreadService *ts = ThreadService::getService();
	thread = ts -> runThread( "SensorFileSysWalker" , this , ( ObjectThreadFunction )&SensorFileSysWalker::runThreadReader , NULL );
}

void SensorFileSysWalker::stopSensor() {
	continueRunFlag = false;
	closeWaitHandle();
	if( thread == NULL )
		return;

	// stop thread
	rfc_hnd_evsignal( commandEvent );
	ThreadService *ts = ThreadService::getService();
	ts -> waitThreadExited( thread );
	thread = NULL;
}

// called when inputs updated - i.e. control commands
void SensorFileSysWalker::processSensorControl() {
	if( executeSensorControl() ) {
		produceSensorData();
		rfc_hnd_evsignal( commandEvent );
	}
}

// returns status - whether sensor data should be generated
bool SensorFileSysWalker::executeSensorControl() {
	lock();

	bool res = false;
	try {
		// possible commands are - focus up, down, increase, decrease, changedepth (1-5)
		// neuro-input is [-1,1]
		curFocusCommand = ( FOCUS_COMMAND )( int )NEURAL_TO_NUMBER( 0 , COMMAND_LAST , vin[0] );
		if( curFocusCommand > COMMAND_LAST )
			curFocusCommand = COMMAND_LAST;
		curFocusCommandStrength = ( int )NEURAL_TO_NUMBER( 0 , 100 , vin[1] );

		switch( curFocusCommand ) {
			case COMMAND_FOCUS_UP :			
				res = commandFocusUp();
				if( res )
					logger.logDebug( "executeSensorControl: commandFocusUp - new focus area=" + getCurFocusArea() );
				break;
			case COMMAND_FOCUS_DOWN :		
				res = commandFocusDown(); 
				if( res )
					logger.logDebug( "executeSensorControl: commandFocusDown - new focus area=" + getCurFocusArea() );
				break;
			case COMMAND_FOCUS_INCREASE :	
				res = commandFocusIncrease(); 
				if( res )
					logger.logDebug( "executeSensorControl: commandFocusIncrease - new focus area=" + getCurFocusArea() );
				break;
			case COMMAND_FOCUS_DECREASE :	
				res = commandFocusDecrease(); 
				if( res )
					logger.logDebug( "executeSensorControl: commandFocusDecrease - new focus area=" + getCurFocusArea() );
				break;
			case COMMAND_FOCUS_CHANGEDEPTH :	
				res = commandFocusChangeDepth(); 
				if( res )
					logger.logDebug( "executeSensorControl: commandFocusChangeDepth - new focus area=" + getCurFocusArea() );
				break;
		}
	}
	catch( RuntimeException& e ) {
		logger.printStack( e );
	}

	if( res )
		closeWaitHandle();

	unlock();

	return( res );
}

void SensorFileSysWalker::produceSensorData() {
	lock();
	try {
		logger.logInfo( "produceSensorData: produce sensor data..." );
		
		switch( curFocusType ) {
			case FOCUS_COMPUTER :	sendNewComputerInfo(); break;
			case FOCUS_DISK :		sendNewDiskInfo(); break;
			case FOCUS_DIR :		sendNewDirectoryInfo(); break;
			case FOCUS_FILE :		sendNewFileInfo(); break;
		}
	}
	catch( RuntimeException& e ) {
		logger.printStack( e );
	}
	unlock();
}

// #############################################################################
// #############################################################################
// command and sensor data details

// prepare wait handle
void SensorFileSysWalker::prepareWaitComputerInfo() {
	closeWaitHandle();
}

void SensorFileSysWalker::prepareWaitDiskInfo() {
	closeWaitHandle();
}

void SensorFileSysWalker::prepareWaitDirectoryInfo() {
	if( changeHandle == NULL )
		changeHandle = startTracking( curDir + "\\" , true );
	else
		continueTracking( changeHandle );
}

void SensorFileSysWalker::prepareWaitFileInfo() {
	if( changeHandle == NULL )
		changeHandle = startTracking( curFile , false );
	else
		continueTracking( changeHandle );
}

// send initial information - as focus changed
void SensorFileSysWalker::sendNewComputerInfo() {
	logger.logDebug( "sendNewComputerInfo: execute" );
	String name = getComputerName();
	sendSignal( SIGNAL_COMPUTER_NAME , name );

	String disks = getDiskList();
	for( int k = 0; k < disks.length(); k++ ) {
		String disk = disks.getMid( k , 1 ) + ":";
		sendSignal( SIGNAL_DISK_LISTITEM , disk );
	}
}

void SensorFileSysWalker::sendNewDiskInfo() {
	logger.logDebug( "sendNewDiskInfo: execute" );

	// send disk information
	float diskSpaceTotalGB;
	float diskSpaceUsedGB;
	float diskSpaceFreeGB;

	getDiskInfo( curDisk , &diskSpaceTotalGB , &diskSpaceUsedGB , &diskSpaceFreeGB );
	sendSignal( SIGNAL_DISK_NAME , curDisk );
	sendSignal( SIGNAL_DISK_SPACETOTAL , String("") + diskSpaceTotalGB + "GB" );
	sendSignal( SIGNAL_DISK_SPACEUSED , String("") + diskSpaceUsedGB + "GB" );
	sendSignal( SIGNAL_DISK_SPACEFREE , String("") + diskSpaceFreeGB + "GB" );
}

void SensorFileSysWalker::sendNewDirectoryInfo() {
	logger.logDebug( "sendNewDirectoryInfo: execute" );

	// send current directory list
	StringList files;
	getDirList( curDir , files );
	for( int k = 0; k < files.count(); k++ ) {
		String file = files.get( k );
		sendSignal( SIGNAL_DIR_LISTITEM , file );
	}
}

void SensorFileSysWalker::sendNewFileInfo() {
	logger.logDebug( "sendNewFileInfo: execute" );

	String file = getFileOnly( curFile );
	sendSignal( SIGNAL_FILE_NAME , file );
	sendSignal( SIGNAL_FILE_TYPE , getFileType( curFile ) );
}

// send initial information - as focus changed
bool SensorFileSysWalker::commandFocusUp() {
	if( curFocusCommandStrength == 0 )
		curFocusCommandStrength = 1;
	return( commandMove( -curFocusCommandStrength ) );
}

bool SensorFileSysWalker::commandFocusDown() {
	if( curFocusCommandStrength == 0 )
		curFocusCommandStrength = 1;
	return( commandMove( curFocusCommandStrength ) );
}

bool SensorFileSysWalker::commandMove( int change ) {
	String item;
	switch( curFocusType ) {
		case FOCUS_DISK :
			item = getDiskUpDown( curDisk , change );
			if( item.equals( curDisk ) )
				return( false );
			curDisk = item;
			return( true );
		case FOCUS_DIR :
			if( curDir.equals( curDisk + ":" ) )
				return( false );
			item = getFileUpDown( curDir , change );
			if( item.equals( curDir ) )
				return( false );
			curDir = item;
			return( true );
		case FOCUS_FILE :
			item = getFileUpDown( curFile , change );
			if( item.equals( curFile ) )
				return( false );
			curFile = item;
			return( true );
	}
	return( false );
}

bool SensorFileSysWalker::commandFocusIncrease() {
	switch( curFocusType ) {
		case FOCUS_COMPUTER :
			switch( curFocusCommandStrength / 35 ) {
				case 0 :
					curDisk = getFirstDisk();
					curFocusType = FOCUS_DISK;
					break;
				case 1 :
					curDisk = getFirstDisk();
					curDir = getRootDiskDirectory( curDisk );
					curFocusType = FOCUS_DIR;
					break;
				case 2 :
					curDisk = getFirstDisk();
					curDir = getRootDiskDirectory( curDisk );
					curFile = getFirstDirectoryFile( curDir );
					if( curFile.isEmpty() )
						curFocusType = FOCUS_DIR;
					else
						curFocusType = FOCUS_FILE;
					break;
			}
			return( true );
		case FOCUS_DISK :
			switch( curFocusCommandStrength / 50 ) {
				case 0 :
					curDir = getRootDiskDirectory( curDisk );
					curFocusType = FOCUS_DIR;
					break;
				case 1 :
					curDir = getRootDiskDirectory( curDisk );
					curFile = getFirstDirectoryFile( curDir );
					if( curFile.isEmpty() )
						curFocusType = FOCUS_DIR;
					else
						curFocusType = FOCUS_FILE;
					break;
			}
			return( true );
		case FOCUS_DIR :
			curFile = getFirstDirectoryFile( curDir );
			if( curFile.isEmpty() )
				return( false );

			curFocusType = FOCUS_FILE;
			return( true );
		case FOCUS_FILE :
			if( !isDirectory( curFile ) )
				return( false );
			curDir = curFile;
			curFocusType = FOCUS_DIR;
			return( true );
	}
	return( false );
}

bool SensorFileSysWalker::commandFocusDecrease() {
	switch( curFocusType ) {
		case FOCUS_DISK :
			curFocusType = FOCUS_COMPUTER;
			curDisk.clear();
			return( true );
		case FOCUS_DIR :
			if( curFocusCommandStrength / 50 ) {
				curFocusType = FOCUS_COMPUTER;
				curDisk.clear();
				curDir.clear();
				return( true );
			}

			curFocusType = FOCUS_DISK;
			curDir.clear();
			return( true );
		case FOCUS_FILE :
			switch( curFocusCommandStrength / 35 ) {
				case 0 : 
					curFocusType = FOCUS_DIR; 
					curFile.clear();
					return( true );
				case 1 : 
					curFocusType = FOCUS_DISK; 
					curDir.clear();
					curFile.clear();
					return( true );
				case 2 : 
					curFocusType = FOCUS_COMPUTER; 
					curDisk.clear();
					curDir.clear();
					curFile.clear();
					return( true );
			}
			break;
	}
	return( false );
}

bool SensorFileSysWalker::commandFocusChangeDepth() {
	int newFocusDepth = curFocusCommandStrength / FOCUS_DEPTH_LEVELS;
	if( newFocusDepth == ( FOCUS_DEPTH_LEVELS - 1 ) )
		newFocusDepth = -1;

	if( newFocusDepth == curFocusDepth )
		return( false );

	curFocusDepth = newFocusDepth;
	return( true );
}

String SensorFileSysWalker::getCurFocusArea() {
	switch( curFocusType ) {
		case FOCUS_COMPUTER :	return( "computer" ); break;
		case FOCUS_DISK :		return( "disk/" + curDisk ); break;
		case FOCUS_DIR :		return( "dir/" + curDir + "/depth=" + curFocusDepth ); break;
		case FOCUS_FILE :		return( "file/" + curFile ); break;
	}
	return( "" );
}

void SensorFileSysWalker::sendSignal( neurovt type , String value ) {
	// set value by chunks split by directory delimiter
	char *p = value.getBuffer();
	ASSERTMSG( p != NULL , "Unexpected" );
	int nSent = 0;
	while( *p ) {
		// set type
		vout[ 0 ] = type;

		// find delimiter
		char *next = NULL;
		char *pn = strchr( p , '\\' );
		if( pn == NULL ) {
			pn = p + strlen( p );
			next = pn;
		}
		else
			next = pn + 1;

		// check long name
		int spaceSize = SENSOR_WIDTH_DATA - 1;
		if( pn - p > spaceSize ) {
			pn = p + spaceSize;
			next = pn;
		}

		// set chunk item
		int len = pn - p;
		for( int k = 0; k < len; k++ )
			vout[ k + 1 ] = NUMBER_TO_NEURAL( 0 , 255 , p[ k ] );
		for( int k = len + 1; k < SENSOR_WIDTH_DATA; k++ )
			vout[ k ] = 0;

		// produce item flow
		// logger.logDebug( String( "sendSignal: processSensorData - " ) + String( p , next - p ) );
		MindSensor::processSensorData();
		nSent++;
		p = next;
	}

	logger.logDebug( String( "sendSignal: type=" ) + type + ", nSent=" + nSent +", value=" + value );
}

// #############################################################################
// #############################################################################
// helpers

// lock/unlock
void SensorFileSysWalker::lock() {
	rfc_hnd_semlock( lockHandle );
}

void SensorFileSysWalker::unlock() {
	rfc_hnd_semunlock( lockHandle );
}

void SensorFileSysWalker::closeWaitHandle() {
	if( changeHandle != NULL ) {
		HANDLE h = changeHandle;
		changeHandle = NULL;
		stopTracking( h );
	}
}

String SensorFileSysWalker::getComputerName() {
	char l_name[ 128 ];
	DWORD l_size = sizeof( l_name );
	::GetComputerName( l_name , &l_size );
	return( l_name );
}

String SensorFileSysWalker::getFirstDisk() {
	String disks = getDiskList();
	return( disks.getMid( 0 , 1 ) );
}

String SensorFileSysWalker::getRootDiskDirectory( String disk ) {
	return( disk + ":" );
}

String SensorFileSysWalker::getFirstDirectoryFile( String directory ) {
	// read files
	WIN32_FIND_DATA findFileData;
	BOOL findNext = TRUE;
	HANDLE hFind = ::FindFirstFile( directory + "\\*" , &findFileData );
	if( hFind == INVALID_HANDLE_VALUE )
		return( "" );

	for( ; hFind != INVALID_HANDLE_VALUE && findNext; findNext = ::FindNextFileA( hFind , &findFileData ) ) {
		String item = findFileData.cFileName;

		// ignore special current and parent dirs
		if( item.equals( "." ) || item.equals( ".." ) )
			continue;

		break;
	}
	::FindClose( hFind );

	String resFile = findFileData.cFileName;
	return( directory + "\\" + resFile );
}

String SensorFileSysWalker::getDiskUpDown( String disk , int move ) {
	ASSERTMSG( move != 0 , "Unexpected" );
	String disks = getDiskList();

	int index = disks.find( disk );
	ASSERTMSG( index >= 0 , "Unexpected: " + disk );

	int indexMove = ( move > 0 )? ( ( disks.length() - index ) * move ) / 100 : ( index * move ) / 100;

	// assure at least move by 1
	if( indexMove == 0 )
		indexMove = ( move > 0 )? 1 : -1;

	index += indexMove;
	if( index < 0 )
		index = 0;
	else
	if( index >= disks.length() )
		index = disks.length() - 1;

	return( disks.getMid( index , 1 ) );
}

String SensorFileSysWalker::getDiskList() {
	String disks;
	DWORD mask = ::GetLogicalDrives();
	char letter = 'A';
	for( int bit = 1; bit < 0x7FFFFFF; bit <<= 1 , letter++ )
		if( mask & bit )
			disks += letter;
	return( disks );
}

String SensorFileSysWalker::getFileUpDown( String file , int move ) {
	ASSERTMSG( move != 0 , "Unexpected" );
	String dir = getDir( file );
	StringList files;

	// read directory
	getDirList( dir , files );

	// find current index
	String fileOnly = getFileOnly( file );
	int index = files.find( fileOnly );
	ASSERTMSG( index >= 0 , "Unexpected: " + file );

	int indexMove = ( move > 0 )? ( ( files.count() - index ) * move ) / 100 : ( index * move ) / 100;

	// assure at least move by 1
	if( indexMove == 0 )
		indexMove = ( move > 0 )? 1 : -1;

	index += indexMove;
	if( index < 0 )
		index = 0;
	else
	if( index >= files.count() )
		index = files.count() - 1;

	String fileNew = dir + "\\" + files.get( index );
	return( fileNew );
}

bool SensorFileSysWalker::isDirectory( String file ) {
	DWORD attrs = GetFileAttributes( file );
	return( ( attrs & FILE_ATTRIBUTE_DIRECTORY )? true : false );
}

String SensorFileSysWalker::getDir( String file ) {
	int index = file.findLast( '\\' );
	ASSERTMSG( index >= 0 , "Unexpected: " + file );

	// directory name does not contain trailing slash
	return( file.getMid( 0 , index ) );
}

String SensorFileSysWalker::getFileOnly( String file ) {
	int index = file.findLast( '\\' );
	ASSERTMSG( index >= 0 , "Unexpected: " + file );

	return( file.getMid( index + 1 ) );
}

void SensorFileSysWalker::getDirList( String dir , StringList& files ) {
	String findName = dir + "\\*";

	// read files
	WIN32_FIND_DATA findFileData;
	BOOL findNext = TRUE;
	HANDLE hFind = ::FindFirstFile( findName , &findFileData );
	for( ; hFind != INVALID_HANDLE_VALUE && findNext; findNext = ::FindNextFileA( hFind , &findFileData ) ) {
		String item = findFileData.cFileName;

		// ignore specifal current and parent dirs
		if( item.equals( "." ) || item.equals( ".." ) )
			continue;

		files.add( item );
	}
	if( hFind != INVALID_HANDLE_VALUE )
		::FindClose( hFind );

	// sort
	files.sort();
}

String SensorFileSysWalker::getFileType( String file ) {
	DWORD attrs = ::GetFileAttributes( file );
	if( attrs & FILE_ATTRIBUTE_DIRECTORY )
		return( "dir" );
	if( attrs & FILE_ATTRIBUTE_HIDDEN )
		return( "hidden" );
	return( "normal" );
}

void SensorFileSysWalker::getDiskInfo( String disk , float *diskSpaceTotalGB , float *diskSpaceUsedGB , float *diskSpaceFreeGB ) {
	RFC_INT64 ignore , spaceTotalGB , spaceUsedGB , spaceFreeGB;
	ASSERT( ::GetDiskFreeSpaceEx( disk + ":\\" , ( PULARGE_INTEGER ) &ignore , ( PULARGE_INTEGER )&spaceTotalGB , ( PULARGE_INTEGER )&spaceFreeGB ) );
	spaceUsedGB = spaceTotalGB - spaceFreeGB;
	float v1gb = 1024. * 1024. * 1024.;

	*diskSpaceTotalGB = spaceTotalGB / v1gb;
	*diskSpaceUsedGB = spaceUsedGB / v1gb;
	*diskSpaceFreeGB = spaceFreeGB / v1gb;
}

HANDLE SensorFileSysWalker::startTracking( String path , bool isDir ) {
	logger.logDebug( "startTracking: " + path );

	String dir = path;
	if( !isDir )
		dir = getDir( path );

	HANDLE hDir = ::CreateFile( 
		dir , /* pointer to the directory name */
		FILE_LIST_DIRECTORY,                /* access (read-write) mode */
		FILE_SHARE_READ|FILE_SHARE_DELETE,  /* share mode */
		NULL, /* security descriptor */
		OPEN_EXISTING, /* how to create */
		FILE_FLAG_BACKUP_SEMANTICS, /* file attributes */
		NULL /* file with attributes to copy */
	);

	return( hDir );
}

void SensorFileSysWalker::continueTracking( HANDLE handle ) {
	logger.logDebug( "continueTracking: execute" );
}

void SensorFileSysWalker::stopTracking( HANDLE handle ) {
	logger.logDebug( "stopTracking: ..." );
	::CancelIoEx( handle , NULL );
	::CloseHandle( handle );
	logger.logDebug( "stopTracking: - done" );
}

void SensorFileSysWalker::readDirChanges( HANDLE handle , void *buf , DWORD bufLength , int depth ) {
	logger.logDebug( "readDirChanges: execute" );

	FILE_NOTIFY_INFORMATION *pe = ( FILE_NOTIFY_INFORMATION * )buf;
	while( true ) {
		// use event
		if( pe -> Action >= 1 && pe -> Action <= MAX_FILE_NOTIFY_ACTIONS ) {
			// convert widechar to ansi
			char name[ 1024 ];
			sprintf( name , "%S" , pe -> FileName );

			// verify depth filter
			if( depth >= 0 ) {
				char *p = name;
				int n = 0;
				while( *p )
					if( *p++ == '\\' )
						n++;

				if( n > depth )
					continue;
			}

			// send change event as signal
			sendSignal( actions[ pe -> Action - 1 ] , name );
		}

		// go to next record
		if( !pe -> NextEntryOffset )
			break;

		pe = ( FILE_NOTIFY_INFORMATION * )( ( ( char * )pe ) + pe -> NextEntryOffset );
	}
}

void SensorFileSysWalker::waitChangeEventAndExecute() {
	logger.logDebug( "waitChangeEventAndExecute: execute" );

	// read changes
	DWORD bytesRead = 0;
	DWORD buf[ 1024 ];
	BOOL res = ::ReadDirectoryChangesW( changeHandle , buf , sizeof( buf ) , TRUE , FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_DIR_NAME , &bytesRead , NULL , NULL );
	if( res == FALSE || bytesRead <= 0 )
		return;

	// check wakeup occurred because of thread stop
	if( !continueRunFlag )
		return;

	// real event - process it
	lock();
	readDirChanges( changeHandle , buf , sizeof( buf ) , curFocusDepth );
	unlock();
}

// #############################################################################
// #############################################################################
// reading thread

void SensorFileSysWalker::runThreadReader( void *p_arg ) {
	// produce sensor output - first time
	produceSensorData();

	// read in cycle
	while( continueRunFlag ) {
		// wait event or interrupt
		continueRead();
	}

	// cleanup
	closeWaitHandle();
}

void SensorFileSysWalker::continueRead() {
	// after read event - prepare waiter
	lock();
	switch( curFocusType ) {
		case FOCUS_COMPUTER :	prepareWaitComputerInfo(); break;
		case FOCUS_DISK :		prepareWaitDiskInfo(); break;
		case FOCUS_DIR :		prepareWaitDirectoryInfo(); break;
		case FOCUS_FILE :		prepareWaitFileInfo(); break;
	}

	if( changeHandle == NULL ) {
		// wait command event
		unlock();
		rfc_hnd_waitevent( commandEvent , -1 );
		rfc_hnd_evreset( commandEvent );
		return;
	}

	unlock();

	// wait event
	waitChangeEventAndExecute();
}

// #############################################################################
// #############################################################################

MindSensor *AWeeTarget::createFileSysWalker( SensorArea *area ) {
	return( new SensorFileSysWalker( area ) );
}

