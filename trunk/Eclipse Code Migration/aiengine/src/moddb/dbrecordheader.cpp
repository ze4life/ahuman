
#include <aidb_impl.h>

/*#########################################################################*/
/*#########################################################################*/

AIDBRecordHeader::AIDBRecordHeader( long p_fileHeaderSize )
{
	fileHeaderSize = p_fileHeaderSize;

	recordHeaderSize = 0;
	recordDataSize = 0;
	recordStatus = 'U';
}

AIDBRecordHeader::~AIDBRecordHeader()
{
}

bool AIDBRecordHeader::read( FILE *file )
{
	int pkSize;
	long posBefore = ftell( file );
	if( fscanf( file , "R:%c:%d:%d:" , &recordStatus , &pkSize , &recordDataSize ) != 3 )
		return( false );

	// header size is above String plus pk size plus 1 ('$')
	long posAfter = ftell( file );
	recordHeaderSize = posAfter - posBefore + pkSize + 1;

	// read PK
	if( recordPK.size() < pkSize )
		recordPK.resize( pkSize );

	char *ptr = recordPK.getBuffer();
	if( fread( ptr , 1 , pkSize , file ) != ( unsigned )pkSize )
		return( false );
	ptr[ pkSize ] = 0;

	// check terminator
	if( getc( file ) != '$' )
		return( false );

	return( true );
}

void AIDBRecordHeader::readData( String& data , FILE *file )
{
	if( recordStatus != 'N' )
		throw RuntimeError( "AIDBRecordHeader::readData: invalid record to read from file" );

	if( data.size() < recordDataSize )
		data.resize( recordDataSize );

	char *ptr = data.getBuffer();
	if( fread( ptr , 1 , recordDataSize , file ) != ( unsigned )recordDataSize )
		throw RuntimeError( "AIDBRecordHeader::readData: cannot read from file required size" );
	ptr[ recordDataSize ] = 0;

	// skip record terminator
	if( getc( file ) != '\n' )
		throw RuntimeError( "AIDBRecordHeader::readData: no record terminator" );
}

void AIDBRecordHeader::write( FILE *file )
{
	char l_buf[ 100 ];
	sprintf( l_buf , "R:%c:%d:%d:" , recordStatus , recordPK.length() , recordDataSize );
	fwrite( l_buf , strlen( l_buf ) , 1 , file );
	fwrite( recordPK , recordPK.length() , 1 , file );
	putc( '$' , file );
}

void AIDBRecordHeader::writeData( FILE *file , const char *data )
{
	fwrite( data , strlen( data ) , 1 , file );
	putc( '\n' , file );
}

const char *AIDBRecordHeader::getDataPK()
{
	return( recordPK );
}

bool AIDBRecordHeader::checkPK( const char *pk )
{
	if( recordStatus == 'N' &&
		strcmp( recordPK , pk ) == 0 )
		return( true );

	return( false );
}

void AIDBRecordHeader::skipData( FILE *file )
{
	fseek( file , recordDataSize + 1 , SEEK_CUR );
}

void AIDBRecordHeader::moveBeforeHeader( FILE *file )
{
	fseek( file , -recordHeaderSize , SEEK_CUR );
}

void AIDBRecordHeader::setStatusDeleted()
{
	recordStatus = 'D';
}

bool AIDBRecordHeader::isStatusDeleted()
{
	return( recordStatus == 'D' );
}

void AIDBRecordHeader::setStatusNormal()
{
	recordStatus = 'N';
}

void AIDBRecordHeader::moveToEnd( FILE *file )
{
	fseek( file , 0 , SEEK_END );
}

void AIDBRecordHeader::moveBeforeFirstRow( FILE *file )
{
	fseek( file , fileHeaderSize , SEEK_SET );
}

void AIDBRecordHeader::setDataSize( int size )
{
	recordDataSize = size;
}

void AIDBRecordHeader::setDataPK( const char *pk )
{
	recordPK = pk;
}

