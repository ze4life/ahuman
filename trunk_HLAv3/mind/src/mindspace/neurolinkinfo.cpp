#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroLinkInfo::NeuroLinkInfo( MindNetworkType *p_netType ) {
	netType = p_netType;
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
	if( type.equals( "ExcitatoryLink" ) )
		link = new ExcitatoryLink( regionLink );
	else
	if( type.equals( "InhibitoryLink" ) )
		link = new InhibitoryLink( regionLink );
	else
	if( type.equals( "ModulatoryLink" ) )
		link = new ModulatoryLink( regionLink );
	else
		ASSERTFAILED( "Unknown NeuroLink type=" + type + ", name=" + name );
	
	// set link info
	link -> setNeuroLinkInfo( this );
	link -> setTransmitter( transmitter );

	return( link );
}
