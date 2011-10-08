#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaInfo::MindAreaInfo() {
	attachLogger();
	enabled = false;
	location = NULL;
}

MindAreaInfo::~MindAreaInfo() {
	linkSet.destroy();
	if( location != NULL )
		delete location;
};

void MindAreaInfo::createFromXml( Xml xml ) {
	// attributes are properties
	areaId = xml.getAttribute( "id" );
	enabled = xml.getBooleanAttribute( "enabled" , true );
	if( !enabled )
		return;

	MindLocationInfo li;
	li.createFromXml( xml.getChildNode( "MindLocation" ) );
	location = li.createLocation();
}

bool MindAreaInfo::runEnabled() {
	return( enabled );
}
