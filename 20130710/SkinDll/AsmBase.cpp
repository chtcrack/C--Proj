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
		MyDebug("����ַ���-%s-ȡǰ��������-%s",TempStr,TempStr.Left(4));
		if(TempStr.Left(4)=="��ɫ")
		{
			CheckCharKey=1;
			MyDebug("��ѡ���ɫ����-%s",TempStr);

		}
		if(TempStr=="������ʿ")
		{
			CheckCharKey=2;
			MyDebug("�ڴ�����ɫ����-%s",TempStr);

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
	//	MyDebug("����ַ���-%s",TempStr);
		
		if(TempStr=="��ɫ�����Ѿ�����")
		{
			CheckCharKey=3;
			MyDebug("��ɫ����-%s",TempStr);
		}
		if(TempStr=="����")
		{
			CheckCharKey=4;
			MyDebug("��⵽��Ϸ��ȡ��ɹؼ���-%s",TempStr);
		}
	}
	return;
}

DWORD GetEsi()
{

	TempEsi=0;
	HookNode* node = Hook((void*)0x00588966,2,Routin,false);//��¼���滻ip��ȡ����

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
DWORD GetCharNameeax()//��ȡ������ɫʱ������,�����ڵ�¼ǰ��ʵ�����Ի�ȡ�û���������
{
	Tempeax=0;
	MyDebug("��ʼ�ҹ���ȡ��ɫ����ָ��");
	HookNode* node1 = Hook((void*)0x0044BE52,1,Routin,false);//���ڴ��ַ0x0044BE62���ҹ�,�õ�ַ��СΪ1�ֽ�,ִ��Routin����
	MyDebug("��ɫ����ָ��ҹ����");
	for (int i=0;i!=100;i++)
	{
		if (Tempeax!=0 && !IsBadReadPtr((LPVOID)Tempeax,4))
		{
			MyDebug("��ȡ����eax-%08X",Tempeax);
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
bool GetLoginStatus()//���10���Ƿ��ڴ�����ɫ����,����Ƿ���true,���򷵻�false���н�ɫ��
{
	FirstLogin=false;
	MyDebug("��ʼ�ҹ�����Ƿ��ڴ�����ɫ");
	CheckCharKey=0;
	Tempeax=0;
	HookNode* node2 = Hook((void*)0x10001627,1,Routin1,false);//���ڴ��ַ0x0044BE62���ҹ�,�õ�ַ��СΪ1�ֽ�,ִ��Routin����
	int i=0;
	while(i!=1000)//�ȴ�10��
	{

		if (CheckCharKey==1)
		{
			MyDebug("��⵽ѡ���ɫ����");
			HookClear();
			return false;
		}
		if(CheckCharKey==2)
		{
			MyDebug("��⵽�ڴ�����ɫ����");
			FirstLogin=true;
			HookClear();
			return true;
		}
		Sleep(10);
		i++;
	}

	MyDebug("���н�ɫ,ʮ���ѹ�,ж�ع���");
	HookClear();
	return false;
}

bool CheckCreatStatus()//���10���Ƿ񴴽���ɫ�ɹ�,����ɹ�����true,���򷵻�false����ɫ����
{
	CheckCharKey=0;
	MyDebug("��ʼ��ⴴ����ɫ�Ƿ�ɹ�");
	Tempeax=0;
	HookNode* node3 = Hook((void*)0x10001627,1,Routin2,false);//���ڴ��ַ0x0044BE62���ҹ�,�õ�ַ��СΪ1�ֽ�,ִ��Routin����
	int i=0;
	while(i!=1000)//�ȴ�10��
	{
		if (CheckCharKey==3)
		{
			 HookClear();
			 MyDebug("��ɫ����-%s",TempStr);
			 return false;
		 }
		Sleep(10);
		i++;
	}

	MyDebug("ʮ���ѹ�,ж�ع���,��ɫ������");
	CheckCharKey=0;
	HookClear();
	return true;
}
bool CheckGameLoad()//�����Ϸ�Ƿ��ȡ���,�Ǻͳ�ʱ����false
{
	
	CheckCharKey=0;
	MyDebug("��ʼ�����Ϸ�Ƿ��ȡ���");
	Tempeax=0;
	HookNode* node4 = Hook((void*)0x10001627,1,Routin2,false);//���ڴ��ַ0x0044BE62���ҹ�,�õ�ַ��СΪ1�ֽ�,ִ��Routin����
	int i=0;
	while(i!=1000)//�ȴ�10��
	{
		if (CheckCharKey==4)
		{
			HookClear();
			MyDebug("��Ϸ��ȡ���-%s",TempStr);
			return false;
		}
		Sleep(10);
		i++;
	}

	MyDebug("15���ѹ�,�ٶ���Ϸ�Ѷ�ȡ���");
	HookClear();
	return false;
}


