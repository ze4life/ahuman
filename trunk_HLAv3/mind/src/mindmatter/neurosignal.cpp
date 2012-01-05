#include <ah_mind.h>
#include <ah_mind_impl.h>

static const int DEFAULT_ARRAY_SIZE = 256;

/*#########################################################################*/
/*#########################################################################*/

NeuroSignal::NeuroSignal() {
	ts = 0;
	sizeX = 0;
	sizeY = 0;
}

NeuroSignal::NeuroSignal( int p_sizeX , int p_sizeY ) {
	ts = 0;
	sizeX = p_sizeX;
	sizeY = p_sizeY;
	data.allocate( DEFAULT_ARRAY_SIZE );
}

NeuroSignal::NeuroSignal( NeuroSignal *src ) {
	id = src -> id;
	ts = src -> ts;
	sizeX = src -> sizeX;
	sizeY = src -> sizeY;
	data.copy( src -> data );
}

NeuroSignal::~NeuroSignal() {
}

int *NeuroSignal::getIndexRawData() {
	return( data.getAll() );
}

void NeuroSignal::create( int p_sizeX , int p_sizeY ) {
	sizeX = p_sizeX;
	sizeY = p_sizeY;
	data.allocate( DEFAULT_ARRAY_SIZE );
	data.clear();
}

void NeuroSignal::setTs( RFC_INT64 p_ts ) {
	ts = p_ts;
}

void NeuroSignal::setId( String p_id ) {
	id = p_id;
}

String NeuroSignal::getId() {
	return( id );
}

void NeuroSignal::getSizeInfo( int *nx , int *ny ) {
	*nx = sizeX;
	*ny = sizeY;
}

int NeuroSignal::getMaxSize() {
	return( sizeX * sizeY );
}

int NeuroSignal::getDataSize() {
	return( data.count() );
}

void NeuroSignal::createFromPool( NeuroPool *pool ) {
	int snx , sny;
	pool -> getNeuronDimensions( &snx , &sny );
	int sn = snx * sny;
	TwoIndexArray<NEURON_DATA>& poolData = pool -> getNeuronData();

	create( snx , sny );
	data.clear();
	int *dv = data.getAll();
	int aSig = data.size();
	int nSig = 0;

	// copy activated pool data to signal data
	NEURON_DATA *sv = poolData.getData();

	RFC_INT64 msNow = Timer::getCurrentTimeMillis();
	ts = msNow;

	for( int sk = 0; sk < sn; sk++ , sv++ ) {
		// get current state and update timestamp
		RFC_INT64 msPassed = msNow - sv -> updated_fs;
		neurovt_state state = sv -> output;

		// adjust state by timestamp
		if( msPassed < NEURON_FULL_RELAX_ms ) {
			state -= ( ( neurovt_state )msPassed ) * NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms;
			if( state < 0 )
				state = 0;
		}
		else
			state = 0;

		// process only at or above threshold
		if( state >= NEURON_FIRE_OUTPUT_THRESHOLD_pQ ) {
			// clear fire state
			sv -> output = -NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms * NEURON_FIRE_OUTPUT_SILENT_ms;

			// allocate signal data
			if( nSig == aSig ) {
				aSig *= 2;
				data.allocate( aSig );
				dv = data.getAll();
			}

			// add to signal
			*dv++ = sk;
			nSig++;
		}
	}

	data.setCount( nSig );
}

String NeuroSignal::getBinaryDataString() {
	int sn = data.count();
	String ds;

	String sz = "0";
	for( int k = 0; k < sn; k++ ) {
		int idx = data.get( k );

		// zeros before
		int nz = ( k == 0 )? data.get( k ) : data.get( k ) - data.get( k - 1 ) - 1; 
		if( nz > 0 )
			ds += sz.replicate( nz );

		ds += '1';
	}

	return( ds );
}

String NeuroSignal::getNumberDataString() {
	int sn = data.count();
	String ds;

	for( int k = 0; k < sn; k++ ) {
		int idx = data.get( k );
		if( k > 0 )
			ds += ".";

		ds += idx;
	}

	return( ds );
}

void NeuroSignal::clearData() {
	data.clear();
}

void NeuroSignal::addIndexData( int index ) {
	data.add( index );
}

void NeuroSignal::removeNotFiringIndexes() {
	int *rp = data.getAll();
	int *wp = rp;
	int n = data.count();

	// skip equal
	while( n ) {
		if( *rp++ < 0 ) {
			rp--;
			break;
		}
		n--;
	}

	wp = rp;

	// remove count
	int rc = 0;
	int v;

	while( n-- ) {
		if( ( v = *rp++ ) >= 0 )
			*wp++ = v;
		else
			rc++;
	}

	if( rc > 0 )
		data.setCount( data.count() - rc );
}
