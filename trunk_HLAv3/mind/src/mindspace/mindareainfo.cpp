#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaInfo::MindAreaInfo() {
	attachLogger();
	enabled = false;
}

MindAreaInfo::~MindAreaInfo() {
	links.destroy();
};

void MindAreaInfo::createFromXml( Xml xml ) {
	// attributes are properties
	areaId = xml.getAttribute( "id" );
	enabled = xml.getBooleanAttribute( "enabled" , true );
	if( !enabled )
		return;

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

	String transmittersList = xml.getProperty( "transmitters" , "" );
	transmittersList.split( transmitters , "," );
	transmitters.trim();
}

bool MindAreaInfo::runEnabled() {
	return( enabled );
}
