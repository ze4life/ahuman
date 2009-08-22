
#include "aiknowledge_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AITokenAssociations::AITokenAssociations()
:	engine( AIEngine::getInstance() )
{
	assocMatrix = NULL;
	matrixSize = 0;
}

AITokenAssociations::~AITokenAssociations()
{
	for( int k = 0; k < matrixSize; k++ )
		delete assocMatrix[ k ];

	if( assocMatrix != NULL )
		free( assocMatrix );
}

/*#########################################################################*/
/*#########################################################################*/

const char *AITokenAssociations::NAME = "AITokenAssociations";

String AITokenAssociations::getPK()
{
	return( "global" );
}

// Object interface
void AITokenAssociations::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( AITokenAssociations::onCreate );
	so -> addFieldInt( "matrixSize" );

	AITokenAssocData::createSerializeObject();
}

void AITokenAssociations::serialize( SerializeObject& so )
{
	so.setPropInt( matrixSize , "matrixSize" );
}

void AITokenAssociations::deserialize( Object *parent , SerializeObject& so )
{
	matrixSize = so.getPropInt( "matrixSize" );
}

void AITokenAssociations::load()
{
	AITokenList *tokenList = knowledge.getTokenList();
	int tokenCount = tokenList -> getTokenCount();

	matrixSize = tokenCount * tokenCount;
	assocMatrix = ( AITokenAssocData ** )calloc( matrixSize , sizeof( AITokenAssocData * ) );

	for( int left = 0; left < tokenCount; left++ )
		for( int right = 0; right < tokenCount; right++ )
			{
				AIToken *leftToken = tokenList -> getTokenByOrder( left );
				AIToken *rightToken = tokenList -> getTokenByOrder( right );
				assocMatrix[ left * tokenCount + right ] = new AITokenAssocData( leftToken, rightToken );
			}

	// read associations
	AIDBCursor& cur = db.scan( AITokenAssocData::getSerializeObject() );
	while( cur.next() )
		{
			int left;
			int right;
			sscanf( cur.getDataPK() , "%d-%d" , &left , &right );
			left--;
			right--;

			// read data to object
			AITokenAssocData *ad = assocMatrix[ left * tokenCount + right ];
			cur.getData( ad );
		}
}

void AITokenAssociations::addAssoc( AISession *session , AIToken *left , AIToken *right )
{
	AITokenAssocData *assoc = getAssoc( left , right );
	assoc -> addUsage( session );
}

AITokenAssocData *AITokenAssociations::getAssoc( AIToken *left , AIToken *right )
{
	AITokenList *tokenList = knowledge.getTokenList();
	int tokenCount = tokenList -> getTokenCount();

	int index = ( left -> getOrderPos() - 1 ) * tokenCount + right -> getOrderPos() - 1;
	return( assocMatrix[ index ] );
}

void AITokenAssociations::save()
{
	db.update( this );

	AIDBFile& file = db.getFile( AITokenAssocData::getSerializeObject() );
	file.truncate();
	file.insert( ( Object ** )assocMatrix , matrixSize );

	// strong associations
	logger.logInfo( "STRONG ASSOCIATIONS:" );
	for( int k = 0; k < matrixSize; k++ )
		{
			AITokenAssocData *ad = assocMatrix[ k ];
			if( ad -> isStrong() )
				logger.logInfo( String( ad -> getLeft() -> getText() ) + " -> " + ad -> getRight() -> getText() );
		}
}
