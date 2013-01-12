#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitConnectionDef::MindCircuitConnectionDef( MindCircuitDef *p_circuit ) {
	attachLogger();

	circuitDef = p_circuit;
	type = NULL;
}

void MindCircuitConnectionDef::createFromXml( Xml xml ) {
	// attributes are properties
	typeName = xml.getAttribute( "type" );
	Object::setInstance( typeName );

	srcRegion = xml.getAttribute( "src" );
	dstRegion = xml.getAttribute( "dst" );
}

void MindCircuitConnectionDef::resolveReferences( MindMap *map ) {
	type = map -> getConnectionTypeDefByName( typeName );
	ASSERTMSG( type != NULL , "connection type=" + typeName + " not found in circuit connection src=" + srcRegion + ", dst=" + dstRegion );
}
