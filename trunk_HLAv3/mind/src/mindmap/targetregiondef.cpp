#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

TargetRegionDef::TargetRegionDef( TargetAreaDef *p_areaInfo ) : MindRegionDef( areaInfo , NULL ) {
	areaInfo = p_areaInfo;
	circuitInfo = NULL;
}

TargetRegionDef::~TargetRegionDef() {
	if( MindRegionDef::type != NULL )
		delete MindRegionDef::type;
}

void TargetRegionDef::defineSensorRegion( Xml xml ) {
	MindRegionDef::id = xml.getAttribute( "id" );
	MindRegionDef::target = true;
	MindRegionDef::sensor = true;

	Object::setInstance( MindRegionDef::id );

	MindRegionDef::role = MIND_REGION_ROLE_TARGETSENSOR;
	MindRegionDef::size = xml.getIntAttribute( "size" , 0 );

	// region type for sensor is the same as region itself
	TargetRegionTypeDef *regionTypeInfo = new TargetRegionTypeDef();
	regionTypeInfo -> defineSensorRegionType( areaInfo , xml );
	MindRegionDef::type = regionTypeInfo;
	MindRegionDef::typeName = regionTypeInfo -> getName();
}

void TargetRegionDef::defineEffectorRegion( Xml xml ) {
	MindRegionDef::id = xml.getAttribute( "id" );
	MindRegionDef::target = true;
	MindRegionDef::sensor = false;

	Object::setInstance( MindRegionDef::id );

	MindRegionDef::role = MIND_REGION_ROLE_TARGETEFFECTOR;
	MindRegionDef::size = xml.getIntAttribute( "size" , 0 );

	// region type for effector is the same as region itself
	TargetRegionTypeDef *regionTypeInfo = new TargetRegionTypeDef();
	regionTypeInfo -> defineEffectorRegionType( areaInfo , xml );
	MindRegionDef::type = regionTypeInfo;
	MindRegionDef::typeName = regionTypeInfo -> getName();
}

