#include "aihtmlib_impl.h"

const char *HtmLayer::NAME = "HtmLayer";

const int ACCEPT_WP_EXACT_LASTDECREMENTED = 1;
const int ACCEPT_WP_SHORT_LASTDECREMENTED = 2;
const int ACCEPT_WP_EXACT_NOLAST = 3;
const int ACCEPT_WP_SHORT_NOLAST = 4;
const int ACCEPT_WP_ADDED_LASTDECREMENTED = 5;
const int ACCEPT_WP_ADDED_NOLAST = 6;
const int ACCEPT_WP_NEW_IGNORED = 7;
const int ACCEPT_WP_NEW_FOUND_LOWPROBABILITY = 8;

/*#########################################################################*/
/*#########################################################################*/

HtmLayer::HtmLayer( int pos , int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source )
:	ctx( p_ctx ) ,
	outputs( p_d1 , p_d2 ) ,
	outputsPredicted( p_d1 , p_d2 ) ,
	childLayer( p_source ) ,
	maxHistoryLength( calcMaxHistoryLength( pos , p_d1 , p_d2 , p_ctx , p_source ) ) ,
	childCountH( calcChildCountH( p_d1 , p_d2 , p_ctx , p_source ) ) ,
	childCountV( calcChildCountV( p_d1 , p_d2 , p_ctx , p_source ) ) ,
	currentSequence( p_d1 , p_d2 ) ,
	memory( calcMemorySize( p_d1 , p_d2 , p_ctx , p_source ) )
{
	layerPos = pos;
	logger.attach( this );
	int childCount = childCountH * childCountV;
	highProbablePrecision = 80;

	// create current sequences for all subregions
	HtmRect rc = getRect();
	for( int v = rc.fromV; v <= rc.toV; v++ )
		for( int h = rc.fromH; h <= rc.toH; h++ )
			{
				HtmSequence *cs = currentSequence[ v ][ h ];
				cs -> create( maxHistoryLength , childCount );
			}
}

HtmLayer::~HtmLayer()
{
	currentSequence.destroy();
}

int HtmLayer::getLayerPos()
{
	return( layerPos );
}

int HtmLayer::getSizeH()
{
	return( outputs.getN1() );
}

int HtmLayer::getSizeV()
{
	return( outputs.getN2() );
}

int HtmLayer::getMaxHistory()
{
	return( maxHistoryLength );
}

int HtmLayer::calcMaxHistoryLength( int pos , int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source )
{
	if( pos == 0 )
		return( 1 );

	return( 2 );
}

int HtmLayer::calcChildCountH( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source )
{
	int cd1 = ( p_source != NULL )? p_source -> getSizeH() : p_ctx -> getInputsSizeH();
	int rate = cd1 / p_d1;
	if( rate * p_d1 < cd1 )
		rate++;
	return( rate );
}

int HtmLayer::calcChildCountV( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source )
{
	int cd2 = ( p_source != NULL )? p_source -> getSizeV() : p_ctx -> getInputsSizeV();
	int rate = cd2 / p_d2;
	if( rate * p_d2 < cd2 )
		rate++;
	return( rate );
}

int HtmLayer::calcMemorySize( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source )
{
	// calculate number of sequences to store in the memory
	return( p_d1 * p_d2 );
}

TwoIndexArray<int>& HtmLayer::getOutputs()
{
	return( outputs );
}

TwoIndexArray<int>& HtmLayer::getOutputsPredicted()
{
	return( outputsPredicted );
}

int HtmLayer::getChildSizeH()
{
	return( childCountH );
}

int HtmLayer::getChildSizeV()
{
	return( childCountV );
}

HtmRect HtmLayer::getRect()
{
	return( HtmRect( 0 , outputs.getN1() - 1 , 0 , outputs.getN2() - 1 ) );
}

HtmRect HtmLayer::getRectFromChild( const HtmRect& rcChild )
{
	int cd1 = ( childLayer != NULL )? childLayer -> getSizeH() : ctx -> getInputsSizeH();
	int cd2 = ( childLayer != NULL )? childLayer -> getSizeV() : ctx -> getInputsSizeV();

	int d1 = outputs.getN1();
	int d2 = outputs.getN2();

	int fromH = ( rcChild.fromH * d1 ) / cd1;
	int toH = ( rcChild.toH * d1 ) / cd1;
	int fromV = ( rcChild.fromV * d2 ) / cd2;
	int toV = ( rcChild.toV * d2 ) / cd2;

	if( fromH < 0 )
		fromH = 0;
	if( toH >= d1 )
		toH = d1 - 1;
	if( fromV < 0 )
		fromV = 0;
	if( toV >= d2 )
		toV = d2 - 1;
	return( HtmRect( fromH , toH , fromV , toV ) );
}

HtmRect HtmLayer::getChildRect( int h , int v )
{
	int cd1 = ( childLayer != NULL )? childLayer -> getSizeH() : ctx -> getInputsSizeH();
	int cd2 = ( childLayer != NULL )? childLayer -> getSizeV() : ctx -> getInputsSizeV();

	int hc = ( h * cd1 ) / outputs.getN1();
	int vc = ( v * cd2 ) / outputs.getN2();

	HtmRect rc( hc , hc + childCountH - 1 , vc , vc + childCountV - 1 );
	if( rc.toH >= cd1 )
		rc.toH = cd1 - 1;
	if( rc.toV >= cd2 )
		rc.toV = cd2 - 1;

	return( rc );
}

void HtmLayer::recalculate( const HtmRect& rc )
{
	int cd1 = ( childLayer != NULL )? childLayer -> getSizeH() : ctx -> getInputsSizeH();
	int cd2 = ( childLayer != NULL )? childLayer -> getSizeV() : ctx -> getInputsSizeV();
	int d1 = outputs.getN1();
	int d2 = outputs.getN2();
	TwoIndexArray<int>& inputs = ( childLayer != NULL )? childLayer -> getOutputs() : ctx -> getInputs();
	TwoIndexArray<int>& inputsPredicted = ( childLayer != NULL )? childLayer -> getOutputsPredicted() : ctx -> getInputsPredicted();

	HtmRect rcc( 0 , 0 , 0 , 0 );
	for( int v = rc.fromV; v <= rc.toV; v++ )
		{
			int *pv = outputs[ v ];
			int *pvPredicted = outputsPredicted[ v ];
			HtmSequence **pvh = currentSequence[ v ];

			rcc.fromV = ( v * cd2 ) / d2;
			rcc.toV = rcc.fromV + childCountV - 1;
			if( rcc.toV >= cd2 )
				rcc.toV = cd2 - 1;

			for( int h = rc.fromH; h <= rc.toH; h++ )
				{
					// find sequence source subregion
					rcc.fromH = ( h * cd1 ) / d1;
					rcc.toH = rcc.fromH + childCountH - 1;
					if( rcc.toH >= cd1 )
						rcc.toH = cd1 - 1;

					// generate sequence
					HtmSequence *cs = pvh[ h ];

					// predicted sequence
					int predicted = pvPredicted[ h ];

					// recognise sequence
					recalculatePoint( pv[ h ] , v , h , cs , predicted , inputs , inputsPredicted , rcc );
				}
		}

	HtmHelper helper( logger );
	helper.showLayer( String( "Layer " ) + layerPos , this );
}

void HtmLayer::recalculatePoint( int& rv , int v , int h , HtmSequence *cs , int predicted , TwoIndexArray<int>& inputs , TwoIndexArray<int>& inputsPredicted , HtmRect& rcc )
{
	// ignore pattern the same as previously seen
	if( !cs -> isNewPattern( inputs , rcc ) )
		return;							

	// start sequence if currently maximum achieved
	if( cs -> getHistoryCount() == maxHistoryLength )
		cs -> clearCurrent();

	// add pattern to sequence
	cs -> addPattern( inputs , rcc );

	// calculate output from current sequence
	int action;
	HtmSequence *csa = acceptWithoutPrediction( cs , &action );

	HtmHelper helper( logger );
	helper.showAcceptWithoutPrediction( layerPos , h , v , cs , csa , action );

	// ignore new pattern if cannot be assigned
	if( csa != NULL )
		rv = csa -> getId();
	else
		rv = 0;
}

HtmSequence *HtmLayer::acceptWithoutPrediction( HtmSequence *cs , int *action )
{
	// find last_spatial_temporal_sequence in memory
	int precision;
	int probability;
	HtmSequence *csf = memory.findLike( cs , &precision , &probability );

	if( csf != NULL )
		{
			// if found as a high-probable same-size or longer-size sequence then
			if( precision >= highProbablePrecision )
				{
					// decrement last_returned_sequence_ID if any
					int lastPrecision;
					HtmSequence *csl = cs -> getLastReturned( &lastPrecision );
					if( csl != NULL )
						{
							if( csf -> getHistoryCount() == cs -> getHistoryCount() )
								*action = ACCEPT_WP_EXACT_LASTDECREMENTED;
							else
								*action = ACCEPT_WP_SHORT_LASTDECREMENTED;
							memory.decrementUsage( csl );
						}
					else
						{
							if( csf -> getHistoryCount() == cs -> getHistoryCount() )
								*action = ACCEPT_WP_EXACT_NOLAST;
							else
								*action = ACCEPT_WP_SHORT_NOLAST;
						}

					// increment found sequence usage
					memory.incrementUsage( csf );
					// last_returned_sequence_ID = found sequence ID, last_returned_sequence_probability = found probability, return last_returned_sequence_ID
					cs -> setLastReturned( csf , precision );
					return( csf );
				}
		}

	// if able to store sequence
	int lastPrecision;
	HtmSequence *csl = cs -> getLastReturned( &lastPrecision );
	if( memory.hasSpace() )
		{
			// decrement last_returned_sequence_ID if any
			if( csl != NULL )
				{
					*action = ACCEPT_WP_ADDED_LASTDECREMENTED;
					memory.decrementUsage( csl );
				}
			else
				*action = ACCEPT_WP_ADDED_NOLAST;

			// store sequence
			// select victim to forget
			int pos = memory.selectLeastUsedPos();

			// store new sequence in memory
			HtmSequence *csn = memory.store( pos , cs );

			// last_returned_sequence_ID = stored sequence ID, last_returned_sequence_probability = 1, return last_returned_sequence_ID
			cs -> setLastReturned( csn , 100 );
			return( csn );
		}

	// if has last sequence
	if( csl != NULL )
		{
			// last_spatial_temporal_sequence = new_spatial_pattern, last_returned_sequence_probability = 0
			cs -> clearCurrentKeepLast();
			// return acceptWithoutPrediction
			return( acceptWithoutPrediction( cs , action ) );
		}

	// if nothing found
	if( csf == NULL )
		{
			// decrement random sequence - i.e. forget something
			memory.decrementUsageRandom();

			// last_returned_sequence_ID = 0, last_returned_sequence_probability = 0 
			cs -> clearCurrent();
			// ignore new pattern
			*action = ACCEPT_WP_NEW_IGNORED;
			return( NULL );
		}

	// last_returned_sequence_ID = found sequence ID, last_returned_sequence_probability = found probability, return last_returned_sequence_ID
	cs -> setLastReturned( csf , precision );
	*action = ACCEPT_WP_NEW_FOUND_LOWPROBABILITY;
	return( csf );
}

HtmLayerMemory *HtmLayer::getMemory()
{
	return( &memory );
}

void HtmLayer::serialize( SerializeObject& so )
{
}

void HtmLayer::deserialize( Object *parent , SerializeObject& so )
{
}

