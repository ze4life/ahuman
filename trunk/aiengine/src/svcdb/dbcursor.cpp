
#include "db_impl.h"

/*#########################################################################*/
/*#########################################################################*/

const char *AIDBCursorImpl::getDataPK()
{
	if( isNoRecord )
		throw RuntimeError( "AIDBCursorImpl::no record to get PK" );

	return( rh.getDataPK() );
}

void AIDBCursorImpl::getData( Object *o )
{
	if( isNoRecord )
		throw RuntimeError( "AIDBCursorImpl::no record to get data" );

	// get serialization info
	SerializeObject *sop = o -> getSerializeObject();

	// deserialize from read data
	SerializeObject::readFromString( data , sop , NULL , &o );
	Object::deserialize( NULL , o , *sop );
}

AIDBCursorImpl::AIDBCursorImpl( SerializeObject& p_so , FILE *file , long p_fileHeaderSize )
:	so( p_so ) ,
	rh( p_fileHeaderSize )
{
	stream = file;
	fileHeaderSize = p_fileHeaderSize;

	isNoRecord = true;
	currentRow = -1;
	filePos = 0;
	firstDone = false;
}

AIDBCursorImpl::~AIDBCursorImpl()
{
}

bool AIDBCursorImpl::readFirst()
{
	currentRow = -1;
	isNoRecord = true;
	filePos = 0;
	firstDone = true;

	// go to head
	rh.moveBeforeFirstRow( stream );

	// find first non-deleted row
	while( 1 )
		{
			// read header
			if( !rh.read( stream ) )
				return( false );

			// stop if non-deleted data
			if( !rh.isStatusDeleted() )
				break;

			// skip deleted record
			rh.skipData( stream );
		}

	// read data
	rh.readData( data , stream );
	
	// set row info
	currentRow = 0;
	isNoRecord = false;

	// save FILE position
	filePos = ftell( stream );

	return( true );
}

bool AIDBCursorImpl::next()
{
	if( !firstDone )
		return( readFirst() );

	if( isNoRecord )
		return( false );

	// ensure reading from saved pos
	if( ftell( stream ) != filePos )
		fseek( stream , SEEK_SET , filePos );

	// read next non-deleted row
	while( 1 )
		{
			// read header
			if( !rh.read( stream ) )
				{
					isNoRecord = true;
					return( false );
				}

			// stop if non-deleted data
			if( !rh.isStatusDeleted() )
				break;

			// skip deleted record
			rh.skipData( stream );
		}

	// read data
	rh.readData( data , stream );

	// set row info
	currentRow++;

	// save FILE position
	filePos = ftell( stream );

	return( true );
}
