#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegionDef::MindRegionDef( MindAreaDef *p_area ) {
	attachLogger();
	area = p_area;
}

MindRegionDef::~MindRegionDef() {
};

void MindRegionDef::createFromXml( Xml xml ) {
	// attributes are properties
	name = xml.getAttribute( "name" );
	typeName = xml.getAttribute( "type" );
	size = xml.getIntAttribute( "size" , 0 );
}

void MindRegionDef::resolveReferences( MindMap *map ) {
	type = map -> getRegionTypeDefByName( typeName );
}

