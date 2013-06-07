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
	id = xml.getAttribute( "id" );
	Object::setInstance( id );

	typeName = xml.getAttribute( "type" );
	size = xml.getIntAttribute( "size" , 0 );
}

void MindRegionDef::resolveReferences( MindMap *map ) {
	type = map -> getRegionTypeDefByName( typeName );
}

