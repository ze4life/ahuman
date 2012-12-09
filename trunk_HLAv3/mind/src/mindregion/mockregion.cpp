#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MockRegion::MockRegion( String p_typeName , MindArea *p_area )
:	MindRegion( p_area ) {
	typeName = p_typeName;
	attachLogger();
}

String MockRegion::getRegionType() {
	return( typeName );
}

void MockRegion::createRegion( MindRegionInfo *info ) {
	MindRegion::createRegion( info );
	logger.logDebug( String( "createRegion: created mock region original type=" + typeName ) );

	// get prototype definition
	MindRegionTypeDef *regionDef = info -> getType();
	MindRegionTypeDef *regionOriginalDef = regionDef -> getOriginalTypeDef();

	ClassList<MindRegionConnectorDef>& connectors = regionOriginalDef -> getConnectors();
	for( int k = 0; k < connectors.count(); k++ ) {
		MindRegionConnectorDef *connectorDef = connectors.get( k );
		String connectorType = connectorDef -> getType();

		if( connectorType.equals( "source" ) || connectorType.equals( "any" ) ) {
			NeuroLinkSource *source = new NeuroLinkSource;
			sourceConnectors.add( source );
			source -> create( this , connectorDef -> getId() );
			source -> setHandler( ( MindRegion::NeuroLinkSourceHandler )&MockRegion::handleGetNeuroLinkMessage );
		}

		if( connectorType.equals( "target" ) || connectorType.equals( "any" ) ) {
			NeuroLinkTarget *target = new NeuroLinkTarget;
			targetConnectors.add( target );
			target -> create( this , connectorDef -> getId() );
			target -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&MockRegion::handleApplyNeuroLinkMessage );
		}
	}
}

void MockRegion::getSourceSizes( String entity , int *p_sizeX , int *p_sizeY ) {
	*p_sizeX = 0;
	*p_sizeY = 0;
}

void MockRegion::exitRegion() {
}

void MockRegion::destroyRegion() {
}

NeuroSignalSet *MockRegion::handleApplyNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *inputSignal ) {
	return( NULL );
}

NeuroSignal *MockRegion::handleGetNeuroLinkMessage( NeuroLink *link , NeuroLinkSource *point ) {
	return( NULL );
}
