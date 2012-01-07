#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaLinkInfo::MindAreaLinkInfo() {
	linkType = NULL;
}

void MindAreaLinkInfo::createFromXml( Xml xml ) {
	enabled = xml.getBooleanAttribute( "enabled" , true );
	typeName = xml.getAttribute( "type" );
	masterAreaId = xml.getAttribute( "masterArea" );
	slaveAreaId = xml.getAttribute( "slaveArea" );
	masterChannelId = xml.getAttribute( "masterChannel" , "" );
	slaveChannelId = xml.getAttribute( "slaveChannel" , "" );
}

void MindAreaLinkInfo::setLinkType( MindLinkType *p_linkType ) {
	linkType = p_linkType;
}

MindLinkType *MindAreaLinkInfo::getLinkType() {
	return( linkType );
}

