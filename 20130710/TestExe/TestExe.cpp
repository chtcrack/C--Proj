// TestExe.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "TestExe.h"
#include "TestExeDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestExeApp

BEGIN_MESSAGE_MAP(CTestExeApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestExeApp ����

CTestExeApp::CTestExeApp()
{
	
}


// Ψһ��һ�� CTestExeApp ����

CTestExeApp theApp;


// CTestExeApp ��ʼ��

BOOL CTestExeApp::InitInstance()
{

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

 	CTestExeDlg dlg;
 	m_pMainWnd = &dlg;
 	INT_PTR nResponse = dlg.DoModal();






	return FALSE;
}
