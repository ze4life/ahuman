#ifndef	INCLUDE_AIHEART_IMPL_H
#define INCLUDE_AIHEART_IMPL_H

#include <aiengine.h>
#include <aiheart.h>
#include <aimind.h>

/*#########################################################################*/
/*#########################################################################*/

typedef enum {
	AIEMOTION_MIXED = -1 ,

	AIEMOTION_ANGRY = 0 ,
	AIEMOTION_SHAMED = 1 ,
	AIEMOTION_CALM = 2 ,
	AIEMOTION_KNOWLEDGEINTERESTED = 3 ,
	AIEMOTION_ACTIVE = 4 ,
	AIEMOTION_CONFIDENT = 5 ,
	AIEMOTION_SEXPOWERED = 6 ,
	AIEMOTION_COMMUNICATIVE = 7 ,

	AIEMOTION_COUNT = 8
} AIEmotionType;

typedef struct
{
	AIEmotionType from;
	AIEmotionType to;
	int rate;
} AIEmotionCorr;

#define APPROVED_SIZE_RATE_MIN 10
#define APPROVED_SIZE_RATE_MAX 10

class AIEmotionImpl;

/*#########################################################################*/
/*#########################################################################*/

// personality object - wishes, likes/don't likes
class AIHeartImpl : public AIHeart , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Heart" ); };

// external interface
public:
	virtual bool isApprovedEmotion( const AIEmotion& e );

	// Object interface
	AIHeartImpl();

// base class interface
private:
	void startIndependentThinking();
	void stopIndependentThinking();

	bool canContinue() { return( enabled ); };
	void doLive();

// internals
public:
	int performIndependentThinking();

// internals
private:
	AIEngine& engine;
	AIEmotionImpl *emotion;

	bool enabled;
	RFC_THREAD independentThreadID;
};

// #############################################################################
// #############################################################################

// emotion class
class AIEmotionImpl : public AIEmotion
{
public:
	AIEmotionImpl( AIEmotionType p_type , int p_val );
	AIEmotionImpl( const AIEmotionImpl& p_one , const AIEmotionImpl& p_two );
											  
	bool isApproved( const AIEmotionImpl& e ) const;
	int size2() const;

	// Object interface

public:
	AIEmotionType type;
	int val[ AIEMOTION_COUNT ];
};

AIEmotionImpl operator +( const AIEmotionImpl& left , const AIEmotionImpl& right );	
int operator *( const AIEmotionImpl& left , const AIEmotionImpl& right );

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIHEART_IMPL_H
