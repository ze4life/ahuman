// ChildView.cpp : implementation of the CChildView class
//

#include "aihtmview.h"
#include "ChildView.h"
#include "aihtmops.h"

#include <wx/clipbrd.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_WIDTH		200
#define MAX_HEIGHT		200
#define BOX_MARGIN		5
#define EYE_WIDTH		100
#define EYE_HEIGHT		100

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView( wxWindow *parent )
:	wxScrolledWindow( parent, wxID_ANY, wxDefaultPosition , wxDefaultSize,
		wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE )
{
	// excluding margins
	rcEye = wxRect( 0 , 0 , EYE_WIDTH , EYE_HEIGHT );

	AIHtmOps *htm = wxGetApp().getHtm();
	htm -> createCortex( EYE_WIDTH , EYE_HEIGHT );

	memoryBitmap.Create( MAX_WIDTH , MAX_HEIGHT , 24 );
}

CChildView::~CChildView()
{
}

BEGIN_EVENT_TABLE( CChildView , wxScrolledWindow )
	//{{AFX_MSG_MAP(CChildView)
	EVT_PAINT( CChildView::OnPaint )
	EVT_MENU( wxID_PASTE , CChildView::OnPaste )
	EVT_UPDATE_UI( wxID_PASTE, CChildView::OnUpdatePaste )
	EVT_ERASE_BACKGROUND( CChildView::OnEraseBackground )
	EVT_KEY_DOWN( CChildView::OnKeyDown )
	//}}AFX_MSG_MAP
END_EVENT_TABLE()

/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers
void CChildView::onCreate()
{
}

void CChildView::onDestroy()
{
}

void CChildView::UpdateWindowUI( long flags )
{
}

void CChildView::OnPaint( wxPaintEvent &WXUNUSED(event) ) 
{
	wxPaintDC dc( this ); // device context for painting
	
	// TODO: Add your message handler code here
	mdc.SelectObjectAsSource( memoryBitmap );
	dc.Blit( BOX_MARGIN , BOX_MARGIN , MAX_WIDTH , MAX_HEIGHT , &mdc , 0 , 0 , wxCOPY );

	// show rect around draw box
	dc.SetBrush( *wxTRANSPARENT_BRUSH );
	wxRect rc;
	rc.x = BOX_MARGIN;
	rc.y = BOX_MARGIN;
	rc.width = MAX_WIDTH;
	rc.height = MAX_HEIGHT;
	rc.Inflate( 1 , 1 );
	dc.SetPen( *wxWHITE_PEN );
	dc.DrawRectangle( rc.x , rc.y , rc.width , rc.height );
	rc.Inflate( 1 , 1 );
	dc.SetPen( *wxBLACK_PEN );
	dc.DrawRectangle( rc.x , rc.y , rc.width , rc.height );
	
	// show eye box
	showEyeBox( dc );
}

void CChildView::showEyeBox( wxDC& dc )
{
	wxRect rc = rcEye;
	rc.Offset( BOX_MARGIN , BOX_MARGIN );
	rc.Inflate( 1 , 1 );
	dc.SetPen( *wxWHITE_PEN );
	dc.DrawRectangle( rc.x , rc.y , rc.width , rc.height );
	rc.Inflate( 1 , 1 );
	dc.SetPen( *wxBLACK_PEN );
	dc.DrawRectangle( rc.x , rc.y , rc.width , rc.height );
	rc.Inflate( 1 , 1 );
	dc.SetPen( *wxWHITE_PEN );
	dc.DrawRectangle( rc.x , rc.y , rc.width , rc.height );
}

void CChildView::OnPaste( wxCommandEvent& event ) 
{
	// TODO: Add your command handler code here
	if( !wxTheClipboard -> Open() )
		return;
		
	if( wxTheClipboard -> IsSupported( wxDF_BITMAP ) )
		{
			wxBitmapDataObject bdo;
			wxTheClipboard -> GetData( bdo );
			wxBitmap bmp = bdo.GetBitmap();
			
			wxMemoryDC dcx( bmp );
			int w = bmp.GetWidth();
			int h = bmp.GetHeight();
			
			if( w > MAX_WIDTH )
				w = MAX_WIDTH;
			if( h > MAX_HEIGHT )
				h = MAX_HEIGHT;
			
			mdc.SelectObject( memoryBitmap );
			mdc.Blit( 0 , 0 , w , h , &dcx , 0 , 0 , wxCOPY );
			
			wxRect rc( BOX_MARGIN , BOX_MARGIN , w , h );
			RefreshRect( rc );
		}
		
	wxTheClipboard -> Close();
}

void CChildView::OnUpdatePaste( wxUpdateUIEvent& event ) 
{
	// TODO: Add your command update UI handler code here
	bool available = wxTheClipboard -> IsSupported( wxDF_BITMAP );
	event.Enable( available );
}

void CChildView::OnEraseBackground( wxEraseEvent& event ) 
{
	// TODO: Add your message handler code here and/or call default
	wxDC *dc = event.GetDC();
	
	wxRect rca;
	dc -> GetClippingBox( &rca.x , &rca.y , &rca.width , &rca.height );
	wxRegion rgn1( rca );

	wxRect rc;
	rc.x = BOX_MARGIN;
	rc.y = BOX_MARGIN;
	rc.width = MAX_WIDTH;
	rc.height = MAX_HEIGHT;
	wxRegion rgn2( rc );

	rgn1.Xor( rgn2 );
	wxDCClipper clip( *dc , rgn1 );

	wxDCBrushChanger brushChange( *dc , *wxWHITE_BRUSH );
	dc -> DrawRectangle( rca.x , rca.y , rca.width , rca.height );
	
	event.Skip();
}

void CChildView::OnKeyDown( wxKeyEvent& event ) 
{
	// TODO: Add your message handler code here and/or call default
	int nChar = event.GetKeyCode();
	if( nChar == WXK_DOWN || nChar == WXK_UP || nChar == WXK_LEFT || nChar == WXK_RIGHT )
		moveEye( nChar , event );
}

void CChildView::moveEye( int key , wxKeyEvent& ks )
{
	int av = 1;
	if( ks.AltDown() )
		av = 2;
	if( ks.ControlDown() )
		av = ( av == 2 )? 8 : 4;

	if( key == WXK_LEFT )
		{
			if( rcEye.x == 0 )
				return;
			if( av > rcEye.x )
				av = rcEye.x;
			rcEye.Offset( -av , 0 );
		}
	else
	if( key == WXK_RIGHT )
		{
			if( rcEye.GetRight() == MAX_WIDTH )
				return;
			if( av > ( MAX_WIDTH - rcEye.GetRight() ) )
				av = MAX_WIDTH - rcEye.GetRight();
			rcEye.Offset( av , 0 );
		}
	else
	if( key == WXK_UP )
		{
			if( rcEye.y == 0 )
				return;
			if( av > rcEye.y )
				av = rcEye.y;
			rcEye.Offset( 0 , -av );
		}
	else
	if( key == WXK_DOWN )
		{
			if( rcEye.GetBottom() == MAX_HEIGHT )
				return;
			if( av > ( MAX_HEIGHT - rcEye.GetBottom() ) )
				av = MAX_HEIGHT - rcEye.GetBottom();
			rcEye.Offset( 0 , av );
		}

	wxRect rc = rcEye;
	rc.Offset( BOX_MARGIN , BOX_MARGIN );
	rc.Inflate( BOX_MARGIN + av , BOX_MARGIN + av );
	RefreshRect( rc );

	// check need to send
	if( !ks.ShiftDown() )
		return;

	AIHtmOps *htm = wxGetApp().getHtm();
	const char *data = getEyeData();
	htm -> sendPicture( data );
}

const char *CChildView::getEyeData()
{
	static char v[ EYE_HEIGHT ][ EYE_WIDTH * 6 + 1 ];

	int height = rcEye.height;
	
	// read bitmap
	wxNativePixelData data( memoryBitmap , rcEye );
	wxNativePixelData::Iterator p( data );
	for( int y = 0; y < EYE_HEIGHT; ++y )
        {
            wxNativePixelData::Iterator rowStart = p;
			char *pw = v[ y ];
			
			unsigned char pc[ 3 ];
			unsigned char *xp = pc;
			for( int x = 0; x < EYE_WIDTH; ++x , ++p )
				{
					pc[ 0 ] = p.Red();
					pc[ 1 ] = p.Green();
					pc[ 2 ] = p.Blue();
					
					for( int z = 0; z < 3; z++ )
						{
							unsigned char c = *xp++;
							unsigned int hx = ( c >> 4 );
							*pw++ = ( hx >= 10 )? 'A' + ( hx - 10 ) : '0' + hx;
							hx = c & 0x0F;
							*pw++ = ( hx >= 10 )? 'A' + ( hx - 10 ) : '0' + hx;
						}
				}

            p = rowStart;
            p.OffsetY( data , 1 );
			v[ y ][ EYE_WIDTH * 6 ] = '\n';
		}

	v[ EYE_HEIGHT - 1 ][ EYE_WIDTH * 6 ] = 0;

	return( ( const char * )v );
}
