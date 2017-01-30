// ExtiDlg.h : header file
//

#if !defined(AFX_EXTIDLG_H__079DF256_A4F7_4BCE_8E05_41987D0FBFEA__INCLUDED_)
#define AFX_EXTIDLG_H__079DF256_A4F7_4BCE_8E05_41987D0FBFEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "DataNode.h"
#include "MakeCode.h"
/////////////////////////////////////////////////////////////////////////////
// CExtiDlg dialog

class CExtiDlg : public CDialog
{
// Construction
public:
	CExtiDlg(CWnd* pParent = NULL);	// standard constructor

private:
	CList<CDataNode,CDataNode> dataList;
protected:
	void InitDataList();
// Dialog Data
	//{{AFX_DATA(CExtiDlg)
	enum { IDD = IDD_EXTI_DIALOG };
	CButton	m_btnModify;
	CButton	m_btnMakeCode;
	CButton	m_btnDelete;
	CButton	m_btnClear;
	CButton	m_btnAdd;
	CListCtrl	m_listExti;
	CComboBox	m_comTrigger;
	CComboBox	m_comSubPri;
	CComboBox	m_comPrePri;
	CComboBox	m_comPinLast;
	CComboBox	m_comPinGroup;
	CComboBox	m_comNvicGroup;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExtiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelendokComboNvicGroup();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonModify();
	afx_msg void OnButtonMakeCode();
	afx_msg void OnClickListExti(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTIDLG_H__079DF256_A4F7_4BCE_8E05_41987D0FBFEA__INCLUDED_)
