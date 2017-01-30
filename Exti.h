// Exti.h : main header file for the EXTI application
//

#if !defined(AFX_EXTI_H__08786DB5_527E_49BA_8337_B00DD0B0F509__INCLUDED_)
#define AFX_EXTI_H__08786DB5_527E_49BA_8337_B00DD0B0F509__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExtiApp:
// See Exti.cpp for the implementation of this class
//

class CExtiApp : public CWinApp
{
public:
	CExtiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExtiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTI_H__08786DB5_527E_49BA_8337_B00DD0B0F509__INCLUDED_)
