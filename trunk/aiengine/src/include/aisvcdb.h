#ifndef	INCLUDE_AIDB_H
#define INCLUDE_AIDB_H

class AIDB;
class AIDBFile;
class AIDBCursor;

/*#########################################################################*/
/*#########################################################################*/

// manages persistence of knowledge
class AIDB
{
// interface
public:
	virtual AIDBFile& getFile( SerializeObject *so )
		{ return( thisPtr -> getFile( so ) ); };

	virtual void save( Object *o , const char *p_file )
		{ thisPtr -> save( o , p_file ); };

	virtual bool load( Object *o , const char *p_file )
		{ return( thisPtr -> load( o , p_file ) ); };

	virtual void remove( Object *o )
		{ thisPtr -> remove( o ); };

	virtual void update( Object *o )
		{ thisPtr -> update( o ); };

	virtual void insert( Object *o )
		{ thisPtr -> insert( o ); };

	virtual void insert( Object **o , int n )
		{ thisPtr -> insert( o , n ); };

	virtual bool select( Object *o , const char *pk )
		{ return( thisPtr -> select( o , pk ) ); };

	virtual AIDBCursor& scan( SerializeObject *so )
		{ return( thisPtr -> scan( so ) ); };

// engine helpers
public:
	static Service *createService();
	AIDB *thisPtr;
	AIDB();
};

/*#########################################################################*/
/*#########################################################################*/

class AIDBFile : public Object
{
public:
	virtual void open() = 0;
	virtual void close() = 0;

	virtual void truncate() = 0;
	virtual AIDBCursor& scan() = 0;

	virtual void remove( Object *o ) = 0;
	virtual void update( Object *o ) = 0;
	virtual void insert( Object *o , const char *pk ) = 0;
	virtual void insert( Object **o , int n ) = 0;
	virtual bool drop( Object *o ) = 0;
	virtual bool select( Object *o , const char *pk ) = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class AIDBCursor : public Object
{
public:
	virtual bool next() = 0;
	virtual const char *getDataPK() = 0;
	virtual void getData( Object *o ) = 0;
};

#endif	// INCLUDE_AIDB_H
