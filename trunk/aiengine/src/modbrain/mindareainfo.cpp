#include "brain_impl.h"

MindAreaInfo::MindAreaInfo()
{
	size = 0;
	sizeNotAllocated = 0;
	lockStructure = rfc_hnd_semcreate();
	logger.attach( this );
}

MindAreaInfo::~MindAreaInfo()
{
	links.destroy();
	rfc_hnd_semdestroy( lockStructure );
};

void MindAreaInfo::createFromXml( Xml xml )
{
	// attributes are properties
	areaId = xml.getAttribute( "id" );
	sizeNotAllocated = size = xml.getIntProperty( "size" );

	// child elements are MindLink
	for( Xml xmlChild = xml.getFirstChild( "MindLink" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindLink" ) ) {
		// construct MindArea from attributes
		MindLinkInfo *info = new MindLinkInfo;
		info -> createFromXml( xmlChild );

		// add
		links.add( info );
	}
}

void MindAreaInfo::allocate( int p_size )
{
	// verify
	lock();
	int na = sizeNotAllocated;
	if( na < p_size ) {
		unlock();
		ASSERTMSG( na >= p_size , String( "area memory is exhausted - nonallocated=" ) + na + ", requestedsize=" + p_size );
	}

	// allocate
	sizeNotAllocated -= p_size;
	logger.logInfo( "mind area id=" + areaId + ": allocated " + p_size + " of " + na + " (total=" + size + ")" );
	unlock();
}

