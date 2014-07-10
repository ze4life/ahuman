#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindServiceDef::MindServiceDef( MindAreaDef *p_area ) {
	attachLogger();
	area = p_area;
}

MindServiceDef::~MindServiceDef() {
};

void MindServiceDef::createFromXml( Xml xml ) {
	// attributes are properties
	serviceId = xml.getAttribute( "id" );
	Object::setInstance( serviceId );

	serviceName = xml.getAttribute( "name" );

	// read regions
	for( Xml xmlChild = xml.getFirstChild( "region" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "region" ) ) {
		// construct MindArea from attributes
		MindRegionDef *region = new MindRegionDef( area );
		region -> createFromXml( xmlChild );
		regionMap.add( region -> getId() , region );
		area -> addRegion( region );
	}
}
