#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroSignal::NeuroSignal() {
}

NeuroSignal::NeuroSignal( int sizeX , int sizeY ) {
	data.create( sizeX , sizeY );
}

NeuroSignal::NeuroSignal( NeuroSignal *src ) {
	data.copy( src -> getVectorData() );
}

NeuroSignal::~NeuroSignal() {
}

void NeuroSignal::create( int sizeX , int sizeY ) {
	data.create( sizeX , sizeY );
}

neurovt_signal *NeuroSignal::getRawData() {
	return( data.getData() );
}

TwoIndexArray<neurovt_signal>& NeuroSignal::getVectorData() {
	return( data );
}

void NeuroSignal::getSizeInfo( int *nx , int *ny ) {
	*nx = data.getN1();
	*ny = data.getN2();
}

void NeuroSignal::createFromPool( NeuroPool *pool ) {
	const neurovt_state NEURON_FIRE_IMPULSE_pQ = ( neurovt_state )10;

	int snx , sny;
	pool -> getNeuronDimensions( &snx , &sny );
	TwoIndexArray<NEURON_DATA>& poolData = pool -> getNeuronData();

	int dnx = data.getN1();
	int dny = data.getN2();

	// project pool data to signal data
	NEURON_DATA *sv = poolData.getData();
	neurovt_signal *dv = data.getData();

	bool generateOutputs = false;

	bool srcDrivenX = ( snx < dnx );
	bool srcDrivenY = ( sny < dny );
	int maxX = ( srcDrivenX )? snx : dnx;
	int maxY = ( srcDrivenY )? sny : dny;
	for( int kx = 0; kx < maxX; kx++ ) {
		// map x position
		int sx = ( srcDrivenX )? kx : ( kx * snx / dnx );
		int dx = ( srcDrivenX )? ( kx * dnx / snx ) : kx;

		for( int ky = 0; ky < maxY; ky++ ) {
			// map y position
			int sy = ( srcDrivenY )? ky : ( ky * sny / dny );
			int dy = ( srcDrivenY )? ( ky * dny / sny ) : ky;

			// get value and project
			int spos = sy * snx + sx;
			NEURON_DATA& actionPotential = sv[ spos ];

			// ignore absense of signal
			int dpos = dy * dnx + dx;
			dv[ dpos ] = ( actionPotential.output == 0 )? 0 : NEURON_FIRE_IMPULSE_pQ;
		}
	}
}

