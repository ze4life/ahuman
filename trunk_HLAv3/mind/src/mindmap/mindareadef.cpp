#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaDef::MindAreaDef() {
	attachLogger();
	enabled = false;
}

MindAreaDef::~MindAreaDef() {
};

void MindAreaDef::createFromXml( Xml xml ) {
	// attributes are properties
	areaId = xml.getAttribute( "name" );
	enabled = xml.getBooleanAttribute( "enabled" , true );
	if( !enabled )
		return;

	channelId = areaId;

	// read regions
	for( Xml xmlChild = xml.getFirstChild( "region" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "region" ) ) {
		// construct MindArea from attributes
		MindRegionDef *region = new MindRegionDef( this );
		region -> createFromXml( xmlChild );
		regions.add( region );
		regionMap.add( region -> getName() , region );
	}
}

bool MindAreaDef::runEnabled() {
	return( enabled );
}

String MindAreaDef::getChannelId() {
	return( channelId );
}

ClassList<MindRegionDef>& MindAreaDef::getRegions() {
	return( regions );
}
