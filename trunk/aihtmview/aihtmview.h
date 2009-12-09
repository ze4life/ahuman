// aihtmview.h : main header file for the AIHTMVIEW application
//

#if !defined(AFX_AIHTMVIEW_H__55DBD5CC_FD6C_4456_A94B_40013D331936__INCLUDED_)
#define AFX_AIHTMVIEW_H__55DBD5CC_FD6C_4456_A94B_40013D331936__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAihtmviewApp:
// See aihtmview.cpp for the implementation of this class
//

class AIHtmOps;
class CAihtmviewApp : public CWinApp
{
public:
	CAihtmviewApp();

	AIHtmOps *getHtm() { return( htm ); };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAihtmviewApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	AIHtmOps *htm;

public:
	//{{AFX_MSG(CAihtmviewApp)
	afx_msg void OnAppAbout();
	afx_msg void OnCmdShowtop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIHTMVIEW_H__55DBD5CC_FD6C_4456_A94B_40013D331936__INCLUDED_)
