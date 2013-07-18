// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SkinDll.h"
#include "MainDlg.h"
#include ".\maindlg.h"

#include "GameMain.h"

#include "AsmBase.h"
#include <Shlwapi.h> 
#pragma comment(lib, "shlwapi.lib")
FindWay fw;
BaseCall bs;
// MainDlg 对话框

IMPLEMENT_DYNAMIC(MainDlg, CDialog)
MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MainDlg::IDD, pParent)
{
	//bs.SetHook();
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
	//bs.UnSetHook();

}

void MainDlg::OnBnClickedButtonTest()
{
	// TODO: 在此添加控件通知处理程序代码
	//bs.Test();
	//fw.RootAllObject();
		//bs.TTTTT();
	//[[00C26110+40]+0x818+0x4]
	/*
	DWORD xx = *(DWORD*)((*(DWORD*)(Hp_QuestTargt+0x40)) + 0x81c);
		
		fw.RootID(xx);*/
	
			//fw.FindToNpc("夏花儿");*/
	//fw.FindToNpc("夏花儿");
	//fw.BackToCity();
/*
	CString dd;
	GetDlgItemText(IDC_Test,dd);
	int xx;
	::StrToIntEx(dd.GetString(),STIF_SUPPORT_HEX,&xx);
	bs.bll(xx);*/

	//bs.Bl();
bs.hhh();
	
}
