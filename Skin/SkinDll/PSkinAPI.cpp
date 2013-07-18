#include "StdAfx.h"
#include ".\pskinapi.h"


typedef struct tagDRIIVE
{
	CString			FunName;//函数名
	CString			(__stdcall *PSpkin)(CString StrA, CString strB,DWORD Any);
}DRIIVE;


//声明
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
//函数驱动表
DRIIVE m_FunList[]=
{
	{"接任务",			myFun0},
	{"交任务",			myFun1},
	{"使用物品",		myFun2},
	{"升级技能",		myFun3},
	{"打星",			myFun4},
	{"开启内挂",		myFun5},
	{"装备面具",		myFun6},
	{"购买",			myFun7},
	{"扫荡副本",		myFun8},
	{"进入副本",		myFun9},
	{"装备",			myFun10},
	{"摇钱树",			myFun11},
	{"装备传承",		myFun12},
	{"进入惑之塔",		myFun13},
	{"回城",			myFun14},
	{"搜神录",			myFun15},
	{"镶嵌",			myFun16},
	{"打孔",			myFun17},
	{"洗边",			myFun18}
};


//解析

CString CallFun(CString FunName,CString StrA,CString StrB,DWORD Any)
{
	int DriverSize = sizeof(m_FunList) / sizeof(DRIIVE);

	CString RetStr = "找不到调用";

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



