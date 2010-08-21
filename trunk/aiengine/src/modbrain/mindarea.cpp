#include "brain_impl.h"

MindArea::MindArea()
{
	lockHandle = rfc_hnd_semcreate();
	size = 0;
	sizeNotAllocated = 0;
}

MindArea::~MindArea()
{
	rfc_hnd_semdestroy( lockHandle );
}

void MindArea::attach( String id )
{
	areaId = id;

	AIBrainImpl *brain = AIBrainImpl::getInstance();
	MindMap *map = brain -> getMindMap();
	MindAreaInfo *info = map -> getAreaById( areaId );
	ASSERTMSG( info != NULL , "Unknown area id=" + areaId );

	location = info -> getLocation();
	size = location.getSize();
	sizeNotAllocated = size;
}

void MindArea::addCortex( Cortex *cortex )
{
	const BrainLocation& locationCortex = cortex -> getLocation();
	
	lock();

	// size control
	int sizeCortex = locationCortex.getSize();
	if( sizeCortex > sizeNotAllocated ) {
		unlock();
		ASSERTFAILED( "Mind area id=" + areaId + " does not have enough space: sizeCortex=" + sizeCortex + ", sizeNotAllocated=" + sizeNotAllocated );
	}

	sizeNotAllocated -= sizeCortex;

	// add to cortex list
	cortexList.add( cortex );

	unlock();

	// event to area class
	onCreateCortex( cortex );
}


