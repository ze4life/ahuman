// aihtmview.cpp : Defines the class behaviors for the application.
//

#include "aihtmview.h"

#include "MainFrm.h"
#include "aihtmops.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAihtmviewApp

BEGIN_EVENT_TABLE( CAihtmviewApp , wxApp )
END_EVENT_TABLE()

/////////////////////////////////////////////////////////////////////////////
// CAihtmviewApp construction

CAihtmviewApp::CAihtmviewApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	htm = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CAihtmviewApp initialization

bool CAihtmviewApp::OnInit()
{
	htm = new AIHtmOps;
	if( !htm -> connect( "169.254.27.205:20001" ) )
		return( false );

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	m_mainFrame = new CMainFrame( wxT( "AIHTMVIEW" ) );

	// The one and only window has been initialized, so show and update it.
	m_mainFrame -> Show( true );

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CAihtmviewApp message handlers

int CAihtmviewApp::OnExit() 
{
	// TODO: Add your specialized code here and/or call the base class
	if( htm != NULL )
		{
			htm -> disconnect();
			delete htm;
		}
	
	return wxApp::OnExit();
}
