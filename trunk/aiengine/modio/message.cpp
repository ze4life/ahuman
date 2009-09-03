#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIMessage::AIMessage()
{
}

AIMessage::~AIMessage()
{
	if( xml.exists() )
		{
			AIEngine& engine = AIEngine::getInstance();
			engine.destroyXmlDoc( xml );
		}
}

Xml AIMessage::getXml( const char *contentType )
{
	if( !xml.exists() )
		{
			AIEngine& engine = AIEngine::getInstance();
			xml = engine.readXml( message , contentType );
		}

	ASSERT( xml.getName().equals( contentType ) );
	return( xml );
}
