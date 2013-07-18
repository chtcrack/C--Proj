// DebugExeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DebugExe.h"
#include "DebugExeDlg.h"
#include ".\debugexedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDebugExeDlg �Ի���



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


// CDebugExeDlg ��Ϣ�������

BOOL CDebugExeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDebugExeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CDebugExeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDebugExeDlg::OnBnClickedOk()//����һ�������߳�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)CheckAccount,NULL,NULL,NULL);
}

void CheckAccount()
{
CIni ini("Account.ini");

}

void CDebugExeDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: Add your control notification handler code here UpdateData(TRUE); char szDir[MAX_PATH]; BROWSEINFO bi; ITEMIDLIST *pidl; 
	 UpdateData(TRUE);
BROWSEINFO bi;
char szDir[200];
ITEMIDLIST *pidl;
	bi.hwndOwner = this->m_hWnd; // ָ�������ڣ��ڶԻ�����ʾ�ڼ䣬�����ڽ�������   
	bi.pidlRoot = NULL; // ���ָ��NULL�����ԡ����桱Ϊ��    
	bi.pszDisplayName = szDir; 
	bi.lpszTitle = "��ѡ��Ŀ¼"; // ��һ�н���ʾ�ڶԻ���Ķ���   
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
