#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindActiveMemoryObject::MindActiveMemoryObject( int id ) {
	activeMemoryObjectId = id;
	name = String( "AMO" ) + id;
	setInstance( name );
}

MindActiveMemoryObject::~MindActiveMemoryObject() {
}

void MindActiveMemoryObject::setCortex( Cortex *p_cortex ) {
	cortex = p_cortex;
}

void MindActiveMemoryObject::execute() {
	double x = 0;
	for( int k = 0; k < 10000; k++ )
		x += ::log( ( double )k );
}

bool MindActiveMemoryObject::needExecution() {
	return( true );
}

bool MindActiveMemoryObject::finished() {
	return( false );
}

