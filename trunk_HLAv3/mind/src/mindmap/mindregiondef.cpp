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
}

void MindRegionDef::resolveReferences( MindMap *map ) {
	type = map -> getRegionTypeDefByName( typeName );
}

String MindRegionDef::getName() {
	return( name );
}

String MindRegionDef::getTypeName() {
	return( typeName );
}

MindRegionTypeDef *MindRegionDef::getType() {
	return( type );
}
