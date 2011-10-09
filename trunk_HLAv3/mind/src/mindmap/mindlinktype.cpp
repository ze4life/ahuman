#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindLinkType::MindLinkType() {
}

MindLinkType::~MindLinkType() {
	neuroLinkSet.destroy();
}

void MindLinkType::createFromXml( Xml xml ) {
	// attributes
	name = xml.getAttribute( "name" );

	// neurolinks
	for( Xml xmlChild = xml.getFirstChild( "NeuroLink" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "NeuroLink" ) ) {
		// construct NeuroLink from attributes
		NeuroLinkInfo *info = new NeuroLinkInfo( this );
		neuroLinkSet.add( info );

		info -> createFromXml( xmlChild );
	}
}

int MindLinkType::getNeuroLinkCount() {
	return( neuroLinkSet.count() );
}

NeuroLinkInfo *MindLinkType::getNeuroLinkInfo( int pos ) {
	return( neuroLinkSet.get( pos ) );
}
