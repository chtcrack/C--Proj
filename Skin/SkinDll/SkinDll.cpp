// SkinDll.cpp : ���� DLL �ĳ�ʼ�����̡�
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


// CSkinDllApp ����

CSkinDllApp::CSkinDllApp()
{

	//Load INI Setting Here
}


// Ψһ��һ�� CSkinDllApp ����

CSkinDllApp theApp;



MainDlg *p_Dlg = new MainDlg;

void ShowDialog(MainDlg *pMainDlg)
{
	pMainDlg->DoModal();
}



// CSkinDllApp ��ʼ��

BOOL CSkinDllApp::InitInstance()
{
	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ShowDialog,(LPVOID)p_Dlg,NULL,NULL);
	
	//bs.SetHook();

	CWinApp::InitInstance();

	return TRUE;
}



//����ж��
DWORD WINAPI UloadProce(PVOID param)
{
	//bs.UnSetHook();
	Sleep(1000);
	CloseHandle(theApp.m_hInstance);
	FreeLibraryAndExitThread(theApp.m_hInstance, 0); 
	return 0;  
}