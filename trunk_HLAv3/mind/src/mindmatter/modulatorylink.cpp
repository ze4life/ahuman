#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class ModulatoryLink : public NeuroLink {
public:
	ModulatoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "ModulatoryLink" ); };

public:
	virtual void apply( NeuroVector *srcData );
};

/*#########################################################################*/
/*#########################################################################*/

NeuroLink *MindService::createModulatoryLink( MindRegionLink *link ) { return( new ModulatoryLink( link ) ); };

/*#########################################################################*/
/*#########################################################################*/

ModulatoryLink::ModulatoryLink( MindRegionLink *p_regionLink ) : NeuroLink( p_regionLink ) {
	attachLogger();
}

void ModulatoryLink::apply( NeuroVector *srcData ) {
}
