#include "StdAfx.h"
#include ".\pskinapi.h"


typedef struct tagDRIIVE
{
	CString			FunName;//������
	CString			(__stdcall *PSpkin)(CString StrA, CString strB,DWORD Any);
}DRIIVE;


//����
CString __stdcall myFun0(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun1(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun2(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun3(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun4(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun5(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun6(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun7(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun8(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun9(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun10(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun11(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun12(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun13(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun14(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun15(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun16(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun17(CString StrA = "", CString strB="",DWORD Any = NULL);
CString __stdcall myFun18(CString StrA = "", CString strB="",DWORD Any = NULL);
//����������
DRIIVE m_FunList[]=
{
	{"������",			myFun0},
	{"������",			myFun1},
	{"ʹ����Ʒ",		myFun2},
	{"��������",		myFun3},
	{"����",			myFun4},
	{"�����ڹ�",		myFun5},
	{"װ�����",		myFun6},
	{"����",			myFun7},
	{"ɨ������",		myFun8},
	{"���븱��",		myFun9},
	{"װ��",			myFun10},
	{"ҡǮ��",			myFun11},
	{"װ������",		myFun12},
	{"�����֮��",		myFun13},
	{"�س�",			myFun14},
	{"����¼",			myFun15},
	{"��Ƕ",			myFun16},
	{"���",			myFun17},
	{"ϴ��",			myFun18}
};


//����

CString CallFun(CString FunName,CString StrA,CString StrB,DWORD Any)
{
	int DriverSize = sizeof(m_FunList) / sizeof(DRIIVE);

	CString RetStr = "�Ҳ�������";

	for (int i = 0; i < DriverSize; i++)
	{
		if (m_FunList[i].FunName == FunName)
		{
			RetStr = m_FunList[i].PSpkin(StrA,StrB,Any);
		}
	}
	return RetStr;
}


CString __stdcall myFun0( CString StrA, CString strB,DWORD Any)
{
 return "";
}
CString __stdcall myFun1(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun2(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun3(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun4(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun5(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun6(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun7(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun8(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun9(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun10(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun11(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun12(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun13(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun14(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun15(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun16(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun17(CString StrA, CString strB,DWORD Any)
{
	return "";
}
CString __stdcall myFun18(CString StrA, CString strB,DWORD Any)
{
	return "";
}



