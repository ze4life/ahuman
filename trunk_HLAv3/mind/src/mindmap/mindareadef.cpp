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
	linkSet.destroy();
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
	li.createFromXml( xml.getChildNode( "MindLocation" ) );
	location = li.createLocation();

	setChannelInfo( xml.getChildNode( "MindAreaChannel" ) );

	// mind area networks
	for( Xml xmlChild = xml.getFirstChild( "MindAreaNetwork" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindAreaNetwork" ) ) {
		// construct MindAreaNetwork from attributes
		MindAreaNetInfo *info = new MindAreaNetInfo();
		netSet.add( info );

		info -> createFromXml( xmlChild );

		// get link name
		String name = info -> getNetName();
		ASSERTMSG( !name.isEmpty() , "neurolink is not defined: " + xmlChild.serialize() );
		ASSERTMSG( netMap.get( name ) == NULL , name + ": area network duplicate found for name=" + name );

		// add
		netMap.add( name , info );
	}
}

void MindAreaDef::setChannelInfo( Xml xml ) {
	if( !xml.exists() )
		return;

	channelId = xml.getAttribute( "name" );
}

bool MindAreaDef::runEnabled() {
	return( enabled );
}

MindAreaNetInfo *MindAreaDef::getNetInfo( String name ) {
	return( netMap.get( name ) );
}

String MindAreaDef::getChannelId() {
	return( channelId );
}
