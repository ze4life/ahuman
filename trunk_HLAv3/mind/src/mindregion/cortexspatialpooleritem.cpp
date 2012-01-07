#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

CortexSpatialPoolerItem::CortexSpatialPoolerItem() {
	attachLogger();

	id = -1;
	usage = 0;
}

void CortexSpatialPoolerItem::setId( int p_id ) {
	id = p_id;
}

int CortexSpatialPoolerItem::setStateFromPool( NeuroPool *pool ) {
	TwoIndexArray<NEURON_DATA>& nd = pool -> getNeuronData();
	int n = nd.getN1() * nd.getN2();
	NEURON_DATA *sv = nd.getData();

	state.setCount( n );
	neurovt_state *dv = state.getAll();

	RFC_INT64 msNow = Timer::getCurrentTimeMillis();
	int cn = 0;
	while( n-- ) {
		// get state
		neurovt_state state = sv -> output;

		// adjust by timestamp
		RFC_INT64 msPassed = msNow - sv -> updated_fs;
		if( msPassed < NEURON_FULL_RELAX_ms ) {
			state -= ( ( neurovt_state )msPassed ) * NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms;
			if( state < 0 )
				state = 0;
		}
		else
			state = 0;

		sv++;

		// copy state
		*dv++ = state;
		if( state > 0 )
			cn++;
	}

	return( cn );
}

void CortexSpatialPoolerItem::setStateFromSignal( NeuroSignal *signal ) {
	int *sv = signal -> getIndexRawData();
	int sn = signal -> getDataSize();
	ASSERTMSG( sn > 0 , "invalid signal" );

	// resize and init to zero values
	state.setCount( sv[ sn - 1 ] + 1 );
	state.set( 0 );

	// update from signal
	neurovt_state *dv = state.getAll();
	while( sn-- ) {
		int index = *sv++;
		dv[ index ] = NEURON_FIRE_OUTPUT_THRESHOLD_pQ;
	}
}

int CortexSpatialPoolerItem::getDifferencePercentage( CortexSpatialPoolerItem *item , neurovt_state toleranceNeuronState ) {
	int sn = item -> state.count();
	int vn = state.count();
	neurovt_state *sv = item -> state.getAll();
	neurovt_state *dv = state.getAll();

	int d = 0;
	int maxn = max( sn , vn );
	int minn = min( sn , vn );
	neurovt_state vx;
	neurovt_state dx;
	int cn = maxn;
	for( int k = 0; k < maxn; k++ ) {
		if( k < minn ) {
			dx = ( vx = *sv++ ) - *dv++;
			if( dx < 0 )
				dx = -dx;
		}
		else {
			vx = 0;
			if( k >= sn ) 
				dx = *dv++;
			else
				dx = *sv++;
		}

		if( dx == 0 ) {
			if( vx == 0 )
				cn--;
		}
		else
		if( dx > toleranceNeuronState )
			d++;
	}

	ASSERTMSG( cn > 0 , "all item neurons are silent" );
	int pt = ( d * 100 ) / cn;
	return( pt );
}

int CortexSpatialPoolerItem::getId() {
	return( id );
}

int CortexSpatialPoolerItem::getUsage() {
	return( usage );
}

void CortexSpatialPoolerItem::addUsage() {
	usage++;
}

void CortexSpatialPoolerItem::getPoolFromState( NeuroPool *pool ) {
	TwoIndexArray<NEURON_DATA>& nd = pool -> getNeuronData();
	NEURON_DATA *dv = nd.getData();

	neurovt_state *sv = state.getAll();
	int n = state.count();

	RFC_INT64 msNow = Timer::getCurrentTimeMillis();
	while( n-- ) {
		dv -> output = *sv++;
		dv++ -> updated_fs = msNow;
	}
}

void CortexSpatialPoolerItem::getSignalFromState( NeuroSignal *signal ) {
	neurovt_state *dv = state.getAll();

	RFC_INT64 msNow = Timer::getCurrentTimeMillis();
	int n = state.count();
	
	for( int k = 0; k < n; k++ , dv++ ) {
		if( *dv >= NEURON_FIRE_OUTPUT_THRESHOLD_pQ )
			signal -> addIndexData( k );
	}
}

void CortexSpatialPoolerItem::logItem() {
	LOGDEBUG( String( "id=" ) +  id + ", usage=" + usage + ", state=" + getBinaryState() );
}

String CortexSpatialPoolerItem::getBinaryState() {
	String ps;

	neurovt_state *s = state.getAll();
	int n = state.count();
	for( int k = 0; k < n; k++ ) {
		char x;
		if( s[ k ] == 0 )
			x = '0';
		else
		if( s[ k ] < NEURON_FIRE_OUTPUT_THRESHOLD_pQ )
			x = 'l';
		else
			x = 'h';

		ps += x;
	}
	
	ps.trimTrailing( '0' );
	return( ps );
}

String CortexSpatialPoolerItem::getNumberedState() {
	String ps;

	neurovt_state *s = state.getAll();

	bool first = true;
	int n = state.count();
	for( int k = 0; k < n; k++ ) {
		if( s[ k ] == 0 )
			continue;

		if( first )
			first = false;
		else
			ps += ".";

		ps += k;
		if( s[ k ] < NEURON_FIRE_OUTPUT_THRESHOLD_pQ )
			ps += 'l';
	}
	
	return( ps );
}
