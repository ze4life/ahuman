#include <aiengine.h>

class HtmRect;
class HtmCortex;
class HtmSequence;
class HtmLayerMemory;
class HtmLayer;
class HtmHelper;

/*#########################################################################*/
/*#########################################################################*/

class HtmRect
{
public:
	HtmRect( int fromH , int toH , int fromV , int toV );

	int getSize() const;
	int getHeight() const;
	int getWidth() const;

public:
	int fromH;
	int toH;
	int fromV;
	int toV;
};

/*#########################################################################*/
/*#########################################################################*/

class HtmCortex : public Object
{
public:
	HtmCortex();
	~HtmCortex();

public:
	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( new HtmCortex ); };

public:
	void create( int d1 , int d2 );

	int getLayerCount();
	HtmLayer *getLayer( int pos );
	TwoIndexArray<int>& getInputs();
	TwoIndexArray<int>& getInputsPredicted();
	int getInputsSizeH();
	int getInputsSizeV();

	HtmRect getRect();

	void recalculate( const HtmRect& rc );

private:
	int calculateNumberOfLayers( int d1 , int d2 );
	void calculateLayerDimensions( int pos , int d1 , int d2 , int *nd1 , int *nd2 );

private:
	ClassList<HtmLayer> layers;
	TwoIndexArray<int> *inputs;
	TwoIndexArray<int> *inputsPredicted;
};

/*#########################################################################*/
/*#########################################################################*/

//  temporal element: {low-level patterns}
class HtmSequence
{
public:
	HtmSequence();
	HtmSequence( int nTemporalCount  , int nChilds );
	~HtmSequence();

	void create( int nTemporalCount  , int nChilds );
	int getHistoryCount();
	int getChildCount();
	bool isEmpty();

	bool addPattern( TwoIndexArray<int>& inputs , const HtmRect& rc );
	bool isNewPattern( TwoIndexArray<int>& inputs , const HtmRect& rc );
	void copyPatterns( HtmSequence *cs );
	void clear();
	void clearCurrent();
	int *getData( int *psize );

	void setId( int id );
	int getId();
	bool storedSequence();

	void incrementUsage();
	void decrementUsage();
	int getUsage();
	void clearUsage();

	void setMemoryPos( int pos );
	int getMemoryPos();

	void setLastReturned( HtmSequence *cs , int probability );
	HtmSequence *getLastReturned( int *probability );
	void clearCurrentKeepLast();

private:
	bool isStored;
	union {
		struct {
			int ID;
			int memoryPos;
			int usage;
		} stored;
		struct {
			HtmSequence *lastReturned;
			int lastProbability;
		} current;
		int dummy[3];
	};
	int historyCount;
	int childCount;
	FlatList<int> data;
};

/*#########################################################################*/
/*#########################################################################*/

// learned sequences
class HtmLayerMemory
{
public:
	HtmLayerMemory( int limitCount );
	~HtmLayerMemory();

public:
	HtmSequence *findLike( HtmSequence *cs , int *precision , int *probability );
	HtmSequence *getSequenceByPos( int pos );
	float compare( HtmSequence *cs1 , HtmSequence *cs2 );

	void incrementUsage( HtmSequence *cs );
	void decrementUsage( HtmSequence *cs );
	void decrementUsageRandom();
	int selectLeastUsedPos();
	bool hasSpace();
	HtmSequence *store( int pos , HtmSequence *cs );

	int getSequenceCount();
	int getMaxSize();

private:
	int limitCount;
	int limitLeastUsed;

	int mostUsedCount;
	int lastId;
	float thresholdOne;
	float thresholdMany;
	ClassList<HtmSequence> sequences;
};

/*#########################################################################*/
/*#########################################################################*/

// layer of abstraction
class HtmLayer : public Object
{
public:
	HtmLayer();
	HtmLayer( int pos , int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source );
	~HtmLayer();

public:
	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( new HtmLayer ); };

public:
	int getLayerPos();
	TwoIndexArray<int>& getOutputs();
	TwoIndexArray<int>& getOutputsPredicted();

	int getSizeH();
	int getSizeV();
	int getChildSizeH();
	int getChildSizeV();
	int getMaxHistory();

	HtmRect getRect();
	HtmRect getChildRect( int h , int v );
	HtmRect getRectFromChild( const HtmRect& rcChild );

	HtmLayerMemory *getMemory();

	void recalculate( const HtmRect& rc );

private:
	static int calcMaxHistoryLength( int pos , int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source );
	static int calcChildCountH( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source );
	static int calcChildCountV( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source );
	static int calcMemorySize( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source );

	void extendSequence( HtmSequence *cs , TwoIndexArray<int>& inputs , const HtmRect& rc );
	HtmSequence *acceptWithoutPrediction( HtmSequence *cs , int *action );
	void recalculatePoint( int& rv , int v , int h , HtmSequence *cs , int predicted , TwoIndexArray<int>& inputs , TwoIndexArray<int>& inputsPredicted , HtmRect& rcc );

private:
	Logger logger;
	HtmCortex *ctx;
	HtmLayer *childLayer;
	TwoIndexClassArray<HtmSequence> currentSequence;
	TwoIndexArray<int> outputs;
	TwoIndexArray<int> outputsPredicted;
	HtmLayerMemory memory;

	int layerPos;
	int highProbablePrecision;
	int maxHistoryLength;
	int childCountH;
	int childCountV;
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
	void showCortexInputs( HtmCortex *cortex );
	void showCortexMemorySize( HtmCortex *cortex );
	void showSequence( const char *name , HtmSequence *cs );
	void showAcceptWithoutPrediction( int layerPos , int h , int v , HtmSequence *cs , HtmSequence *csa , int action );
	void showTopLayer( HtmCortex *ctx );
	void showLayer( String title , HtmLayer *layer );
	String getIntArrayBySegments( int *pv , int segCount , int segLen );

private:
	Logger& logger;
};

/*#########################################################################*/
/*#########################################################################*/
