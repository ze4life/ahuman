#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindNetSet::MindNetSet() {
	attachLogger();
	list.destroy();
}

MindNetSet::~MindNetSet() {
}

MindNet *MindNetSet::createMindNet( MindNetInfo *info ) {
	MindNet *net = new MindNet();
	net -> setInfo( info );
	map.set( net -> getName() , net );

	logger.logInfo( "createMindNet: mind network created name=" + net -> getName() );
	return( net );
}

MindNet *MindNetSet::getMindNet( String net ) {
	return( map.get( net ) );
}
