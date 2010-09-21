#include "../body_impl.h"
#include <windows.h>

// #############################################################################
// #############################################################################

class SensorFileSysWalker : public Object , public Sensor
{
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

	static const int FOCUS_DEPTH_LEVELS = 10;
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

// signals emitted
#define SIGNAL_COMPUTER_NAME "COMPUTERNAME"
#define SIGNAL_DISK_LISTITEM "DISK"
#define SIGNAL_DIR_LISTITEM "DIRECTORYITEM"
#define SIGNAL_FILE_NAME "FILENAME"
#define SIGNAL_FILE_TYPE "FILETYPE"
#define SIGNAL_DISK_NAME "DISKNAME"
#define SIGNAL_DISK_SPACETOTAL "DISKSPACETOTAL"
#define SIGNAL_DISK_SPACEUSED "DISKSPACEUSED"
#define SIGNAL_DISK_SPACEFREE "DISKSPACEFREE"

private:
	AIEngine& engine;
	static const int NINPUTS = 2;
	float *vin;

	static const int SENSOR_WIDTH_CONTROL = 16;
	static const int SENSOR_WIDTH_DATA = 16;
	static const int SENSOR_SEQUENCE_WIDTH = SENSOR_WIDTH_CONTROL + SENSOR_WIDTH_DATA;
	static const int NOUTPUTS = SENSOR_SEQUENCE_WIDTH;
	float *vout;
	RFC_HND thread;
	RFC_HND commandEvent;
	RFC_HND lockHandle;

#define NUMBER_TO_NEURAL( numMin , numMax , value ) ( (value) * 2.f / ( (numMax) - (numMin) ) - 1 )
	HANDLE changeHandle;
	bool continueRunFlag;

public:
	SensorFileSysWalker( MindArea *area ) 
	:	Sensor( "FileSysWalker" , area , NINPUTS , NOUTPUTS ) ,
		engine( AIEngine::getInstance() ) {

		// internal data
		vin = Cortex::getInputs();
		vout = Cortex::getOutputs();
		commandEvent = rfc_hnd_evcreate();
		lockHandle = rfc_hnd_semcreate();
		continueRunFlag = false;

		// ensure variables are initialised
		changeHandle = NULL;
		thread = NULL;

		// autonomous, polling is not required
		Sensor::setPollState( false );
		logger.attach( this );

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
	}

	virtual ~SensorFileSysWalker() {
		rfc_hnd_evdestroy( commandEvent );
		rfc_hnd_semdestroy( lockHandle );
	};
	virtual const char *getClass() { return( "SensorFileSysWalker" ); };

	virtual void startSensor() {
		// start reading thread
		continueRunFlag = true;
		thread = engine.runThread( "SensorFileSysWalker" , this , ( ObjectThreadFunction )&SensorFileSysWalker::runThreadReader , NULL );
	}

	virtual void stopSensor() {
		continueRunFlag = false;
		closeWaitHandle();
		if( thread == NULL )
			return;

		// stop thread
		rfc_hnd_evsignal( commandEvent );
		engine.waitThreadExited( thread );
		thread = NULL;
	}

	// called when inputs updated - i.e. control commands
	virtual void processSensorControl() {
		if( executeSensorControl() ) {
			produceSensorData();
			rfc_hnd_evsignal( commandEvent );
		}
	}

	// returns status - whether sensor data should be generated
	virtual bool executeSensorControl() {
		lock();

		bool res = false;
		try {
			// possible commands are - focus up, down, increase, decrease, changedepth (1-5)
			// neuro-input is [-1,1]
			curFocusCommand = ( FOCUS_COMMAND )( 1 + ( int )( ( ( vin[0] + 1 ) * COMMAND_LAST ) / 2 ) );
			if( curFocusCommand > COMMAND_LAST )
				curFocusCommand = COMMAND_LAST;
			curFocusCommandStrength = ( int )( ( vin[1] + 1 ) * 50 );

			switch( curFocusCommand ) {
				case COMMAND_FOCUS_UP :			
					res = commandFocusUp();
					if( res )
						logger.logDebug( "SensorFileSysWalker::commandFocusUp - new focus area=" + getCurFocusArea() );
					break;
				case COMMAND_FOCUS_DOWN :		
					res = commandFocusDown(); 
					if( res )
						logger.logDebug( "SensorFileSysWalker::commandFocusDown - new focus area=" + getCurFocusArea() );
					break;
				case COMMAND_FOCUS_INCREASE :	
					res = commandFocusIncrease(); 
					if( res )
						logger.logDebug( "SensorFileSysWalker::commandFocusIncrease - new focus area=" + getCurFocusArea() );
					break;
				case COMMAND_FOCUS_DECREASE :	
					res = commandFocusDecrease(); 
					if( res )
						logger.logDebug( "SensorFileSysWalker::commandFocusDecrease - new focus area=" + getCurFocusArea() );
					break;
				case COMMAND_FOCUS_CHANGEDEPTH :	
					res = commandFocusChangeDepth(); 
					if( res )
						logger.logDebug( "SensorFileSysWalker::commandFocusChangeDepth - new focus area=" + getCurFocusArea() );
					break;
			}
		}
		catch( RuntimeException& e ) {
			e.printStack( logger );
		}

		if( res )
			closeWaitHandle();

		unlock();

		return( res );
	}

	virtual void produceSensorData() {
		lock();
		try {
			logger.logInfo( "SensorFileSysWalker: produce sensor data..." );
		
			switch( curFocusType ) {
				case FOCUS_COMPUTER :	sendNewComputerInfo(); break;
				case FOCUS_DISK :		sendNewDiskInfo(); break;
				case FOCUS_DIR :		sendNewDirectoryInfo(); break;
				case FOCUS_FILE :		sendNewFileInfo(); break;
			}
		}
		catch( RuntimeException& e ) {
			e.printStack( logger );
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
		logger.logDebug( "SensorFileSysWalker::sendNewComputerInfo" );
		String name = getComputerName();
		sendSignal( SIGNAL_COMPUTER_NAME , name );

		String disks = getDiskList();
		for( int k = 0; k < disks.length(); k++ ) {
			String disk = disks.getMid( k , 1 ) + ":";
			sendSignal( SIGNAL_DISK_LISTITEM , disk );
		}
	}

	void SensorFileSysWalker::sendNewDiskInfo() {
		logger.logDebug( "SensorFileSysWalker::sendNewDiskInfo" );

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
		logger.logDebug( "SensorFileSysWalker::sendNewDirectoryInfo" );

		// send current directory list
		StringList files;
		getDirList( curDir , files );
		for( int k = 0; k < files.count(); k++ ) {
			String file = files.get( k );
			sendSignal( SIGNAL_DIR_LISTITEM , file );
		}
	}

	void SensorFileSysWalker::sendNewFileInfo() {
		logger.logDebug( "SensorFileSysWalker::sendNewFileInfo" );

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

	bool commandMove( int change ) {
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

	String getCurFocusArea() {
		switch( curFocusType ) {
			case FOCUS_COMPUTER :	return( "computer" ); break;
			case FOCUS_DISK :		return( "disk/" + curDisk ); break;
			case FOCUS_DIR :		return( "dir/" + curDir + "/depth=" + curFocusDepth ); break;
			case FOCUS_FILE :		return( "file/" + curFile ); break;
		}
		return( "" );
	}

	void sendSignal( String type , String value ) {
		logger.logDebug( "sendSignal: type=" + type + ", value=" + value );

		// set type
		int len = type.length();
		ASSERTMSG( len <= SENSOR_WIDTH_CONTROL , "Unexpected" );

		for( int k = 0; k < len; k++ )
			vout[ k ] = NUMBER_TO_NEURAL( 0 , 255 , type[ k ] );
		for( int k = len; k < SENSOR_WIDTH_CONTROL; k++ )
			vout[ k ] = -1;

		// set value by chunks ended with directory delimiter or sensor data width
		char *p = value.getBuffer();
		ASSERTMSG( p != NULL , "Unexpected" );
		while( *p ) {
			// find delimiter
			char *next = NULL;
			char *pn = strchr( p , '\\' );
			if( pn == NULL ) {
				pn = p + strlen( p );
				next = pn;
			}
			else
				next = p + 1;

			// check long name
			if( pn - p > SENSOR_WIDTH_CONTROL ) {
				pn = p + SENSOR_WIDTH_CONTROL;
				next = pn;
			}

			// set chunk item
			int len = pn - p;
			for( int k = 0; k < len; k++ )
				vout[ k ] = NUMBER_TO_NEURAL( 0 , 255 , value[ k ] );
			for( int k = len; k < SENSOR_WIDTH_DATA; k++ )
				vout[ k ] = -1;

			// produce item flow
			Cortex::processOutputsUpdated();
			p = next;
		}
	}

// #############################################################################
// #############################################################################
// helpers

	// lock/unlock
	void lock() {
		rfc_hnd_semlock( lockHandle );
	}

	void unlock() {
		rfc_hnd_semunlock( lockHandle );
	}

	void closeWaitHandle() {
		if( changeHandle != NULL ) {
			stopTracking( changeHandle );
			changeHandle = NULL;
		}
	}

	String getComputerName() {
		char l_name[ 128 ];
		DWORD l_size = sizeof( l_name );
		::GetComputerName( l_name , &l_size );
		return( l_name );
	}

	String getFirstDisk() {
		String disks = getDiskList();
		return( disks.getMid( 0 , 1 ) );
	}

	String getRootDiskDirectory( String disk ) {
		return( disk + ":" );
	}

	String getFirstDirectoryFile( String directory ) {
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

	String getDiskUpDown( String disk , int move ) {
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

	String getDiskList() {
		String disks;
		DWORD mask = ::GetLogicalDrives();
		char letter = 'A';
		for( int bit = 1; bit < 0x7FFFFFF; bit <<= 1 , letter++ )
			if( mask & bit )
				disks += letter;
		return( disks );
	}

	String getFileUpDown( String file , int move ) {
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

	bool isDirectory( String file ) {
		DWORD attrs = GetFileAttributes( file );
		return( ( attrs & FILE_ATTRIBUTE_DIRECTORY )? true : false );
	}

	String getDir( String file ) {
		int index = file.findLast( '\\' );
		ASSERTMSG( index >= 0 , "Unexpected: " + file );

		// directory name does not contain trailing slash
		return( file.getMid( 0 , index ) );
	}

	String getFileOnly( String file ) {
		int index = file.findLast( '\\' );
		ASSERTMSG( index >= 0 , "Unexpected: " + file );

		return( file.getMid( index + 1 ) );
	}

	void getDirList( String dir , StringList& files ) {
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

	String getFileType( String file ) {
		DWORD attrs = ::GetFileAttributes( file );
		if( attrs & FILE_ATTRIBUTE_DIRECTORY )
			return( "dir" );
		if( attrs & FILE_ATTRIBUTE_HIDDEN )
			return( "hidden" );
		return( "normal" );
	}

	void getDiskInfo( String disk , float *diskSpaceTotalGB , float *diskSpaceUsedGB , float *diskSpaceFreeGB ) {
		RFC_INT64 ignore , spaceTotalGB , spaceUsedGB , spaceFreeGB;
		ASSERT( ::GetDiskFreeSpaceEx( disk + ":\\" , ( PULARGE_INTEGER ) &ignore , ( PULARGE_INTEGER )&spaceTotalGB , ( PULARGE_INTEGER )&spaceFreeGB ) );
		spaceUsedGB = spaceTotalGB - spaceFreeGB;
		float v1gb = 1024. * 1024. * 1024.;

		*diskSpaceTotalGB = spaceTotalGB / v1gb;
		*diskSpaceUsedGB = spaceUsedGB / v1gb;
		*diskSpaceFreeGB = spaceFreeGB / v1gb;
	}

	HANDLE startTracking( String path , bool isDir ) {
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

	void continueTracking( HANDLE handle ) {
		logger.logDebug( "continueTracking" );
	}

	void stopTracking( HANDLE handle ) {
		logger.logDebug( "stopTracking..." );
		::CancelIoEx( handle , NULL );
		::CloseHandle( handle );
		logger.logDebug( "stopTracking - done" );
	}

	void readDirChanges( HANDLE handle , void *buf , DWORD bufLength , int depth ) {
		logger.logDebug( "readDirChanges" );

		FILE_NOTIFY_INFORMATION *pe = ( FILE_NOTIFY_INFORMATION * )buf;
		while( true ) {
			// use event
			static const char *actions[5] = { "Added" , "Removed" , "Modified" , "RenamedFrom" , "RenamedTo" };
			if( pe -> Action >= 1 && pe -> Action <= 5 ) {
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

	void waitChangeEventAndExecute() {
		logger.logDebug( "waitChangeEventAndExecute" );

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

	void runThreadReader( void *p_arg ) {
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
			rfc_hnd_waitevent( commandEvent );
			rfc_hnd_evreset( commandEvent );
			return;
		}

		unlock();

		// wait event
		waitChangeEventAndExecute();
	}
};

// #############################################################################
// #############################################################################

Sensor *Sensor::createFileSysWalker( MindArea *area )
{
	SensorFileSysWalker *att = new SensorFileSysWalker( area );
	return( att );
}

