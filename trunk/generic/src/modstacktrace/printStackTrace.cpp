#include "printStackTrace.h"
#include "StackTrace.h"
#include "MapFile.h"
#include <stdio.h>
#include <string.h>

//-----------------------------------------------------------------------------

using namespace MAPFILE;

//-----------------------------------------------------------------------------

/**
 * Prints stack trace using callback
 */
extern "C" short getThreadStackTrace( unsigned long thread , void *ptr , ::getStackTraceCB cb )
{
	// find out map file name
	char modname[500];
	MapFile::getModuleMapFilename( modname, sizeof(modname) );

	// parse map file
	MapFile map( modname );
	if( map.error() )
	{
		( *cb )( ptr , modname , NULL , NULL , map.errorString() );
		if( map.error() )
			return( 0 );
	}

	// print stack trace into buffer
	MapFile* maps[] = {&map};
	if( StackTrace::getStackTrace( thread , maps, 1, ptr , cb ) )
		return( 1 );

	return( 0 );
}

extern "C" short getModuleItemByAddr( void *p_addr , char *p_class , char *p_func )
{
	// find out map file name
	char modname[500];
	MapFile::getModuleMapFilename( modname, sizeof(modname) );

	// print stack trace to buffer
	MapFile map( modname );
	if( map.error() )
		return( 0 );

	int entry = map.findSymbol( ( long )p_addr );
	if( entry < 0 )
		return( 0 );

	StackTrace::fillMapEntry( map , entry , p_class , p_func );
	return( true );
}

/*
 * Copyright (c) 2001 Jani Kajala
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Jani Kajala makes no representations about the suitability 
 * of this software for any purpose. It is provided "as is" 
 * without express or implied warranty.
 */

// modified by VS 2009
