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

	RFC_INT64 msNow = Timer::getCurrentTimeMillis();
	ts = msNow;

	for( int sk = 0; sk < sn; sk++ , sv++ ) {
		// map position
		int dk = ( int )( ( sk * (RFC_INT64)dn ) / sn );

		// get current state and update timestamp
		RFC_INT64 msPassed = msNow - sv -> updated;
		neurovt_state state = sv -> output;

		// adjust state by timestamp
		if( msPassed < NEURON_FULL_RELAX_ms ) {
			state -= ( ( neurovt_state )msPassed ) * NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms;
			if( state < 0 )
				state = 0;
		}
		else
			state = 0;

		// ignore absense of signal
		dv[ dk ] = ( state < NEURON_FIRE_OUTPUT_THRESHOLD_pQ )? 0 : NEURON_FIRE_IMPULSE_pQ;

		// clear fire state
		sv -> output = 0;
	}
}
