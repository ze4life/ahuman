#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class ExcitatoryLink : public NeuroLink {
public:
	ExcitatoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "ExcitatoryLink" ); };

public:
	virtual void apply( NeuroVector *srcData , NeuroPool *dstPool );
};

/*#########################################################################*/
/*#########################################################################*/

NeuroLink *MindService::createExcitatoryLink( MindRegionLink *link ) { return( new ExcitatoryLink( link ) ); };

/*#########################################################################*/
/*#########################################################################*/

ExcitatoryLink::ExcitatoryLink( MindRegionLink *p_regionLink ) : NeuroLink( p_regionLink ) {
	attachLogger();
}

void ExcitatoryLink::apply( NeuroVector *srcData , NeuroPool *dstPool ) {
	// map source surface to target surface
	int dnx , dny;
	dstPool -> getNeuronDimensions( &dnx , &dny );

	// project source to target
	dstPool -> startProjection( this );

	// project speicifc values
	TwoIndexArray<neurovt>& src = srcData -> getVectorData();
	int snx , sny;
	srcData -> getSizeInfo( &snx , &sny );
	neurovt *sv = srcData -> getRawData();

	bool srcDrivenX = ( snx < dnx );
	bool srcDrivenY = ( sny < dny );
	int maxX = ( srcDrivenX )? snx : dnx;
	int maxY = ( srcDrivenY )? sny : dny;
	for( int kx = 0; kx < maxX; kx++ ) {
		// map x position
		int sx = ( srcDrivenX )? kx : ( kx * snx / dnx );
		int dx = ( srcDrivenX )? ( kx * dnx / snx ) : kx;

		for( int ky = 0; ky < maxY; ky++ ) {
			// map y position
			int sy = ( srcDrivenY )? ky : ( ky * sny / dny );
			int dy = ( srcDrivenY )? ( ky * dny / sny ) : ky;

			// get value and project
			neurovt value = sv[ sy * snx + sx ];
			dstPool -> executeProjection( this , dx , dy , value );
		}
	}

	// finish projection
	dstPool -> finishProjection( this );
}
