#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindLinkType::MindLinkType() {
}

MindLinkType::~MindLinkType() {
	neuroLinks.destroy();
}

void MindLinkType::createFromXml( Xml xml ) {
	// attributes
	name = xml.getAttribute( "name" );

	// neurolinks
	for( Xml xmlChild = xml.getFirstChild( "NeuroLink" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "NeuroLink" ) ) {
		// construct NeuroLink from attributes
		NeuroLinkInfo *info = new NeuroLinkInfo( this );
		neuroLinks.add( info );

		info -> createFromXml( xmlChild );

		// get link name
		String name = info -> getName();
		ASSERTMSG( !name.isEmpty() , "neurolink is not defined: " + xmlChild.serialize() );
		ASSERTMSG( neuroLinkMap.get( name ) == NULL , name + ": neurolink duplicate found for name=" + name );

		// add
		neuroLinkMap.add( name , info );
	}
}

int MindLinkType::getNeuroLinkCount() {
	return( neuroLinkMap.count() );
}

NeuroLinkInfo *MindLinkType::getNeuroLinkInfo( int pos ) {
	return( neuroLinkMap.getClassByIndex( pos ) );
}
