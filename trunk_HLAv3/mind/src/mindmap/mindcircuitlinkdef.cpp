#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitLinkDef::MindCircuitLinkDef( MindRegionType *p_regionType ) {
	attachLogger();

	linkType = NULL;
	regionType = p_regionType;
	forward = true;
}

MindCircuitLinkDef::MindCircuitLinkDef( MindCircuitLinkTypeDef *p_linkType ) {
	attachLogger();

	linkType = p_linkType;
	regionType = NULL;
	forward = true;
}

void MindCircuitLinkDef::createFromXml( Xml xml ) {
	// attributes are properties
	id = xml.getAttribute( "id" , "" );
	type = xml.getAttribute( "type" );
	masterEntity = xml.getAttribute( "masterEntity" , "" );
	slaveEntity = xml.getAttribute( "slaveEntity" , "" );
	transmitter = xml.getAttribute( "transmitter" );
	forward = xml.getBooleanAttribute( "forward" , true );
}

NeuroLink *MindCircuitLinkDef::createNeuroLink( MindRegionLink *regionLink , NeuroLinkSource *srcData , NeuroLinkTarget *dstData ) {
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
		ASSERTFAILED( "Unknown NeuroLink type=" + type + ", master=" + masterEntity + ", slave=" + slaveEntity );
	
	// set link info
	link -> create( srcData , dstData );
	link -> setMindCircuitLinkDef( this );
	link -> setTransmitter( transmitter );

	logger.logInfo( String( "createNeuroLink: NeuroLink created id=" ) + link -> getId() + ", type=" + type + " in MindRegionLink id=" + regionLink -> getId() + ", master=" + masterEntity + ", slave=" + slaveEntity + ", forward=" + forward );
	return( link );
}

NeuroLink *MindCircuitLinkDef::createInternalNeuroLink( MindRegion *region ) {
	NeuroLink *link = NULL;

	MindService *ms = MindService::getService();
	if( type.equals( "ExcitatoryLink" ) )
		link = ms -> createExcitatoryLink( NULL );
	else
	if( type.equals( "InhibitoryLink" ) )
		link = ms -> createInhibitoryLink( NULL );
	else
	if( type.equals( "ModulatoryLink" ) )
		link = ms -> createModulatoryLink( NULL );
	else
		ASSERTFAILED( "Unknown NeuroLink type=" + type + ", master=" + masterEntity + ", slave=" + slaveEntity );
	
	// set link info
	link -> createInternal( region );
	link -> setMindCircuitLinkDef( this );
	link -> setTransmitter( transmitter );

	logger.logInfo( String( "createNeuroLink: NeuroLink created id=" ) + link -> getId() + ", type=" + type + ", in MindRegion id=" + region -> getFullRegionId() );
	return( link );
}
