#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindConnectionTypeDef::MindConnectionTypeDef() {
}

MindConnectionTypeDef::~MindConnectionTypeDef() {
}

void MindConnectionTypeDef::createFromXml( Xml xml ) {
	// attributes
	name = xml.getAttribute( "name" );

	// links
	for( Xml xmlChild = xml.getFirstChild( "link-type" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "link-type" ) ) {
		// construct MindArea from attributes
		MindConnectionLinkTypeDef *link = new MindConnectionLinkTypeDef( this );
		link -> createFromXml( xmlChild );
		links.add( link );
		linkMap.add( link -> getName() , link );
	}
}

void MindConnectionTypeDef::resolveReferences( MindMap *map ) {
}

ClassList<MindConnectionLinkTypeDef>& MindConnectionTypeDef::getLinks() {
	return( links );
}

