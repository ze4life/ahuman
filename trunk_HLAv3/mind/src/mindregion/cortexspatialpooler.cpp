#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

CortexSpatialPooler::CortexSpatialPooler() {
	attachLogger();

	maxPoolSize = 0;
	patternSizeX = 0;
	patternSizeY = 0;

	matchTolerancePattern = 0;
	matchToleranceNeuronState = 0;
	protectedUsage = 0;
}

CortexSpatialPooler::~CortexSpatialPooler() {
	items.destroy();
}

void CortexSpatialPooler::create( int p_poolSize , int sizeX , int sizeY ) {
	maxPoolSize = p_poolSize;
	patternSizeX = sizeX;
	patternSizeY = sizeY;
}

void CortexSpatialPooler::setMatchTolerance( int tolerancePattern , int toleranceNeuronState ) {
	matchTolerancePattern = tolerancePattern;
	matchToleranceNeuronState = toleranceNeuronState;
}

void CortexSpatialPooler::setProtectedUsage( int usage ) {
	protectedUsage = usage;
}

int CortexSpatialPooler::matchPattern( NeuroPool *p_pool , int *patternForgotten ) {
	CortexSpatialPoolerItem *item = new CortexSpatialPoolerItem();
	item -> setStateFromPool( p_pool );

	// find closest match
	int difference;
	CortexSpatialPoolerItem *bestItem = findBestMatch( item , &difference );
	if( bestItem != NULL ) {
		if( difference <= matchTolerancePattern ) {
			delete item;
			bestItem -> addUsage();
			*patternForgotten = -1;
			return( bestItem -> getId() );
		}
	}

	// check free space
	if( items.count() < maxPoolSize ) {
		// add item
		int id = items.add( item );
		item -> setId( id );
		item -> addUsage();
		*patternForgotten = -1;
		return( id );
	}

	// check can free some
	CortexSpatialPoolerItem *leastUsed = findLeastUsed();
	if( leastUsed -> getUsage() >= protectedUsage ) {
		delete item;
		*patternForgotten = -1;
		return( -1 );
	}

	// free (replace)
	int id = leastUsed -> getId();
	item -> setId( id );
	item -> addUsage();
	items.set( id , item );
	delete leastUsed;

	*patternForgotten = id;
	return( id );
}

bool CortexSpatialPooler::getPattern( int pattern , NeuroPool *p_pool ) {
	if( items.count() <= pattern )
		return( false );

	CortexSpatialPoolerItem *item = items[ pattern ];
	item -> getPoolFromState( p_pool );
	return( true );
}

CortexSpatialPoolerItem *CortexSpatialPooler::findBestMatch( CortexSpatialPoolerItem *data , int *difference ) {
	int minDiffValue = 0;
	CortexSpatialPoolerItem *minDiffItem = NULL;
	for( int k = 0; k < items.count(); k++ ) {
		// get difference
		CortexSpatialPoolerItem *item = items[ k ];
		int diff = item -> getDifferencePercentage( data , matchToleranceNeuronState );
		if( minDiffItem == NULL || diff < minDiffValue ) {
			minDiffItem = item;
			minDiffValue = diff;
		}
	}

	*difference = minDiffValue;
	return( minDiffItem );
}

CortexSpatialPoolerItem *CortexSpatialPooler::findLeastUsed() {
	int minUsageValue = 0;
	CortexSpatialPoolerItem *minUsageItem = NULL;
	for( int k = 0; k < items.count(); k++ ) {
		// get usage
		CortexSpatialPoolerItem *item = items[ k ];
		int usage = item -> getUsage();
		if( minUsageItem == NULL || usage < minUsageValue ) {
			minUsageItem = item;
			minUsageValue = usage;
		}
	}
	return( minUsageItem );
}

void CortexSpatialPooler::logItems() {
	logger.logDebug( String( "logItems: spatial pooler items, total=" ) + items.count() );
	for( int k = 0; k < items.count(); k++ ) {
		CortexSpatialPoolerItem *item = items[ k ];
		item -> logItem();
	}
}
