
#include <aiknowledge_impl.h>

/*#########################################################################*/
/*#########################################################################*/

// class AITokenAssocData
AITokenAssocData::AITokenAssocData()
{
	usageCount = 0;
	usageCountThreshold = 10;
	strong = false;

	left = NULL;
	right = NULL;
}

AITokenAssocData::AITokenAssocData( AIToken *p_left , AIToken *p_right )
{
	usageCount = 0;
	usageCountThreshold = 10;
	strong = false;

	left = p_left;
	right = p_right;
}

AITokenAssocData::~AITokenAssocData()
{
}

/*#########################################################################*/
/*#########################################################################*/

const char *AITokenAssocData::NAME = "AITokenAssocData";

String AITokenAssocData::getPK()
{
	char l_buf[ 20 ];
	sprintf( l_buf , "%d-%d" , left -> getOrderPos() , right -> getOrderPos() );

	return( l_buf );
}

// AIObject interface
void AITokenAssocData::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( AITokenAssocData::onCreate );

	so -> addFieldInt( "tokenLeft" );
	so -> addFieldInt( "tokenRight" );
	so -> addFieldInt( "usageCount" );
	so -> addFieldInt( "strong" );
}

void AITokenAssocData::serialize( SerializeObject& so )
{
	so.setPropInt( left -> getOrderPos() , "tokenLeft" );
	so.setPropInt( right -> getOrderPos() , "tokenRight" );
	so.setPropInt( usageCount , "usageCount" );
	so.setPropInt( strong , "strong" );
}

void AITokenAssocData::deserialize( Object *parent , SerializeObject& so )
{
	AIKnowledge knowledge;
	AITokenList *tl = knowledge.getTokenList();

	usageCount = so.getPropInt( "usageCount" );
	strong = ( so.getPropInt( "strong" ) == 0 )? false : true;
}

void AITokenAssocData::addUsage( AISession *session )
{
	if( strong )
		return;

	usageCount++;
	if( usageCount >= usageCountThreshold )
		strong = true;
}
