// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "aihtmview.h"
#include "ChildView.h"
#include "aihtmops.h"

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

CChildView::CChildView()
{
	// excluding margins
	rcEye.SetRect( 0 , 0 , EYE_WIDTH , EYE_HEIGHT );

	AIHtmOps *htm = ( ( CAihtmviewApp * )AfxGetApp() ) -> getHtm();
	htm -> createCortex( EYE_WIDTH , EYE_HEIGHT );
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	mdc.CreateCompatibleDC( NULL );
	memoryBitmap.CreateBitmap( MAX_WIDTH , MAX_HEIGHT , 1 , 32 , NULL );

	memset( &sbmp , 0 , sizeof( BITMAP ) );
	memoryBitmap.GetBitmap( &sbmp );
	scanLineBytes = sbmp.bmWidthBytes;

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rc;
	dc.GetClipBox( rc );
	CBitmap *defaultBitmap = mdc.SelectObject( &memoryBitmap );
	ASSERT( dc.BitBlt( rc.left , rc.top , rc.Width() , rc.Height() , &mdc , rc.left - BOX_MARGIN , rc.top - BOX_MARGIN , SRCCOPY ) );

	// show rect around draw box
	rc.left = BOX_MARGIN;
	rc.top = BOX_MARGIN;
	rc.right = rc.left + MAX_WIDTH;
	rc.bottom = rc.top + MAX_HEIGHT;
	rc.InflateRect( 3 , 3 );
	dc.DrawEdge( rc , EDGE_ETCHED , BF_RECT );

	// show eye box
	showEyeBox( dc );
	mdc.SelectObject( defaultBitmap );
}

void CChildView::showEyeBox( CDC& dc )
{
	CRect rc = rcEye;
	rc.OffsetRect( BOX_MARGIN , BOX_MARGIN );
	rc.InflateRect( 1 , 1 );
	dc.Draw3dRect( rc , RGB( 0 , 0 , 255 ) , RGB( 0 , 0 , 128 ) );
	rc.InflateRect( 1 , 1 );
	dc.Draw3dRect( rc , RGB( 0 , 0 , 128 ) , RGB( 0 , 0 , 255 ) );
	rc.InflateRect( 1 , 1 );
	dc.DrawFocusRect( rc );
}

void CChildView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	::OpenClipboard( CWnd::GetSafeHwnd() );
	HBITMAP hbmp = ( HBITMAP )::GetClipboardData( CF_BITMAP );
	if( hbmp == NULL )
		{
			::CloseClipboard();
			return;
		}

	CDC dcx;
	dcx.CreateCompatibleDC( &mdc );

	CBitmap *bmp = CBitmap::FromHandle( hbmp );
	CBitmap *save = dcx.SelectObject( bmp );

	BITMAP pbmp;
	memset( &pbmp , 0 , sizeof( BITMAP ) );
	bmp -> GetBitmap( &pbmp );
	CSize s( pbmp.bmWidth , pbmp.bmHeight );
	if( s.cx > MAX_WIDTH )
		s.cx = MAX_WIDTH;
	if( s.cy > MAX_HEIGHT )
		s.cy = MAX_HEIGHT;

	CBitmap *defaultBitmap = mdc.SelectObject( &memoryBitmap );
	ASSERT( mdc.BitBlt( 0 , 0 , s.cx , s.cy , &dcx , 0 , 0 , SRCCOPY ) );
	dcx.SelectObject( save );
	mdc.SelectObject( defaultBitmap );
	dcx.DeleteDC();

	CRect rc( BOX_MARGIN , BOX_MARGIN , BOX_MARGIN + s.cx , BOX_MARGIN + s.cy );
	InvalidateRect( rc );
	UpdateWindow();

	::CloseClipboard();
}

void CChildView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable( ::IsClipboardFormatAvailable( CF_BITMAP ) );
}

void CChildView::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	mdc.DeleteDC();
	memoryBitmap.DeleteObject();
	
	CWnd ::PostNcDestroy();
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	pDC -> GetClipBox( rc );
	CRgn rgn1;
	rgn1.CreateRectRgnIndirect( rc );

	rc.left = BOX_MARGIN;
	rc.top = BOX_MARGIN;
	rc.right = rc.left + MAX_WIDTH;
	rc.bottom = rc.top + MAX_HEIGHT;
	CRgn rgn2;
	rgn2.CreateRectRgnIndirect( rc );

	CRgn rgn;
	rgn.CreateRectRgn( 0 , 0 , 0 , 0 );
	rgn.CombineRgn( &rgn1 , &rgn2 , RGN_DIFF );

	HBRUSH hbr = ( HBRUSH )::GetStockObject( WHITE_BRUSH );
	CBrush *br = CBrush::FromHandle( hbr );
	pDC -> FillRgn( &rgn , br );
	
	rgn1.DeleteObject();
	rgn2.DeleteObject();
	rgn.DeleteObject();

	return TRUE;
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if( nChar == VK_DOWN || nChar == VK_UP || nChar == VK_LEFT || nChar == VK_RIGHT )
		moveEye( nChar );
	
	CWnd ::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::moveEye( UINT key )
{
	int av = 1;
	if( ::GetKeyState( VK_CONTROL ) & 0x8000 )
		av = 2;
	if( ::GetKeyState( VK_SHIFT ) & 0x8000 )
		av = ( av == 2 )? 8 : 4;

	if( key == VK_LEFT )
		{
			if( rcEye.left == 0 )
				return;
			if( av > rcEye.left )
				av = rcEye.left;
			rcEye.OffsetRect( -av , 0 );
		}
	else
	if( key == VK_RIGHT )
		{
			if( rcEye.right == MAX_WIDTH )
				return;
			if( av > ( MAX_WIDTH - rcEye.right ) )
				av = MAX_WIDTH - rcEye.right;
			rcEye.OffsetRect( av , 0 );
		}
	else
	if( key == VK_UP )
		{
			if( rcEye.top == 0 )
				return;
			if( av > rcEye.top )
				av = rcEye.top;
			rcEye.OffsetRect( 0 , -av );
		}
	else
	if( key == VK_DOWN )
		{
			if( rcEye.bottom == MAX_WIDTH )
				return;
			if( av > ( MAX_WIDTH - rcEye.bottom ) )
				av = MAX_WIDTH - rcEye.bottom;
			rcEye.OffsetRect( 0 , av );
		}

	CRect rc = rcEye;
	rc.OffsetRect( BOX_MARGIN , BOX_MARGIN );
	rc.InflateRect( BOX_MARGIN + av , BOX_MARGIN + av );
	InvalidateRect( rc );
	UpdateWindow();

	// check need to send
	if( !( ::GetKeyState( VK_CAPITAL ) & 1 ) )
		return;

	AIHtmOps *htm = ( ( CAihtmviewApp * )AfxGetApp() ) -> getHtm();
	const char *data = getEyeData();
	htm -> sendPicture( data );
}

const char *CChildView::getEyeData()
{
	static char v[ EYE_HEIGHT ][ EYE_WIDTH * 6 + 1 ];
	char *readBuf = ( char * )calloc( 1 , sizeof( BITMAPINFOHEADER ) + sizeof( int ) * EYE_HEIGHT * MAX_WIDTH );

	int height = rcEye.Height();
	
	BITMAPINFO& bi = *( BITMAPINFO * )readBuf;
	memset( &bi , 0 , sizeof( BITMAPINFO ) );
	bi.bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
	bi.bmiHeader.biBitCount = 0;
	// bi.bmiHeader.biBitCount = sbmp.bmBitsPixel;
	// bi.bmiHeader.biWidth = sbmp.bmWidth;
	// bi.bmiHeader.biHeight = sbmp.bmHeight;
	// bi.bmiHeader.biPlanes = sbmp.bmPlanes;
	// bi.bmiHeader.biCompression = BI_RGB;
	// bi.bmiHeader.biSizeImage = sizeof( int ) * height * MAX_WIDTH;

	BITMAP pbmp;
	memset( &pbmp , 0 , sizeof( BITMAP ) );
	memoryBitmap.GetBitmap( &pbmp );

	// read bitmap - it will store lines in bottom to up formap
	ASSERT( ::GetDIBits( mdc.GetSafeHdc() , ( HBITMAP )memoryBitmap.GetSafeHandle() , 0 , height , NULL , &bi , DIB_RGB_COLORS ) );
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = sizeof( int ) * height * MAX_WIDTH;
	int res = ::GetDIBits( mdc.GetSafeHdc() , ( HBITMAP )memoryBitmap.GetSafeHandle() , MAX_HEIGHT - rcEye.bottom , height , bi.bmiColors , &bi , DIB_RGB_COLORS );
	ASSERT( res == height );

	// convert to hex - revert to have from top to bottom
	char *bp = readBuf + sizeof( BITMAPINFOHEADER );
	for( int k1 = 0; k1 < height; k1++ )
		{
			int revPos = height - k1 - 1;
			for( int k2 = 0; k2 < EYE_WIDTH; k2++ )
				{
					char *p = v[ revPos ] + k2 * 6;
					char *xp = bp + scanLineBytes * k1 + sizeof( int ) * ( rcEye.left + k2 ); // int:0bgr, int byte order:4321=rgb0

					// do char to hex
					for( int z = 0; z < 3; z++ )
						{
							unsigned char c = *xp++;
							unsigned int v = ( c >> 4 );
							*p++ = ( v >= 10 )? 'A' + ( v - 10 ) : '0' + v;
							v = c & 0x0F;
							*p++ = ( v >= 10 )? 'A' + ( v - 10 ) : '0' + v;
						}
				}
			v[ revPos ][ EYE_WIDTH * 6 ] = '\n';
		}

	v[ EYE_HEIGHT - 1 ][ EYE_WIDTH * 6 ] = 0;

	return( ( const char * )v );
}
