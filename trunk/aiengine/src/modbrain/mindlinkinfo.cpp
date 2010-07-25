#include "brain_impl.h"

MindLinkInfo::MindLinkInfo()
{
	masterArea = NULL;
	slaveArea = NULL;
}

void MindLinkInfo::createFromXml( Xml xml )
{
	masterAreaId = xml.getAttribute( "masterArea" );
	slaveAreaId = xml.getAttribute( "slaveArea" );
}

void MindLinkInfo::resolveLinks( MindMap *map )
{
	masterArea = map -> getAreaById( masterAreaId );
	slaveArea = map -> getAreaById( slaveAreaId );
}
