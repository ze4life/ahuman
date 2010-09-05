#include "../body_impl.h"
#include <windows.h>

// #############################################################################
// #############################################################################

class SensorFileSysWalker : public Object , public Sensor
{
	// every sensor should implement:
	//		control state: capture area
	String curDisk;
	String curDir;
	String curFile;
	enum {
		FOCUS_COMPUTER = 0 ,
		FOCUS_DISK = 1 ,
		FOCUS_DIR = 2 ,
		FOCUS_FILE = 3
	} curFocusType;

	typedef enum {
		COMMAND_FOCUS_NOCMD = 0 ,
		COMMAND_FOCUS_UP = 1 ,
		COMMAND_FOCUS_DOWN = 2 ,
		COMMAND_FOCUS_INCREASE = 3 ,
		COMMAND_FOCUS_DECREASE = 4 ,
		COMMAND_LAST = 4
	} FOCUS_COMMAND;

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

	// command to be executed
	FOCUS_COMMAND curFocusCommand;
	// power of command - 1-100
	int curFocusCommandStrength;

	//		control state: capture resolution
	//		deliver captured properties from external world and transfer to sensordata IO channel according to control state
	//		deriver exposed properties from control state and deliver them to external world

private:
	AIEngine& engine;
	float *vin;
	float *vout;
	RFC_HND thread;
	RFC_HND commandEvent;
	RFC_HND lockHandle;

	static const int NINPUTS = 2;
	static const int NOUTPUTS = 1;
	HANDLE changeHandle;
	bool continueRunFlag;

public:
	SensorFileSysWalker( MindArea *area ) 
	:	Sensor( "FileSysWalker" , area , NINPUTS , NOUTPUTS ) ,
		engine( AIEngine::getInstance() ) {

		// data
		vin = Cortex::getInputs();
		vout = Cortex::getOutputs();
		curFocusType = FOCUS_COMPUTER;

		// autonomous, polling is not required
		Sensor::setPollState( false );
		logger.attach( this );

		// init control data
		changeHandle = NULL;
		commandEvent = rfc_hnd_evcreate();
		lockHandle = rfc_hnd_semcreate();

		// ensure variables are initialised
		continueRunFlag = false;
		thread = NULL;
		curFocusCommand = COMMAND_FOCUS_NOCMD;
		curFocusCommandStrength = 0;
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
		if( thread == NULL )
			return;

		// stop thread
		rfc_hnd_evsignal( commandEvent );
		engine.waitThreadExited( thread );
		thread = NULL;
	}

	// called when inputs updated - i.e. control commands
	virtual void processSensorControl() {
		if( executeSensorControl() )
			produceSensorData();
	}

	// returns status - whether sensor data should be generated
	virtual bool executeSensorControl() {
		lock();

		bool res = false;
		try {
			// possible commands are - focus up, down, increase, decrease (1-4)
			// neuro-input is [-1,1]
			curFocusCommand = ( FOCUS_COMMAND )( 1 + ( int )( ( vin[0] + 1 ) * 2 ) );
			if( curFocusCommand > COMMAND_LAST )
				curFocusCommand = COMMAND_LAST;
			curFocusCommandStrength = ( int )( ( vin[1] + 1 ) * 50 );

			switch( curFocusCommand ) {
				case COMMAND_FOCUS_UP :			res = commandFocusUp(); break;
				case COMMAND_FOCUS_DOWN :		res = commandFocusDown(); break;
				case COMMAND_FOCUS_INCREASE :	res = commandFocusIncrease(); break;
				case COMMAND_FOCUS_DECREASE :	res = commandFocusDecrease(); break;
			}
		}
		catch( RuntimeException& e ) {
			e.printStack( logger );
		}

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
			changeHandle = ::FindFirstChangeNotification( curDir , FALSE , FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE );
		else
			::FindNextChangeNotification( changeHandle );
	}

	void SensorFileSysWalker::prepareWaitFileInfo() {
		if( changeHandle == NULL )
			changeHandle = ::FindFirstChangeNotification( curFile , FALSE , FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE );
		else
			::FindNextChangeNotification( changeHandle );
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

	// send update from event
	void SensorFileSysWalker::sendUpdateComputerInfo() {
		// not expected
		logger.logDebug( "SensorFileSysWalker::sendUpdateComputerInfo" );
	}

	void SensorFileSysWalker::sendUpdateDiskInfo() {
		// not expected
		logger.logDebug( "SensorFileSysWalker::sendUpdateDiskInfo" );
	}

	void SensorFileSysWalker::sendUpdateDirectoryInfo() {
		logger.logDebug( "SensorFileSysWalker::sendUpdateDirectoryInfo" );
	}

	void SensorFileSysWalker::sendUpdateFileInfo() {
		logger.logDebug( "SensorFileSysWalker::sendUpdateFileInfo" );
	}

	// send initial information - as focus changed
	bool SensorFileSysWalker::commandFocusUp() {
		return( commandMove( -curFocusCommandStrength ) );
	}

	bool SensorFileSysWalker::commandFocusDown() {
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
				switch( curFocusCommandStrength % 35 ) {
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
				switch( curFocusCommandStrength % 50 ) {
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
				if( curFocusCommandStrength % 50 ) {
					curFocusType = FOCUS_COMPUTER;
					curDisk.clear();
					curDir.clear();
					return( true );
				}

				curFocusType = FOCUS_DISK;
				curDir.clear();
				return( true );
			case FOCUS_FILE :
				switch( curFocusCommandStrength % 35 ) {
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

	String getCurPos() {
		switch( curFocusType ) {
			case FOCUS_COMPUTER :	return( "computer" ); break;
			case FOCUS_DISK :		return( "disk/" + curDisk ); break;
			case FOCUS_DIR :		return( "dir/" + curDir); break;
			case FOCUS_FILE :		return( "file/" + curFile ); break;
		}
		return( "" );
	}

	void sendSignal( String type , String value ) {
		logger.logDebug( "sendSignal: type=" + type + ", value=" + value );
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
			::FindCloseChangeNotification( changeHandle );
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
		WIN32_FIND_DATA findFileData;
		
		HANDLE hFind = ::FindFirstFile( directory + "\\*" , &findFileData );
		if( hFind == INVALID_HANDLE_VALUE )
			return( "" );

		String resFile = findFileData.cFileName;
		::FindClose( hFind );

		return( directory + "\\" + resFile );
	}

	String getDiskUpDown( String disk , int move ) {
		String disks = getDiskList();

		int index = disks.find( disk );
		ASSERTMSG( index < 0 , "Unexpected" );

		int indexMove = ( move > 0 )? ( ( disks.length() - index ) * move ) / 100 : ( index * move ) / 100;
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
		String dir = getDir( file );
		StringList files;

		// read directory
		getDirList( dir , files );

		// find current index
		String fileOnly = getFileOnly( dir );
		int index = files.find( fileOnly );
		ASSERTMSG( index < 0 , "Unexpected" );

		int indexMove = ( move > 0 )? ( ( files.count() - index ) * move ) / 100 : ( index * move ) / 100;
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
		ASSERTMSG( index >= 0 , "Unexpected" );

		// directory name does not contain trailing slash
		return( file.getMid( 0 , index ) );
	}

	String getFileOnly( String file ) {
		int index = file.findLast( '\\' );
		ASSERTMSG( index >= 0 , "Unexpected" );

		return( file.getMid( index + 1 ) );
	}

	void getDirList( String dir , StringList& files ) {
		String findName = dir + "\\*";
		WIN32_FIND_DATA findFileData;
		BOOL findNext = TRUE;

		// read files
		HANDLE hFind = ::FindFirstFile( findName , &findFileData );
		for( ; hFind != INVALID_HANDLE_VALUE && findNext; findNext = ::FindNextFileA( hFind , &findFileData ) )
			files.add( findFileData.cFileName );
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
			return;
		}

		// wait event
		if( WaitForSingleObject( changeHandle , INFINITE ) != WAIT_OBJECT_0 ) {
			// not signaled actually
			unlock();
			return;
		}

		// check wakeup occurred because of thread stop
		if( !continueRunFlag ) {
			unlock();
			return;
		}

		// real event - process it
		switch( curFocusType ) {
			case FOCUS_COMPUTER :	sendUpdateComputerInfo(); break;
			case FOCUS_DISK :		sendUpdateDiskInfo(); break;
			case FOCUS_DIR :		sendUpdateDirectoryInfo(); break;
			case FOCUS_FILE :		sendUpdateFileInfo(); break;
		}
		unlock();
	}
};

// #############################################################################
// #############################################################################

Sensor *Sensor::createFileSysWalker( MindArea *area )
{
	SensorFileSysWalker *att = new SensorFileSysWalker( area );
	return( att );
}

