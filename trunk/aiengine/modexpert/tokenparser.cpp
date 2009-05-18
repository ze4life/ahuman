
#include <aiexpert_impl.h>

extern "C" static  int onSortTokens( void *p_userdata , AIToken **p_e1 , AIToken **p_e2 )
{
	return( strcmp( (*p_e1) -> getText() , (*p_e2) -> getText() ) );
}

/*#########################################################################*/
/*#########################################################################*/

AITokenParser::AITokenParser()
:	engine( AIEngine::getInstance() )
{
	// copy tokens to internal list
	AITokenList *list = knowledge.getTokenList();
	for( int k = 0; k < list -> getTokenCount(); k++ )
		tokens.add( list -> getTokenByOrder( k ) );

	// sort to improve parsing
	tokens.sort( ( rfc_lst_compare )onSortTokens );
}

AITokenParser::~AITokenParser()
{
	tokens.clear();
}

void AITokenParser::splitToSentenses( AIMessage *msg , ClassList<AISentense>& p_list )
{
	const char *s = skipSpacing( msg -> getMessage() );

	AISentense *currentSentense = NULL;

	// start text
	logger.logInfo( String( "PARSE MESSAGE: " ) + msg -> getId() , 1 );

	bool unknown = false;
	bool first = true;
	String so;
	while( *s )
		{
			// end of sentense - but dot not required in the end of all text
			if( *s == '.' )
				{
					if( currentSentense != NULL )
						{
							currentSentense = NULL;
						}

					// end sentense
					if( unknown )
						logger.logInfo( so + " ." , 0 );
					else
						logger.logInfo( so + "." , 0 );
					so.clear();

					s++;
					s = skipSpacing( s );
					unknown = false;
					first = true;

					continue;
				}

			// find most wide token
			// sentenses without known tokens should be ignored
			AIToken *token = findToken( s );
			if( token == NULL )
				{
					// show unknown
					if( !unknown )
						{
							// spacing before token
							if( !first )
								so += " ";

							so += "...";
							unknown = true;
							first = false;
						}

					// skip all till space or end of sentense
					while( *s )
						if( isSpacing( *s ) || *s == '.' )
							break;
						else
							s++;
				}
			else
				{
					// create sentense if not created
					if( currentSentense == NULL )
						{
							currentSentense = knowledge.createSentense();
							p_list.add( currentSentense );
						}

					currentSentense -> addToken( token );

					// skip token
					const char *text = token -> getText();

					// spacing before token
					if( !first )
						so += " ";

					so += text;
					unknown = false;
					first = false;

					s += strlen( text );
				}

			// ignore spaces
			s = skipSpacing( s );
		}

	// finish sentense if w/o .
	if( currentSentense != NULL )
		{
			logger.logInfo( so , 0 );
			so.clear();
		}

	// finish text
	logger.logInfo( so , 2 );
}

const char *AITokenParser::skipSpacing( const char *s )
{
	while( *s )
		if( !isSpacing( *s ) )
			return( s );
		else
			s++;

	return( s );
}

bool AITokenParser::isSpacing( char c )
{
	return( c == ' ' || c == '\t' || c == '\r' || c == '\n' );
}

AIToken *AITokenParser::findToken( const char *s )
{
	int count = tokens.count();
	int tokenPos = 0;
	int charPos = 0;
	while( 1 )
		{
			// k is always position of first token that starts with [0-(pos-1)] of s
			// iteration is looking for the next char
			char next = s[ charPos ];

			// check source token end
			if( isSpacing( next ) || *s == '.' || *s == 0 )
				{
					// check that token found before equals to the s
					AIToken *token = tokens[ tokenPos ];
					if( strlen( token -> getText() ) == charPos )
						return( token );

					// token only starts with given sequence
					break;;
				}

			// find first token starting from given sequence
			charPos++;
			for( ; tokenPos < count; tokenPos++ )
				if( !strncmp( tokens[ tokenPos ] -> getText() , s , charPos ) )
					break;

			// check not found
			if( tokenPos == count )
				break;
		}

	return( NULL );
}

