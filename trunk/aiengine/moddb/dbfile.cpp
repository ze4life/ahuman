
#include <aidb_impl.h>

/*#########################################################################*/
/*#########################################################################*/

AIDBFileImpl::AIDBFileImpl( SerializeObject& p_so , const char *p_path )
:	so( p_so )
{
	path = p_path;
	stream = NULL;

	isCorrupted = false;
	isOpen = false;
	lastCursor = NULL;
	headerSize = 0;

	soSrc = NULL;
}

AIDBFileImpl::~AIDBFileImpl()
{
	if( stream != NULL )
		fclose( stream );

	clearLastCursor();
}

void AIDBFileImpl::clearLastCursor()
{
	if( lastCursor != NULL )
		{
			delete lastCursor;
			lastCursor = NULL;
		}
}

void AIDBFileImpl::open()
{
	if( isCorrupted )
		return;

	// open if exists
	stream = fopen( path , "r+b" );

	// open if exists
	if( stream != NULL )
		{
			if( readFileHeader() ) 
				{
					isOpen = true;
					return;
				}
		}
	else
		{
			// create if not exists
			stream = fopen( path , "w+b" );
			if( stream != NULL )
				{
					writeFileHeader();
					isOpen = true;
					return;
				}
		}

	// trouble if cannot open
	isCorrupted = true;

	String err = "AIDBFileImpl::cannot open/create file: ";
	err += path;
	throw RuntimeError( err );
}

void AIDBFileImpl::close()
{
	if( stream == NULL )
		return;

	fclose( stream );
	stream = NULL;
	isOpen = false;
	isCorrupted = false;
}

void AIDBFileImpl::update( Object *o )
{
	if( !isOpen )
		return;

	Object::serialize( o , so );

	AIDBRecordSet rs( stream , headerSize );
	String pk = o -> getPK();
	if( rs.findPK( pk ) )
		rs.deleteCurrent();

	// insert
	String s = so.getDataStringIdToValue();
	rs.append( pk , s );
}

void AIDBFileImpl::remove( Object *o )
{
	if( !isOpen )
		return;

	Object::serialize( o , so );

	AIDBRecordSet rs( stream , headerSize );
	String pk = o -> getPK();
	if( rs.findPK( pk ) )
		rs.deleteCurrent();
}

void AIDBFileImpl::truncate()
{
	if( !isOpen )
		return;

	fclose( stream );
	stream = fopen( path , "w+b" );

	// trouble if cannot open
	if( stream == NULL )
		{
			isCorrupted = true;

			String err = "AIDBFileImpl::cannot truncate file: ";
			err += path;
			throw RuntimeError( err );
		}

	headerSize = writeFileHeader();
}

void AIDBFileImpl::insert( Object *o , const char *pk )
{
	if( !isOpen )
		return;

	Object::serialize( o , so );

	AIDBRecordSet rs( stream , headerSize );

	// insert
	String s = so.getDataStringIdToValue();
	rs.append( pk , s );
}

void AIDBFileImpl::insert( Object **o , int n )
{
	if( !isOpen )
		return;

	for( int k = 0; k < n; k++ )
		{
			String pk = o[ k ] -> getPK();
			insert( o[ k ] , pk );
		}
}

bool AIDBFileImpl::drop( Object *o )
{
	if( !isOpen )
		return( false );

	AIDBRecordSet rs( stream , headerSize );
	const char *pk = o -> getPK();

	// not found
	if( !rs.findPK( pk ) )
		return( false );

	// delete found
	rs.deleteCurrent();
	return( true );
}

bool AIDBFileImpl::select( Object *o , const char *pk )
{
	if( !isOpen )
		return( false );

	SerializeObject *sop = o -> getSerializeObject();

	AIDBRecordSet rs( stream , headerSize );
	String s;
	if( !rs.readByPK( pk , s ) )
		return( false );

	SerializeObject::readFromString( s , sop , soSrc , &o );
	Object::deserialize( NULL , o , *sop );

	return( true );
}

AIDBCursor& AIDBFileImpl::scan()
{
	clearLastCursor();
	lastCursor = new AIDBCursorImpl( so , stream , headerSize );

	return( *lastCursor );
}

bool AIDBFileImpl::readFileHeader()
{
	if( lastCursor != NULL )
		throw RuntimeError( "AIDBFileImpl::readFileHeader: cursor exists while reading header" );

	// read header block
	String s;
	headerSize = readHeaderString( stream , s );

	// read file metadata
	// get serialize object of serialize object
	SerializeObject *soso = so.getSerializeObject();
	soSrc = new SerializeObject();
	SerializeObject::readFromString( s , soso , NULL , ( Object ** )&soSrc );

	// read serialize object from s
	Object::deserialize( NULL , soSrc , *soso );

	// add to known objects
	replaceSerializeObjectInstance( soSrc );
	return( true );
}

int AIDBFileImpl::readHeaderString( FILE *stream , String& s )
{
	rewind( stream );

	// read all up to end mark "$\n"
	int len = 0;
	char c;
	while( ( c = getc( stream ) ) != EOF )
		{
			switch( c )
				{
					case '\\' :
						// ignore next
						s += getc( stream );
						len++;
						break;
					case '$' :
						if( getc( stream ) != '\n' )
							throw RuntimeError( "AIDBFileImpl::readHeaderSring: newline expected" );
						return( ftell( stream ) );
					case '\n' :
						// ignore new lines
						break;
					default:
						s += c;
						len++;
						break;
				}
		}

	throw RuntimeError( "AIDBFileImpl::readHeaderSring: wrong file header" );
}

int AIDBFileImpl::writeFileHeader()
{
	if( lastCursor != NULL )
		throw RuntimeError( "AIDBFileImpl::writeFileHeader: cursor exists while writing header" );

	// use new source
	soSrc = &so;
	replaceSerializeObjectInstance( soSrc );

	// get serialize object of serialize object
	SerializeObject *soso = so.getSerializeObject();
	Object::serialize( &so , *soso );

	// write, handle delimiter
	rewind( stream );
	String s = soso -> getDataStringNameToValue();

	fputs( s , stream );
	fputs( "\n$\n" , stream );
	fflush( stream );

	return( ftell( stream ) );
}

void AIDBFileImpl::replaceSerializeObjectInstance( SerializeObject *so )
{
	AIEngine::getInstance().replaceSerializeObjectInstanceSrc( so );
}

