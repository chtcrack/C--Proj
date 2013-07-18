// TestExe.cpp : 定义应用程序的类行为。
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


// CTestExeApp 构造

CTestExeApp::CTestExeApp()
{
	
}


// 唯一的一个 CTestExeApp 对象

CTestExeApp theApp;


// CTestExeApp 初始化

BOOL CTestExeApp::InitInstance()
{

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

 	CTestExeDlg dlg;
 	m_pMainWnd = &dlg;
 	INT_PTR nResponse = dlg.DoModal();






	return FALSE;
}
