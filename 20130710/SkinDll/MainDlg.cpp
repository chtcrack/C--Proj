// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SkinDll.h"
#include "MainDlg.h"
#include ".\maindlg.h"
#include "Login.h"
#include "AsmBase.h"


// MainDlg �Ի���

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


// MainDlg ��Ϣ�������

void MainDlg::OnClose()
{
	
	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)UloadProce,NULL,NULL,NULL);
	CDialog::OnClose();
}

void MainDlg::OnBnClickedButtonGuaji()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

void MainDlg::OnBnClickedButtonTest()
{


	

	
	

	CIni ini("na.ini");

	ini.SetFileName("gameacc.ini");


	//	DWORD Ecxptr=*(DWORD*)(GetEdi()+0x38);


	// TODO: �ڴ���ӿؼ�֪ͨ����������

	Login Tlogin;
	Tlogin.SelectServer("�ڲ��¶���","��¹");

	//Tlogin.WriteUserName("chtcrack");
	Tlogin.InputPassWord("cht111");
	if(GetLoginStatus())
	{
		Tlogin.CreatChar("���־�");
		Tlogin.EnterGame();
	}
	else
	{
		Tlogin.EnterGame();
	}

			

	

	
	/*
	bool IsChar=Tlogin.CheckHaveChart("��ѩ��");
		if (IsChar)
		{
			Tlogin.EnterGame();
		}
		else
		{
	
			Tlogin.CreatChar("���־�");
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



	DWORD ConAddr=0;//����Ϊȫ�ֱ���

	
	CString str;
	str.Format("%s",lf.account);
	//���ڴ�ӳ���ļ�
	HANDLE hOFM = OpenFileMapping(FILE_MAP_WRITE,FALSE,str);

	//����ļ�������,�򴴽�һ��
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


			//��ȡ��¼������Ϣ����¼.



			/*
	switch (info)//�¼���
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




