#include "StackTrace.h"
#include "MapFile.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>

//-----------------------------------------------------------------------------

#define MAX_DEPTH 256

//-----------------------------------------------------------------------------

namespace MAPFILE
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

// if thread is NULL - use for current thread, otherwise can be used only for suspended thread
bool StackTrace::getStackTrace( unsigned long thread , MapFile** map, int maps, void *ptr , getStackTraceCB cb )
{
	// list callers
	long callersAddr[ MAX_DEPTH ];
	int callers = 0;
	int i;
	bool longStack = false;
	bool errorGettingStack = false;

	// handle foreign thread
	CONTEXT saveContext;
	if( thread != NULL )
		switchContext( thread , &saveContext );

	long addr;
	for( i = 1; i <= MAX_DEPTH; i++ )
		{
			if( i == MAX_DEPTH )
				{
					longStack = true;
					break;
				}

			try
				{
					addr = getCaller( i );
				}
			catch( ... )
				{
					errorGettingStack = true;
					break;
				}

			callersAddr[ callers++ ] = addr;

			// check it is final function
			if( addr == 0 )
				break;
		}

	// restore context
	if( thread != NULL )
		restoreContext( thread , &saveContext );

	// output call stack
	int needed = 0;
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
					entry = map[ j ] -> findSymbol( addr );
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
			sprintf( addrName , "0x%x", addr );

			const char *entryName = NULL;
			if( entryMap != NULL )
				entryName = entryMap -> getSymbol( entry ) -> f_symname;

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

	const char *entryName = map.getSymbol( entry ) -> f_symname;
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

void StackTrace::switchContext( unsigned long thread , void *saveContext )
{
	// can be used only for suspended threads
	// get context
	CONTEXT *context = ( CONTEXT * )saveContext;
	CONTEXT foreign;
	::GetThreadContext( ( HANDLE )thread , &foreign );

	DWORD ebxSave , ebpSave, ecxSave, eaxSave;
	DWORD ebxSet , ebpSet, ecxSet, eaxSet;

	ebxSet = foreign.Ebx;
	ebpSet = foreign.Ebp;
	ecxSet = foreign.Ecx;
	eaxSet = foreign.Eax;

	// set context of current thread to required thread, save existing state
	__asm
	{
		mov ebxSave, ebx
		mov ebpSave, ebp
		mov ecxSave, ecx
		mov eaxSave, eax
		mov ebx, ebxSet
		mov ebp, ebpSet
		mov ecx, ecxSet
		mov eax, eaxSet
	}

	context -> Ebx = ebxSave;
	context -> Ebp = ebpSave;
	context -> Ecx = ecxSave;
	context -> Eax = eaxSave;
}

void StackTrace::restoreContext( unsigned long thread , void *saveContext )
{
	// can be used only for suspended threads
	// restore context of current thread
	CONTEXT *context = ( CONTEXT * )saveContext;

	DWORD ebxSet , ebpSet, ecxSet, eaxSet;
	ebxSet = context -> Ebx;
	ebpSet = context -> Ebp;
	ecxSet = context -> Ecx;
	eaxSet = context -> Eax;

	__asm
	{
		mov ebx, ebxSet
		mov ebp, ebpSet
		mov ecx, ecxSet
		mov eax, eaxSet
	}
}

} // dev
