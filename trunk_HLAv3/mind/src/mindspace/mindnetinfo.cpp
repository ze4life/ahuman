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
}

String MindNetInfo::getName() {
	return( name );
}

bool MindNetInfo::runEnabled() {
	return( enabled );
}
