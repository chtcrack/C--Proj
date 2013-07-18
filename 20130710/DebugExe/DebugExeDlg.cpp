// DebugExeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DebugExe.h"
#include "DebugExeDlg.h"
#include ".\debugexedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDebugExeDlg 对话框



CDebugExeDlg::CDebugExeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDebugExeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDebugExeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDebugExeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CDebugExeDlg 消息处理程序

BOOL CDebugExeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDebugExeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CDebugExeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDebugExeDlg::OnBnClickedOk()//创建一个工作线程
{
	// TODO: 在此添加控件通知处理程序代码
	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)CheckAccount,NULL,NULL,NULL);
}

void CheckAccount()
{
CIni ini("Account.ini");

}

void CDebugExeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here UpdateData(TRUE); char szDir[MAX_PATH]; BROWSEINFO bi; ITEMIDLIST *pidl; 
	 UpdateData(TRUE);
BROWSEINFO bi;
char szDir[200];
ITEMIDLIST *pidl;
	bi.hwndOwner = this->m_hWnd; // 指定父窗口，在对话框显示期间，父窗口将被禁用   
	bi.pidlRoot = NULL; // 如果指定NULL，就以“桌面”为根    
	bi.pszDisplayName = szDir; 
	bi.lpszTitle = "请选择目录"; // 这一行将显示在对话框的顶端   
	bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL; bi.lParam = 0; bi.iImage = 0; 
	pidl = SHBrowseForFolder(&bi);
	if(pidl == NULL) return; 
	if(!SHGetPathFromIDList(pidl, szDir))
	{
		return;
	}
	else 
	{
		m_strPath = szDir;
		SetDlgItemText(IDC_EDIT1,(LPCTSTR)m_strPath);
	}
		UpdateData(FALSE); 
}
