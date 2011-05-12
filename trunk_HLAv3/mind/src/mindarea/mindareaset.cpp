#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

void MindAreaSet::addMindArea( MindArea *area ) {
	list.add( area );
	map.add( area -> getMindAreaInfo() -> getAreaId() , area );
}

MindArea *MindAreaSet::getMindArea( String id ) {
	return( map.get( id ) );
}

void MindAreaSet::initRegionsInAreaSet() {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> initRegionsInArea();
}

void MindAreaSet::wakeupAreaSet( MindActiveMemory *activeMemory ) {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> wakeupArea( activeMemory );
}

void MindAreaSet::asleepAreaSet() {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> asleepArea();
}

void MindAreaSet::exitAreaSet() {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> exitArea();
}

void MindAreaSet::destroyAreaSet() {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> destroyArea();

	map.clear();
	list.destroy();
}

