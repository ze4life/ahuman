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
	while( n-- )
		*sv++ = pv++ -> output;
}

int CortexSpatialPoolerItem::getDifferencePercentage( CortexSpatialPoolerItem *item , neurovt_state toleranceNeuronState ) {
	int n = item -> state.count();
	ASSERTMSG( n == state.count() , "invalid size" );
	neurovt_state *sv = item -> state.getAll();
	neurovt_state *dv = item -> state.getAll();

	int d = 0;
	for( int k = 0; k < n; k++ ) {
		neurovt_state dx = *sv++ - *dv++;
		if( dx < 0 )
			dx = -dx;
		if( dx > toleranceNeuronState )
			d++;
	}

	int pt = ( int )( ( d * (RFC_INT64)100 ) / n );
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
	while( n-- )
		sv++ -> output = *dv++;
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
		if( s[ k ] < NEURON_FIRE_THRESHOLD_pQ )
			x = 'l';
		else
			x = 'h';

		logmsg += x;
	}
	
	logmsg.trimTrailing( '0' );
	logger.logDebug( logmsg );
}
