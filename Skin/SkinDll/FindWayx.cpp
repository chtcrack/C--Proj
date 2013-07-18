#include "StdAfx.h"
#include ".\findwayx.h"
#include "AsmBase.h"

FindWayx::FindWayx(void)
{
}

FindWayx::~FindWayx(void)
{
}

UNIT dd;



int SouZaiDiTuY()
{
	return *(DWORD*)Hp_SouZaiMap;
}


void MoveObj(CString xxx,int xx)
{
	//dd = pcX.ListUnit0(xxx,xx);
	DWORD myObj = *(DWORD*)Hp_myObj;
	if (myObj == 0) return;
	*(DWORD*)((myObj + 0x148)) = dd.X;
	*(DWORD*)((myObj + 0x14c)) = dd.Y;
	*(DWORD*)((myObj + 0x150)) = dd.Z;
	Sleep(1000);
	return;
}

void MoveObj(int X,int Y, int Z)
{
	DWORD myObj = *(DWORD*)Hp_myObj;
	*(DWORD*)((myObj + 0x148)) = X;
	*(DWORD*)((myObj + 0x14c)) = Y;
	*(DWORD*)((myObj + 0x150)) = Z;
}

void Nxunlu()
{
	BYTE buf[512];ZeroMemory(buf,512);
	DWORD PackAddr=(DWORD)&buf;

	*(DWORD*)(PackAddr)	=	0x1943BE4E;
	*(DWORD*)(PackAddr+0x4) =   0x26;
	*(DWORD*)(PackAddr+0x8) =   dd.X;
	*(DWORD*)(PackAddr+0xc) = dd.Y;
	*(DWORD*)(PackAddr+0x10) = dd.Z;//0x003062BF;
	*(DWORD*)(PackAddr+0x14) = dd.X;
	*(DWORD*)(PackAddr+0x18) = dd.Y;//0x003062BC;
	*(DWORD*)(PackAddr+0x1c) = dd.Z;
	*(DWORD*)(PackAddr+0x20) = 0;
	*(DWORD*)(PackAddr+0x24) = 0x0;
	//pcX.WanNengCall0(PackAddr);

}

void Tacking0(int DiTu)
{
	for(;*(DWORD*)(SouZaiDiTuY()) != DiTu;)
	{
		Tacking(DiTu);
		Sleep(5000);
	}
}

void Tacking(int DiTu)
{

}





