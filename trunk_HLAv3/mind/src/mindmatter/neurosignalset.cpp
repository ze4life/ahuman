#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

void NeuroSignalSet::destroy() {
	signalMap.destroy();
}

void NeuroSignalSet::addSetItem( String connector , NeuroSignal *signal ) {
	signalMap.add( connector , signal );
}
