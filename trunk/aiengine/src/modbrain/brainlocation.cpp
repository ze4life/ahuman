#include "brain_impl.h"

BrainLocation BrainLocation::getAbsoluteLocation( const BrainLocation& relativeLocation ) const
{
	// get lower corner
	int cx , cy , cz;
	getLowerCorner( cx , cy , cz );

	// make lower corner absolute position and center
	BrainLocation location = relativeLocation;
	location.centerByLowerCorner( location.x + cx , location.y + cy , location.z + cz );
	return( location );
}

bool BrainLocation::placeLocation( BrainLocation& cover , BrainLocation& add ) const
{
	if( cover.getSize() == 0 )
		return( placeLocationFirst( cover , add ) );
	return( false );
}

bool BrainLocation::placeLocationFirst( BrainLocation& cover , BrainLocation& add ) const
{
	// first placement - use lower left corner
	if( add.dx > dx || add.dy > dy || add.dz > dz )
		return( false );
	
	// lower corner
	int cx , cy , cz;
	getLowerCorner( cx , cy , cz );
	
	// align by lower corner
	add.centerByLowerCorner( cx , cy , cz );
	cover = add;
	return( true );
}

void BrainLocation::getLowerCorner( int& cx , int& cy , int& cz ) const
{
	cx = x - dx/2;
	cy = y - dy/2;
	cz = z - dz/2;
}

void BrainLocation::centerByLowerCorner( int cx , int cy , int cz )
{
	x = cx + dx/2;
	y = cy + dy/2;
	z = cz + dz/2;
}

