#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaLinkInfo::MindAreaLinkInfo() {
}

void MindAreaLinkInfo::createFromXml( Xml xml ) {
	masterAreaId = xml.getAttribute( "masterArea" );
	slaveAreaId = xml.getAttribute( "slaveArea" );
	channelId = xml.getAttribute( "channel" );
}
