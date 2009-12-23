#include "StackTrace.h"
#include "MapFile.h"
#include "MapFileEntry.h"
#include <string.h>
#include <stdio.h>

//-----------------------------------------------------------------------------

#define MAX_DEPTH 256

//-----------------------------------------------------------------------------

namespace dev
{


static long getCaller( int index )
{
#if defined(_DEBUG) && defined(_MSC_VER) && defined(_M_IX86)

	long caller = 0;
	__asm
	{
		mov ebx, ebp
		mov ecx, index
		inc ecx
		xor eax, eax
StackTrace_getCaller_next:
		mov eax, [ebx+4]
		mov ebx, [ebx]
		dec ecx
		jnz StackTrace_getCaller_next
		mov caller, eax
	}
	return caller;

#else

	return 0;

#endif
}

bool StackTrace::getStackTrace( MapFile** map, int maps, void *ptr , getStackTraceCB cb )
{
	// list callers
	long callersAddr[ MAX_DEPTH ];
	int callers = 0;
	int i;
	bool longStack = false;
	bool errorGettingStack = false;

	long addr;
	for( i = 1; i <= MAX_DEPTH; i++ )
		{
			if( i == MAX_DEPTH )
				{
					longStack = true;
					break;
				}
			/* TODO: Modified while migrating to eclipse */
			try
				{
					addr = getCaller( i );
				}
			catch(...)
				{
					errorGettingStack = true;
					break;
				}

			callersAddr[ callers++ ] = addr;

			// check it is final function
			if( addr == 0 )
				break;
		}

	// output call stack
	char names[ 600 ];
	char moduleName[ 600 ];
	for( i = 1; i < callers; i++ )
		{
			long addr = callersAddr[ callers - i - 1 ];

			// find entry info
			int entry = -1;
			const MapFile *entryMap = NULL;
			for( int j = 0; j < maps; j++ )
				{
					entry = map[ j ] -> findEntry( addr );
					if( entry != -1 )
						{
							entryMap = map[j];
							break;
						}
				}

			// format entry to temporary buf
			if( entryMap != NULL )
				entryMap -> getModuleMapFilename( moduleName , sizeof( moduleName ) );
			else
				strcpy( moduleName , "unknown" );
			char addrName[ 30 ];
			sprintf( addrName , "0x%x", ( unsigned int )addr );

			const char *entryName = NULL;
			if( entryMap != NULL )
				entryName = entryMap -> getEntry( entry ).name();

			// split into class/function
			char *functionName = NULL;
			char *className = NULL;

			if( entryName != NULL )
				{
					strcpy( names , entryName );
					className = strchr( names , '.' );
					if( className != NULL )
						{
							*className++ = 0;
							functionName = names;
						}
					else
						functionName = names;
				}

			( *cb )( ptr , moduleName , className , functionName , addrName );
		}

	// inform about partially reported stack
	if( errorGettingStack )
		( *cb )( ptr , "UNKNOWN" , "UNKNOWN" , "..." , "Error while getting stack" );
	else
	if( longStack )
		( *cb )( ptr , "UNKNOWN" , "UNKNOWN" , "..." , "Too deep stack" );
	else
		return( true );

	return( false );
}

void StackTrace::fillMapEntry( MapFile& map , int entry , char *p_class , char *p_func )
{
	*p_class = 0;
	*p_func = 0;

	const char *entryName = map.getEntry( entry ).name();
	if( entryName == NULL )
		return;

	// split into class/function
	char *functionName = NULL;
	char *className = NULL;

	char names[ 600 ];
	strcpy( names , entryName );
	className = strchr( names , '.' );
	if( className != NULL )
		{
			*className++ = 0;
			functionName = names;
		}
	else
		functionName = names;

	if( className != NULL )
		strcpy( p_class , className );
	if( functionName != NULL )
		strcpy( p_func , functionName );
}

} // dev
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
