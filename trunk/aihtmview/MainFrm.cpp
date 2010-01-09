// MainFrm.cpp : implementation of the CMainFrame class
//

#include "aihtmview.h"

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_CLASS(CMainFrame, wxFrame)

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
END_EVENT_TABLE()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame( const wxString& title )
:	wxFrame( NULL , -1 , title )
{
	view = new CChildView( this );
}

CMainFrame::~CMainFrame()
{
}
