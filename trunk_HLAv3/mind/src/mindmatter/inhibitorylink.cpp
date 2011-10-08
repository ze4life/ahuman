#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class InhibitoryLink : public NeuroLink {
public:
	InhibitoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "InhibitoryLink" ); };

public:
	virtual void apply( NeuroVector *srcData );
};

/*#########################################################################*/
/*#########################################################################*/

NeuroLink *MindService::createInhibitoryLink( MindRegionLink *link ) { return( new InhibitoryLink( link ) ); };

/*#########################################################################*/
/*#########################################################################*/

InhibitoryLink::InhibitoryLink( MindRegionLink *p_regionLink ) : NeuroLink( p_regionLink ) {
	attachLogger();
}

void InhibitoryLink::apply( NeuroVector *srcData ) {
}
