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
	enabled = xml.getBooleanAttribute( "enabled" , true );
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

	// child elements are MindLink
	for( Xml xmlChild = xml.getFirstChild( "MindLink" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindLink" ) ) {
		// construct MindArea from attributes
		MindAreaLinkInfo *info = new MindAreaLinkInfo;
		info -> createFromXml( xmlChild );

		// add
		links.add( info );
	}
}

bool MindAreaInfo::runEnabled() {
	return( enabled );
}
