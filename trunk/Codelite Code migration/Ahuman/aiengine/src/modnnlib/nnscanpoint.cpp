#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

NNScanPoint::NNScanPoint( NN *p_p )
:	pw( p_p )
{
	id = 0;
	statusUnknown = true;
	minimum = false;
	src = NULL;
	variance = 0;
}

NNScanPoint::NNScanPoint( NN *p_p , int p_id )
:	pw( p_p )
{
	id = p_id;
	statusUnknown = true;
	minimum = false;
	src = NULL;
	variance = 0;
}

NNScanPoint::NNScanPoint( NNScanPoint *src )
:	pw( src -> getWeights() -> getNN() )
{
	setFromPoint( src );
}

void NNScanPoint::setFromPoint( NNScanPoint *p_src )
{
	// (do not delete source objects)
	src = p_src;
	id = src -> id;

	pw.setTo( src -> getWeights() );
	statusUnknown = src -> statusUnknown;
	minimum = src -> minimum;
	variance = src -> variance;

	// copy search directions
	searchDirectionsUsed.clear();
	searchDirectionsUsed.add( src -> searchDirectionsUsed );
}

NNScanPoint *NNScanPoint::getSourcePoint()
{
	if( src == NULL )
		return( NULL );

	// check src is the same
	if( src -> id == id )
		return( src );

	// source disappeared
	src = NULL;
	return( NULL );
}

bool NNScanPoint::isSearchDirectionUsed( const char *searchDirection )
{
	return( searchDirectionsUsed.get( searchDirection ) != NULL );
}

int NNScanPoint::getId()
{ 
	return( id ); 
}

void NNScanPoint::setVariance( float value )
{ 
	variance = value; 
}

void NNScanPoint::addSearchDirection( const char *searchDirection )
{
	searchDirectionsUsed.add( searchDirection , this );
}

float NNScanPoint::getVariance() 
{ 
	return( variance ); 
}

NNWeights *NNScanPoint::getWeights() 
{ 
	return( &pw ); 
}

bool NNScanPoint::isStatusUnknown() 
{ 
	return( statusUnknown ); 
}

bool NNScanPoint::isMinimum() 
{ 
	return( minimum ); 
}

void NNScanPoint::setMinimum( bool isMinimum )
{
	statusUnknown = false;
	minimum = isMinimum;
}

void NNScanPoint::reuse( int p_id )
{
	id = p_id;
	statusUnknown = true;
	minimum = false;
	variance = 0;
	searchDirectionsUsed.clear();
}
