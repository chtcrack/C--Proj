#include "StdAfx.h"
#include ".\asmbase.h"
#include "Comm.h"
#include "Hook.h"
#include "common_link.h"
DWORD Ecxptr=0;
DWORD IpEcxPtr=0;
DWORD Tempeax=0;
DWORD TempEcx=0;
DWORD TempEsi=0;
bool FirstLogin;
CString TempStr="";
void __stdcall Routin(CPU_ST* lpcpu)
{

	Tempeax = lpcpu->regEax;
	TempEcx = lpcpu->regEcx;
	TempEsi=lpcpu->regEsi;
	return;
}

void __stdcall Routin1(CPU_ST* lpcpu)
{

	Tempeax = lpcpu->regEax;
	if (Tempeax!=0 && !IsBadReadPtr((LPVOID)Tempeax,4))
	{
		wchar_t *aa;
		aa=(wchar_t *)(Tempeax+0);
		TempStr.Format("%s",UnicodeToGB2312(aa));
		MyDebug("检查字符串-%s-取前二个汉字-%s",TempStr,TempStr.Left(4));
		if(TempStr.Left(4)=="角色")
		{
			CheckCharKey=1;
			MyDebug("在选择角色画面-%s",TempStr);

		}
		if(TempStr=="方外术士")
		{
			CheckCharKey=2;
			MyDebug("在创建角色画面-%s",TempStr);

		}
		
	}
	return;
}
void __stdcall Routin2(CPU_ST* lpcpu)
{

	
	Tempeax = lpcpu->regEax;
	if (Tempeax!=0 && !IsBadReadPtr((LPVOID)Tempeax,4))
	{
		wchar_t *aa;
		aa=(wchar_t *)(Tempeax+0);
		TempStr.Format("%s",UnicodeToGB2312(aa));
	//	MyDebug("检查字符串-%s",TempStr);
		
		if(TempStr=="角色名字已经存在")
		{
			CheckCharKey=3;
			MyDebug("角色重名-%s",TempStr);
		}
		if(TempStr=="在线")
		{
			CheckCharKey=4;
			MyDebug("检测到游戏读取完成关键字-%s",TempStr);
		}
	}
	return;
}

DWORD GetEsi()
{

	TempEsi=0;
	HookNode* node = Hook((void*)0x00588966,2,Routin,false);//登录画面换ip获取钩子

	for (int i=0;i!=100;i++)
	{
		if (TempEsi!=0)
		{
			HookClear();

			break;
		}

		Sleep(10);
	}

	return TempEsi;
}
DWORD GetCharNameeax()//获取创建角色时的姓名,这里在登录前其实还可以获取用户名和密码
{
	Tempeax=0;
	MyDebug("开始挂钩获取角色姓名指针");
	HookNode* node1 = Hook((void*)0x0044BE52,1,Routin,false);//在内存地址0x0044BE62出挂钩,该地址大小为1字节,执行Routin函数
	MyDebug("角色姓名指针挂钩完成");
	for (int i=0;i!=100;i++)
	{
		if (Tempeax!=0 && !IsBadReadPtr((LPVOID)Tempeax,4))
		{
			MyDebug("获取到的eax-%08X",Tempeax);
			HookClear();

			break;
		}

		Sleep(10);
	}

	return Tempeax;
}

void UnHookGouzi()
{
	HookClear();
}
bool GetLoginStatus()//检查10秒是否在创建角色画面,如果是返回true,否则返回false即有角色了
{
	FirstLogin=false;
	MyDebug("开始挂钩检查是否在创建角色");
	CheckCharKey=0;
	Tempeax=0;
	HookNode* node2 = Hook((void*)0x10001627,1,Routin1,false);//在内存地址0x0044BE62出挂钩,该地址大小为1字节,执行Routin函数
	int i=0;
	while(i!=1000)//等待10秒
	{

		if (CheckCharKey==1)
		{
			MyDebug("检测到选择角色画面");
			HookClear();
			return false;
		}
		if(CheckCharKey==2)
		{
			MyDebug("检测到在创建角色画面");
			FirstLogin=true;
			HookClear();
			return true;
		}
		Sleep(10);
		i++;
	}

	MyDebug("已有角色,十秒已过,卸载钩子");
	HookClear();
	return false;
}

bool CheckCreatStatus()//检查10秒是否创建角色成功,如果成功返回true,否则返回false即角色重名
{
	CheckCharKey=0;
	MyDebug("开始检测创建角色是否成功");
	Tempeax=0;
	HookNode* node3 = Hook((void*)0x10001627,1,Routin2,false);//在内存地址0x0044BE62出挂钩,该地址大小为1字节,执行Routin函数
	int i=0;
	while(i!=1000)//等待10秒
	{
		if (CheckCharKey==3)
		{
			 HookClear();
			 MyDebug("角色重名-%s",TempStr);
			 return false;
		 }
		Sleep(10);
		i++;
	}

	MyDebug("十秒已过,卸载钩子,角色无重名");
	CheckCharKey=0;
	HookClear();
	return true;
}
bool CheckGameLoad()//检查游戏是否读取完成,是和超时返回false
{
	
	CheckCharKey=0;
	MyDebug("开始检测游戏是否读取完成");
	Tempeax=0;
	HookNode* node4 = Hook((void*)0x10001627,1,Routin2,false);//在内存地址0x0044BE62出挂钩,该地址大小为1字节,执行Routin函数
	int i=0;
	while(i!=1000)//等待10秒
	{
		if (CheckCharKey==4)
		{
			HookClear();
			MyDebug("游戏读取完成-%s",TempStr);
			return false;
		}
		Sleep(10);
		i++;
	}

	MyDebug("15秒已过,假定游戏已读取完成");
	HookClear();
	return false;
}


