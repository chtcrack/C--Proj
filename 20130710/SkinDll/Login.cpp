#include "StdAfx.h"
#include ".\login.h"
#include "Ini.h"
#include <string>
#include <fstream>
#include "AsmBase.h"
#include "Comm.h"
Login::Login(void)
{

}

Login::~Login(void)
{
}

BYTE CheckCharKey=0;
DWORD CallAddr=0x1003F9C0;//鼠标和键盘操作call
//选择大区和服务器
void Login::SelectServer(CString AreaName,CString ServerName)
{
	IpBuff=0;
	Testip="";


	DWORD ServerZuobiao=0x0143009F;
	if(Ecxptr==0)
	{
		Ecxptr=*(DWORD*)(GetEsi()+0x40);
	}

	if (AreaName=="公测新一区")
	{
		DWORD AeraId=0x0096009C;
		if (ServerName=="虎魄")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.41";

		}
		if (ServerName=="龙渊")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.31";
		}
		if (ServerName=="神舞")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.43";

		}
		if (ServerName=="青锋")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.83";

		}
		if (ServerName=="鸣鸿")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.73";

		}
		if (ServerName=="轩辕")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.71";

		}
	}

	if (AreaName=="老兵回归区")
	{
		DWORD AeraId=0x00930164;
		if (ServerName=="昊天(老兵)")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.81";
		}
	}
	if (AreaName=="内测新二区")
	{
		DWORD AeraId=0x008A01FA;
		if (ServerName=="乾坤")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.237";
		}
		if (ServerName=="辰星")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.197";
		}
		if (ServerName=="天痕")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.231";
		}
		if (ServerName=="幻月")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.189";
		}
		if (ServerName=="凌风")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.187";
		}
		if (ServerName=="红尘")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.195";
		}
		if (ServerName=="苍穹")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.185";
		}
		if (ServerName=="剑影")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.193";
		}
		if (ServerName=="铁血")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.183";
		}
		if (ServerName=="逐鹿")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.181";
		}
		if (ServerName=="烟雨")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.191";
		}
	}
	if (AreaName=="内测新一区")
	{
		DWORD AeraId=0x008902A8;
		if (ServerName=="狼烟")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.179";
		}
		if (ServerName=="阴阳")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.177";
		}
		if (ServerName=="魔宫")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.167";
		}
		if (ServerName=="百鬼")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.169";
		}
		if (ServerName=="魅影")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.165";
		}
		if (ServerName=="玄狐")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.163";
		}
		if (ServerName=="虚灵")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.173";
		}
		if (ServerName=="罗刹")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.167";
		}
		if (ServerName=="天狼")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.171";
		}
		if (ServerName=="鬼魅")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.161";
		}
	}
	if (AreaName=="经典一二区")
	{
		DWORD AeraId=0x008E035A;
		if (ServerName=="黄金家族")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.11.13";
		}
		if (ServerName=="白城魅影")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.11.23";
		}
		if (ServerName=="鬼牌")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.11.11";
		}
		if (ServerName=="寒冰地狱")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.89";
		}
		if (ServerName=="狐仙")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.89";
		}
		if (ServerName=="三惑五劫")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.77";
		}
		if (ServerName=="鬼城惊魂")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.77";
		}
		if (ServerName=="小唯")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.71";
		}
		if (ServerName=="霍心")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.73";
		}
		if (ServerName=="靖公主")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.73";
		}
		if (ServerName=="画皮")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.81";
		}
		if (ServerName=="十二星座")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.81";
		}
		if (ServerName=="画心")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.71";
		}
	}
}
void Login::SelectAreaCall(DWORD AreaId,DWORD Serverid)
{

	DWORD ConfirmSelect=0x02940203;
	ClickZuoBiao(AreaId);//选区
	Sleep(500);
	ClickZuoBiao(Serverid);//选服务器
	Sleep(500);
	ClickZuoBiao(ConfirmSelect);//点击确认选择
	Sleep(500);

}
void Login::WriteUserName(CString UserName)//必须在游戏启动前写入logon.cfg,功能写入登录用户名
{
	std::fstream file1("D:\\画皮世界\\config\\logon.cfg" );
	file1<<"Logon_BogType = 0\n" ;
	file1<<"Logon_BogIndex = 4\n" ;
	file1<<"Logon_WorldIndex = 10\n" ;
	file1<<"Logon_WorldID = 1004\n" ;
	file1<<"Logon_Remember = 1\n" ;
	file1<<"Logon_Account = " + UserName + "\n" ;
	file1<<"Logon_PlayVideo = 1\n" ;
	file1.close();

}


//输入密码并登录
void Login::InputPassWord(CString PassWord)
{
	IpBuff=Testip.GetBuffer();
	SelectServerCall((DWORD)IpBuff);
	//delete IpBuff;
	//IpBuff=0;

	CString Passw=PassWord;
	BYTE PKeyCode=0;
	char* Buf = Passw.GetBuffer();

	int StringLen= Passw.GetLength();

	for (int i=0;i!=StringLen;i++)
	{
		PKeyCode=*(BYTE*)(Buf+i);
		InputPassWordCall(PKeyCode);
		MyDebug("输入密码-%08X",PKeyCode);
	}


	MyDebug("ecxptr-%08X",Ecxptr);
	__asm//按回车
	{
		mov ecx,Ecxptr
			push 0x0
			push 0xD
			push 0x100
			call CallAddr
	}
	Buf=0;
	delete Buf;

}

void Login::InputPassWordCall(DWORD Keycode)//输入密码Call
{
	if(Ecxptr==0)
	{
		Ecxptr=*(DWORD*)(GetEsi()+0x40);
		MyDebug("EcxPtr-%08x",Ecxptr);
	}

	__asm
	{
		mov ecx,Ecxptr
			push 0x0
			push Keycode
			push 0x102
			call CallAddr
	}

}
bool Login:: CheckHaveChart(CString CharName)//检查是否包含角色名的角色
{
	DWORD CheckBase=*(DWORD*)(0xC22B20+0x4);
	if (CheckBase==0)
	{
		return false;
	}
	DWORD CharNamePtr=*(DWORD*)(CheckBase+0x18)+0x14;
	MyDebug("读取到角色名指针-%08X",CharNamePtr);
	CString RCharname;
	wchar_t *aa;
	aa=(wchar_t *)(CharNamePtr+0);

	RCharname.Format("%s",UnicodeToGB2312(aa));
	MyDebug("读取到的角色名-%s",RCharname);
	if (RCharname==CharName)
	{
		return true;
	}
	return false;

}
//创建角色,压入一个参数,职业名
void Login::CreatChar(CString Job)
{
	MyDebug("开始创建角色...");
	DWORD ZuoBiao=0;
	if(Job=="九霄灵狐")
	{
		ZuoBiao=0x0059009A;
	}
	if(Job=="降魔使者")
	{
		ZuoBiao=0x00A100BB;
	}
	if(Job=="御林军")
	{
		ZuoBiao=0x010300A8;
	}
	if(Job=="阴阳师")
	{
		ZuoBiao=0x015E00B0;
	}
	if(Job=="鬼魅刺客")
	{
		ZuoBiao=0x01CD00C6;
	}
	if(Job=="方外术士")
	{
		ZuoBiao=0x021700D1;
	}
	ClickZuoBiao(ZuoBiao);//选择职业

	ZuoBiao=0x02B301EB;
	ClickZuoBiao(ZuoBiao);//点击下一步

	Sleep(3000);
	CString CharName="";
	MyDebug("开始读取创建的角色名");
	DWORD CharNamePtr;
	wchar_t *aa;
CreatButton:
	CharNamePtr=GetCharNameeax();//获取当前创建的角色名指针
	aa=(wchar_t *)(CharNamePtr+0);
	CharName.Format("%s",UnicodeToGB2312(aa));//获取当前创建的角色名,可用来写入ini
	MyDebug("创建的角色名-%s",CharName);
	ZuoBiao=0x02B101D8;
	ClickZuoBiao(ZuoBiao);//点击创建角色
	CheckCreatStatus();//检测如果角色重名
	if(CheckCharKey==3)
	{
		MyDebug("角色重名点击随机生产角色名-%08X",CheckCharKey);

		ZuoBiao=0x028D025F;
		ClickZuoBiao(ZuoBiao);
		Sleep(1000);
		goto CreatButton;
	}


}
void Login::EnterGame()//进入游戏
{
	MyDebug("开始进入游戏...");

	DWORD ZuoBiao=0x02B40201;
	ClickZuoBiao(ZuoBiao);//点击进入游戏

	Sleep(2000);
	ZuoBiao=0x027101CB;
	ClickZuoBiao(ZuoBiao);//点击选择分线的确定
	CheckGameLoad();
	if(FirstLogin)
		MyDebug("角色第一次登录,按ESC");
	{
		__asm//按Esc
		{
			mov ecx,Ecxptr
				push 0xC0010001
				push 0x1B
				push 0x100
				call CallAddr
				mov ecx,Ecxptr
				push 0xC0010001
				push 0x1B
				push 0x101
				call CallAddr
				mov ecx,Ecxptr
				push 0xC0010001
				push 0x1B
				push 0x102
				call CallAddr
		}
	}
}
void Login::SelectServerCall(DWORD IpaddressPtr)
{
	if (IpEcxPtr==0)
	{
		IpEcxPtr=*(DWORD*)(TempEsi+0x260);
	}
	//MyDebug("Ipecx%08X",IpEcxPtr);

	DWORD CallAddr=0x02824320;
	DWORD ServerPort=0x426B;
	__asm
	{
		pushad
			mov ecx,IpEcxPtr;
		push ServerPort
			push IpaddressPtr
			call CallAddr
			popad
	}


}
void Login::ClickZuoBiao(DWORD ZuoBiao)
{

	__asm
	{
		mov ecx,Ecxptr
			push ZuoBiao
			push 0x1
			push 0x200
			call CallAddr

			mov ecx,Ecxptr
			push ZuoBiao
			push 0x1
			push 0x201
			call CallAddr
			mov ecx,Ecxptr
			push ZuoBiao
			push 0x1
			push 0x202
			call CallAddr
	}
}