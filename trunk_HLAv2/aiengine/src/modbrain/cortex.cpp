#include "brain_impl.h"

Cortex::Cortex( const char *p_netType , MindArea *p_area , const CortexIOSizeInfo& p_ioSizeInfo )
{
	netType = p_netType;
	area = p_area;
	ioSizeInfo = p_ioSizeInfo;

	if( ioSizeInfo.nInputsDim1 == 0 || ioSizeInfo.nInputsDim2 == 0 ) {
		int dx = ( int )sqrt( ( double )ioSizeInfo.nInputs );
		if( dx * dx < ioSizeInfo.nInputs )
			dx++;
		ioSizeInfo.nInputsDim1 = ioSizeInfo.nInputsDim2 = dx;
	}

	if( ioSizeInfo.nOutputsDim1 == 0 || ioSizeInfo.nOutputsDim2 == 0 ) {
		int dx = ( int )sqrt( ( double )ioSizeInfo.nOutputs );
		if( dx * dx < ioSizeInfo.nOutputs )
			dx++;
		ioSizeInfo.nOutputsDim1 = ioSizeInfo.nOutputsDim2 = dx;
	}
	
	neuronsUsed = 0;

	inputs = ( ioSizeInfo.nInputs > 0 )? ( cortexvt * )calloc( ioSizeInfo.nInputs , sizeof( cortexvt ) ) : NULL;
	outputs = ( ioSizeInfo.nOutputs > 0 )? ( cortexvt * )calloc( ioSizeInfo.nOutputs , sizeof( cortexvt ) ) : NULL;
};

void Cortex::processInputsUpdated()
{
	onCortexRun();
}

void Cortex::processOutputsUpdated()
{
	if( ioSizeInfo.nOutputs <= 0 )
		return;

	// distribute over links
	ClassList<MindLink>& links = area -> getMindLinks();
	for( int k = links.count() - 1; k >= 0; k-- ) {
		MindLink *link = links.get( k );

		// ignore non-source area
		if( link -> getSourceArea() != area )
			continue;

		// pass message to the channel
		link -> transferOutputs( this );
	}
}

void Cortex::setAreaLocation( const BrainLocation& p_location )
{
	// set cortex location 
	areaLocation = p_location;

	// adjust location of inputs
	inputsSurface = areaLocation.getInputsSurface();
	inputsSurface.setSurfaceDimensions( ioSizeInfo.nInputsDim1 , ioSizeInfo.nInputsDim2 );
	inputsSurface.center( areaLocation.getInputsSurface() );

	outputsSurface = areaLocation.getOutputsSurface();
	outputsSurface.setSurfaceDimensions( ioSizeInfo.nOutputsDim1 , ioSizeInfo.nOutputsDim2 );
	outputsSurface.center( areaLocation.getOutputsSurface() );

	// derive number of neurons as volume
	neuronsUsed = areaLocation.getSize();
}

