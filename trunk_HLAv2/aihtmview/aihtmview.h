// aihtmview.h : main header file for the AIHTMVIEW application
//

#include <wx/wx.h>

/////////////////////////////////////////////////////////////////////////////
// CAihtmviewApp:
// See aihtmview.cpp for the implementation of this class
//

class AIHtmOps;
class CMainFrame;
class CAihtmviewApp : public wxApp
{
public:
	CAihtmviewApp();

	AIHtmOps *getHtm() { return( htm ); };

// Overrides
public:
	virtual bool OnInit();
	virtual int OnExit();

// Implementation
    CMainFrame* m_mainFrame;
	AIHtmOps *htm;

public:
	DECLARE_EVENT_TABLE();
};

DECLARE_APP( CAihtmviewApp )
