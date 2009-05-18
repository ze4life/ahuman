
#include <aidb_impl.h>
#include <direct.h>

/*#########################################################################*/
/*#########################################################################*/

AIDB::AIDB() 
{ 
	thisPtr = static_cast<AIDBImpl *>( AIEngine::getInstance().getService( "AIDB" ) ); 
}

/* static */ Service *AIDB::createService()
{
	Service *svc = new AIDBImpl();
	AIEngine::getInstance().registerService( svc , "AIDB" );
	return( svc );
}

void AIDBImpl::initService()
{
	openDatabase();
}

void AIDBImpl::runService()
{
	/* nothing to do */
}

void AIDBImpl::exitService()
{
	closeDatabase();
}

void AIDBImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

AIDBImpl::AIDBImpl()
:	engine( AIEngine::getInstance() )
{
	mapFileIdToFile = rfc_map_strcreate();
}

AIDBImpl::~AIDBImpl()
{
	rfc_map_strdrop( mapFileIdToFile );
}

void AIDBImpl::openDatabase()
{
	TiXmlElement *el = engine.getRoot( "database" );
	el = el -> FirstChildElement( "path" );
	
	// get database path
	dbPath = el -> GetText();
}

void AIDBImpl::closeDatabase()
{
	for( int k = 0; k < rfc_map_strcount( mapFileIdToFile ); k++ )
		{
			AIDBFile *file = ( AIDBFile * )rfc_map_strget( mapFileIdToFile , k );
			file -> close();
			delete file;
		}
	rfc_map_strclear( mapFileIdToFile );
}

AIDBFile& AIDBImpl::openFile( SerializeObject& so , const char *name )
{
	const char *dbt = so.getObjectClass();

	String filePath = getFilePath( dbt , name , FILETYPE_DB );
	AIDBFile *file = new AIDBFileImpl( so , filePath );
	rfc_map_stradd( mapFileIdToFile , dbt , file );

	file -> open();

	return( *file );
}

AIDBFile *AIDBImpl::createCustomFile( const char *name , SerializeObject& so )
{
	const char *dbt = so.getObjectClass();

	String filePath = getFilePath( dbt , name , FILETYPE_DBCUSTOM );
	AIDBFileImpl *file = new AIDBFileImpl( so , filePath );

	file -> open();

	return( file );
}

AIDBFile *AIDBImpl::openCustomFile( const char *name )
{
	return( NULL );
}

AIDBFile& AIDBImpl::getFile( SerializeObject *so )
{
	const char *dbt = so -> getObjectClass();

	// find file
	AIDBFile *file;
	if( rfc_map_strcheck( mapFileIdToFile , dbt , ( void ** )&file ) >= 0 )
		return( *file );

	// create/open file
	return( openFile( *so , "std" ) );
}

String AIDBImpl::getFilePath( const char *dbt , const char *name , FileType type )
{
	String path = dbPath;

	String md1;
	String md2;
	switch( type )
		{
			case FILETYPE_DB :
				md1 = path + "/db";
				path = md1 + "/" + name + "." + dbt + ".adb";
				createDirectory( md1 );
				break;
			case FILETYPE_DBCUSTOM :
				md1 = path + "/db";
				md2 = md1 + "/" + dbt;
				path = md2 + "/" + name + ".adb"; 
				createDirectory( md1 );
				createDirectory( md2 );
				break;
			case FILETYPE_OBJECT :
				md1 = path + "/" + dbt;
				path = md1 + "/" + name + ".aob"; 
				createDirectory( md1 );
				break;
			default :
				ASSERT( false );
		}

	return( path );
}

void AIDBImpl::createDirectory( const char *path )
{
	_mkdir( path );
}

void AIDBImpl::update( Object *o )
{
	SerializeObject *so = o -> getSerializeObject();
	AIDBFile& file = getFile( so );
	file.update( o );
}

void AIDBImpl::insert( Object *o )
{
	SerializeObject *so = o -> getSerializeObject();
	AIDBFile& file = getFile( so );

	String pk = o -> getPK();
	file.insert( o , pk );
}

void AIDBImpl::remove( Object *o )
{
	SerializeObject *so = o -> getSerializeObject();
	AIDBFile& file = getFile( so );
	file.remove( o );
}

void AIDBImpl::insert( Object **o , int n )
{
	if( n <= 0 )
		return;

	SerializeObject *so =  (*o) -> getSerializeObject();
	AIDBFile& file = getFile( so );

	file.insert( o , n );
}

bool AIDBImpl::select( Object *o , const char *pk )
{
	SerializeObject *so = o -> getSerializeObject();
	AIDBFile& file = getFile( so );
	return( file.select( o , pk ) );
}

AIDBCursor& AIDBImpl::scan( SerializeObject *so )
{
	AIDBFile& file = getFile( so );
	return( file.scan() );
}

void AIDBImpl::save( Object *o , const char *p_file )
{
	String objectClass = o -> getClass();
	String filePath = getFilePath( objectClass , p_file , FILETYPE_OBJECT );

	FILE *f = fopen( filePath , "wt" );
	if( f == NULL )
		throw RuntimeError( String( "AIDBImpl::save: cannot save file: " ) + filePath );

	// fill String
	SerializeObject *so = o -> getSerializeObject();
	Object::serialize( o , *so );
	String s = so -> getDataStringNameToValue();

	// write to file
	fputs( s , f );
	fclose( f );

	logger.logInfo( String( "saved object " ) + o -> getClass() + 
		" to file " + p_file );
}

bool AIDBImpl::load( Object *o , const char *p_file )
{
	String objectClass = o -> getClass();
	String filePath = getFilePath( objectClass , p_file , FILETYPE_OBJECT );

	FILE *f = fopen( filePath , "rt" );
	if( f == NULL )
		return( false );

	// read file to String
	String data;
	freadString( data , f );
	fclose( f );

	// gather to object
	SerializeObject *so = o -> getSerializeObject();
	SerializeObject::readFromString( data , so , NULL , &o );

	Object::deserialize( NULL , o , *so );
	logger.logInfo( String( "loaded object " ) + o -> getClass() + 
		" from file " + p_file );

	return( true );
}

