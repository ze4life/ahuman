#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindLocalCircuitConnectionDef::MindLocalCircuitConnectionDef( MindLocalCircuitDef *p_circuit ) {
	attachLogger();

	circuitDef = p_circuit;
	type = NULL;
}

void MindLocalCircuitConnectionDef::createFromXml( Xml xml ) {
	// attributes are properties
	typeName = xml.getAttribute( "type" );

	primary = xml.getBooleanAttribute( "primary" , false );
	srcRegion = xml.getAttribute( "src" );
	dstRegion = xml.getAttribute( "dst" );

	Object::setInstance( srcRegion + "-" + dstRegion );
}

String MindLocalCircuitConnectionDef::getId() {
	return( Object::instance );
}

MindConnectionLinkTypeDef *MindLocalCircuitConnectionDef::getPrimaryLinkType() {
	return( type -> getPrimaryLink() );
}

void MindLocalCircuitConnectionDef::resolveReferences( MindMap *map ) {
	type = map -> getConnectionTypeDefByName( typeName );
	ASSERTMSG( type != NULL , "connection type=" + typeName + " not found in circuit connection src=" + srcRegion + ", dst=" + dstRegion );

	// check connection region types
	MindRegionDef *srcreg = map -> getRegionDefById( srcRegion );
	String s1 = srcreg -> getTypeName();
	String s2 = type -> getSrcRegionType();
	ASSERTMSG( s1.equals( s2 ) , "src type mismatched for connection " + srcRegion + " -> " + dstRegion + " - " + s1 + " != " + s2 );

	MindRegionDef *dstreg = map -> getRegionDefById( dstRegion );
	s1 = dstreg -> getTypeName();
	s2 = type -> getDstRegionType();
	ASSERTMSG( s1.equals( s2 ) , "dst type mismatched for connection " + srcRegion + " -> " + dstRegion + " - " + s1 + " != " + s2 );
}
