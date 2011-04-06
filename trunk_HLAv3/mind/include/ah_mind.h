#ifndef	INCLUDE_AH_MIND_H
#define INCLUDE_AH_MIND_H

/*#########################################################################*/
/*#########################################################################*/

#include "platform/include/ah_platform.h"

class MindManager;
class MindLocation;
class MindArea;
class MindLink;
class Cortex;
class CortexIOSizeInfo;
class CortexMessage;

// cortex value type
typedef float cortexvt;

/*#########################################################################*/
/*#########################################################################*/

class MindMap;
class MindActiveMemory;
class MindLinkInfo;

class MindManager : public Service {
// interface
public:
	// mind areas
	void addMindArea( String areaId , MindArea *area );
	MindArea *getMindArea( String areaId );
	  
	// cortex
	void registerSensorCortex( MindArea *area , MindLocation& relativeLocation , Cortex *cortex );
	Cortex *createNeoCortex( MindArea *area , MindLocation& relativeLocation );
	Cortex *getCortex( String cortexId );

// service
public:
	virtual const char *getServiceName() { return( "MindManager" ); };
	virtual void configureService( Xml config );
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void stopService();
	virtual void exitService();
	virtual void destroyService();

protected:
	MindManager();
public:
	static Service *newService();
	static MindManager *getService() { return( ( MindManager * )ServiceManager::getInstance().getService( "MindManager" ) ); };

// internals:
public:
	MindMap *getMindMap();

private:
	MindLink *createMindLink( MindLinkInfo *linkInfo , MindArea *masterArea , MindArea *slaveArea );
	void registerCortex( Cortex *cortex , MindArea *area , const MindLocation& relativeLocation );

	// cortex region to neural network adapter
	Cortex *createCortexAdapter( String cortexType , MindArea *area , MindLocation& relativeLocation );

	// structure lock
	void lock() { rfc_hnd_semlock( lockStructure );	}
	void unlock() { rfc_hnd_semunlock( lockStructure );	}

private:
	Xml config;
	MindMap *mindMap;
	MapStringToClass<MindArea> mindAreas;

	RFC_HND lockStructure;
	int sessionId;
	int cortexId;
	MapStringToClass<Cortex> mapCortex;
	MindActiveMemory *activeMemory;
	ClassList<MindLink> mindLinks;
	MessageSession *ioBrainSession;
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
class MindLocation {
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
	MindLocation() {
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
	MindLocation getAbsoluteLocation( const MindLocation& relativeLocation ) const;
	MindLocation getRelativeLocation( const MindLocation& absoluteLocation ) const;
	bool placeLocation( MindLocation& cover , MindLocation& add ) const;
	void getCenter( int& cx , int& cy , int& cz ) const;
	void movePosition( int cx , int cy , int cz );
	void resize( int cx , int cy , int cz );
	void setSurfaceDimensions( int d1 , int d2 );
	void center( const MindLocation& parent );
	void moveInside( MindLocation& relativePosition ) const;

	// get inputs/outputs surface according to orientation
	MindLocation getInputsSurface() const;
	MindLocation getOutputsSurface() const;
	void getSurfaceDimensions( int& sa , int& sb ) const;
	int getSurfaceSize() const;

private:
	bool placeLocationFirst( MindLocation& cover , MindLocation& add ) const;
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
/* interface */ class MindArea {
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

	const MindLocation& getLocation() { return( location ); };

	void addMindLink( MindLink *link ) {
		mindLinks.add( link );
	}
	ClassList<MindLink>& getMindLinks() {
		return( mindLinks );
	}
	void addCortex( Cortex *cortex , const MindLocation& relativeLocation );
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
	MindLocation location;

	ClassList<MindLink> mindLinks;
	ClassList<Cortex> cortexList;
	int size;
	int sizeNotAllocated;
	RFC_HND lockHandle;
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
class MindLink : public MessageSubscriber {
public:
	MindLink( MindLinkInfo *p_info );
	~MindLink();

// operations
public:
	virtual void onMessage( Message *msg );

	void open( MessageSession *session );
	void transferOutputs( Cortex *cortex );
	MessageSubscription *subscribe( MessageSubscriber *handler , String name );
	MessageSubscription *subscribeSelector( MessageSubscriber *handler , String name , String selector );

	MindArea *getSourceArea() { return( sourceArea ); };
	MindArea *getDestinationArea() { return( destinationArea ); };

private:
	MindLinkInfo *info;

	MindArea *sourceArea;
	MindArea *destinationArea;
	float distanceFactor;

	MessageSession *session;
	MessageSubscription *iosub;
	MessagePublisher *iopub;
};

/*#########################################################################*/
/*#########################################################################*/

class CortexIOSizeInfo {
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
/* interface */ class Cortex {
private:
	String cortexId;
	MindArea *area;
	String netType;

	MindLocation areaLocation;
	MindLocation inputsSurface;
	MindLocation outputsSurface;
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
	void setAreaLocation( const MindLocation& p_location );
	const MindLocation& getAreaLocation() { return( areaLocation ); };
	const MindLocation& getInputsSurface() { return( inputsSurface ); };
	const MindLocation& getOutputsSurface() { return( outputsSurface ); };

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

// class to snapshot outputs from cortex and transfer to other cortexes
class CortexMessage : public Message {
private:
	unsigned size;
	cortexvt *data;
	Cortex *cortex;

public:
	CortexMessage( Cortex *p_cortex ) : Message( Message::MsgType_Binary ) { 
		cortex = p_cortex;
		size = cortex -> getNOutputs();
		data = ( cortexvt * )calloc( size , sizeof( cortexvt ) ); 
		setMessageType( "CortexMessage" );
	};
	virtual ~CortexMessage() {
		if( data != NULL )
			free( data );
	}
	const char *getClass() { return( "CortexMessage" ); };

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

#endif	// INCLUDE_AH_MIND_H
