#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindNet::MindNet() {
}

MindNet::~MindNet() {
}

void MindNet::setInfo( MindNetInfo *p_info ) {
	info = p_info;
	name = p_info -> getName();
}

MindNetInfo *MindNet::getInfo() {
	return( info );
}

String MindNet::getName() {
	return( name );
}
