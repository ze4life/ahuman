#ifndef	INCLUDE_AIBRAIN_H
#define INCLUDE_AIBRAIN_H

#include <aiengine.h>
#include <aisvcio.h>

class MindArea;
class Cortex;
class MindLink;
class CortexLink;
class BrainLocation;

// #############################################################################
// #############################################################################

// cortex value type
typedef float cortexvt;

/*#########################################################################*/
/*#########################################################################*/

// brain instantiates multi-cortex network
// top-level brain structure is represented by mind map, consists of mind areas and not changed with time
// brain controls lifecycle of cortexes and connections among them
// brain providers adapters to cortex for every library implementing one of cortex approaches
class AIBrain
{
public:

// engine helpers
public:
	static Service *newService();
	AIBrain *thisPtr;
	AIBrain();

// operations
public:
	// mind areas
	virtual void addMindArea( String areaId , MindArea *area ) {
		thisPtr -> addMindArea( areaId , area );
	}

	virtual MindArea *getMindArea( String areaId ) {
		return( thisPtr -> getMindArea( areaId ) );
	}

	// cortex construction
	virtual void createSensorCortex( MindArea *area , BrainLocation& relativeLocation , Cortex *cortex ) {
		return( thisPtr -> createSensorCortex( area , relativeLocation , cortex ) );
	}
	virtual Cortex *createNeoCortex( MindArea *area , BrainLocation& relativeLocation , Cortex *sensorCortex ) {
		return( thisPtr -> createNeoCortex( area , relativeLocation , sensorCortex ) );
	}

	// get cortex by ID
	virtual Cortex *getCortex( String cortexId ) {
		return( thisPtr -> getCortex( cortexId ) );
	}

	// mind area helpers
	static MindArea *getNeoCortexArea() { AIBrain brain; return( brain.getMindArea( "NeoCortex" ) ); }
};

/*#########################################################################*/
/*#########################################################################*/

// every mind area and cortex have exact location in brain 3D space
// location is parallelogramm, centered in given absolute point, and having X, Y, Z dimentions
// brain has no limits
// mind area has pre-configured location in brain space
// inter-area connections between neurons are established within specific mind link, all mind links are pre-configured
// inter-cortex connections between neurons are established within specific cortex link, all cortex links are dynamic
// connections evolve all the time
// probability of establishing inter-area and inter-cortex connections depends on distance between neurons
// to diminish rough shapes of mind areas and cortexes, distances are adjusted by factor equal to distance between cortex/area centers
// brain controls that areas/cortexes do not overlap
class BrainLocation
{
private:
	// lower corner position (relative to parent)
	int x;
	int y;
	int z;

	// dimensions
	int dx;
	int dy;
	int dz;

	// orientation (-1,0,1)
	int ox;
	int oy;
	int oz;

public:
	BrainLocation() {
		x = y = z = 0;
		dx = dy = dz = 0;
		ox = oy = oz = 0;
	}

	void setPosition( int p_x , int p_y , int p_z ) {
		x = p_x; y = p_y; z = p_z;
	}
	void setDimensions( int p_dx , int p_dy , int p_dz ) {
		dx = p_dx; dy = p_dy; dz = p_dz;
	}
	void setOrientationX( bool p_neg2pos ) {
		oz = ( p_neg2pos )? 1 : -1; oy = 0; oz = 0;
	}
	void setOrientationY( bool p_neg2pos ) {
		ox = 0; oy = ( p_neg2pos )? 1 : -1; oz = 0;
	}
	void setOrientationZ( bool p_neg2pos ) {
		ox = 0; oy = 0; oz = ( p_neg2pos )? 1 : -1;
	}
	int getSize() const {
		return( dx * dy * dz );
	}

	// relative is counted from lower corner
	BrainLocation getAbsoluteLocation( const BrainLocation& relativeLocation ) const;
	BrainLocation getRelativeLocation( const BrainLocation& absoluteLocation ) const;
	bool placeLocation( BrainLocation& cover , BrainLocation& add ) const;
	void getCenter( int& cx , int& cy , int& cz ) const;
	void movePosition( int cx , int cy , int cz );
	void resize( int cx , int cy , int cz );
	void setSurfaceDimensions( int d1 , int d2 );
	void center( const BrainLocation& parent );
	void moveInside( BrainLocation& relativePosition ) const;

	// get inputs/outputs surface according to orientation
	BrainLocation getInputsSurface() const;
	BrainLocation getOutputsSurface() const;
	void getSurfaceDimensions( int& sa , int& sb ) const;
	int getSurfaceSize() const;

private:
	bool placeLocationFirst( BrainLocation& cover , BrainLocation& add ) const;
};

/*#########################################################################*/
/*#########################################################################*/

// brain provides implementation for mind areas
// each mind area is implemented by module components - next level folder under mod...
// each mind area has own name and own location in the brain
// mind area has pre-defined size as number of neurons, no matter of neuron type
// inter-area connections have own lifecycle, controlled by brain
// mind area consists a set of cortexes, where each cortex is neural or belief network of any type
// a number of cortexes, their types and inter-connections are defined dynamically by related modules
/* interface */ class MindArea
{
public:
	MindArea();
	virtual ~MindArea();

public:
	// mind area events
	virtual void onCreateArea() = 0;
	virtual void onLoadArea() = 0;
	virtual void onBrainStart() {};
	virtual void onBrainStop() {};
	// cortex events
	virtual void onCreateCortex( Cortex *cortex ) {};
	virtual void onAddCortex( Cortex *cortex ) {};
	// mind link events
	virtual void onOpenMindLinkSource( MindLink *link , String channelId ) {};
	virtual void onOpenMindLinkDestination( MindLink *link , String channelId ) {};

	void attach( String id );
	String getId() {
		return( areaId );
	}

	const BrainLocation& getLocation() { return( location ); };

	void addMindLink( MindLink *link ) {
		mindLinks.add( link );
	}
	ClassList<MindLink>& getMindLinks() {
		return( mindLinks );
	}
	void addCortex( Cortex *cortex , const BrainLocation& relativeLocation );
	ClassList<Cortex>& getCortexList() {
		return( cortexList );
	}

private:
	void lock() {
		rfc_hnd_semlock( lockHandle );
	}
	void unlock() {
		rfc_hnd_semunlock( lockHandle );
	}

private:
	String areaId;
	BrainLocation location;

	ClassList<MindLink> mindLinks;
	ClassList<Cortex> cortexList;
	int size;
	int sizeNotAllocated;
	RFC_HND lockHandle;
};

/*#########################################################################*/
/*#########################################################################*/

class CortexIOSizeInfo
{
public:
	CortexIOSizeInfo() {};
	CortexIOSizeInfo( int p_nInputs , int p_nOutputs ) {
		nInputs = p_nInputs;
		nInputsDim1 = 0;
		nInputsDim2 = 0;

		nOutputs = p_nOutputs;
		nOutputsDim1 = 0;
		nOutputsDim2 = 0;
	};
	CortexIOSizeInfo( int p_nInputs , int p_nInputsDim1 , int p_nInputsDim2 , int p_nOutputs , int p_nOutputsDim1 , int p_nOutputsDim2 ) {
		nInputs = p_nInputs;
		nInputsDim1 = p_nInputsDim1;
		nInputsDim2 = p_nInputsDim2;

		nOutputs = p_nOutputs;
		nOutputsDim1 = p_nOutputsDim1;
		nOutputsDim2 = p_nOutputsDim2;
	};

public:
	int nInputs;
	int nInputsDim1;
	int nInputsDim2;

	int nOutputs;
	int nOutputsDim1;
	int nOutputsDim2;
};

/*#########################################################################*/
/*#########################################################################*/

// any neural network, belief or ANN
// each cortex is created by component, which defines its type and properties by means of specific libnn or libbn library
// cortex can be inbound, outbound or internal
/* interface */ class Cortex
{
private:
	String cortexId;
	MindArea *area;
	String netType;

	BrainLocation areaLocation;
	BrainLocation inputsSurface;
	BrainLocation outputsSurface;
	CortexIOSizeInfo ioSizeInfo;
	int neuronsUsed;

	cortexvt *inputs;
	cortexvt *outputs;

protected:
	Cortex( const char *netType , MindArea *p_area , const CortexIOSizeInfo& p_ioSizeInfo );
public:
	virtual ~Cortex() {
		if( inputs != NULL )
			free( inputs );
		if( outputs != NULL )
			free( outputs );
	};

	void setId( String id ) {
		cortexId = id;
	}
	String getId() {
		return( cortexId );
	}
	void setAreaLocation( const BrainLocation& p_location );
	const BrainLocation& getAreaLocation() { return( areaLocation ); };
	const BrainLocation& getInputsSurface() { return( inputsSurface ); };
	const BrainLocation& getOutputsSurface() { return( outputsSurface ); };

	// standard cortex events
	virtual void onCortexRun() {};

	// process standard cortex changes
	void processInputsUpdated();
	void processOutputsUpdated();

	MindArea *getArea() { return( area ); };
	int getNInputs() { return( ioSizeInfo.nInputs ); };
	int getNOutputs() { return( ioSizeInfo.nOutputs ); };
	int getNInputs( int& dim1 , int& dim2 ) { dim1 = ioSizeInfo.nInputsDim1; dim2 = ioSizeInfo.nInputsDim2; return( ioSizeInfo.nInputs ); };
	int getNOutputs( int& dim1 , int& dim2 ) { dim1 = ioSizeInfo.nOutputsDim1; dim2 = ioSizeInfo.nOutputsDim2; return( ioSizeInfo.nOutputs ); };

	String getNetType() { return( netType ); };
	int getNSize() { return( neuronsUsed ); };

	cortexvt *getInputs() { return( inputs ); };
	cortexvt *getOutputs() { return( outputs ); };
};

/*#########################################################################*/
/*#########################################################################*/

class MindLinkInfo;

// created by static setup on start
// however each inter-area connection has its own lifecycle in terms of connection details
// connection details declare which cortexes are connected, and specific interneuron connections in these intercortex connections can emerge or disappear
// inter-area connection connects outputs of one area and inputs of another area
// dynamics of connection is directed by brain
// how inputs/outputs are connected to cortexes - it is defined by related component
class MindLink : public Subscriber
{
public:
	MindLink( MindLinkInfo *p_info );
	~MindLink();

// operations
public:
	virtual void onMessage( Message *msg );

	void open( Session *session );
	void transferOutputs( Cortex *cortex );
	Subscription *subscribe( Subscriber *handler , String name );
	Subscription *subscribeSelector( Subscriber *handler , String name , String selector );

	MindArea *getSourceArea() { return( sourceArea ); };
	MindArea *getDestinationArea() { return( destinationArea ); };

private:
	MindLinkInfo *info;

	MindArea *sourceArea;
	MindArea *destinationArea;
	float distanceFactor;

	Session *session;
	Subscription *iosub;
	Publisher *iopub;
};

/*#########################################################################*/
/*#########################################################################*/

// created by related component
//  can link only cortexes in the same area
class CortexLink
{
public:
	CortexLink() {};
	virtual ~CortexLink() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

// class to snapshot outputs from cortex and transfer to other cortexes
class CortexMessage : public Message
{
private:
	unsigned size;
	cortexvt *data;
	Cortex *cortex;

public:
	CortexMessage( Cortex *p_cortex ) : Message( Message::MsgType_Binary , "cortexmessage" ) { 
		cortex = p_cortex;
		size = cortex -> getNOutputs();
		data = ( cortexvt * )calloc( size , sizeof( cortexvt ) ); 
	};
	virtual ~CortexMessage() {
		if( data != NULL )
			free( data );
	}

public:
	Cortex *getSourceCortex() { return( cortex ); };
	void *getBuffer() { return( data ); };
	int getSize() { return( ( int )size ); };

	void capture() {
		// capture outputs from cortex
		cortexvt *outputs = cortex -> getOutputs();
		memcpy( data , outputs , size * sizeof( cortexvt ) );
	}

	void get( unsigned n , cortexvt *values ) {
		ASSERTMSG( "message does not fit into buffer" , n >= size );
		memcpy( values , data , size * sizeof( float ) );
	}
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIBRAIN_H