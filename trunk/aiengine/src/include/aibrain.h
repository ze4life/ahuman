#ifndef	INCLUDE_AIBRAIN_H
#define INCLUDE_AIBRAIN_H

#include <aiengine.h>
#include <aisvcio.h>

class MindArea;
class Cortex;
class MindLink;
class CortexLink;
class BrainLocation;

/*#########################################################################*/
/*#########################################################################*/

// brain instantiates multi-cortex network
// top-level brain structure is represented by mind map, consists of mind areas and not changed with time
// brain controls lifecycle of cortexes and connections among them
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
	  
	// cortex - relative location from lower corner
	virtual Cortex *createCortex( MindArea *area , BrainLocation& relativeLocation , String netType , int inputs , int outputs ) {
		return( thisPtr -> createCortex( area , relativeLocation , netType , inputs , outputs ) );
	}
	virtual void addHardcodedCortex( MindArea *area , BrainLocation& relativeLocation , Cortex *cortex ) {
		return( thisPtr -> addHardcodedCortex( area , relativeLocation , cortex ) );
	}

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
	void setOrientaion( int p_ox , int p_y , int p_oz ) {
#ifndef sign
#define sign(x) (((x)>0)?1:((x)<0)?-1:0)
#endif
		ox = sign( p_ox ); oy = sign( oy ); oz = sign( p_oz );
	}
	int getSize() const {
		return( dx * dy * dz );
	}

	// relative is counted from lower corner
	BrainLocation getAbsoluteLocation( const BrainLocation& relativeLocation ) const;
	bool placeLocation( BrainLocation& cover , BrainLocation& add ) const;
	void getLowerCorner( int& cx , int& cy , int& cz ) const;
	void centerByLowerCorner( int cx , int cy , int cz );

	// get output surface according to orientation
	BrainLocation getOutputLocation() const;
	// get surface dimentions
	void get2Dsizes( int& sa , int& sb ) const;

private:
	bool placeLocationFirst( BrainLocation& cover , BrainLocation& add ) const;

private:
	// absolute center position
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
	void addCortex( Cortex *cortex );
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

// cortex value type
typedef float cortexvt;

// any neural network, belief or ANN
// each cortex is created by component, which defines its type and properties by means of specific libnn or libbn library
// cortex can be inbound, outbound or internal
/* interface */ class Cortex
{
public:
	Cortex( MindArea *p_area , int p_ninputs , int p_noutputs ) {
		area = p_area;
		nInputs = p_ninputs;
		nOutputs = p_noutputs;
		neuronsUsed = 0;

		inputs = ( nInputs > 0 )? ( cortexvt * )calloc( nInputs , sizeof( cortexvt ) ) : NULL;
		outputs = ( nOutputs > 0 )? ( cortexvt * )calloc( nOutputs , sizeof( cortexvt ) ) : NULL;
	};
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
	void setLocation( const BrainLocation& p_location ) { location = p_location; };
	const BrainLocation& getLocation() { return( location ); };

	// standard cortex events
	virtual void onCortexRun() {};

	// process standard cortex changes
	void processInputsUpdated();
	void processOutputsUpdated();

	Cortex *getArea();
	int getNInputs() { return( nInputs ); };
	int getNOutputs() { return( nOutputs ); };

	String getNetType() { return( netType ); };
	void setNetType( String type ) { netType = type; };

	int getNSize() { return( neuronsUsed ); };
	void setNSize( int p_nsize ) { neuronsUsed = p_nsize; };

	cortexvt *getInputs() { return( inputs ); };
	cortexvt *getOutputs() { return( outputs ); };

private:
	String cortexId;
	MindArea *area;
	BrainLocation location;
	String netType;

	int nInputs;
	int nOutputs;
	int neuronsUsed;

	cortexvt *inputs;
	cortexvt *outputs;
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
	void publish( BinaryMessage *msg );
	Subscription *subscribe( Subscriber *handler , String name , String selector );

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

#endif	// INCLUDE_AIBRAIN_H