#include "MapFile.h"
#include "TextFile.h"
#include <string.h>
#include <ctype.h>
#ifdef WIN32
#include <windows.h>
#include <Psapi.h>
#endif

//-----------------------------------------------------------------------------

namespace MAPFILE
{

extern "C" int onSortMapSymbols( const void *p_e1 , const void *p_e2 )
{
	// sort by address
	return( (*( const MAP_FILE_SYMBOL ** )p_e1) -> f_fulladdr - (*( const MAP_FILE_SYMBOL ** )p_e2) -> f_fulladdr );
}

class MapFile::MapFileImpl
{
public:
	long				loadAddrPlanned;
	long				loadAddrActual;
	char				name[256];
	MAP_FILE_SYMBOL		**symbols;
	int					symbols_n;
	int					symbols_a;

	MapFileImpl( const char* filename ) :
		loadAddrPlanned(0), m_file( filename ), m_err( MapFile::ERROR_NONE ) , m_errString( NULL )
	{
		loadAddrActual = 0;
		symbols_n = 0;
		symbols_a = 1024;
		symbols = ( MAP_FILE_SYMBOL ** )calloc( sizeof( MAP_FILE_SYMBOL * ) , symbols_a );

		if( m_file.error() )
			return;

		m_file.readString( name, sizeof(name) );

		char buf[1024];
		while ( m_file.readString(buf,sizeof(buf)) )
		{
			if ( !strcmp("Preferred",buf) )
				parseLoadAddress();
			else if ( !strcmp("Start",buf) )
				parseSegments();
			else if ( !strcmp("Address",buf) )
				parseEntries();
			else
				m_file.skipLine();
		}

		qsort( symbols , symbols_n , sizeof( MAP_FILE_SYMBOL * ) , onSortMapSymbols );
		loadAddrActual = loadAddrPlanned;
	}

	~MapFileImpl()
	{
		if( m_errString != NULL )
			free( m_errString );

		// free data
		if( symbols != NULL ) {
			for( int k = 0; k < symbols_n; k++ )
				free( symbols[ k ] );

			free( symbols );
		}
	}

	MapFile::ErrorType error()
	{
		if ( m_err != MapFile::ERROR_NONE )
			return m_err;

		setErrorString( m_file.getErrorString() );
		switch ( m_file.error() )
		{
		case TextFile::ERROR_OPEN:	return MapFile::ERROR_OPEN;
		case TextFile::ERROR_READ:	return MapFile::ERROR_READ;
		case TextFile::ERROR_PARSE:	return MapFile::ERROR_PARSE;
		default:					return MapFile::ERROR_NONE;
		}
	}
	
	const char *errorString()
	{
		error();
		return( m_errString );
	}

	void setErrorString( const char *text )
	{
		if( m_errString != NULL ) {
			free( m_errString );
			m_errString = NULL;
		}
		
		m_errString = _strdup( text );
	}

	int line() const
	{
		if ( m_err != MapFile::ERROR_NONE )
			return m_errLine;

		return m_file.line();
	}
	
private:
	TextFile			m_file;
	MapFile::ErrorType	m_err;
	int					m_errLine;
	char *				m_errString;

	/**
	 * Returns true if the next line is empty.
	 */
	bool nextLineEmpty()
	{
		m_file.skipLine();
		char ch;
		while ( m_file.peekChar(&ch) && isspace(ch) && ch != '\n' )
			m_file.readChar( &ch );
		if ( m_file.peekChar(&ch) && ch == '\n' )
			return true;
		return false;
	}

	/** 
	 * Parses specified string. 
	 * Sets error if parsed string doesnt match. 
	 */
	void parse( const char* str )
	{
		char buf[256];
		m_file.readString( buf, sizeof(buf) );
		if ( strcmp(str,buf) )
		{
			m_err = MapFile::ERROR_PARSE;
			m_errLine = m_file.line();
		}
	}

	/**
	 * Parses specified character. 
	 * Sets error if parsed character doesnt match. 
	 */
	void parse( char ch )
	{
		char ch2;
		if ( !m_file.readChar(&ch2) || ch2 != ch )
		{
			m_err = MapFile::ERROR_PARSE;
			m_errLine = m_file.line();
		}
	}

	/**
	 * Example:
	 * (Preferred) load address is 00400000
	 */
	void parseLoadAddress()
	{
		parse( "load" ); parse( "address" ); parse( "is" );
		loadAddrPlanned = m_file.readHex();
	}

	/**
	 * Example:
	 * (Start)       Length     Name                   Class
	 * 0001:00000000 00002c05H .text                   CODE
	 */
	void parseSegments()
	{
		// ignore this section
		parse( "Length" );
		parse( "Name" );
		parse( "Class" );
		m_file.skipWhitespace();
		
		while ( !error() )
		{
			// break at empty line
			if ( nextLineEmpty() )
				break;
		}
	}

	void addNewSymbol( long seg , long offs , const char *entryname , long fulladdr , char type1 , char type2 , const char *libname , const char *objname )
	{
		// calc sizes
		int l_len = sizeof( MAP_FILE_SYMBOL );
		if( entryname != NULL )
			l_len += strlen( entryname ) + 1;
		if( libname != NULL )
			l_len += strlen( libname ) + 1;
		if( objname != NULL )
			l_len += strlen( objname ) + 1;

		MAP_FILE_SYMBOL *s = ( MAP_FILE_SYMBOL * )calloc( 1 , l_len );
		s -> f_section = seg;
		s -> f_addr = offs;
		s -> f_fulladdr = fulladdr;
		s -> f_type1 = type1;
		s -> f_type2 = type2;

		char *writeptr = ( char * )( s + 1 );
		if( entryname != NULL ) {
			s -> f_symname = writeptr;
			strcpy( writeptr , entryname );
			writeptr += strlen( entryname ) + 1;
		}

		if( libname != NULL ) {
			s -> f_symlib = writeptr;
			strcpy( writeptr , libname );
			writeptr += strlen( libname ) + 1;
		}
		
		if( objname != NULL ) {
			s -> f_symfile = writeptr;
			strcpy( writeptr , objname );
			writeptr += strlen( objname ) + 1;
		}

		// add to array
		if( symbols_a == symbols_n ) {
			symbols_a *= 2;
			symbols = ( MAP_FILE_SYMBOL ** )realloc( symbols , symbols_a * sizeof( MAP_FILE_SYMBOL * ) );
		}

		symbols[ symbols_n++ ] = s;
	}


	/**
	 * Example:
	 * (Address)       Publics by Value           Rva+Base     Lib:Object
	 * 0002:000aa6b0       ??_GTestUnit@@QAEPAXI@Z    005106b0 f i test.obj
 	 */
	void parseEntries()
	{
		parse( "Publics" ); parse( "by" ); parse( "Value" );
		parse( "Rva+Base" );
		parse( "Lib:Object" );
		m_file.skipWhitespace();
		
		while ( !error() )
		{
			int seg = m_file.readHex();
			parse( ':' );
			int offs = m_file.readHex();
			char symbol[256];
			m_file.readString( symbol, sizeof(symbol) );
			char* entryname = symbol;
			int fulladdr = m_file.readHex();
			char space;
			char type1;
			char type2;
			m_file.readChar( &space ); m_file.readChar( &type1 ); m_file.readChar( &space ); m_file.readChar( &type2 ); m_file.readChar( &space ); 
			char obj[256];
			m_file.readString( obj, sizeof(obj) );
			char *libname = NULL;
			char *objname = strchr( obj , ':' );
			if( objname != NULL ) {
				libname = obj;
				*objname++ = 0;
			}
			else {
				libname = NULL;
				objname = obj;
			}

			// chop entry name at @@
			char* end = strstr( entryname, "@@" );
			if ( end )
				*end = 0;
			// skip preceding ?01..
			while ( isdigit(*entryname) || *entryname == '?' || *entryname == '$' )
				++entryname;
			// conv @ -> .
			for ( char* str = entryname ; *str ; ++str )
				if ( *str == '@' )
					*str = '.';

			addNewSymbol( seg , offs , entryname , fulladdr , type1 , type2 , libname , objname );

			// break at empty line
			if ( nextLineEmpty() )
				break;
		}
	}
};

//-----------------------------------------------------------------------------

MapFile::MapFile( const char* filename )
{
	m_this = new MapFileImpl( filename );
}

MapFile::~MapFile()
{
	delete m_this;
}

long MapFile::loadAddressPlanned() const
{
	return m_this->loadAddrPlanned;
}

long MapFile::loadAddressActual() const
{
	return m_this->loadAddrActual;
}

const MAP_FILE_SYMBOL *MapFile::getSymbol( int i ) const
{
	return m_this->symbols[i];
}

int MapFile::symbols() const
{
	return m_this->symbols_n;
}

MapFile::ErrorType MapFile::error()
{
	return m_this->error();
}

const char *MapFile::errorString()
{
	return( m_this->errorString() );
}

int MapFile::line() const
{
	return m_this->line();
}

int MapFile::findSymbol( long addr ) const
{
	// rewrite address to planned one
	long addrPlanned = addr - loadAddressActual() + loadAddressPlanned();

	// check it is after last address
	MAP_FILE_SYMBOL **ss = m_this -> symbols;
	int n = m_this -> symbols_n;
	if( addr > ss[ n - 1 ] -> f_fulladdr )
		return( -1 );

	// find with linear search in sorted array
	for( int k = n - 1; k >= 0; k-- )
		if( ss[ k ] -> f_fulladdr < addr )
			return( k );

	return( -1 );
}

void MapFile::getModuleMapFilename( char* buffer, int bufferSize )
{
	int len = 0;
	buffer[len] = 0;

#ifdef WIN32
	// get name of the exe/dll
	len = GetModuleFileName( GetModuleHandle(0), buffer, bufferSize-1 );
	buffer[len] = 0;
#endif

	// remove .exe or .dll extension
	if ( len > 3 && 
		(!strcmp(buffer+len-4,".exe") || !strcmp(buffer+len-4,".EXE") || 
		!strcmp(buffer+len-4,".DLL") || !strcmp(buffer+len-4,".dll")) )
	{
		buffer[len-4] = 0;
	}

	// append .map extension
	if ( (int)strlen(buffer)+4 < bufferSize )
	{
		strcat( buffer, ".map" );
	}
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
