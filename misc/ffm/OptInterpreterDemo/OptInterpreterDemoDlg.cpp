// OptInterpreterDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OptInterpreterDemo.h"
#include "OptInterpreterDemoDlg.h"
#include "DefaultOptionExpBuilder.h"
#include "OptionExpTree.h"

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
// COptInterpreterDemoDlg dialog

COptInterpreterDemoDlg::COptInterpreterDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptInterpreterDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptInterpreterDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_pOptExp = NULL;
}

void COptInterpreterDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptInterpreterDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptInterpreterDemoDlg, CDialog)
	//{{AFX_MSG_MAP(COptInterpreterDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptInterpreterDemoDlg message handlers

BOOL COptInterpreterDemoDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COptInterpreterDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COptInterpreterDemoDlg::OnPaint() 
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
HCURSOR COptInterpreterDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void COptInterpreterDemoDlg::InitOptionExp()
{
}

void COptInterpreterDemoDlg::OnBtnUpdate() 
{
	OptionContext optContext;
	OptionContext* pContext = &optContext;
	
	pContext->Put(OVC, "x264");
	pContext->Put(VIDEO_BITRATE, "1200");
	pContext->Put(OFPS, "25");
	pContext->Put(OAC, "pcm");
	pContext->Put(FORCE_OF, "flv");
	pContext->Put(AUDIO_BITRATE, "192");
	pContext->Put(OSRATE, "44100");
	pContext->Put(VIDEO_WIDTH, "789");
	pContext->Put(VIDEO_HEIGHT, "123");
	pContext->Put(IFILE, "Input.file");
	pContext->Put(OFILE, "Output.file");
	
	DefaultOptionExpBuilder builder;
	OptionExpTree optTree;
	bool bRet = optTree.Build(pContext, &builder);
	if(!bRet)
	{
		SetDlgItemText(IDC_EDIT_RESULT, _T("Build Option Tree Failed"));
		return;
	}

	std::string szResult;
	bRet = optTree.Evaluate(pContext, szResult);

	if(!bRet)
	{
		std::string szErrorMsg;
		bRet = pContext->Get(ERROR_STR, szErrorMsg);
		if(!bRet)
		{
			szResult.append("Evaluate Failed. Error Str=NULL");
		}
		else
		{
			szResult.assign("Evaluate Failed. Error Str=").append(szErrorMsg);
		}
		SetDlgItemText(IDC_EDIT_RESULT, szResult.c_str());
	}
	else
	{
		std::string szErrorMsg;
		bRet = pContext->Get(ERROR_STR, szErrorMsg);
		if(bRet)
		{
			AfxTrace(_T("%s\n"), szErrorMsg.c_str());
			szResult.append("ErrorMsg=NULL");
		}

		SetDlgItemText(IDC_EDIT_RESULT, szResult.c_str());
	}
}
