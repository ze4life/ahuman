#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroLinkInfo::NeuroLinkInfo( MindLinkType *p_linkType ) {
	linkType = p_linkType;
	forward = true;
}

void NeuroLinkInfo::createFromXml( Xml xml ) {
	// attributes are properties
	name = xml.getAttribute( "name" );
	type = xml.getAttribute( "type" );
	transmitter = xml.getAttribute( "transmitter" );
	forward = xml.getBooleanAttribute( "forward" , true );
}

NeuroLink *NeuroLinkInfo::createNeuroLink( MindRegionLink *regionLink ) {
	NeuroLink *link = NULL;

	MindService *ms = MindService::getService();
	if( type.equals( "ExcitatoryLink" ) )
		link = ms -> createExcitatoryLink( regionLink );
	else
	if( type.equals( "InhibitoryLink" ) )
		link = ms -> createInhibitoryLink( regionLink );
	else
	if( type.equals( "ModulatoryLink" ) )
		link = ms -> createModulatoryLink( regionLink );
	else
		ASSERTFAILED( "Unknown NeuroLink type=" + type + ", name=" + name );
	
	// set link info
	link -> setNeuroLinkInfo( this );
	link -> setTransmitter( transmitter );

	return( link );
}
