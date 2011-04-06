#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindLinkInfo::MindLinkInfo() {
}

void MindLinkInfo::createFromXml( Xml xml ) {
	masterAreaId = xml.getAttribute( "masterArea" );
	slaveAreaId = xml.getAttribute( "slaveArea" );
	channelId = xml.getAttribute( "channel" );
}
