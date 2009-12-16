// generic low-level functions

#ifndef	INCLUDE_AIBASETYPES_H
#define INCLUDE_AIBASETYPES_H

// utility functions & classes
#define ASSERT( x ) if( !(x) ) throw RuntimeError( String( "assertion failed (" ) + (#x) + ")" )
#define ASSERTMSG( x , msg ) if( !(x) ) throw RuntimeError( String( "assertion failed (" ) + (#x) + "): " + (msg) )
#define ASSERTFAILED( msg ) throw RuntimeError( String( "assertion failed: " ) + msg )

class Logger;

class String;
class RuntimeException;
class Timer;
class MultiIndexIterator;

template<typename T> class FlatList;
template<class T> class TwoIndexArray;
template<class T> class TwoIndexVarArray;
template<class T> class ClassList;
template<typename T> class FixedPtrList;
template<class T> class TwoIndexClassArray;
template<class T> class MapIntToClass;
template<class TK , class TV> class MapPtrToClass;
template<class T> class MapStringToClass;
template<class TA, class TC> class Sort;
template<class T> class VectorMap;

// #############################################################################
// #############################################################################

class String
{
public:
	String();
	~String();
	String( const char *s );
	String( const String& s );
	String( const char *s , int len );

	String& operator +=( const char *v );
	String& operator +=( char v );
	String& operator +=( int v );
	String& operator +=( float v );
	operator const char *() const;
	String& operator =( const char *s );
	String& operator =( String& s );

	bool equals( const char *s );
	void clear();
	String& append( int count , char c );
	String& append( const char *s , int nChars );
	String& assign( const char *s , int nChars );

	void resize( int length );
	char *getBuffer();
	int size() const;
	int length() const;
	bool isEmpty() const;

	int findLastAny( const char *chars );
	int findLast( char c );
	String getMid( int from , int n );
	char getChar( int index );

private:
	void createFromString( const char *s );
private:
	char *v;
};

String operator +( const String& s1 , const char *s2 );
String operator +( const String& s1 , int value );
String operator +( const String& s1 , float value );
String operator +( const String& s1 , char value );
String operator +( const String& s1 , bool value );

// #############################################################################
// #############################################################################

class RuntimeException
{
public:
	RuntimeException( unsigned int code , int skipLevels , void *p_addr );
	RuntimeException( const char *p_msg , const char *p_file , int p_line );
	void printStack( Logger& logger );
	String printStack();

	bool isSEH();
	const char *getClassName();
	const char *getFunctionName();
	const char *getMsg();

private:
	int getSkipCount();

public:
	bool seh;

	String className;
	String functionName;
	String msg;
	String file;
	String fileShort;
	int line;
	rfc_threadstack *stack;
};

#define RuntimeError( msg ) RuntimeException( msg , __FILE__ , __LINE__ )

// #############################################################################
// #############################################################################

// generic struct/simple type list, flat sequential storage
template<typename T> class FlatList
{
public:
	FlatList() { data = NULL; n = a = 0; };
	FlatList( int count ) 
		{ 
			ASSERT( count >= 0 );
			n = a = count;
			data = NULL;
			if( count > 0 )
				data = ( T * )calloc( a , sizeof( T ) );
		};
	~FlatList() { if( data != NULL ) free( data ); };

	int count() const { return( n ); };
	int size() const { return( a ); };

	void setCount( int count ) { n = count; };

	T *getAll() const { return( data ); };
	T *getAt( int index ) const { ASSERT( index >= 0 && index < a ); return( &data[ index ] ); };
	T& getRef( int index ) const { ASSERT( index >= 0 && index < a ); return( data[ index ] ); };
	T get( int index ) const { ASSERT( index >= 0 && index < a ); return( data[ index ] ); };

	void insert( int index , const T& v ) 
		{
			ASSERT( index >= 0 && index <= n );
			allocate( n + 1 );
			memmove( &data[ index + 1 ] , &data[ index ] , sizeof( T ) * ( n - index ) );
			data[ index ] = v;
			n++;
		};
	void insert( int index , int count , const T& v ) 
		{
			ASSERT( index >= 0 && index <= n );
			allocate( n + count );
			memmove( &data[ index + count ] , &data[ index ] , sizeof( T ) * ( n - index ) );
			for( int k = 0; k < count; k++ )
				data[ index + k ] = v;
			n += count;
		};
	T& first() const { return( getRef( 0 ) ); };
	T& last() const { return( getRef( n - 1 ) ); };
	T& operator []( int index ) const { return( getRef( index ) ); };

	void add( const T *values , int p_n )
		{
			allocate( n + p_n );
			for( int k = 0; k < p_n; k++ )
				data[ n + k ] = values[ k ];
			n += p_n;
		};
	int add( const T& p ) { allocate( n + 1 ); data[ n ] = p; return( n++ ); };
	int add( int count , const T& p ) 
		{ 
			allocate( n + count );
			for( int k = 0; k < count; k++ )
				data[ n + k ] = p; 

			n += count;
			return( n ); 
		};
	void clear() { memset( data , 0 , sizeof( T ) * n ); n = 0; };
	void destroy() { free( data ); data = NULL; n = a = 0; };
	void remove( int k ) 
		{ 
			ASSERT( k >= 0 && k < n ); 
			n--;
			memmove( &data[ k ] , &data[ k + 1 ] , sizeof( T ) * ( n - k ) );
			memset( &data[ n ] , 0 , sizeof( T ) );
		};
	void move( int p_from , int p_to )
		{ 
			if( p_from == p_to )
				return;

			ASSERT( p_from >= 0 && p_from < n );
			ASSERT( p_to >= 0 && p_to < n );

			T tmp;
			memcpy( &tmp , &data[ p_from ] , sizeof( T ) );
			remove( data , p_from );
			insert( p_to , &tmp );
		};
	void cut( int p_from )
		{
			if( n > p_from )
				{
					memset( &data[ p_from ] , 0 , ( n - p_from ) * sizeof( T ) );
					n = p_from;
				}
		};
	void create( int p_n ) { ASSERT( p_n >= 0 ); allocate( p_n ); n = p_n; };
	void create( int p_n , const T& value ) { ASSERT( p_n >= 0 ); allocate( p_n ); n = p_n; set( value ); };
	void set( const T& value )
		{
			for( int k = 0; k < n; k++ )
				data[ k ] = value;
		};
	void set( const T *values , int p_n )
		{
			create( p_n );
			for( int k = 0; k < p_n; k++ )
				data[ k ] = *values++;
		};
	void allocate( int an ) 
		{ 
			if( an <= a )
				return;

			an *= 2;
			if( an < 4 )
				an = 4;

			allocateExact( an );
		};
	void allocateExact( int an ) 
		{ 
			if( an <= a )
				return;

			if( data == NULL )
				data = ( T * )calloc( an , sizeof( T ) );
			else
				{
					data = ( T * )realloc( data , sizeof( T ) * an );
					memset( &data[ a ] , 0 , sizeof( T ) * ( an - a ) );
				}
			a = an;
		};

private:
	T *data;
	int n;
	int a;
};

// #############################################################################
// #############################################################################

template<class T> class TwoIndexArray
{
public:
	TwoIndexArray()
		{
			n1 = n2 = 0;
			data = NULL;
		};
	TwoIndexArray( int p_n1 , int p_n2 )
		{
			create( p_n1 , p_n2 );
		};
	void create( int p_n1 , int p_n2 )
		{ 
			n1 = p_n1; 
			n2 = p_n2;
			if( n1 > 0 && n2 > 0 )
				data = ( T * )calloc( p_n1 * p_n2 , sizeof( T ) );
			else
				data = NULL;
		};
	~TwoIndexArray() 
		{ 
			if( data != NULL )
				free( data ); 
		};

	T *operator []( int index ) { return( data + n2 * index ); };
	void setAllValues( T value ) 
		{ 
			for( int k = n1 * n2 - 1; k >= 0; k-- )
				data[ k ] = value;
		};
	void copy( const TwoIndexArray<T>& src )
		{
			memcpy( data , src.data , n1 * n2 * sizeof( T ) );
		};
	int getN1() { return( n1 ); };
	int getN2() { return( n2 ); };
	T *getData() { return( data ); };

private:
	int n1;
	int n2;
	T *data;
};

// #############################################################################
// #############################################################################

template<class T> class TwoIndexVarArray
{
public:
	TwoIndexVarArray()
		{
			n1 = 0;
			pn2 = NULL;
			data = NULL;
		};
	TwoIndexVarArray( int p_n1 ) 
		{ 
			n1 = 0;
			pn2 = NULL;
			data = NULL;

			createN1( p_n1 );
		};
	~TwoIndexVarArray() 
		{ 
			for( int k = 0; k < n1; k++ )
				if( data[ k ] != NULL )
					free( data[ k ] );
			free( pn2 );
			free( data );
		};

	int getN1() { return( n1 ); };
	int getN2( int p_index1 ) { return( pn2[ p_index1 ] ); };
	void createN1( int p_n1 )
		{
			ASSERT( data == NULL );

			n1 = p_n1; 
			pn2 = ( int * )calloc( n1 , sizeof( int ) ); 
			data = ( T ** )calloc( n1 , sizeof( T * ) );
		};

	void createN2( int p_index1 , int n2 ) 
		{ 
			ASSERT( data[ p_index1 ] == NULL );

			pn2[ p_index1 ] = n2;
			data[ p_index1 ] = ( T * )calloc( n2 , sizeof( T ) );
		};
	T *operator []( int index ) { return( data[ index ] ); };
	void setValues( int index1 , T *values )
		{
			memcpy( data[ index1 ] , values , pn2[ index1 ] * sizeof( T ) );
		};
	void initValue( T value )
		{
			for( int k = 0; k < n1; k++ )
				for( int m = 0; m < pn2[ k ]; m++ )
					data[ k ][ m ] = value;
		};
	void initZeros()
		{
			for( int k = 0; k < n1; k++ )
				memset( data[ k ] , 0 , pn2[ k ] * sizeof( T ) );
		};
	T *getValues( int index ) { return( data[ index ] ); };

private:
	int n1;
	int *pn2;
	T **data;
};

// #############################################################################
// #############################################################################

// generic class list
template<class T> class ClassList
{
public:
	ClassList() { data = rfc_lst_create( RFC_EXT_TYPEPTR ); };
	ClassList( int count ) 
		{ 
			data = rfc_lst_create( RFC_EXT_TYPEPTR ); 
			for( int k = 0; k < count; k++ )
				add( new T );
		};
	~ClassList() { rfc_lst_destroy( data ); };

	int count() const { return( rfc_lst_count( data ) ); };
	T *get( int index ) const { return( ( T * )( rfc_lst_get( data , index ) -> u_p ) ); };
	void set( int index , T *value ) { rfc_lst_get( data , index ) -> u_p = value; };
	T& getRef( int index ) const { return( *get( index ) ); };

	void insert( int index , T *v ) 
		{ 
			rfc_lst_allocate( data , data -> s_n + 1 );
			memmove( &data -> s_p[ index + 1 ] , &data -> s_p[ index ] , sizeof( RFC_TYPE ) * ( data -> s_n - index ) );
			data -> s_p[ index ].u_p = v;
			data -> s_n++;
		};
	T *first() const { int n = count(); if( n == 0 ) return( NULL ); return( get( 0 ) ); };
	T *last() const { int n = count(); if( n == 0 ) return( NULL ); return( get( n - 1 ) ); };
	T *operator [] ( int index ) const { return( get( index ) ); };
	int add( T *p ) { RFC_TYPE val; val.u_p = p; return( rfc_lst_add( data , &val ) ); };
	void clear() { rfc_lst_clear( data ); };
	void destroy() { for( int k = count() - 1; k >= 0; k-- ) delete (*this)[k]; clear(); };
	void remove( int k ) { rfc_lst_remove( data , k ); };
	void move( int p_from , int p_to ) 
		{ 
			if( p_from == p_to )
				return;

			T *v = get( p_from );
			rfc_lst_remove( data , p_from );
			insert( p_to , v );
		};
	void allocate( int n ) { if( n > count() ) rfc_lst_allocate( data , n ); };
	void create( int n ) 
		{ 
			destroy();
			allocate( n );
			for( int k = 0; k < n; k++ )
				add( new T );
		};
	void createNulls( int n ) 
		{ 
			destroy();
			allocate( n );
			for( int k = 0; k < n; k++ )
				set( k , NULL );
		};
	void sort( rfc_lst_compare pf , void *p_userdata = NULL ) 
		{ 
			if( data == NULL ) 
				return; 
			rfc_lst_sort( data , p_userdata , ( rfc_lst_compare )pf );
		};

private:
	rfc_list *data;
};

// #############################################################################
// #############################################################################

// list of items with not updated addresses
template<typename T> class FixedPtrList
{
public:
	FixedPtrList() {};
	FixedPtrList( int count , T& value ) 
		{ 
			ASSERT( count >= 0 );
			add( count , value );
		};
	~FixedPtrList() { chunks.destroy(); };

	int count() const { return( data.count() ); };
	int size() const { return( data.size() ); };

	T * const *getAll() const { return( data.getAll() ); };
	T *getAt( int index ) const { ASSERT( index >= 0 && index < data.count() ); return( data[ index ] ); };
	T& getRef( int index ) const { ASSERT( index >= 0 && index < data.count() ); return( *data[ index ] ); };

	void insert( int index , const T& v ) 
		{
			insert( index , 1 , v );
		};
	void insert( int index , int count , const T& v ) 
		{
			ASSERT( index >= 0 && index <= data.count() );
			if( count == 0 )
				return;

			// allocate data and set pointers
			int n = data.count();
			allocate( n + count );

			// save pointers
			FlatList<T *> save( count );
			memcpy( save.getAll() , data.getAll() + n , count * sizeof( T * ) );

			// move pointers
			memmove( &data[ index + count ] , &data[ index ] , sizeof( T ) * ( n - index ) );

			// move saved pointers ahead
			memcpy( data[ index ] , save.getAll() , count * sizeof( T * ) );

			// set initial values
			for( int k = 0; k < count; k++ )
				*data[ index + k ] = v;

			// set new size
			data.setCount( n + count );
		};
	T& first() const { return( getRef( 0 ) ); };
	T& last() const { return( getRef( data.count() - 1 ) ); };
	T& operator []( int index ) const { return( getRef( index ) ); };

	T *add() 
		{ 
			int n = data.count();
			allocate( n + 1 ); 
			data.setCount( n + 1 );
			return( data[ n ] ); 
		};
	int add( const T& p ) 
		{ 
			int n = data.count();
			allocate( n + 1 ); 
			*data[ n ] = p;
			data.setCount( n + 1 );
			return( n ); 
		};
	int add( int count , const T& p ) 
		{ 
			int n = data.count();
			allocate( n + count ); 
			for( int k = 0; k < count; k++ )
				*data[ n + k ] = p; 

			data.setCount( n + count );
			return( n ); 
		};
	void clear() 
		{ 
			for( int k = 0; k < chunks.count(); k++ )
				memset( chunks[ k ] -> getAll() , 0 , sizeof( T ) * chunks[ k ] -> count() ); 
			data.setCount( 0 );
		};
	void destroy() { data.destroy(); chunks.destroy(); };
	void remove( int k )
		{ 
			int n = data.count();
			ASSERT( k >= 0 && k < n );

			n--;
			memmove( &data[ k ] , &data[ k + 1 ] , sizeof( T ) * ( n - k ) );
			memset( data[ n ] , 0 , sizeof( T ) );
			data.setCount( n );
		};
	void move( int p_from , int p_to )
		{ 
			if( p_from == p_to )
				return;

			int n = data.count();
			ASSERT( p_from >= 0 && p_from < n );
			ASSERT( p_to >= 0 && p_to < n );

			T *tmp = data[ p_from ];
			if( p_from < p_to )
				memmove( data.getAll() + p_from , data.getAll() + p_from + 1 , ( p_to - p_from ) * sizeof( T * ) );
			else
				memmove( data.getAll() + p_to + 1 , data.getAll() + p_to , ( p_from - p_to ) * sizeof( T * ) );

			data[ p_to ] = tmp;
		};
	void create( int p_n ) { ASSERT( p_n >= 0 ); allocate( p_n ); data.setCount( p_n ); };
	void create( int p_n , const T& value ) { ASSERT( p_n >= 0 ); allocate( p_n ); data.setCount( p_n ); set( value ); };
	void set( const T& value )
		{
			for( int k = 0; k < data.count(); k++ )
				*data[ k ] = value;
		};
	void set( const T *values , int p_n )
		{
			create( p_n );
			for( int k = 0; k < p_n; k++ )
				*data[ k ] = *values++;
		};
	void allocate( int an ) 
		{ 
			if( an <= data.size() )
				return;

			an *= 2;
			if( an < 4 )
				an = 4;

			// count in blocks
			const int blockSize = 16;
			int blocks = an / blockSize;
			if( an % blockSize )
				blocks++;

			// allocate pointers memory
			int sizeOld = data.size();
			data.allocateExact( sizeOld + blocks * blockSize );

			// add new chunks
			T**	ptrV = data.getAll() + sizeOld;
			for( int k = 0; k < blocks; k++ )
				{
					FlatList<T> *chunk = new FlatList<T>( blockSize );
					chunks.add( chunk );

					// fill chunk pointers
					T *ptr = chunk -> getAll();
					for( int m = 0; m < blockSize; m++ )
						*ptrV++ = ptr++;
				}
		};

private:
	FlatList<T *> data; // all the pointers
	ClassList<FlatList<T> > chunks; // data spread over chunks
};

// #############################################################################
// #############################################################################

template<class T> class TwoIndexClassArray
{
public:
	TwoIndexClassArray()
		{
			n1 = n2 = 0;
			data = NULL;
		};
	TwoIndexClassArray( int p_n1 , int p_n2 )
		{
			create( p_n1 , p_n2 );
		};
	void create( int p_n1 , int p_n2 )
		{ 
			n1 = p_n1; 
			n2 = p_n2;
			if( n1 > 0 && n2 > 0 )
				{
					data = ( T ** )calloc( p_n1 * p_n2 , sizeof( T * ) );
					for( int k = 0; k < n1 * n2; k++ )
						data[ k ] = new T;
				}
			else
				data = NULL;
		};
	~TwoIndexClassArray() 
		{ 
			if( data != NULL )
				free( data ); 
		};

	void destroy() 
		{
			for( int k = n1 * n2 - 1; k >= 0; k-- )
				{
					T *& p = data[ k ];
					if( p != NULL )
						{
							delete p;
							p = NULL;
						}
				}
		}

	T **operator []( int index ) { return( data + n2 * index ); };
	void setAllValues( T& value ) 
		{ 
			for( int k = n1 * n2 - 1; k >= 0; k-- )
				*(data[ k ]) = value;
		};
	void copy( const TwoIndexClassArray<T>& src )
		{
			for( int k = n1 * n2 - 1; k >= 0; k-- )
				*(data[ k ]) = *(src.data[ k ]);
		};
	int getN1() { return( n1 ); };
	int getN2() { return( n2 ); };
	T **getData() { return( data ); };

private:
	int n1;
	int n2;
	T **data;
};

// #############################################################################
// #############################################################################

// map int to Class
template<class T> class MapIntToClass
{
public:
	MapIntToClass()
		{
			mapData = rfc_map_ptrcreate();
		};
	~MapIntToClass()
		{
			rfc_map_ptrdrop( mapData );
		};

public:
	void allocate( int count )
		{
			rfc_map_ptralloc( mapData , count );
		};

	int add( int key , T *value )
		{
			T *l_value;
			if( rfc_map_ptrcheck( mapData , ( void * )key , ( unsigned long * )&l_value ) >= 0 )
				throw RuntimeError( "MapIntToClass::add - key already exists" );

			int index = rfc_map_ptrsetkey( mapData , ( void * )key , ( unsigned long )value );
			return( index );
		};

	void add( MapIntToClass& a )
		{
			rfc_ptrmap *s = a.mapData;
			for( int k = 0; k < rfc_map_ptrcount( s ); k++ )
				rfc_map_ptradd( mapData , s -> s_p[ k ].s_x , s -> s_p[ k ].s_y );
		};

	T *set( int key , T *value )
		{
			T *l_value;
			if( rfc_map_ptrcheck( mapData , ( void * )key , ( unsigned long * )&l_value ) < 0 )
				l_value = NULL;;

			rfc_map_ptrsetkey( mapData , ( void * )key , ( unsigned long )value );
			return( l_value );
		};

	T *get( int key ) const
		{
			T *l_value;
			if( rfc_map_ptrcheck( mapData , ( void * )key , ( unsigned long * )&l_value ) < 0 )
				return( NULL );

			return( l_value );
		};

	T *removeByKey( int key )
		{
			return( ( T * )rfc_map_ptrremove( mapData , ( void * )key ) );
		};

	T *removeByPos( int pos )
		{
			ASSERT( pos >= 0 && pos < mapData -> s_n );
			return( ( T * )rfc_map_ptrremovepos( mapData , pos ) );
		};

	void clear()
		{
			rfc_map_ptrclear( mapData );
		};

	int count() const
		{
			return( rfc_map_ptrcount( mapData ) );
		};

	void destroy()
		{
			rfc_ptrmap *s = mapData;
			for( int k = 0; k < rfc_map_ptrcount( s ); k++ )
				{
					T *c = ( T * )s -> s_p[ k ].s_y;
					delete c;
				}
			rfc_map_ptrclear( mapData );
		};

	T *getClassByIndex( int k ) const
		{
			ASSERT( k >= 0 && k < rfc_map_ptrcount( mapData ) );
			return( ( T * )rfc_map_ptrget( mapData , k ) );
		};
			
	int getKeyByIndex( int k ) const
		{
			ASSERT( k >= 0 && k < rfc_map_ptrcount( mapData ) );
			return( ( int )mapData -> s_p[ k ].s_x );
		};

	void copyTo( ClassList<T>& dst )
		{
			dst.allocate( mapData -> s_n );
			for( int k = 0; k < mapData -> s_n; k++ )
				dst.add( ( T * )mapData -> s_p[ k ].s_y );
		};

	int getInsertPos( int key )
		{
			return( rfc_map_ptrinsertpos( mapData , ( void * )key ) );
		};
			
private:
	rfc_ptrmap *mapData;
};

// #############################################################################
// #############################################################################

// map ptr to class
template<class TK , class TV> class MapPtrToClass
{
public:
	MapPtrToClass()
		{
			mapData = rfc_map_ptrcreate();
		};
	~MapPtrToClass()
		{
			rfc_map_ptrdrop( mapData );
		};

public:
	void allocate( int count )
		{
			rfc_map_ptralloc( mapData , count );
		};

	TV *addCalloc( TK *key )
		{
			TV *v = ( TV * )calloc( 1 , sizeof( TV ) );
			int pos = add( key , v );
			return( getClassByIndex( pos ) );
		};

	int add( TK *key , TV *value )
		{
			TV *l_value;
			if( rfc_map_ptrcheck( mapData , ( void * )key , ( unsigned long * )&l_value ) >= 0 )
				throw RuntimeError( "MapPtrToClass::add - key already exists" );

			int index = rfc_map_ptrsetkey( mapData , ( void * )key , ( unsigned long )value );
			return( index );
		};

	void add( MapPtrToClass& a )
		{
			rfc_ptrmap *s = a.mapData;
			for( int k = 0; k < rfc_map_ptrcount( s ); k++ )
				rfc_map_ptradd( mapData , s -> s_p[ k ].s_x , s -> s_p[ k ].s_y );
		};

	TV *set( TK *key , TV *value )
		{
			TV *l_value;
			if( rfc_map_ptrcheck( mapData , ( void * )key , ( unsigned long * )&l_value ) < 0 )
				l_value = NULL;;

			rfc_map_ptrsetkey( mapData , ( void * )key , ( unsigned long )value );
			return( l_value );
		};

	TV *get( TK *key )
		{
			TV *l_value;
			if( rfc_map_ptrcheck( mapData , ( void * )key , ( unsigned long * )&l_value ) < 0 )
				return( NULL );

			return( l_value );
		};

	TV *remove( TK *key )
		{
			return( ( TV * )rfc_map_ptrremove( mapData , ( void * )key ) );
		};

	void clear()
		{
			rfc_map_ptrclear( mapData );
		};

	int count()
		{
			return( rfc_map_ptrcount( mapData ) );
		};

	void free()
		{
			rfc_ptrmap *s = mapData;
			for( int k = 0; k < rfc_map_ptrcount( s ); k++ )
				{
					TV *c = ( TV * )s -> s_p[ k ].s_y;
					::free( c );
				}
			rfc_map_ptrclear( mapData );
		};

	TV *getClassByIndex( int k )
		{
			ASSERT( k >= 0 && k < rfc_map_ptrcount( mapData ) );
			return( ( TV * )rfc_map_ptrget( mapData , k ) );
		};
			
	TK *getKeyByIndex( int k )
		{
			ASSERT( k >= 0 && k < rfc_map_ptrcount( mapData ) );
			return( ( TK * )mapData -> s_p[ k ].s_x );
		};
			
private:
	rfc_ptrmap *mapData;
};

// #############################################################################
// #############################################################################

// map String to Class
template<class T> class MapStringToClass
{
public:
	MapStringToClass()
		{
			mapData = rfc_map_strcreate();
		};
	~MapStringToClass()
		{
			rfc_map_strdrop( mapData );
		};

public:
	void allocate( int count )
		{
			rfc_map_stralloc( mapData , count );
		};

	int add( const char *key , T *value )
		{
			T *l_value;
			if( rfc_map_strcheck( mapData , key , ( void ** )&l_value ) >= 0 )
				throw RuntimeError( "MapStringToClass::add - key already exists" );

			int index = rfc_map_strsetkey( mapData , key , value );
			return( index );
		};

	void add( MapStringToClass& a )
		{
			rfc_strmap *s = a.mapData;
			for( int k = 0; k < rfc_map_strcount( s ); k++ )
				rfc_map_stradd( mapData , s -> s_p[ k ].s_x , s -> s_p[ k ].s_y );
		};

	T *set( const char *key , T *value )
		{
			T *l_value;
			if( rfc_map_strcheck( mapData , key , ( void ** )&l_value ) < 0 )
				l_value = NULL;;

			rfc_map_strsetkey( mapData , key , value );
			return( l_value );
		};

	T *get( const char *key )
		{
			T *l_value;
			if( rfc_map_strcheck( mapData , key , ( void ** )&l_value ) < 0 )
				return( NULL );

			return( l_value );
		};
	// return item from which given string begins
	T *getPartial( const char *key )
		{
			int n = rfc_map_strcount( mapData );
			if( n == 0 )
				return( NULL );

			int fp = rfc_map_strinsertpos( mapData , key );

			// check returned - it could be equal to required
			if( fp < n )
				{
					const char *kfp = mapData -> s_p[ fp ].s_x;
					if( !strcmp( kfp , key ) )
						return( ( T * )mapData -> s_p[ fp ].s_y );
				}

			// check previous - it could be partially equal to returned
			if( fp > 0 )
				{
					fp--;
					const char *kfp = mapData -> s_p[ fp ].s_x;
					if( !strncmp( kfp , key , strlen( kfp ) ) )
						return( ( T * )mapData -> s_p[ fp ].s_y );
				}

			return( NULL );
		};

	T *remove( const char *key )
		{
			return( ( T * )rfc_map_strremove( mapData , key ) );
		};

	void clear()
		{
			rfc_map_strclear( mapData );
		};

	int count()
		{
			return( rfc_map_strcount( mapData ) );
		};

	void destroy()
		{
			rfc_strmap *s = mapData;
			for( int k = 0; k < rfc_map_strcount( s ); k++ )
				{
					T *c = ( T * )s -> s_p[ k ].s_y;
					delete c;
				}
			rfc_map_strclear( mapData );
		};

	T *getClassByIndex( int k )
		{
			if( k < 0 || k >= rfc_map_strcount( mapData ) )
				throw RuntimeError( "MapStringToClass::getByIndex - invalid index" );

			return( ( T * )rfc_map_strget( mapData , k ) );
		};
			
	const char *getKeyByIndex( int k )
		{
			if( k < 0 || k >= rfc_map_strcount( mapData ) )
				throw RuntimeError( "MapStringToClass::getByIndex - invalid index" );

			return( mapData -> s_p[ k ].s_x );
		};
			
private:
	rfc_strmap *mapData;
};

// #############################################################################
// #############################################################################

class Timer
{
public:
	Timer();
	Timer( int waitTime );

public:
	// time passed - in ms
	int timePassed();
	bool go();

private:
	long timeStarted;
	int waitTime;
};

// #############################################################################
// #############################################################################

template<class TA, class TC> class Sort
{
	typedef int (TC::*PF)( const TA& v1 , const TA& v2 );

public:
	Sort( TA *va , int n , TC *p_p , int (TC::*p_pf)( const TA& v1 , const TA& v2 ) )
		{
			p = p_p;
			pf = p_pf;
			rfc_qsort( this , va , n , sizeof( TA ) , qsortcb );
		};
	static int qsortcb( void *p_userdata , const void *p_el1 , const void *p_el2 )
		{
			Sort *cThis = ( Sort * )p_userdata;
			TC *p = cThis -> p;
			PF pf = cThis -> pf;
			return( ( p ->* pf )( *( TA * )p_el1 , *( TA * )p_el2 ) );
		};

private:
	TC *p;
	PF pf;
};

// #############################################################################
// #############################################################################

class MultiIndexIterator
{
public:
	MultiIndexIterator( int numberOfAxis , int axisPoints );
	~MultiIndexIterator();

public:
	void start();
	void startAround( MultiIndexIterator& point );
	void startDistinctUnsorted();

	bool next();
	bool nextAround();
	bool nextDistinctUnsorted();

	int getGlobalIndex();
	int getGlobalIndexAround();

	int getAxisIndex( int axis );
	int getAxisIndexAround( int axis );

	int getNumberOfAxis();
	int getAxisPoints();

	bool hasEqualIndexes();

private:
	bool isBeyondAround();

private:
	int totalPoints;
	int numberOfAxis;
	int axisPoints;

	int *axisIndex; // [numberOfAxis]
	int globalIndex;

	int *axisIndexAround; // [numberOfAxis], delta for axisIndex, 0=0,1=1,2=-1
	int globalIndexAround;
};

// #############################################################################
// #############################################################################

template<class T> class VectorMapItem
{
public:
	VectorMapItem( int p_nIn , int p_nOut )
		{
			nIn = p_nIn;
			nOut = p_nOut;
			vIn = ( T * )calloc( nIn , sizeof( T ) );
			vOut = ( T * )calloc( nOut , sizeof( T ) );
		};
	~VectorMapItem()
		{
			free( vIn );
			free( vOut );
		};

	T *in() { return( vIn ); };
	T *out() { return( vOut ); };

	int getNIn() { return( nIn ); };
	int getNOut() { return( nOut ); };

	void set( T *in , T *out )
		{
			if( in != NULL )
				memcpy( vIn , in , sizeof( T ) * nIn );
			if( out != NULL )
				memcpy( vOut , out , sizeof( T ) * nOut );
		};

private:
	int nIn;
	int nOut;
	T *vIn;
	T *vOut;
};

template<class T> class VectorMap
{
public:
	VectorMap( int p_nIn , int p_nOut ) 
		{ 
			ASSERT( p_nIn > 0 && p_nOut > 0 );
			nIn = p_nIn;
			nOut = p_nOut;
		};
	~VectorMap() 
		{ 
			data.destroy();
		};

	int count() { return( data.count() ); };
	int sizeIn() { return( nIn ); };
	int sizeOut() { return( nOut ); };
	VectorMapItem<T> *operator []( int index ) { return( get( index ) ); };
	VectorMapItem<T> *get( int index ) 
		{
			ASSERT( index >= 0 && index < data.count() ); 
			return( data[ index ] );
		};

	int add( T *vIn , T *vOut )
		{
			VectorMapItem<T> *p = new VectorMapItem<T>( nIn , nOut );
			memcpy( p -> in() , vIn , nIn * sizeof( T ) );
			memcpy( p -> out() , vOut , nOut * sizeof( T ) );
			return( data.add( p ) );
		};

	int add( VectorMapItem<T> *p )
		{
			return( add( p -> in() , p -> out() ) );
		};

	void add( VectorMap *vm )
		{
			for( int k = 0; k < vm -> count(); k++ )
				add( vm -> get( k ) );
		};

private:
	int nIn;
	int nOut;
	ClassList<VectorMapItem<T> > data;
};

// #############################################################################
// #############################################################################

#define ABS( x ) ( ( (x) > 0 )? (x) : -(x) )

extern float getMin( float v1 , float v2 );
extern float getMax( float v1 , float v2 );
extern float getMinMul( float a1 , float a2 , float b1 , float b2 );
extern float getMaxMul( float a1 , float a2 , float b1 , float b2 );

extern String aiutils_getnextlinefromfile( FILE *f );
extern int compareFloats( float v1 , float v2 , float tolerance = 0.000001 );
extern void freadString( String& s , FILE *f );

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIBASETYPES_H
