/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/
/* routines */

typedef struct 
{
	char *	s_mem;			/* blob memory head */
	int		s_a;			/* blob allocated size */
	char	s_data[ 1 ];	/* active pointer memory (rfc_blob.s_ptr) */
} rfc_blobdata;

#define SIZE_OF_RFC_BLOBDATA		offsetof( rfc_blobdata , s_data )

static rfc_blobdata *
	_rfc_blob_data( const rfc_blob *p_blob )
{
	if( p_blob -> s_ptr == NULL )
		return( NULL );
	return( ( rfc_blobdata * )( p_blob -> s_ptr - SIZE_OF_RFC_BLOBDATA ) );
}

/*#######################################################*/
/*#######################################################*/

/* blob allocation and free */
void
	rfc_blob_alloc( rfc_blob *p_blob , int p_size )
{
	rfc_blobdata *l_data;
	l_data = ( rfc_blobdata * )calloc( 1 , SIZE_OF_RFC_BLOBDATA + p_size );
	l_data -> s_mem = ( char * )l_data;
	l_data -> s_a = p_size;

	p_blob -> s_ptr = l_data -> s_data;
	p_blob -> s_size = 0;
}

/* blob empty */
void
	rfc_blob_empty( rfc_blob *p_blob )
{
	rfc_blobdata *l_data;
	int l_alloc;

	if( p_blob -> s_ptr == NULL )
		return;

	l_data = _rfc_blob_data( p_blob );
	l_alloc = l_data -> s_a;

	l_data = ( rfc_blobdata * )l_data -> s_mem;
	l_data -> s_mem = ( char * )l_data;
	l_data -> s_a = l_alloc;

	p_blob -> s_ptr = l_data -> s_data;
	p_blob -> s_size = 0;
}

void
	rfc_blob_reserve( rfc_blob *p_blob , int p_size )
{
	rfc_blob_realloc( p_blob , p_size );
	memset( p_blob -> s_ptr + p_blob -> s_size , 0 , p_size );
	p_blob -> s_size += p_size;
}

/* blob reallocation */
void
	rfc_blob_realloc( rfc_blob *p_blob , int p_size_add )
{
	rfc_blobdata *l_data;
	int l_alloc;
	int l_offset;
	int l_space;
	char *l_p;

	/* get space left */
	l_data = _rfc_blob_data( p_blob );
	if( l_data == NULL )
		{
			/* create new */
			rfc_blob_alloc( p_blob , p_size_add );
		}
	else
		{
			/* check reallocate */
			l_space = ( l_data -> s_mem + SIZE_OF_RFC_BLOBDATA + l_data -> s_a ) - ( p_blob -> s_ptr + p_blob -> s_size );
			if( l_space < p_size_add )
				{
					/* for the future append reserve */
					l_alloc = l_data -> s_a + ( p_size_add - l_space ) + 64;
					l_offset = p_blob -> s_ptr - l_data -> s_mem;
					l_p = ( char * )realloc( l_data -> s_mem , SIZE_OF_RFC_BLOBDATA + l_alloc );

					p_blob -> s_ptr = l_p + l_offset;
					l_data = _rfc_blob_data( p_blob );
					l_data -> s_a = l_alloc;
					l_data -> s_mem = l_p;
				}
		}
}

/* replace blob data */
void
	rfc_blob_copy( rfc_blob *p_dest , const rfc_blob *p_source )
{
	rfc_blob_empty( p_dest );
	rfc_blob_realloc( p_dest , p_source -> s_size );

	p_dest -> s_size = p_source -> s_size;
	memcpy( p_dest -> s_ptr , p_source -> s_ptr , p_source -> s_size );
}

/* get allocated size */
int
	rfc_blob_size( const rfc_blob *p_blob )
{
	rfc_blobdata *l_data = _rfc_blob_data( p_blob );
	if( l_data == NULL )
		return( 0 );
	return( l_data -> s_a );
}

/* append item to blob */
int
	rfc_blob_add( rfc_blob *p_blob , int p_type , const RFC_TYPE *p_data )
{
	int l_size;
	const unsigned char *l_ptr;
	unsigned char l_v[ 8 ];
	int l_space_add;
	unsigned char *l_p;

	/* get space needed for value */ 
	if( p_data == NULL )
		l_size = 0;
	else
		{
			switch( p_type )
				{
					case RFC_EXT_TYPESHORT :
						l_size = sizeof( short );
						_RFC_SET_SHORT( l_v , p_data -> u_d );
						l_ptr = l_v;
						break;
					case RFC_EXT_TYPELONG :
					case RFC_EXT_TYPEMOMENT :
					case RFC_EXT_TYPETIMET :
						l_size = sizeof( long );
						_RFC_SET_LONG( l_v , p_data -> u_l );
						l_ptr = l_v;
						break;
					case RFC_EXT_TYPEMONEY :
						l_size = sizeof( RFC_INT64 );
						_RFC_SET_MONEY( l_v , p_data -> u_mm );
						l_ptr = l_v;
						break;
					case RFC_EXT_TYPEDOUBLE :
						l_size = sizeof( double );
						l_ptr = ( const unsigned char * )p_data;
						break;
					case RFC_EXT_TYPEFLOAT :
						l_size = sizeof( float );
						l_ptr = ( const unsigned char * )p_data;
						break;
					case RFC_EXT_TYPEWCHAR :
						if( p_data -> u_wc == NULL )
							l_size = 0;
						else
							l_size = rfc_wstr_len( p_data -> u_wc ) * 2 + 2;
						l_ptr = ( const unsigned char * )p_data -> u_wc;
						break;
					case RFC_EXT_TYPELCHAR :
						if( p_data -> u_lc.s_ptr == NULL )
							l_size = 0;
						else
							l_size = strlen( p_data -> u_lc.s_ptr ) + 1;
						l_ptr = ( const unsigned char * )p_data -> u_lc.s_ptr;
						break;
					case RFC_EXT_TYPECHAR :
					case RFC_EXT_TYPESTRING :
						if( p_data -> u_s == NULL )
							l_size = 0;
						else
							l_size = strlen( p_data -> u_s ) + 1;
						l_ptr = ( const unsigned char * )p_data -> u_s;
						break;
					case RFC_EXT_TYPEBLOB :
						l_size = p_data -> u_o.s_size;
						l_ptr = ( const unsigned char * )p_data -> u_o.s_ptr;
						break;
					case RFC_EXT_TYPEBYTE :
						l_size = 1;
						l_ptr = ( const unsigned char * )&p_data -> u_b;
						break;

					default :
						l_size = 0;
						break;
				}
		}

	/* special handling of non-empty RFC_EXT_TYPELCHAR */
	if( p_type == RFC_EXT_TYPELCHAR && l_size )
		{
			/* add type, size and data */
			l_space_add = sizeof( long ) + sizeof( long ) + sizeof( long ) + l_size;

			/* ensure space left */
			rfc_blob_realloc( p_blob , l_space_add );

			/* fill with information */
			l_p = ( unsigned char * )p_blob -> s_ptr + p_blob -> s_size;
			_RFC_SET_LONG( l_p , p_type );
			l_p += sizeof( long );

			l_size += sizeof( long );
			_RFC_SET_LONG( l_p , l_size );
			l_size -= sizeof( long );

			l_p += sizeof( long );
			memcpy( l_p , l_ptr , l_size );

			/* codepage information */
			l_p += l_size;
			_RFC_SET_LONG( l_p , p_data -> u_lc.s_cp );

			p_blob -> s_size += l_space_add;
		}
	else
		{
			/* add type, size and data */
			l_space_add = sizeof( long ) + sizeof( long ) + l_size;

			/* ensure space left */
			rfc_blob_realloc( p_blob , l_space_add );

			/* fill with information */
			l_p = ( unsigned char * )p_blob -> s_ptr + p_blob -> s_size;
			_RFC_SET_LONG( l_p , p_type );
			l_p += sizeof( long );
			_RFC_SET_LONG( l_p , l_size );
			l_p += sizeof( long );

			memcpy( l_p , l_ptr , l_size );
			p_blob -> s_size += l_space_add;
		}

	return( l_size );
}

int
	rfc_blob_collect( rfc_blob *p_blob , rfc_blob *p_data )
{
	if( p_data == NULL )
		return( 0 );

	rfc_blob_realloc( p_blob , p_data -> s_size );
	memcpy( p_blob -> s_ptr + p_blob -> s_size , p_data -> s_ptr , p_data -> s_size );

	return( p_data -> s_size );
}

int
	rfc_blob_tail( rfc_blob *p_blob , rfc_blob *p_dest , int *p_offset )
{
	if( p_dest -> s_size <= *p_offset )
		{
			p_dest -> s_ptr = NULL;
			p_dest -> s_size = 0;
		}
	else
		{
			p_dest -> s_ptr = p_blob -> s_ptr + *p_offset;
			p_dest -> s_size = p_blob -> s_size - *p_offset;
		}

	return( p_dest -> s_size );
}

int
	rfc_blob_extract( rfc_blob *p_blob , int p_type , RFC_TYPE *p_data , int *p_offset )
{
	unsigned char *l_p;
	int l_size;
	int l_type;
	RFC_TYPE l_data;
	RFC_TYPE *l_dp;

	/* check nothing to read */
	if( *p_offset >= p_blob -> s_size )
		return( 0 );

	l_p = ( unsigned char * )p_blob -> s_ptr + *p_offset;

	/* get type */
	_RFC_GET_LONG( l_type , l_p );
	l_p += sizeof( long );

	/* get size */
	_RFC_GET_LONG( l_size , l_p );
	l_p += sizeof( long );

	/* shift */
	*p_offset += sizeof( long ) + sizeof( long ) + l_size;
	if( p_data == NULL )
		return( l_size );

	/* empty data */
	if( !l_size )
		return( 0 );

	if( l_type == p_type )
		l_dp = p_data;
	else
		l_dp = &l_data;

	/* get data */
	switch( l_type )
		{
			case RFC_EXT_TYPESHORT :
				_RFC_GET_SHORT( l_dp -> u_d , l_p );
				break;
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				_RFC_GET_LONG( l_dp -> u_l , l_p );
				break;
			case RFC_EXT_TYPEMONEY :
				_RFC_GET_MONEY( l_dp -> u_mm , l_p );
				break;
			case RFC_EXT_TYPEDOUBLE :
				l_dp -> u_f = *( double * )l_p;
				break;
			case RFC_EXT_TYPEFLOAT :
				l_dp -> u_r = *( float * )l_p;
				break;
			case RFC_EXT_TYPEWCHAR :
				l_dp -> u_wc = ( const unsigned short * )l_p;
				break;
			case RFC_EXT_TYPELCHAR :
				l_dp -> u_lc.s_ptr = ( const char * )l_p;
				l_p += l_size - sizeof( long );
				/* get codepage after string */
				_RFC_GET_LONG( l_dp -> u_lc.s_cp , l_p );
				break;
			case RFC_EXT_TYPECHAR :
			case RFC_EXT_TYPESTRING :
				l_dp -> u_c = ( const char * )l_p;
				break;
			case RFC_EXT_TYPEBLOB :
				l_dp -> u_o.s_ptr = ( char * )l_p;
				l_dp -> u_o.s_size = l_size;
				break;
			case RFC_EXT_TYPEBYTE :
				l_dp -> u_b = *l_p;
				break;

			default :
				return( -1 );
		}

	/* convert */
	if( l_type != p_type )
		if( !rfc_type_cnv( l_dp , l_type , p_data , p_type , NULL , NULL ) )
			return( -1 );

	return( l_size );
}

void
	rfc_blob_free( rfc_blob *p_blob )
{
	rfc_blobdata *l_data = _rfc_blob_data( p_blob );
	if( l_data != NULL )
		free( l_data -> s_mem );
	p_blob -> s_size = 0;
	p_blob -> s_ptr = NULL;
}

/*#######################################################*/
/*#######################################################*/
