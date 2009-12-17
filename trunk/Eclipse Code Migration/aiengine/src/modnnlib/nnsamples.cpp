#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class NN : public Object
NNSamples::NNSamples()
{
	nSizeIn = nSizeOut = 0;
	limitType = LIMITTYPE_EMPTY;
	maxSize = 0;
}

NNSamples::NNSamples( int nIn , int nOut )
{
	nSizeIn = nIn;
	nSizeOut = nOut;
	limitType = LIMITTYPE_EMPTY;
	maxSize = 0;
}

NNSamples::NNSamples( NN *p )
{
	nSizeIn = p -> getNSensors();
	nSizeOut = p -> getNTargets();
	limitType = LIMITTYPE_EMPTY;
	maxSize = 0;
}

NNSamples::~NNSamples()
{
	data.destroy();
}

int NNSamples::sizeIn() const
{
	return( nSizeIn );
}

int NNSamples::sizeOut() const
{
	return( nSizeOut );
}

int NNSamples::count() const
{
	return( data.count() );
}

NNSample *NNSamples::getByPos( int pos ) const
{
	return( data.getClassByIndex( pos ) );
}

NNSample *NNSamples::getById( int id ) const
{
	return( data.get( id ) );
}

void NNSamples::addSensor( float defaultValue )
{
	for( int k = 0; k < data.count(); k++ )
		data.getClassByIndex( k ) -> addSensor( defaultValue );

	nSizeIn++;
}

void NNSamples::addSensors( int count , float defaultValue )
{
	ASSERT( count > 0 );
	for( int k = 0; k < data.count(); k++ )
		data.getClassByIndex( k ) -> addSensors( count , defaultValue );

	nSizeIn += count;
}

void NNSamples::setLimitFIFO( int count )
{
	ASSERT( count > 0 && count >= data.count() );
	maxSize = count;
	limitType = LIMITTYPE_FIFO;
}

void NNSamples::setLimitRandom( int count )
{
	ASSERT( count > 0 && count >= data.count() );
	maxSize = count;
	limitType = LIMITTYPE_RANDOM;
}

int NNSamples::add( const NNSample *sample )
{
	if( limitType != LIMITTYPE_EMPTY && data.count() == maxSize )
		wipeOut();

	ASSERT( data.get( sample -> getId() ) == NULL );
	return( data.add( sample -> getId() , sample -> duplicate() ) );
}

NNSample *NNSamples::add()
{
	if( limitType != LIMITTYPE_EMPTY && data.count() == maxSize )
		wipeOut();

	NNSample *sample = new NNSample( nSizeIn , nSizeOut , true );
	data.add( sample -> getId() , sample );
	return( sample );
}

NNSample *NNSamples::add( float *sensors , float *targets )
{
	if( limitType != LIMITTYPE_EMPTY && data.count() == maxSize )
		wipeOut();

	NNSample *sample = new NNSample( nSizeIn , nSizeOut , sensors , targets );
	data.add( sample -> getId() , sample );
	return( sample );
}

void NNSamples::add( const NNSamples *samples )
{
	for( int k = 0; k < samples -> count(); k++ )
		add( samples -> getByPos( k ) );
}

void NNSamples::getSensorRange( int pos , float *vMin , float *vMax ) const
{
	getValueRange( pos , vMin , vMax , true );
}

void NNSamples::getTargetRange( int pos , float *vMin , float *vMax ) const
{
	getValueRange( pos , vMin , vMax , false );
}

void NNSamples::getValueRange( int pos , float *vMin , float *vMax , bool sensors ) const
{
	float l_vMin = 0;
	float l_vMax = 0;

	for( int s = 0; s < count(); s++ )
		{
			NNSample *sample = getByPos( s );

			// output
			float *values = ( sensors )? sample -> getSensors() : sample -> getTargets();
			float v = values[ pos ];
			if( s == 0 || v < l_vMin )
				l_vMin = v;
			if( s == 0 || v > l_vMax )
				l_vMax = v;
		}

	*vMin = l_vMin;
	*vMax = l_vMax;
}

void NNSamples::getSensorStat( int pos , float *vMean , float *vStddev ) const
{
	getValueStat( pos , vMean , vStddev , true );
}

void NNSamples::getTargetStat( int pos , float *vMean , float *vStddev ) const
{
	getValueStat( pos , vMean , vStddev , false );
}

void NNSamples::getValueStat( int pos , float *vMean , float *vStddev , bool sensors ) const
{
	// find mean
	float mean = 0;
	int s;
	for( s = 0; s < count(); s++ )
		{
			NNSample *sample = getByPos( s );

			// input
			float *values = ( sensors )? sample -> getSensors() : sample -> getTargets();
			float v = values[ pos ];
			mean += v;
		}
	mean /= count();

	// find stddev
	float stddev = 0;
	for( s = 0; s < count(); s++ )
		{
			NNSample *sample = getByPos( s );

			// input
			float *values = ( sensors )? sample -> getSensors() : sample -> getTargets();
			float v = values[ pos ];
			stddev += ( v - mean ) * ( v - mean );
		}
	stddev = sqrt( stddev / count() );

	*vMean = mean;
	*vStddev = stddev;
}

void NNSamples::clear()
{
	data.destroy();
}

void NNSamples::clearLearnData()
{
	for( int k = 0; k < data.count(); k++ )
		data.getClassByIndex( k ) -> clearLearnData();
}

void NNSamples::clearValidateData()
{
	for( int k = 0; k < data.count(); k++ )
		data.getClassByIndex( k ) -> clearValidateData();
}

NNSamples *NNSamples::duplicate() const
{
	return( copy( 0 , count() - 1 ) );
}

NNSamples *NNSamples::copy( int posFrom , int posTo ) const
{
	ASSERT( posFrom >= 0 );
	ASSERT( posTo < count() );

	NNSamples *x = new NNSamples( nSizeIn , nSizeOut );
	for( int s = posFrom; s <= posTo; s++ )
		{
			NNSample *sample = getByPos( s );
			x -> add( sample );
		}

	return( x );
}

void NNSamples::merge( NNSamples *src )
{
	ASSERT( src -> nSizeIn == nSizeIn );
	ASSERT( src -> nSizeOut == nSizeOut );

	for( int s = 0; s < src -> count(); s++ )
		{
			NNSample *sample = src -> getByPos( s );
			if( getById( sample -> getId() ) != NULL )
				continue;

			add( sample );
		}
}

void NNSamples::wipeOut()
{
	// find remove position
	int pos;
	switch( limitType )
		{
			case LIMITTYPE_FIFO :
				pos = 0;
				break;
			case LIMITTYPE_RANDOM :
				pos = Random::getRandomIntStatic( 0 , data.count() - 1 );
				break;
			default :
				ASSERT( false );
		}

	NNSample *sample = data.removeByPos( pos );
	delete sample;
}

// Object interface
const char *NNSamples::NAME = "NNSamples";

void NNSamples::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNSamples::onCreate );

	so -> addFieldInt( "nSizeIn" );
	so -> addFieldInt( "nSizeOut" );
	so -> addFieldObjectList( "sampleList" , NNSample::getSerializeObject() );
	so -> addFieldInt( "limitType" );
	so -> addFieldInt( "maxSize" );
}

void NNSamples::serialize( SerializeObject& so )
{
	so.setPropInt( nSizeIn , "nSizeIn" );
	so.setPropInt( nSizeOut , "nSizeOut" );

	ClassList<NNSample> list;
	data.copyTo( list );
	so.setPropObjectList( ( ClassList<Object>& )list , "sampleList" , false );

	so.setPropInt( limitType , "limitType" );
	so.setPropInt( maxSize , "maxSize" );
}

void NNSamples::deserialize( Object *parent , SerializeObject& so )
{
	clear();

	nSizeIn = so.getPropInt( "nSizeIn" );
	nSizeOut = so.getPropInt( "nSizeOut" );
	
	ClassList<NNSample> va;
	so.getPropObjectList( ( ClassList<Object>& )va , "sampleList" , true );

	for( int k = 0; k < va.count(); k++ )
		{
			NNSample *sample = va.get( k );
			data.add( sample -> getId() , sample );
		}

	limitType = ( LimitType )so.getPropInt( "limitType" );
	maxSize = so.getPropInt( "maxSize" );
}
