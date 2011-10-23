#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class InhibitoryLink : public NeuroLink {
public:
	InhibitoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "InhibitoryLink" ); };

public:
	virtual void apply( NeuroSignal *srcData , NeuroPool *dstPool );
};

/*#########################################################################*/
/*#########################################################################*/

NeuroLink *MindService::createInhibitoryLink( MindRegionLink *link ) { return( new InhibitoryLink( link ) ); };

/*#########################################################################*/
/*#########################################################################*/

InhibitoryLink::InhibitoryLink( MindRegionLink *p_regionLink ) : NeuroLink( p_regionLink ) {
	attachLogger();
}

void InhibitoryLink::apply( NeuroSignal *srcData , NeuroPool *dstPool ) {
	logger.logError( "apply: apply message to NeuroPool - not implemented" );
}
