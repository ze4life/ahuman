#include <ah_tools.h>
#include <ah_consoletool.h>

/*#########################################################################*/
/*#########################################################################*/

ToolBase *ToolBase::getTool( String name ) {
	if( name.equals( "console" ) )
		return( new ConsoleTool() );

	return( NULL );
}
