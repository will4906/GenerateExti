// ExtiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Exti.h"
#include "ExtiDlg.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtiDlg dialog

CExtiDlg::CExtiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExtiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExtiDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtiDlg)
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_btnModify);
	DDX_Control(pDX, IDC_BUTTON_MAKE_CODE, m_btnMakeCode);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_btnClear);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_LIST_EXTI, m_listExti);
	DDX_Control(pDX, IDC_COMBO_TRIGGER, m_comTrigger);
	DDX_Control(pDX, IDC_COMBO_SUB_PRI, m_comSubPri);
	DDX_Control(pDX, IDC_COMBO_PRE_PRI, m_comPrePri);
	DDX_Control(pDX, IDC_COMBO_PIN_LAST, m_comPinLast);
	DDX_Control(pDX, IDC_COMBO_PIN_GROUP, m_comPinGroup);
	DDX_Control(pDX, IDC_COMBO_NVIC_GROUP, m_comNvicGroup);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExtiDlg, CDialog)
	//{{AFX_MSG_MAP(CExtiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELENDOK(IDC_COMBO_NVIC_GROUP, OnSelendokComboNvicGroup)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_MAKE_CODE, OnButtonMakeCode)
	ON_NOTIFY(NM_CLICK, IDC_LIST_EXTI, OnClickListExti)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtiDlg message handlers

BOOL CExtiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	InitDataList();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExtiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExtiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CExtiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExtiDlg::InitDataList()
{
	m_comPinGroup.SetCurSel(0);
	m_comPinLast.SetCurSel(0);
	m_comTrigger.SetCurSel(1);
	m_comNvicGroup.SetCurSel(2);
	m_comPrePri.SetCurSel(2);
	m_comSubPri.SetCurSel(2);

	m_listExti.InsertColumn(0, "Pin", LVCFMT_CENTER, 55);
	m_listExti.InsertColumn(1, _T("Trigger"), LVCFMT_CENTER, 100);
	m_listExti.InsertColumn(2, "PrePriority", LVCFMT_CENTER, 100);
	m_listExti.InsertColumn(3, "SubPriority", LVCFMT_CENTER, 100);

	m_btnClear.EnableWindow(FALSE);
	m_btnDelete.EnableWindow(FALSE);
	m_btnMakeCode.EnableWindow(FALSE);
	m_btnModify.EnableWindow(FALSE);
	//使能鼠标选中功能
	::SendMessage(m_listExti.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
}

void CExtiDlg::OnSelendokComboNvicGroup() 
{
	// TODO: Add your control notification handler code here
	int groupIndex = m_comNvicGroup.GetCurSel();
	int preSum = (int)pow(2, groupIndex);
	int subSum = (int)pow(2, 4 - groupIndex);
	CString strTmp;

	m_comPrePri.ResetContent();
	m_comSubPri.ResetContent();
	for (int i = 0; i < preSum; i ++)
	{
		strTmp.Format("%d",i);
		m_comPrePri.AddString(strTmp);
	}
	m_comPrePri.SetCurSel(0);
	for (i = 0; i < subSum; i ++)
	{
		strTmp.Format("%d",i);
		m_comSubPri.AddString(strTmp);
	}
	m_comSubPri.SetCurSel(0);
}

void CExtiDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	CDataNode dataNode;
	CString strTmp,strGroup;
	char *p;
	int nCount = m_listExti.GetItemCount();

	m_comPinGroup.GetWindowText(strGroup);
	dataNode.SetPinGroup(strGroup);
	m_comPinLast.GetWindowText(strTmp);
	dataNode.SetPin(strtol(strTmp, &p, 10));
	m_listExti.InsertItem(nCount, strGroup + strTmp);

	dataNode.SetTrigger(m_comTrigger.GetCurSel());
	m_comTrigger.GetWindowText(strTmp);
	m_listExti.SetItemText(nCount, 1, strTmp);

	m_comPrePri.GetWindowText(strTmp);
	m_listExti.SetItemText(nCount, 2, strTmp);
	dataNode.SetPrePri(strtol(strTmp, &p, 10));

	m_comSubPri.GetWindowText(strTmp);
	m_listExti.SetItemText(nCount, 3, strTmp);
	dataNode.SetSubPri(strtol(strTmp, &p, 10));

	dataList.AddTail(dataNode);

	if (dataList.GetCount() == 1)
	{
		m_comNvicGroup.EnableWindow(FALSE);
		m_btnClear.EnableWindow(TRUE);
		m_btnMakeCode.EnableWindow(TRUE);
	}
}

void CExtiDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	if (AfxMessageBox("确定要删除全部吗!",MB_YESNO) == IDYES)
	{
		dataList.RemoveAll();
		m_listExti.DeleteAllItems();

		m_comNvicGroup.EnableWindow(TRUE);
		m_btnClear.EnableWindow(FALSE);
		m_btnDelete.EnableWindow(FALSE);
		m_btnMakeCode.EnableWindow(FALSE);
		m_btnModify.EnableWindow(FALSE);
	}
}

void CExtiDlg::OnClickListExti(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int index = m_listExti.GetNextItem(-1,LVIS_SELECTED);
	
	if (index >= 0)
	{
		CString strTmp;
		
		CDataNode dataNode = dataList.GetAt(dataList.FindIndex(index));
		strTmp = dataNode.GetPinGroup();
		m_comPinGroup.SetCurSel(strTmp.GetAt(0) - 65);
		m_comPinLast.SetCurSel(dataNode.GetPin());
		m_comPrePri.SetCurSel(dataNode.GetPrePri());
		m_comSubPri.SetCurSel(dataNode.GetSubPri());
		switch (dataNode.GetTrigger())
		{
		case RISING:
			m_comTrigger.SetCurSel(0);
			break;
		case FALLING:
			m_comTrigger.SetCurSel(1);
			break;
		case RISING_FALLING:
			m_comTrigger.SetCurSel(2);
			break;
		default:
			m_comTrigger.SetCurSel(0);
			break;
		}
		m_btnDelete.EnableWindow(TRUE);
		m_btnModify.EnableWindow(TRUE);
	}
	else
	{
		m_btnDelete.EnableWindow(FALSE);
		m_btnModify.EnableWindow(FALSE);
	}
	*pResult = 0;
}

void CExtiDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	int index = m_listExti.GetNextItem(-1,LVIS_SELECTED);
	if (index >= 0)
	{
		dataList.RemoveAt(dataList.FindIndex(index));
		m_listExti.DeleteItem(index);

		m_btnDelete.EnableWindow(FALSE);
		m_btnModify.EnableWindow(FALSE);

		if (dataList.GetCount() == 0)
		{
			m_comNvicGroup.EnableWindow(TRUE);
			m_btnClear.EnableWindow(FALSE);
			m_btnMakeCode.EnableWindow(FALSE);
		}
	}
}

void CExtiDlg::OnButtonModify() 
{
	// TODO: Add your control notification handler code here
	int index = m_listExti.GetNextItem(-1,LVIS_SELECTED);
	if (index >= 0)
	{	
		CDataNode dataNode = dataList.GetAt(dataList.FindIndex(index));
		CString strPin,strGroup,strTrigger,strPre,strSub;
		char *p;
		
		m_comPinGroup.GetWindowText(strGroup);
		dataNode.SetPinGroup(strGroup);
		m_comPinLast.GetWindowText(strPin);
		dataNode.SetPin(strtol(strPin, &p, 10));
		
		
		dataNode.SetTrigger(m_comTrigger.GetCurSel());
		m_comTrigger.GetWindowText(strTrigger);
		
		m_comPrePri.GetWindowText(strPre);
		dataNode.SetPrePri(strtol(strPre, &p, 10));
		
		m_comSubPri.GetWindowText(strSub);
		dataNode.SetSubPri(strtol(strSub, &p, 10));

		m_listExti.SetItemText(index, 0, strGroup + strPin);
		m_listExti.SetItemText(index, 1, strTrigger);
		m_listExti.SetItemText(index, 2, strPre);
		m_listExti.SetItemText(index, 3, strSub);

		dataList.SetAt(dataList.FindIndex(index), dataNode);
		

		m_btnDelete.EnableWindow(FALSE);
		m_btnModify.EnableWindow(FALSE);
	}
}

void CExtiDlg::OnButtonMakeCode() 
{
	// TODO: Add your control notification handler code here
	CMakeCode *makeCode = new CMakeCode(&dataList);

	CTime time;  
	CString strTime,strTmp;
	time=CTime::GetCurrentTime();//获得当前时间  
	strTime=time.Format("%Y-%m-%d %H:%M:%S ");//将时间转化为字符串 
	const char pszFilter[] = _T("Code Files (*.h)|*.h||");
	
	CString strFile;
	strFile = "Exti.h";
	
	CFileDialog dlgSave( FALSE, //FALSE为保存
		_T(".h"), //自动加上的扩展名
		_T(strFile), //默认保存的文件名
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		pszFilter, this);
	if(dlgSave.DoModal() == IDOK)
	{
		if (makeCode->GeneratingCode())
		{
			strTime += "Generating The Code Successfully!";
		}
		else
		{
			strTime += "Failed To Generate Code!";
		}
		AfxMessageBox(strTime);
	}
	delete makeCode;
}


