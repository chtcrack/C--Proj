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
DWORD CallAddr=0x1003F9C0;//���ͼ��̲���call
//ѡ������ͷ�����
void Login::SelectServer(CString AreaName,CString ServerName)
{
	IpBuff=0;
	Testip="";


	DWORD ServerZuobiao=0x0143009F;
	if(Ecxptr==0)
	{
		Ecxptr=*(DWORD*)(GetEsi()+0x40);
	}

	if (AreaName=="������һ��")
	{
		DWORD AeraId=0x0096009C;
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.41";

		}
		if (ServerName=="��Ԩ")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.31";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.43";

		}
		if (ServerName=="���")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.83";

		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.73";

		}
		if (ServerName=="��ԯ")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.71";

		}
	}

	if (AreaName=="�ϱ��ع���")
	{
		DWORD AeraId=0x00930164;
		if (ServerName=="���(�ϱ�)")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="210.73.209.81";
		}
	}
	if (AreaName=="�ڲ��¶���")
	{
		DWORD AeraId=0x008A01FA;
		if (ServerName=="Ǭ��")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.237";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.197";
		}
		if (ServerName=="���")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.231";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.189";
		}
		if (ServerName=="���")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.187";
		}
		if (ServerName=="�쳾")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.195";
		}
		if (ServerName=="���")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.185";
		}
		if (ServerName=="��Ӱ")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.193";
		}
		if (ServerName=="��Ѫ")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.183";
		}
		if (ServerName=="��¹")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.181";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.191";
		}
	}
	if (AreaName=="�ڲ���һ��")
	{
		DWORD AeraId=0x008902A8;
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.179";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.177";
		}
		if (ServerName=="ħ��")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.167";
		}
		if (ServerName=="�ٹ�")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.169";
		}
		if (ServerName=="��Ӱ")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.165";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.163";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.173";
		}
		if (ServerName=="��ɲ")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.167";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.171";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.25.161";
		}
	}
	if (AreaName=="����һ����")
	{
		DWORD AeraId=0x008E035A;
		if (ServerName=="�ƽ����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.11.13";
		}
		if (ServerName=="�׳���Ӱ")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.11.23";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="42.62.11.11";
		}
		if (ServerName=="��������")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.89";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.89";
		}
		if (ServerName=="�������")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.77";
		}
		if (ServerName=="��Ǿ���")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.77";
		}
		if (ServerName=="СΨ")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.71";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.73";
		}
		if (ServerName=="������")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.73";
		}
		if (ServerName=="��Ƥ")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.81";
		}
		if (ServerName=="ʮ������")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.81";
		}
		if (ServerName=="����")
		{
			SelectAreaCall(AeraId,ServerZuobiao);
			Testip="118.26.204.71";
		}
	}
}
void Login::SelectAreaCall(DWORD AreaId,DWORD Serverid)
{

	DWORD ConfirmSelect=0x02940203;
	ClickZuoBiao(AreaId);//ѡ��
	Sleep(500);
	ClickZuoBiao(Serverid);//ѡ������
	Sleep(500);
	ClickZuoBiao(ConfirmSelect);//���ȷ��ѡ��
	Sleep(500);

}
void Login::WriteUserName(CString UserName)//��������Ϸ����ǰд��logon.cfg,����д���¼�û���
{
	std::fstream file1("D:\\��Ƥ����\\config\\logon.cfg" );
	file1<<"Logon_BogType = 0\n" ;
	file1<<"Logon_BogIndex = 4\n" ;
	file1<<"Logon_WorldIndex = 10\n" ;
	file1<<"Logon_WorldID = 1004\n" ;
	file1<<"Logon_Remember = 1\n" ;
	file1<<"Logon_Account = " + UserName + "\n" ;
	file1<<"Logon_PlayVideo = 1\n" ;
	file1.close();

}


//�������벢��¼
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
		MyDebug("��������-%08X",PKeyCode);
	}


	MyDebug("ecxptr-%08X",Ecxptr);
	__asm//���س�
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

void Login::InputPassWordCall(DWORD Keycode)//��������Call
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
bool Login:: CheckHaveChart(CString CharName)//����Ƿ������ɫ���Ľ�ɫ
{
	DWORD CheckBase=*(DWORD*)(0xC22B20+0x4);
	if (CheckBase==0)
	{
		return false;
	}
	DWORD CharNamePtr=*(DWORD*)(CheckBase+0x18)+0x14;
	MyDebug("��ȡ����ɫ��ָ��-%08X",CharNamePtr);
	CString RCharname;
	wchar_t *aa;
	aa=(wchar_t *)(CharNamePtr+0);

	RCharname.Format("%s",UnicodeToGB2312(aa));
	MyDebug("��ȡ���Ľ�ɫ��-%s",RCharname);
	if (RCharname==CharName)
	{
		return true;
	}
	return false;

}
//������ɫ,ѹ��һ������,ְҵ��
void Login::CreatChar(CString Job)
{
	MyDebug("��ʼ������ɫ...");
	DWORD ZuoBiao=0;
	if(Job=="�������")
	{
		ZuoBiao=0x0059009A;
	}
	if(Job=="��ħʹ��")
	{
		ZuoBiao=0x00A100BB;
	}
	if(Job=="���־�")
	{
		ZuoBiao=0x010300A8;
	}
	if(Job=="����ʦ")
	{
		ZuoBiao=0x015E00B0;
	}
	if(Job=="���ȴ̿�")
	{
		ZuoBiao=0x01CD00C6;
	}
	if(Job=="������ʿ")
	{
		ZuoBiao=0x021700D1;
	}
	ClickZuoBiao(ZuoBiao);//ѡ��ְҵ

	ZuoBiao=0x02B301EB;
	ClickZuoBiao(ZuoBiao);//�����һ��

	Sleep(3000);
	CString CharName="";
	MyDebug("��ʼ��ȡ�����Ľ�ɫ��");
	DWORD CharNamePtr;
	wchar_t *aa;
CreatButton:
	CharNamePtr=GetCharNameeax();//��ȡ��ǰ�����Ľ�ɫ��ָ��
	aa=(wchar_t *)(CharNamePtr+0);
	CharName.Format("%s",UnicodeToGB2312(aa));//��ȡ��ǰ�����Ľ�ɫ��,������д��ini
	MyDebug("�����Ľ�ɫ��-%s",CharName);
	ZuoBiao=0x02B101D8;
	ClickZuoBiao(ZuoBiao);//���������ɫ
	CheckCreatStatus();//��������ɫ����
	if(CheckCharKey==3)
	{
		MyDebug("��ɫ����������������ɫ��-%08X",CheckCharKey);

		ZuoBiao=0x028D025F;
		ClickZuoBiao(ZuoBiao);
		Sleep(1000);
		goto CreatButton;
	}


}
void Login::EnterGame()//������Ϸ
{
	MyDebug("��ʼ������Ϸ...");

	DWORD ZuoBiao=0x02B40201;
	ClickZuoBiao(ZuoBiao);//���������Ϸ

	Sleep(2000);
	ZuoBiao=0x027101CB;
	ClickZuoBiao(ZuoBiao);//���ѡ����ߵ�ȷ��
	CheckGameLoad();
	if(FirstLogin)
		MyDebug("��ɫ��һ�ε�¼,��ESC");
	{
		__asm//��Esc
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