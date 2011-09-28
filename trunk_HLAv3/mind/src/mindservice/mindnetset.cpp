#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindNetSet::MindNetSet() {
	list.destroy();
}

MindNetSet::~MindNetSet() {
}

MindNet *MindNetSet::createNet( MindNetInfo *info ) {
	MindNet *net = new MindNet();
	net -> setInfo( info );
	map.set( net -> getName() , net );
	return( net );
}

