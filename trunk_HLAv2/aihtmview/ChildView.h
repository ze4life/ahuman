// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#include <wx/rawbmp.h>

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public wxScrolledWindow
{
// Construction
public:
	CChildView( wxWindow *parent );

// Attributes
public:
	wxMemoryDC mdc;
	wxBitmap memoryBitmap;
	wxRect rcEye;

// Operations
public:
	void showEyeBox( wxDC& dc );
	void moveEye( int key , wxKeyEvent& ks );
	const char *getEyeData();
	BOOL eraseBkgnd( wxMemoryDC* pDC );

// Overrides
	virtual void onCreate();
	virtual void onDestroy();
	virtual void UpdateWindowUI( long flags );

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	void OnPaint( wxPaintEvent& event );
	void OnPaste( wxCommandEvent& event );
	void OnUpdatePaste( wxUpdateUIEvent& event );
	void OnEraseBackground( wxEraseEvent& event );
	void OnKeyDown( wxKeyEvent& event );
	DECLARE_EVENT_TABLE();
};
