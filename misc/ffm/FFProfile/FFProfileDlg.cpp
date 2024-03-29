// FFProfileDlg.cpp : implementation file
//
#include "stdafx.h"
#include "FFProfile.h"
#include "FFProfileDlg.h"
#include "PropListMgr.h"
#include "DefaultOptionExpBuilder.h"
#include "OptionExpTree.h"
#include "CmdBuilder.h"
#include "MiscUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#define IDC_PROPLIST		9012

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
// CFFProfileDlg dialog

CFFProfileDlg::CFFProfileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFFProfileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFFProfileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFFProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFFProfileDlg)
	DDX_Control(pDX, IDC_PROPLIST_LOCATION, m_wndPropListLocation);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFFProfileDlg, CDialog)
	//{{AFX_MSG_MAP(CFFProfileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFFProfileDlg message handlers

BOOL CFFProfileDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	InitPropList();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFFProfileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFFProfileDlg::OnPaint() 
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
HCURSOR CFFProfileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFFProfileDlg::InitPropList()
{
	CRect rcPropList;
	m_wndPropListLocation.GetWindowRect(&rcPropList);
	ScreenToClient(&rcPropList);

	CWnd* pWnd = GetDlgItem(IDC_PROPLIST_LOCATION);

	m_wndPropList.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rcPropList, this, 
		IDC_PROPLIST/*(UINT)-1*/);
	
	m_wndPropList.EnableHeaderCtrl ();
	m_wndPropList.EnableDesciptionArea ();
	
	m_wndPropList.SetCustomColors (
		RGB (250, 250, 250),
		RGB (0, 0, 0),
		RGB (240, 240, 240),
		RGB (40, 76, 165),
		RGB (250, 250, 250),
		RGB (0, 85, 136),
		RGB (168, 189, 216));

	CPropListMgr pPropListMgr(&m_wndPropList);
	pPropListMgr.Init(_T("profile.xml"));
}

void CFFProfileDlg::GetPropValue(CBCGPProp* pProp, OptionContext* pPropMap)
{
	ASSERT(pProp);

	std::string szKey, szVal;
	szKey.assign(CFL_T2A(pProp->GetName()));
	MiscUtils::Val2Str(pProp->GetValue(), szVal);
	
	pPropMap->Put(szKey.c_str(), szVal.c_str());
	AfxTrace(_T("%s=%s\n"), CFL_A2T(szKey.c_str()), CFL_A2T(szVal.c_str()));

	for(int i = 0; i < pProp->GetSubItemsCount(); i++)
	{
		GetPropValue(pProp->GetSubItem(i), pPropMap);
	}
}

BOOL CFFProfileDlg::GetPropMap(OptionContext* pPropMap)
{
	int n = m_wndPropList.GetPropertyCount();
	
	CBCGPProp* pProp = NULL;
	for(int i = 0; i < n; i++)
	{
		pProp = m_wndPropList.GetProperty(i);
		GetPropValue(pProp, pPropMap);
	}

	return TRUE;
}

bool ParseSize(const std::string& str, int& w, int& h)
{
	size_t index = str.find('x');
	if(index == std::string::npos || index == 0 || (index == str.size() - 1))
	{
		return false;
	}
	std::string szWidth = str.substr(0, index);
	w = atoi(szWidth.c_str());
	
	std::string szHeight = str.substr(index + 1);
	h = atoi(szHeight.c_str());
	
	return w > 0 && h > 0;
}

void CFFProfileDlg::OnBtnUpdate() 
{
	OptionContext context;
	GetPropMap(&context);

	context.Put(IFILE, "C:\\Temp\\生化危机5Input.avi");
	//context.Put(OFILE, "C:\\Temp\\output.avi");
	
	int w, h;
	std::string val;
	bool bRet = context.Get(VIDEO_SIZE, val);
	if(bRet)
	{
		bRet = ParseSize(val, w, h);

		if(bRet)
		{
			char buf[16];
			sprintf(buf, "%d", w);
			context.Put(VIDEO_WIDTH, buf);

			sprintf(buf, "%d", h);
			context.Put(VIDEO_HEIGHT, buf);
		}
	}

	DefaultOptionExpBuilder builder;

	OptionContext mutableCxt;
	MeCmdBuilder mcb;
	mcb.SetBinFile(_T("mencoder.exe"));
	mcb.SetOptionExpBuilder(&builder).SetOutputFolder("C:\\电影");
	
	CString szText = _T("Build Failed");
	cfl::tstring szCmdLine;

	for(int pass = 1; pass <= 2; pass++)
	{
		mutableCxt = context;
		mcb.SetPass(pass).SetOptionContext(&mutableCxt);

		if(mcb.Build(szCmdLine))
		{
			szText.Format(_T("%s"), szCmdLine.c_str());
			AfxTrace(_T("%s\n"), szCmdLine.c_str());
		}
		SetDlgItemText(IDC_EDIT_RESULT, szText);
	}
}
