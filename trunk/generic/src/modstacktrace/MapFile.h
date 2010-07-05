#ifndef _DEV_MAPFILE_H
#define _DEV_MAPFILE_H


namespace MAPFILE
{

/** An entry in the map file. */
typedef struct
{
	long	f_section;
	long	f_addr;
	long	f_fulladdr;
	char	f_type1;
	char	f_type2;
	char	*f_symname;
	char	*f_symlib;
	char	*f_symfile;
} MAP_FILE_SYMBOL;

/** 
 * Linker generated module map file parser.
 */
class MapFile
{
public:
	/** Error code. */
	enum ErrorType
	{
		/** No error. */
		ERROR_NONE,
		/** File open failed. */
		ERROR_OPEN,
		/** File reading failed. */
		ERROR_READ,
		/** Syntax error. */
		ERROR_PARSE
	};

	/** Reads a map file. */
	explicit MapFile( const char* filename );

	///
	~MapFile();

	/** Returns preferred load address. */
	long				loadAddressPlanned() const;
	long				loadAddressActual() const;

	/** Returns number of entries in the map file. */
	int					symbols() const;
	const MAP_FILE_SYMBOL	*getSymbol( int i ) const;

	/** Returns error code or 0 (ERROR_NONE) if no error. */
	ErrorType			error();
	const char *		errorString();

	/** Returns line number of last successful read character. */
	int					line() const;

	/** 
	 * Finds entry which contains specified address. 
	 * @return Entry index or -1 if not found.
	 */
	int					findSymbol( long addr ) const;

	/** 
	 * Returns current module name, with map extension.
	 * The output buffer is always 0-terminated.
	 */
	static void			getModuleMapFilename( char* buffer, int bufferSize );

private:
	class MapFileImpl;
	MapFileImpl* m_this;

	MapFile( const MapFile& );
	MapFile& operator=( const MapFile& );
};


} // dev


#endif // _DEV_MAPFILE_H
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
