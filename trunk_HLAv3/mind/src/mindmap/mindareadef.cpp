#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaDef::MindAreaDef() {
	attachLogger();
	enabled = false;
	location = NULL;
}

MindAreaDef::~MindAreaDef() {
	if( location != NULL )
		delete location;
};

void MindAreaDef::createFromXml( Xml xml ) {
	// attributes are properties
	areaId = xml.getAttribute( "id" );
	enabled = xml.getBooleanAttribute( "enabled" , true );
	if( !enabled )
		return;

	MindLocationInfo li;
	li.createFromXml( xml.getChildNode( "location" ) );
	location = li.createLocation();

	channelId = areaId;
}

bool MindAreaDef::runEnabled() {
	return( enabled );
}

String MindAreaDef::getChannelId() {
	return( channelId );
}
