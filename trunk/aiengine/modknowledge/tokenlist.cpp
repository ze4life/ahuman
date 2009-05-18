
#include <aiknowledge_impl.h>

/*#########################################################################*/
/*#########################################################################*/

AITokenListImpl::AITokenListImpl()
{
}

AITokenListImpl::~AITokenListImpl()
{
}

void AITokenListImpl::load()
{
	tokens.destroy();

	int l_num = 0;
	tokens.add( new AITokenImpl( "I" , ++l_num ) );
	tokens.add( new AITokenImpl( "he" , ++l_num ) );
	tokens.add( new AITokenImpl( "we" , ++l_num ) );
	tokens.add( new AITokenImpl( "they" , ++l_num ) );
	tokens.add( new AITokenImpl( "friend" , ++l_num ) );
	tokens.add( new AITokenImpl( "name" , ++l_num ) );
	tokens.add( new AITokenImpl( "good" , ++l_num ) );
	tokens.add( new AITokenImpl( "bad" , ++l_num ) );
	tokens.add( new AITokenImpl( "nice" , ++l_num ) );
	tokens.add( new AITokenImpl( "think" , ++l_num ) );
	tokens.add( new AITokenImpl( "know" , ++l_num ) );
	tokens.add( new AITokenImpl( "have" , ++l_num ) );
	tokens.add( new AITokenImpl( "money" , ++l_num ) );
	tokens.add( new AITokenImpl( "want" , ++l_num ) );
	
	//tokens.add( new AITokenImpl( "finger" , ++l_num ) );
	//tokens.add( new AITokenImpl( "revolution" , ++l_num ) );
	//tokens.add( new AITokenImpl( "head" , ++l_num ) );
	//tokens.add( new AITokenImpl( "client" , ++l_num ) );
	//tokens.add( new AITokenImpl( "time" , ++l_num ) );
	//tokens.add( new AITokenImpl( "he" , ++l_num ) );
	//tokens.add( new AITokenImpl( "she" , ++l_num ) );
	//tokens.add( new AITokenImpl( "was" , ++l_num ) );
	//tokens.add( new AITokenImpl( "number" , ++l_num ) );
	//tokens.add( new AITokenImpl( "sell" , ++l_num ) );
	//tokens.add( new AITokenImpl( "picture" , ++l_num ) );
	//tokens.add( new AITokenImpl( "have" , ++l_num ) );
	//tokens.add( new AITokenImpl( "go" , ++l_num ) );
	//tokens.add( new AITokenImpl( "hand" , ++l_num ) );
	//tokens.add( new AITokenImpl( "old" , ++l_num ) );
	//tokens.add( new AITokenImpl( "man" , ++l_num ) );
	//tokens.add( new AITokenImpl( "month" , ++l_num ) );
}

AIToken *AITokenListImpl::getTokenByOrder( int p_order )
{
	if( p_order < 0 || p_order >= tokens.count() )
		return( NULL );

	return( tokens[ p_order ] );
}

void AITokenListImpl::save()
{
}
