#ifndef	INCLUDE_AIDB_IMPL_H
#define INCLUDE_AIDB_IMPL_H

#include <aiengine.h>
#include <aidb.h>

class AIDBCursorImpl;
class AIDBFile;
class AIDBRecordHeader;
class AIDBRecordSet;

/*#########################################################################*/
/*#########################################################################*/

// manages persistence of knowledge
class AIDBImpl : public AIDB , public Service
{
	typedef enum {
		// unknown file type
		FILETYPE_EMPTY = 0 ,
		// standard database file with header and records
		FILETYPE_DB = 1 ,
		// custome database file with header and records
		FILETYPE_DBCUSTOM = 2 ,
		// file for single object
		FILETYPE_OBJECT = 3
	} FileType;

public:
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "DB" ); };

// external interface
public:
	virtual AIDBFile& getFile( SerializeObject *so );

	virtual void save( Object *o , const char *p_file );
	virtual bool load( Object *o , const char *p_file );

	virtual void remove( Object *o );
	virtual void update( Object *o );
	virtual void insert( Object *o );
	virtual void insert( Object **o , int n );
	virtual bool select( Object *o , const char *pk );
	virtual AIDBCursor& scan( SerializeObject *so );

public:
	AIDBImpl();
	~AIDBImpl();

private:
	void openDatabase();
	void closeDatabase();

	AIDBFile& openFile( SerializeObject& so , const char *name );
	String getFilePath( const char *dbt , const char *name , FileType type );

	AIDBFile *createCustomFile( const char *name , SerializeObject& so );
	AIDBFile *openCustomFile( const char *name );

	void clearLastCursor();

	void createDirectory( const char *path );

// internals
private:
	AIEngine& engine;
	String dbPath;
	rfc_strmap *mapFileIdToFile;
};

// #############################################################################
// #############################################################################

class AIDBFileImpl : public AIDBFile
{
	friend class AIDBImpl;

public:
	virtual void open();
	virtual void close();

	virtual void truncate();
	virtual AIDBCursor& scan();

	virtual void remove( Object *o );
	virtual void update( Object *o );
	virtual void insert( Object *o , const char *pk );
	virtual void insert( Object **o , int n );
	virtual bool drop( Object *o );
	virtual bool select( Object *o , const char *pk );

private:
	AIDBFileImpl( SerializeObject& p_so , const char *p_path );
	~AIDBFileImpl();

	void clearLastCursor();
	bool readFileHeader();
	int writeFileHeader();
	int readHeaderString( FILE *stream , String& s );
	void replaceSerializeObjectInstance( SerializeObject *so );

private:
	SerializeObject& so;
	SerializeObject *soSrc;
	String path;
	FILE *stream;
	bool isOpen;
	bool isCorrupted;
	AIDBCursorImpl *lastCursor;
	int headerSize;
};

// #############################################################################
// #############################################################################

class AIDBRecordHeader : public Object
{
public:
	AIDBRecordHeader( long fileHeaderSize );
	~AIDBRecordHeader();

	bool checkPK( const char *pk );
	bool read( FILE *file );
	void readData( String& data , FILE *file );

	void skipData( FILE *file );
	void moveBeforeHeader( FILE *file );
	void moveBeforeFirstRow( FILE *file );
	void moveToEnd( FILE *file );

	const char *getDataPK();
	void setDataPK( const char *pk );
	void setDataSize( int size );
	void setStatusDeleted();
	bool isStatusDeleted();
	void setStatusNormal();

	void write( FILE *file );
	void writeData( FILE *file , const char *data );

private:
	long fileHeaderSize;

	char rawHeaderData[ 100 ];
	
	String recordPK;
	int recordHeaderSize;
	int recordDataSize;
	char recordStatus;
};

// #############################################################################
// #############################################################################

class AIDBRecordSet : public Object
{
public:
	AIDBRecordSet( FILE *f , int headerSize );
	~AIDBRecordSet();

	bool findPK( const char *pk );
	bool readByPK( const char *pk , String& s );
	void deleteCurrent();
	void append( const char *pk , const char *data );

private:
	FILE *stream;
	AIDBRecordHeader rh;

	int currentRow;
};

// #############################################################################
// #############################################################################

class AIDBCursorImpl : public AIDBCursor
{
public:
	virtual bool next();
	virtual const char *getDataPK();
	virtual void getData( Object *o );

public:
	AIDBCursorImpl( SerializeObject& so , FILE *file , long fileHeaderSize );
	~AIDBCursorImpl();

	bool readFirst();
	bool isEOF() { return( isNoRecord ); };

private:
	FILE *stream;
	long fileHeaderSize;

	bool firstDone;
	bool isNoRecord;
	AIDBRecordHeader rh;
	long filePos;

	int currentRow;
	SerializeObject& so;
	String data;
};

#endif	// INCLUDE_AIDB_IMPL_H
