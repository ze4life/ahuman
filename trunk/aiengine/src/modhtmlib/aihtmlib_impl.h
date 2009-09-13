#ifndef	INCLUDE_AIHTMLIB_IMPL_H
#define INCLUDE_AIHTMLIB_IMPL_H

#include <aiengine.h>
#include <aihtmlib.h>
#include <aiio.h>
#include <aidb.h>

class AIHtmLibDebug;
class AIHtmLibImpl;

class HtmRect;
class HtmSequence;
class HtmLayerMemory;
class HtmLayer;
class HtmCortex;
class HtmHelper;

/*#########################################################################*/
/*#########################################################################*/

class AIHtmLibDebug : public Subscriber
{
public:
	AIHtmLibDebug();
	~AIHtmLibDebug();

public:
	void init( Xml config );
	void exit();

	virtual void onMessage( Message *msg );

// tests
private:
	void testHelloWorld( XmlCall& call );

private:
	Publisher *callPub;
	Subscription *callSub;
	Logger logger;
};

/*#########################################################################*/
/*#########################################################################*/

class AIHtmLibImpl : public AIHtmLib , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "HtmLib" ); };

// external interface
public:
	AIHtmLibImpl();
	static AIHtmLibImpl *getServiceImpl();

// internals
private:

private:
	AIEngine& engine;
	AIHtmLibDebug debug;
};

/*#########################################################################*/
/*#########################################################################*/

class HtmRect
{
public:
	HtmRect( int fromH , int toH , int fromV , int toV );

public:
	int fromH;
	int toH;
	int fromV;
	int toV;
};

/*#########################################################################*/
/*#########################################################################*/

//  temporal element: {low-level patterns}
class HtmSequence
{
public:
	HtmSequence( int nTemporalCount  , int nChilds );
	~HtmSequence();

private:
	int ID;
	int usage;
	TwoIndexArray<int> data; // [temporal index of pattern][child item in a pattern]
};

/*#########################################################################*/
/*#########################################################################*/

// learned sequences
class HtmLayerMemory
{
public:
	HtmLayerMemory();
	~HtmLayerMemory();

private:
	ClassList<HtmSequence> sequences;
};

/*#########################################################################*/
/*#########################################################################*/

// layer of abstraction
class HtmLayer
{
public:
	HtmLayer( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source );
	~HtmLayer();

	TwoIndexArray<int>& getOutputs();
	int getSizeH();
	int getSizeV();
	int getChildSizeH();
	int getChildSizeV();

	HtmRect getRect();
	HtmRect getRectFromChild( const HtmRect& rcChild );

	void recalculate( const HtmRect& rc );

private:
	static int calcMaxHistoryLength( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source );
	static int calcChildCountH( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source );
	static int calcChildCountV( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source );

	int acceptWithoutPrediction( int h , int v , int hc , int vc , TwoIndexArray<int>& inputs );

private:
	HtmCortex *ctx;
	HtmLayer *childLayer;
	TwoIndexArray<int> outputs;
	HtmLayerMemory memory;

	int maxHistoryLength;
	int childCountH;
	int childCountV;
	HtmSequence currentSequence;
};

/*#########################################################################*/
/*#########################################################################*/

class HtmCortex
{
public:
	HtmCortex();
	~HtmCortex();

public:
	void create( int d1 , int d2 );

	int getLayerCount();
	HtmLayer *getLayer( int pos );
	TwoIndexArray<int>& getInputs();
	int getInputsSizeH();
	int getInputsSizeV();

	HtmRect getRect();

	void recalculate( const HtmRect& rc );

private:
	ClassList<HtmLayer> layers;
	TwoIndexArray<int> *inputs;
};

/*#########################################################################*/
/*#########################################################################*/

class HtmHelper
{
public:
	HtmHelper( Logger& logger );
	~HtmHelper();

public:
	void showCortex( HtmCortex *cortex );

private:
	Logger& logger;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIHTMLIB_IMPL_H
