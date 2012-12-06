#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitConnectionTypeDef::MindCircuitConnectionTypeDef() {
}

MindCircuitConnectionTypeDef::~MindCircuitConnectionTypeDef() {
}

void MindCircuitConnectionTypeDef::createFromXml( Xml xml ) {
	// attributes
	name = xml.getAttribute( "name" );

	// links
	for( Xml xmlChild = xml.getFirstChild( "link-type" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "link-type" ) ) {
		// construct MindArea from attributes
		MindCircuitLinkTypeDef *link = new MindCircuitLinkTypeDef( this );
		link -> createFromXml( xmlChild );
		links.add( link );
		linkMap.add( link -> getName() , link );
	}
}

ClassList<MindCircuitLinkTypeDef>& MindCircuitConnectionTypeDef::getLinks() {
	return( links );
}

