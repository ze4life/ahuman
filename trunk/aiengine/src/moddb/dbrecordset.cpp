#include "aidb_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIDBRecordSet::AIDBRecordSet( FILE *p_f , int p_headerSize )
:	rh( p_headerSize )
{
	stream = p_f;
	currentRow = -1;
}

AIDBRecordSet::~AIDBRecordSet()
{
}

bool AIDBRecordSet::findPK( const char *pk )
{
	rh.moveBeforeFirstRow( stream );
	currentRow = -1;

	while( rh.read( stream ) )
		{
			currentRow++;

			// if record is normal and primary key is the same - return
			if( rh.checkPK( pk ) )
				return( true );

			// skip data
			rh.skipData( stream );
		}

	currentRow = -1;
	return( false );
}

bool AIDBRecordSet::readByPK( const char *pk , String& s )
{
	if( !findPK( pk ) )
		return( false );

	rh.readData( s , stream );
	return( true );
}

void AIDBRecordSet::deleteCurrent()
{
	if( currentRow < 0 )
		return;

	// current position should be just after record heading
	rh.moveBeforeHeader( stream );
	rh.setStatusDeleted();
	rh.write( stream );
}

void AIDBRecordSet::append( const char *pk , const char *data )
{
	currentRow = -1;
	rh.moveToEnd( stream );

	// write header
	rh.setDataSize( strlen( data ) );
	rh.setDataPK( pk );
	rh.setStatusNormal();
	rh.write( stream );

	// write data
	rh.writeData( stream , data );
}
