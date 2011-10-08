#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaNetInfo::MindAreaNetInfo() {
	attachLogger();
	netInfo = NULL;
}

MindAreaNetInfo::~MindAreaNetInfo() {
}

void MindAreaNetInfo::createFromXml( Xml xml ) {
	// attributes are properties
	netName = xml.getAttribute( "name" );
	transmitters = xml.getAttribute( "transmitters" );
}

String MindAreaNetInfo::getNetName() {
	return( netName );
}

String MindAreaNetInfo::getTransmitters() {
	return( transmitters );
}

void MindAreaNetInfo::setNetInfo( MindNetInfo *p_net ) {
	netInfo = p_net;
}

MindNetInfo *MindAreaNetInfo::getNetInfo() {
	return( netInfo );
}
