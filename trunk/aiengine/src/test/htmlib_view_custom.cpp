#include "test_impl.h"
#include "../libbn/view_custom/htm_custom.h"

/*#########################################################################*/
/*#########################################################################*/

class TestHtmViewCustom : public TestUnit {
// construction
public:
	TestHtmViewCustom() : TestUnit( "TestHtmViewCustom" ) {};

	virtual void init() {
		ADD_METHOD( TestHtmViewCustom::testHelloWorld );
		ADD_METHOD( TestHtmViewCustom::testCreateHtm );
		ADD_METHOD( TestHtmViewCustom::testViewPicture );
	}
	
// tests
private:

void testHelloWorld( XmlCall& call ) {
	HtmCortex ctx;

	int sizeH = call.getIntParam( "sizeH" , 100 );
	int sizeV = call.getIntParam( "sizeV" , 100 );
	logger.logInfo( String( "create cortex sizeH=" ) + sizeH + ", sizeV=" + sizeV );
	
	ctx.create( sizeH , sizeV );

	HtmHelper helper( logger );
	helper.showCortex( &ctx );

	HtmRect rc = ctx.getRect();
	ctx.recalculate( rc );
}

void testCreateHtm( XmlCall& call ) {
	Session *session = call.getSession();

	String name = call.getParam( "cortexName" );
	int sizeH = call.getIntParam( "sizeH" );
	int sizeV = call.getIntParam( "sizeV" );

	HtmCortex *ctx = new HtmCortex;
	session -> setObject( ctx , name );
	
	ctx -> create( sizeH , sizeV );
	HtmHelper helper( logger );
	helper.showCortex( ctx );
}

void testViewPicture( XmlCall& call ) {
	Session *session = call.getSession();

	String name = call.getParam( "cortexName" );
	HtmCortex *ctx = ( HtmCortex * )session -> getObject( name );
	ASSERTMSG( ctx != NULL , String( "[" ) + name + "]: unknown cortex" );

	Xml xml = call.getXml();
	Xml picture = xml.getChildNode( "picture" );
	String text = picture.getValue();
	
	int nh = ctx -> getInputsSizeH();
	int nv = ctx -> getInputsSizeV();
	ASSERT( ( nv * ( nh * 6 + 1 ) - 1 ) == text.length() );

	const char *p = text;
	unsigned char z[ 4 ]; z[0] = z[1] = z[2] = z[3] = 0;
	int *x = ( int * )z; // rgb0
	TwoIndexArray<int>& values = ctx -> getInputs();
	for( int v = 0; v < nv; v++ )
		{
			int *hv = values[ v ];
			for( int h = 0; h < nh; h++ )
				{
					for( int d = 0; d < 3; d++ )
						{
							char c = *p++;
							unsigned char cc = ( c >= 'A' && c <= 'F' )? c + 10 - 'A' : c - '0';
							c = *p++;
							z[ d ] = ( cc << 4 ) | ( ( c >= 'A' && c <= 'F' )? c + 10 - 'A' : c - '0' );
						}

					hv[ h ] = *x;
				}
			if( v != nv - 1 )
				ASSERT( *p++ == '\n' );
		}
	ASSERT( *p == 0 );
	
	HtmRect rc = ctx -> getRect();
	ctx -> recalculate( rc );

	HtmHelper helper( logger );
	helper.showCortexMemorySize( ctx );
}

};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createHtmViewCustom() {
	return( new TestHtmViewCustom );
}

