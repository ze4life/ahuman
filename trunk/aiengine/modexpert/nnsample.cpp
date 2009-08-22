#include "aiexpert_impl.h"

int NNSample::nIDLast = 0;

/*#########################################################################*/
/*#########################################################################*/

NNSample::NNSample()
{
	clearLearnData();
	id = 0;
	clusterID = 0;
}

NNSample::NNSample( int nSizeIn , int nSizeOut , bool createID )
{
	sensors.create( nSizeIn );
	targets.create( nSizeOut );
	clusterID = 0;

	clearLearnData();

	if( createID )
		id = ++nIDLast;
}

NNSample::NNSample( int nSizeIn , int nSizeOut , float *p_sensors , float *p_targets )
{
	clusterID = 0;
	clearLearnData();

	sensors.set( p_sensors , nSizeIn );
	targets.set( p_targets , nSizeOut );

	id = ++nIDLast;
}

NNSample::~NNSample()
{
}

int NNSample::getId() const
{
	return( id );
}

float *NNSample::getSensors() const
{
	return( sensors.getAll() );
}

float *NNSample::getTargets() const
{
	return( targets.getAll() );
}

void NNSample::setError( float v )
{
	lastError = v;
}

float NNSample::getError() const
{
	return( lastError );
}

int NNSample::getClusterID() const
{
	return( clusterID );
}

void NNSample::setClusterID( int cluster )
{
	clusterID = cluster;
}

void NNSample::clearLearnData()
{
	lastError = 0;
	clearValidateData();
}

void NNSample::clearValidateData()
{
	lastValidateFailed = false;
	lastValidateError = 0;
}

void NNSample::setValidateFailed( float error )
{
	lastValidateFailed = true;
	lastValidateError = error;
}

bool NNSample::isValidateFailed() const
{
	return( lastValidateFailed );
}

float NNSample::getValidateError() const
{
	return( lastValidateError );
}

void NNSample::setSensors( const float *values )
{
	sensors.set( values , sensors.count() );
}

void NNSample::setTargets( const float *values )
{
	targets.set( values , targets.count() );
}

NNSample *NNSample::duplicate() const
{
	NNSample *x = new NNSample();

	x -> sensors.set( sensors.getAll() , sensors.count() );
	x -> targets.set( targets.getAll() , targets.count() );
	x -> clusterID = clusterID;

	x -> id = id;
	x -> lastError = lastError;

	return( x );
}

void NNSample::addSensor( float defaultValue )
{
	sensors.add( defaultValue );
}

void NNSample::addSensors( int count , float defaultValue )
{
	sensors.add( count , defaultValue );
}

int NNSample::getNSensors() const
{
	return( sensors.count() );
}

int NNSample::getNTargets() const
{
	return( targets.count() );
}

// Object interface
const char *NNSample::NAME = "NNSample";

void NNSample::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNSample::onCreate );

	so -> addFieldInt( "id" );
	so -> addFieldFloatList( "sensors" );
	so -> addFieldFloatList( "targets" );
	so -> addFieldInt( "clusterID" );
}

void NNSample::serialize( SerializeObject& so )
{
	so.setPropInt( id , "id" );
	so.setPropFloatList( sensors , "sensors" );
	so.setPropFloatList( targets , "targets" );
	so.setPropInt( clusterID , "clusterID" );
}

void NNSample::deserialize( Object *parent , SerializeObject& so )
{
	clearLearnData();

	id = so.getPropInt( "id" );
	so.getPropFloatList( sensors , "sensors" , true );
	so.getPropFloatList( targets , "targets" , true );
	clusterID = so.getPropInt( "clusterID" );
}
