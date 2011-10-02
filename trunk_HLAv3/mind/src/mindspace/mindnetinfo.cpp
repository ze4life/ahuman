#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindNetInfo::MindNetInfo() {
	attachLogger();
	enabled = false;
}

MindNetInfo::~MindNetInfo() {
}

void MindNetInfo::createFromXml( Xml xml ) {
	// attributes are properties
	enabled = xml.getBooleanAttribute( "enabled" , true );
	name = xml.getAttribute( "name" );
	typeName = xml.getAttribute( "type" );
}

String MindNetInfo::getName() {
	return( name );
}

String MindNetInfo::getTypeName() {
	return( typeName );
}

bool MindNetInfo::runEnabled() {
	return( enabled );
}

void MindNetInfo::setNetType( MindNetworkType *p_netType ) {
	netType = p_netType;
}

MindNetworkType *MindNetInfo::getNetType() {
	return( netType );
}
