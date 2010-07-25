#ifndef	INCLUDE_AIBRAIN_H
#define INCLUDE_AIBRAIN_H

#include <aisvcio.h>

class MindArea;
class Cortex;
class MindLink;
class CortexLink;

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
	static Service *createService();
	AIBrain *thisPtr;
	AIBrain();

// operations
public:
	// mind areas
	virtual MindArea *getMindArea( String areaId ) {
		return( thisPtr -> getMindArea( areaId ) );
	}
	  
	// cortex
	virtual Cortex *createCortex( MindArea *area , String netType , int size , int inputs , int outputs ) {
		return( thisPtr -> createCortex( area , netType , size , inputs , outputs ) );
	}

	virtual Cortex *getCortex( String cortexId ) {
		return( thisPtr -> getCortex( cortexId ) );
	}
};

/*#########################################################################*/
/*#########################################################################*/

// brain provides implementation for mind areas
// each mind area is represented by one module component - next level folder under mod...
// each mind area has own name and own location in the brain
// mind area has pre-defined size as number of neurons, no matter of neuron type
// inter-area connections have own lifecycle, controlled by brain
// mind area consists a set of cortexes, where each cortex is neural or belief network of any type
// a number of cortexes, their types and inter-connections are defined dynamically by related modules
/* interface */ class MindArea
{
public:
	MindArea() {};
	virtual ~MindArea() = 0;

// operations
public:

};

/*#########################################################################*/
/*#########################################################################*/

// any neural network, belief or ANN
// each cortex is created by component, which defines its type and properties by means of specific libnn or libbn library
// cortex can be inbound, outbound or internal
class Cortex
{
public:
	Cortex() {};
	virtual ~Cortex() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

// created by static setup on start
// however each inter-area connection has its own lifecycle in terms of connection details
// connection details declare which cortexes are connected, and specific interneuron connections in these intercortex connections can emerge or disappear
// inter-area connection connects outputs of one area and inputs of another area
// dynamics of connection is directed by brain
// how inputs/outputs are connected to cortexes - it is defined by related component
class MindLink
{
public:
	MindLink() {};
	virtual ~MindLink() = 0;
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