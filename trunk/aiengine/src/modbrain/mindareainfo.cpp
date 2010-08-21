#include "brain_impl.h"

MindAreaInfo::MindAreaInfo()
{
	size = 0;
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

	int x , y , z;
	x = xml.getIntProperty( "posX" );
	y = xml.getIntProperty( "posY" );
	z = xml.getIntProperty( "posZ" );
	location.setPosition( x , y , z );

	int dx , dy , dz;
	dx = xml.getIntProperty( "sizeX" );
	dy = xml.getIntProperty( "sizeY" );
	dz = xml.getIntProperty( "sizeZ" );
	location.setDimensions( dx , dy , dz );

	size = location.getSize();

	// child elements are MindLink
	for( Xml xmlChild = xml.getFirstChild( "MindLink" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindLink" ) ) {
		// construct MindArea from attributes
		MindLinkInfo *info = new MindLinkInfo;
		info -> createFromXml( xmlChild );

		// add
		links.add( info );
	}
}

