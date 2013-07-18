// SkinDll.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "SkinDll.h"
#include "MainDlg.h"
//#include "AsmBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CSkinDllApp, CWinApp)
END_MESSAGE_MAP()


// CSkinDllApp 构造

CSkinDllApp::CSkinDllApp()
{

	//Load INI Setting Here
}


// 唯一的一个 CSkinDllApp 对象

CSkinDllApp theApp;



MainDlg *p_Dlg = new MainDlg;

void ShowDialog(MainDlg *pMainDlg)
{
	pMainDlg->DoModal();
}



// CSkinDllApp 初始化

BOOL CSkinDllApp::InitInstance()
{
	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ShowDialog,(LPVOID)p_Dlg,NULL,NULL);
	
	//bs.SetHook();

	CWinApp::InitInstance();

	return TRUE;
}



//自我卸载
DWORD WINAPI UloadProce(PVOID param)
{
	//bs.UnSetHook();
	Sleep(1000);
	CloseHandle(theApp.m_hInstance);
	FreeLibraryAndExitThread(theApp.m_hInstance, 0); 
	return 0;  
}