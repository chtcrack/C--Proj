#pragma once
#include "PSkinBase.h"

DWORD GetEsi();

DWORD GetCharNameeax();
 void UnHookGouzi();
 bool GetLoginStatus();
 bool CheckCreatStatus();//检查10秒是否创建角色成功,如果成功返回true,否则返回false即角色重名
 bool CheckGameLoad();//检查游戏是否读取完成,是和超时返回true
class BaseCall
{
	public:

		typedef struct tagBaseType
		{
			DWORD D1;
			DWORD D2;
			DWORD D3;
			char* D4;
			DWORD D5;
			DWORD D6;
			DWORD D7;
			DWORD D8;
		}BaseType;


		void WanNengCall(DWORD myAddr)
		{
			DWORD myCall = Hp_wnCall;
			DWORD myCall0 = *(DWORD*)Hp_wnCall0;
			DWORD myCall1 = *(DWORD*)Hp_wnCall1;
			DWORD myEdx = *(DWORD*)Hp_wnEdx;

			__asm
			{
				mov ecx,Hp_wnEcx
				call myCall0
				push eax
				mov eax,myEdx
				mov ecx,dword ptr ds:[eax]
				call myCall1
				mov edx,eax
				mov edi,myAddr
				call myCall
			}
			return;
		}


		void WanNengCall0(DWORD myAddr)
		{

			DWORD myCall = Hp_wnCallq;
			DWORD myCall0 = *(DWORD*)Hp_wnCall0;
			DWORD myCall1 = *(DWORD*)Hp_wnCall1;
			DWORD myEdx = *(DWORD*)Hp_wnEdx;
			__asm
			{
				mov ecx,Hp_wnEcxq
				call myCall0
				mov edx,myEdx
				mov ecx,dword ptr ds:[edx]
				push eax
				call myCall1
				mov ecx,myAddr
				push ecx
				push eax
				call myCall
			}
		}

};





class FindWay:BaseCall
{
	public:
		
		//寻路（专属任务寻路对象）
		void FindToXYZ(int MapId,int X,int Y,int Z)
		{
			BaseType m_Bt;
			m_Bt.D1 = myMove;
			m_Bt.D2 = 0xEC82B0AD;
			m_Bt.D3 = 0xEC82B0AD;
			m_Bt.D4 ="MapMove";
			m_Bt.D5 = MapId;
			m_Bt.D6 = X;
			m_Bt.D7 = Y;
			m_Bt.D8 = Z;
			DWORD PackAddr=(DWORD)&m_Bt;
			WanNengCall(PackAddr);
		}
		

		void FindToNpc(CString NPCName)
		{
			UNIT temp = GetUnitByName(NPCName);
			FindToXYZ(temp.DiTu,temp.X,temp.Y,temp.Z);
		}


		void FindToTaskID(int TaskId)
		{

		}


protected:

	
	typedef struct tagUnit
	{
		DWORD	Base;
		int		DiTu;
		int		X;
		int		Y;
		int 	Z;
		CString Name;
		int		UnitId;
		char	Namebuf[64];

		void zero()
		{
			Base=NULL;
			Name="";
			memset(Namebuf,0,64);
			DiTu = 0;
			X=0;
			Y=0;
			Z=0;
		};

	}UNIT;


protected:
	int TempUnitCount;
	UNIT TempUnitList[2048];



protected:
	//遍历地图对象
	int ListUnit()
	{

		TempUnitCount =0;

		RootNpc(Hp_IterateBase+0x20c,(*(DWORD*)(Hp_IterateBase+0x224)));

		for (int i=0;i!=TempUnitCount;++i)
		{
			DWORD xxx = *(DWORD*)(TempUnitList[i].Base + 0x4);
			DWORD xx = *(DWORD*)(TempUnitList[i].Base + 0x8);
		}

		return TempUnitCount;

	}



	//遍历地图对象
	DWORD  RootNpc(DWORD RootExit,DWORD Root)
	{
		//RootNpc(0x00B3A4B8+0x20c,(*(DWORD*)(0x00B3A4B8+0x224)));

		if (Root==*(DWORD*)RootExit)
		{
			return 0;
		}

		if(Root != RootExit)
		{

			DWORD Addr = *(DWORD*)(Root + 0x14);
			TempUnitList[TempUnitCount].Base	=	Addr;
			TempUnitList[TempUnitCount].UnitId	=	*(DWORD*)(Addr);
			TempUnitList[TempUnitCount].Name	=	TEXT((LPCWSTR)(Addr+0x38));
			TempUnitList[TempUnitCount].DiTu	=	*(int*)(Addr + 0x4);
			TempUnitList[TempUnitCount].X		=	*(int*)(Addr + 0x14);
			TempUnitList[TempUnitCount].Y		=	*(int*)(Addr + 0x18);
			TempUnitList[TempUnitCount].Z		=	*(int*)(Addr + 0x1C);
			TempUnitCount++;

		}


		DWORD LeftRoot = *(DWORD*) Root;
		DWORD RightRoot = *(DWORD*) (Root +0x4);

		RootNpc(RootExit,LeftRoot);
		RootNpc(RootExit,RightRoot);
		return 1;
	}



	//返回地图人物对象（名字）
	UNIT GetUnitByName(CString UintName)
	{
		UNIT tmp;
		tmp.zero();
		for (int i=0;i!=TempUnitCount;++i)
		{

			MyDebug("%s,%s",UintName,TempUnitList[i].Name);
			if(TempUnitList[i].Name == UintName)
			{
				return TempUnitList[i];
			}
		}
		return tmp;
	}
};

