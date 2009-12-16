#ifndef	INCLUDE_AIHEART_H
#define INCLUDE_AIHEART_H

#include <aiengine.h>
#include <aimind.h>

class AIEmotion;

/*#########################################################################*/
/*#########################################################################*/

class AIHeart
{
public:
	virtual bool isApprovedEmotion( const AIEmotion& e )
		{ return( thisPtr -> isApprovedEmotion( e ) ); };

// engine helpers
public:
	static Service *createService();
	AIHeart *thisPtr;
	AIHeart();
};

/*#########################################################################*/
/*#########################################################################*/

class AIEmotion : public Object
{
public:
};

#endif	// INCLUDE_AIHEART_H
