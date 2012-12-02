#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitLinkTypeDef::MindCircuitLinkTypeDef() {
}

MindCircuitLinkTypeDef::~MindCircuitLinkTypeDef() {
	neuroLinkSet.destroy();
}

void MindCircuitLinkTypeDef::createFromXml( Xml xml ) {
	// attributes
	name = xml.getAttribute( "name" );

	// neurolinks
	for( Xml xmlChild = xml.getFirstChild( "NeuroLink" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "NeuroLink" ) ) {
		// construct NeuroLink from attributes
		MindCircuitLinkDef *info = new MindCircuitLinkDef( this );
		neuroLinkSet.add( info );

		info -> createFromXml( xmlChild );
	}
}

int MindCircuitLinkTypeDef::getNeuroLinkCount() {
	return( neuroLinkSet.count() );
}

MindCircuitLinkDef *MindCircuitLinkTypeDef::getMindCircuitLinkDef( int pos ) {
	return( neuroLinkSet.get( pos ) );
}
