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

void CortexSpatialPoolerItem::setStateFromPool( NeuroPool *pool ) {
	TwoIndexArray<NEURON_DATA>& nd = pool -> getNeuronData();
	int n = nd.getN1() * nd.getN2();
	NEURON_DATA *pv = nd.getData();

	state.setCount( n );
	neurovt_state *sv = state.getAll();

	RFC_INT64 msNow = Timer::getCurrentTimeMillis();
	while( n-- ) {
		// get state
		neurovt_state state = pv -> output;

		// adjust by timestamp
		RFC_INT64 msPassed = msNow - pv -> updated;
		if( msPassed < NEURON_FULL_RELAX_ms ) {
			state -= ( ( neurovt_state )msPassed ) * NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms;
			if( state < 0 )
				state = 0;
		}
		else
			state = 0;

		pv++;

		// copy state
		*sv++ = state;
	}
}

int CortexSpatialPoolerItem::getDifferencePercentage( CortexSpatialPoolerItem *item , neurovt_state toleranceNeuronState ) {
	int n = item -> state.count();
	ASSERTMSG( n == state.count() , "invalid size" );
	neurovt_state *sv = item -> state.getAll();
	neurovt_state *dv = state.getAll();

	int d = 0;
	int cn = n;
	neurovt_state vx;
	for( int k = 0; k < n; k++ ) {
		neurovt_state dx = ( vx = *sv++ ) - *dv++;
		if( dx < 0 )
			dx = -dx;
		if( dx == 0 ) {
			if( vx == 0 )
				cn--;
		}
		else
		if( dx > toleranceNeuronState )
			d++;
	}

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
	int n = nd.getN1() * nd.getN2();
	NEURON_DATA *sv = nd.getData();

	state.setCount( n );
	neurovt_state *dv = state.getAll();

	RFC_INT64 msNow = Timer::getCurrentTimeMillis();
	while( n-- ) {
		sv -> output = *dv++;
		sv++ -> updated = msNow;
	}
}

void CortexSpatialPoolerItem::logItem() {
	String logmsg = "id=";
	logmsg += id;
	logmsg += ", usage=";
	logmsg += usage;
	logmsg += ", state=";

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

		logmsg += x;
	}
	
	logmsg.trimTrailing( '0' );
	logger.logDebug( logmsg );
}
