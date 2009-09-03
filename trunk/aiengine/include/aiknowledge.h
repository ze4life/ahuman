#ifndef	INCLUDE_AIKNOWLEDGE_H
#define INCLUDE_AIKNOWLEDGE_H

#include <aiio.h>

class AIToken;
class AISentense;
class AITokenList;

/*#########################################################################*/
/*#########################################################################*/

// handle inquires to AI accumulated experience and information
class AIKnowledge
{
public:

// engine helpers
public:
	static Service *createService();
	AIKnowledge *thisPtr;
	AIKnowledge();
};

/*#########################################################################*/
/*#########################################################################*/

class AIToken : public Object
{
public:
	virtual const char *getText() = 0;
	virtual int getOrderPos() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class AISentense : public Object
{
public:
	virtual void addToken( AIToken *p_token ) = 0;
	virtual ClassList<AIToken>& getTokens() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class AITokenList : public Object
{
public:
	virtual ClassList<AIToken>& getTokens() = 0;
	virtual int getTokenCount() = 0;
	virtual AIToken *getTokenByOrder( int p_order ) = 0;
};

#endif	// INCLUDE_AIKNOWLEDGE_H
