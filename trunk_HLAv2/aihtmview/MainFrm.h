// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "ChildView.h"

class CMainFrame : public wxFrame
{
	
public:
	CMainFrame( const wxString& title );
	
protected: 
	DECLARE_CLASS( CMainFrame )

// members
public:
	CChildView *view;

// Implementation
public:
	virtual ~CMainFrame();

// Generated message map functions
protected:
	DECLARE_EVENT_TABLE();
};
