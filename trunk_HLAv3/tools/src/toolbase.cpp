#include <ah_tools.h>
#include <ah_consoletool.h>

/*#########################################################################*/
/*#########################################################################*/

ToolBase::ToolBase( String p_name ) {
	name = p_name;
	logger.attachCustom( name );
}

ToolBase *ToolBase::getTool( String name ) {
	if( name.equals( "console" ) )
		return( new ConsoleTool() );

	return( NULL );
}
