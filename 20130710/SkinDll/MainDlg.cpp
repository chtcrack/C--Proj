// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SkinDll.h"
#include "MainDlg.h"
#include ".\maindlg.h"
#include "Login.h"
#include "AsmBase.h"


// MainDlg 对话框

IMPLEMENT_DYNAMIC(MainDlg, CDialog)
MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MainDlg::IDD, pParent)
{
}

MainDlg::~MainDlg()
{
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_GuaJi, OnBnClickedButtonGuaji)
	ON_BN_CLICKED(IDC_BUTTON_Test, OnBnClickedButtonTest)
END_MESSAGE_MAP()


// MainDlg 消息处理程序

void MainDlg::OnClose()
{
	
	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)UloadProce,NULL,NULL,NULL);
	CDialog::OnClose();
}

void MainDlg::OnBnClickedButtonGuaji()
{
	// TODO: 在此添加控件通知处理程序代码

}

void MainDlg::OnBnClickedButtonTest()
{


	

	
	

	CIni ini("na.ini");

	ini.SetFileName("gameacc.ini");


	//	DWORD Ecxptr=*(DWORD*)(GetEdi()+0x38);


	// TODO: 在此添加控件通知处理程序代码

	Login Tlogin;
	Tlogin.SelectServer("内测新二区","逐鹿");

	//Tlogin.WriteUserName("chtcrack");
	Tlogin.InputPassWord("cht111");
	if(GetLoginStatus())
	{
		Tlogin.CreatChar("御林军");
		Tlogin.EnterGame();
	}
	else
	{
		Tlogin.EnterGame();
	}

			

	

	
	/*
	bool IsChar=Tlogin.CheckHaveChart("武雪曼");
		if (IsChar)
		{
			Tlogin.EnterGame();
		}
		else
		{
	
			Tlogin.CreatChar("御林军");
			Tlogin.EnterGame();
		}*/
	

}

typedef struct LoginInfo
{
	char server[100];
	char qu[100];
	char account[100];
	char password[100];
	char other[100];

}LINFO;


void Login(LINFO &lf)
{



	DWORD ConAddr=0;//必须为全局变量

	
	CString str;
	str.Format("%s",lf.account);
	//打开内存映射文件
	HANDLE hOFM = OpenFileMapping(FILE_MAP_WRITE,FALSE,str);

	//如果文件不存在,则创建一个
	if (hOFM==0)
	{
		hOFM = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,0x10000,str);
	}


	if (hOFM != 0)
	{
		ConAddr =(DWORD)(::MapViewOfFile(hOFM, FILE_MAP_WRITE, 0, 0, 0));
	}

	if (ConAddr==0)
	{
		return;
	}
	else
	{
		memset((PVOID)ConAddr,0,0x10000);
	}

	




	
	
	



	do 
	{


			//获取登录所需信息并登录.



			/*
	switch (info)//事件机
				{
				
				case:
	
	
	
	
				}
	
	
		
	
	
				
			 
	
	
		Sleep(500)*/
	

	} while ();





}


void StartLogin()
{
		//getmemory Fild Data


		HANDLE hOFM = OpenFileMapping(FILE_MAP_WRITE,FALSE,"AdminFileMap");
		DWORD ConAddr =(DWORD)(::MapViewOfFile(hOFM, FILE_MAP_WRITE, 0, 0, 0));


	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Login,(PVOID)ConAddr,NULL,NULL);
}




