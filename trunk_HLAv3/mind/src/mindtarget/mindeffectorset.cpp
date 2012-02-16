#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindEffectorSet::MindEffectorSet() {
	attachLogger();
}

int MindEffectorSet::getCount() {
	return( list.count() );
}

MindEffector *MindEffectorSet::getSetItem( int k ) {
	return( list.get( k ) );
}

void MindEffectorSet::addSetItem( MindEffector *effector ) {
	list.add( effector );
	map.add( effector -> getClass() , effector );
}

MindEffector *MindEffectorSet::getEffector( String name ) {
	return( map.get( name ) );
}

