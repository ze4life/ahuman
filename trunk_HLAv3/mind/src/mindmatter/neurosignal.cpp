#include <ah_mind.h>
#include <ah_mind_impl.h>

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

int NeuroSignal::getSize() {
	return( data.getN1() * data.getN2() );
}

void NeuroSignal::createFromPool( NeuroPool *pool ) {
	int snx , sny;
	pool -> getNeuronDimensions( &snx , &sny );
	int sn = snx * sny;
	TwoIndexArray<NEURON_DATA>& poolData = pool -> getNeuronData();

	int dnx = data.getN1();
	int dny = data.getN2();
	int dn = dnx * dny;

	// project pool data to signal data
	NEURON_DATA *sv = poolData.getData();
	neurovt_signal *dv = data.getData();

	for( int sk = 0; sk < sn; sk++ , sv++ ) {
		// map position
		int dk = ( int )( ( sk * (RFC_INT64)dn ) / sn );

		// ignore absense of signal
		dv[ dk ] = ( sv -> output == 0 )? 0 : NEURON_FIRE_IMPULSE_pQ;

		// clear fire state
		sv -> output = 0;
	}
}
