#include "StdAfx.h"
#include ".\asmbase.h"
#include "AsmBase.h"

typedef int (__stdcall *Fun_Prt)(DWORD A1,DWORD A2);

CString MapTempName="";
int LocalTaskid=0;
Fun_Prt WnCall = (Fun_Prt)0x00899BB0;




int MainFun()
{

	DWORD g_pObjMgr = *(DWORD*)0x00AA0724;

	DWORD GetByType = *(DWORD*)0x00AA0710;

	DWORD p_a1,v17;

	DWORD p_a2;

//	p_a2 = ....;

	if ( g_pObjMgr )
	{
		

		v17 =0x00BDEF68+0x8;

		__asm
		{
			push v17
			mov ecx,g_pObjMgr
			call GetByType
			mov p_a1,eax
		}
	}
	WnCall(p_a1,(DWORD)&p_a2);

}






PmyObj BaseCall::MyObj()
{
	CharObj.myObj = *(DWORD*)Hp_myObj;
	CharObj.myHp = *(DWORD*)(CharObj.myObj + 0x8e0);
	CharObj.myState = *(DWORD*)((*(DWORD*)Hp_myZt) + 0x820C);
	CharObj.myDj = *(DWORD*)(CharObj.myObj + 0x754);
	CharObj.myX = *(DWORD*)(CharObj.myObj + 0x148);
	CharObj.myY = *(DWORD*)(CharObj.myObj + 0x14c);
	CharObj.myZ = *(DWORD*)(CharObj.myObj + 0x150);
	return CharObj;
}
void BaseCall::WanNengCall(DWORD myAddr)
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
void BaseCall::WanNengCall0(DWORD myAddr)
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
void __stdcall Routin(CPU_ST* lpcpu)
{

	CString cs;
	cs.Format("%s",(char*)*(DWORD*)(lpcpu->regEdi+0xc));
	if((cs == "Inst_OpenInstEnter"))
	{
//		FuBenId = *(DWORD*)(lpcpu->regEdi + 0x10);//副本ID
//		IsFuBen = true;
	}
	return;
}
int TaskWj[64]={0};
int TaskWjCount = 0;
bool JiYi = false;



void __stdcall Routin0(CPU_ST* lpcpu)
{
	if (JiYi == false)
	{
		
	}
	else
	{
		for (int i = 0;i < 64; i++)
		{
			if (lpcpu->regEdx == TaskWj[i]) return;
		}
		TaskWj[TaskWjCount] = lpcpu->regEdx;
		TaskWjCount++;
	}
}

void BaseCall::Test()
{
	
	for(int i = 0;i < TaskWjCount; i++)
	{
		//MyDebug("%08X",TaskWj[i]);
		TaskWj[i] = 0;
	}
	TaskWjCount = 0;

	JiYi = true;
	Sleep(1000);
	MyDebug("%08X",TaskWjCount);
	for(int i = 0;i < TaskWjCount; i++)
	{
		MyDebug("%08X",TaskWj[i]);
	}
}
void BaseCall::SetHook()
{
	//0041C729   .  8BC8                              mov ecx,eax
//	0041C72B   .  894424 1C                         mov dword ptr ss:[esp+0x1C],eax
	//			node = Hook((void*)Hp_wnCall,6,Routin,true);  //在0x401000下5 byte JMP XXX钩子，代码先行
	node = Hook((void*)0x0041C729,6,Routin0,true);
}

void BaseCall::UnSetHook()
{
	Unhook(node,false);
}




//遍历地图
void  BaseCall::RootDiTu(DWORD RootExit,DWORD Root,DWORD Mapid)
{
	
	if (Root==*(DWORD*)RootExit)
	{
		return;
	}
	if(Root != RootExit)
	{
		//BagObj[BagXiaBiao] = *(DWORD*)(Root + 0x14);
		//BagXiaBiao++;

		DWORD dxx = *(DWORD*)(Root + 0x14);
		DWORD idd = *(DWORD*)(dxx);
		DWORD idd1 = *(DWORD*)(dxx + 0x4);
		DWORD idd2 = *(DWORD*)(dxx + 0x8);
		

		CString GameObjName;
		GameObjName = _TEXT((LPCWSTR)(dxx+0x38));
		if (idd==Mapid)
		{
			MapTempName=GameObjName;
			
		}
		//if(idd1 != 1 && idd1 != 3 && idd1 != 5)
		//MyDebug("id:%08X--idd:%08X--idd2%08X--名字:%s",idd,idd1,idd2,GameObjName);
		saveini("副本.ini","地图",GameObjName,"0");

	}

	DWORD LeftRoot = *(DWORD*) Root;
	DWORD RightRoot = *(DWORD*) (Root +0x4);
	RootDiTu(RootExit,LeftRoot,Mapid);
	RootDiTu(RootExit,RightRoot,Mapid);
	return ;
}



void BaseCall::hhh()
{
	BaseType m_Bt;
	m_Bt.zeor();
	m_Bt.D1 = 0x00ACF7B8;
	m_Bt.D2 = 0xB7677A5D;
	m_Bt.D3 = 0x8AE0DA74;
	m_Bt.D4 ="MergeTrack";
	m_Bt.D5 = 0x65;
	m_Bt.D6 = 0x55;
	m_Bt.D7 = 0x55;
	m_Bt.D8 = 0x0;
	DWORD PackAddr=(DWORD)&m_Bt;
WanNengCall(PackAddr);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


CString FindWay::GetNowMapName()
{
	DWORD  XXX = *(DWORD*)Hp_SouZaiMap;
	CString NNN;
	NNN = _TEXT((LPCWSTR)(XXX+0x38));
	return NNN;
}
int FindWay::GetNowMapId()
{
	return *(DWORD*)(*(DWORD*)(Hp_SouZaiMap));
}

bool FindWay::IsReach()
{
	PmyObj Temp = MyObj();
	if (fabsf((*(float*)(Temp.myObj+0x148)) - (*(float*)(&XX)))<200 && 
		fabsf((*(float*)(Temp.myObj+0x14c)) - (*(float*)(&YY)))<200 && 
		fabsf((*(float*)(Temp.myObj+0x150)) - (*(float*)(&ZZ)))<200)
	{
		return true;
	}
	return false;
}


void FindWay::Nxunlu(DWORD X,DWORD Y,DWORD Z)
{
	BYTE buf[512];ZeroMemory(buf,512);
	DWORD PackAddr=(DWORD)&buf;

	*(DWORD*)(PackAddr)	= 0x1943BE4E;
	*(DWORD*)(PackAddr+0x4) = 0x26;
	*(DWORD*)(PackAddr+0x8) = X;
	*(DWORD*)(PackAddr+0xc) = Y;
	*(DWORD*)(PackAddr+0x10) = Z;//0x003062BF;
	*(DWORD*)(PackAddr+0x14) = X;
	*(DWORD*)(PackAddr+0x18) = Y;//0x003062BC;
	*(DWORD*)(PackAddr+0x1c) = Z;
	*(DWORD*)(PackAddr+0x20) = 0;
	*(DWORD*)(PackAddr+0x24) = 0x0;
	WanNengCall0(PackAddr);
}


//0012F5D4  069926AB



void FindWay::BackToCity()
{
	BYTE buf[32];ZeroMemory(buf,32);
	DWORD PackAddr=(DWORD)&buf;
	*(DWORD*)(PackAddr)	= 0xB31DDD48;
	*(DWORD*)(PackAddr+0x4) = 0x20;
	*(DWORD*)(PackAddr+0x8) = -1;
	*(DWORD*)(PackAddr+0xc) = -1;
	*(DWORD*)(PackAddr+0x10) = 0x069926AB;//0x003062BF;
	*(DWORD*)(PackAddr+0x14) = 0;
	*(DWORD*)(PackAddr+0x18) = 0;//0x003062BC;
	*(DWORD*)(PackAddr+0x1c) = 0;
	
	WanNengCall0(PackAddr);
	Sleep(10000);
};


//寻路（专属任务寻路对象）
void FindWay::FindToXYZ(DWORD MapId,DWORD X,DWORD Y,DWORD Z)
{
	XX = X;YY=Y;ZZ = Z;
	MoveObj(X,Y,Z);
	
/*
	MyDebug("%08X,%08X,%08X,%08X",MapId,X,Y,Z);
		
		BaseType m_Bt;
		m_Bt.zeor();
		m_Bt.D1 = myMove;
		m_Bt.D2 = 0xEC82B0AD;
		m_Bt.D3 = 0xEC82B0AD;
		m_Bt.D4 ="";
		m_Bt.D5 = MapId;
		m_Bt.D6 = X;
		m_Bt.D7 = Y;
		m_Bt.D8 = Z;
		DWORD PackAddr=(DWORD)&m_Bt;* /
	

	//MyDebug("%08X,%08X,%08X,%s,%08X,%08X,%08X,%08X",*(DWORD*)PackAddr,*(DWORD*)(PackAddr+0x4),*(DWORD*)(PackAddr+0x8),(char*)(PackAddr+0xc),*(DWORD*)(PackAddr+0x10),*(DWORD*)(PackAddr+0x14),*(DWORD*)(PackAddr+0x18),*(DWORD*)(PackAddr+0x1c));

	WanNengCall(PackAddr);*/

	if (*(DWORD*)(*(DWORD*)Hp_SouZaiMap) == MapId)
	{

		Nxunlu();
	}
}

void FindWay::FindToNpc(CString NPCName)
{
	MyDebug("%s",NPCName);
	UNIT temp = GetUnitByName(NPCName);
	MyDebug("%08X",temp.Base);
	RootDiTu((DWORD)(Hp_IterateBase + 0x1e8),(*(DWORD*)(Hp_IterateBase+0x200)),temp.DiTu);
	MyDebug("地图ID-%08X-地图名-%s",temp.DiTu,MapTempName);
	FindWayMap(MapTempName);
	MoveObj(temp.X,temp.Y,temp.Z);
	Sleep(5000);
	Nxunlu();
	
	//FindToXYZ(temp.DiTu,temp.X,temp.Y,temp.Z);
	//FindToXXX(temp.DiTu,temp.X,temp.Y,temp.Z);
	if (IsFuBen=true)
	{
		JinFuBen(FuBenId,0);
	}
	if ((*(DWORD*)(Hp_CFuBenIndex + 0x474)) != -1)
	{
		ChuFuBen((*(DWORD*)(Hp_CFuBenIndex + 0x474)));
	}
}

//根据任务id寻路（任务id，交还是接任务，接是true ,交是false）
void FindWay::FindToTaskID(int TaskId,bool Finshed)
{
	DWORD TaskPtr=0;
	TaskPtr=QuestTarget(TaskId,Finshed);
	FindToXYZ(*(DWORD*)(TaskPtr+0x8),*(DWORD*)(TaskPtr+0xC),*(DWORD*)(TaskPtr+0x10),*(DWORD*)(TaskPtr+0x14));
}

void FindWay::FindByTaskName(CString TaskName)
{
	
	RootQuest(Hp_IterateBase+0x14d0,(*(DWORD*)(Hp_IterateBase+0x14e8))/*,TaskName*/);
	FindToTaskID(LocalTaskid,true);
}



void FindWay::Nxunlu()
{
	BYTE buf[512];ZeroMemory(buf,512);
	DWORD PackAddr=(DWORD)&buf;

	*(DWORD*)(PackAddr)	=	0x1943BE4E;
	*(DWORD*)(PackAddr+0x4) =   0x26;
	*(DWORD*)(PackAddr+0x8) =   MapStruct.X;
	*(DWORD*)(PackAddr+0xc) = MapStruct.Y;
	*(DWORD*)(PackAddr+0x10) = MapStruct.Z;//0x003062BF;
	*(DWORD*)(PackAddr+0x14) = MapStruct.X;
	*(DWORD*)(PackAddr+0x18) = MapStruct.Y;//0x003062BC;
	*(DWORD*)(PackAddr+0x1c) = MapStruct.Z;
	*(DWORD*)(PackAddr+0x20) = 0;
	*(DWORD*)(PackAddr+0x24) = 0x0;
	WanNengCall0(PackAddr);

}

void FindWay::MoveObj(CString AnyName)
{
	MapStruct = GetUnitByName(AnyName,GetNowMapId());
	MyDebug("地图ID-%08X,地图X坐标%08X,地图Y坐标%08X,地图Z坐标%08X",GetNowMapId(),MapStruct.X,MapStruct.Y,MapStruct.Z);
	DWORD myObj = *(DWORD*)Hp_myObj;
	if (myObj == 0) return;
	*(DWORD*)((myObj + 0x148)) = MapStruct.X;
	*(DWORD*)((myObj + 0x14c)) = MapStruct.Y;
	*(DWORD*)((myObj + 0x150)) = MapStruct.Z;
	Sleep(1000);
	Nxunlu();
	Sleep(3000);
	return;
}

void FindWay::MoveObj(int X,int Y, int Z)
{
	DWORD myObj = *(DWORD*)Hp_myObj;
	*(DWORD*)((myObj + 0x148)) = X;
	*(DWORD*)((myObj + 0x14c)) = Y;
	*(DWORD*)((myObj + 0x150)) = Z;
}

void FindWay::GoToMap(CString MapName)
{
	CString MyName;

	if(GetNowMapName() == "西域" && MapName == "白城")
	{
		MoveObj(0x46CD44B2,0x45AAE015,0x4733EA4E);
		return;
	}

	if(GetNowMapName() == "白城" && MapName == "西域")
	{
		
		MoveObj("去往西域");
		
		return;
	}

	MyName = "去"+MapName;
	MyDebug("合并后的去地图-%s",MyName);
	MoveObj(MyName);
	return;

}

void FindWay::FindWayMap(CString MapName)//瞬移到地图名
{	

	while(MapName != GetNowMapName())
	{
		CString MMM = getini("地图.ini",MapName,GetNowMapName());
		if(MMM == "") return;
		GoToMap(MMM);
		MyDebug("要去的地图名-%s,目标地图名%s",MapName,MMM);
		//Sleep(5000);
	}

}

void FindWay::JinFuBen(int myFuBenId,int FuBenType)
{
	BYTE buf[512];ZeroMemory(buf,512);
	DWORD PackAddr=(DWORD)&buf;

	*(DWORD*)(PackAddr)	=	0x795305C0;
	*(DWORD*)(PackAddr+0x4) =   0x20;
	*(DWORD*)(PackAddr+0x8) =   -1;
	*(DWORD*)(PackAddr+0xc) = -1;
	*(DWORD*)(PackAddr+0x10) = -1;//0x003062BF;
	*(DWORD*)(PackAddr+0x14) = myFuBenId;
	*(DWORD*)(PackAddr+0x18) = -1;//0x003062BC;
	*(DWORD*)(PackAddr+0x1c) = FuBenType;
	WanNengCall0(PackAddr);

}

//出入副本（副本InDex）
void FindWay::ChuFuBen(int myFuBenId)
{
	BYTE buf[512];ZeroMemory(buf,512);
	DWORD PackAddr=(DWORD)&buf;

	*(DWORD*)(PackAddr)	=	0x0ae8cf34;
	*(DWORD*)(PackAddr+0x4) =   0x0c;
	*(DWORD*)(PackAddr+0x8) =   myFuBenId;

	WanNengCall0(PackAddr);

}

DWORD FindWay::QuestTarget(DWORD myId,bool IsJ)
{
	//[[00BC5C50+0x40]+0x800+0x4];
	//[[Hp_QuestTargt+0x40]+0x938+0x4];

	DWORD RootZhi = *(DWORD*)(*(DWORD*)(Hp_QuestTargt+0x40)+0x938+0x4);
	DWORD IsRooted = 0;

	if(IsJ == true)
	{
		IsRooted = *(DWORD*)(*(DWORD*)(Hp_QuestTargt+0x40)+0x800+0x4);
	}
	else
	{
		IsRooted = *(DWORD*)(*(DWORD*)(Hp_QuestTargt+0x40)+0x830+0x4);
	}
	__asm
	{
		mov eax,IsRooted
qq2:	mov edx,dword ptr ds:[eax+0x10]
		cmp edx,myId
			jb qq0
			mov edi,eax
			mov eax,dword ptr ds:[eax+0x8]
			jmp qq1
qq0:	mov eax,dword ptr ds:[eax+0xC]
qq1:	test eax,eax
			jnz qq2
			mov IsRooted,edi
	}
	IsRooted = *(DWORD*)(IsRooted + 0x14);


	__asm
	{
		mov eax,RootZhi
qq12:	mov edx,dword ptr ds:[eax+0x10]
		cmp edx,IsRooted
			jb qq10
			mov edi,eax
			mov eax,dword ptr ds:[eax+0x8]
			jmp qq11
qq10:	mov eax,dword ptr ds:[eax+0xC]
qq11:	test eax,eax
			jnz qq12
			mov IsRooted,edi
	}
	return *(DWORD*)(IsRooted + 0x14);
}

//遍历地图对象
int FindWay::ListUnit()
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
DWORD  FindWay::RootNpc(DWORD RootExit,DWORD Root)
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
		TempUnitList[TempUnitCount].Name	=	_TEXT((LPCWSTR)(Addr+0x38));
		TempUnitList[TempUnitCount].DiTu	=	*(DWORD*)(Addr + 0x4);
		TempUnitList[TempUnitCount].X		=	*(DWORD*)(Addr + 0x14);
		TempUnitList[TempUnitCount].Y		=	*(DWORD*)(Addr + 0x18);
		TempUnitList[TempUnitCount].Z		=	*(DWORD*)(Addr + 0x1C);
		TempUnitCount++;

	}


	DWORD LeftRoot = *(DWORD*) Root;
	DWORD RightRoot = *(DWORD*) (Root +0x4);

	RootNpc(RootExit,LeftRoot);
	RootNpc(RootExit,RightRoot);
	return 1;
}

//返回地图人物对象（名字,id
UNIT FindWay::GetUnitByName(CString UintName,int MapId)
{

	UNIT tmp;
	tmp.zero();
	for (int i=0;i!=TempUnitCount;++i)
	{
		if(TempUnitList[i].Name == UintName&& TempUnitList[i].DiTu == MapId)
		{
			return TempUnitList[i];
		}
	}
	return tmp;
}

UNIT FindWay::GetUnitByName(CString UintName)
{

	TempUnitCount = 0;
//saveini("设置.ini","配置","秒杀","0")
	RootNpc((DWORD)(Hp_IterateBase+0x20c),(*(DWORD*)(Hp_IterateBase+0x224)));
	UNIT tmp;
	tmp.zero();
	for (int i=0;i!=TempUnitCount;++i)
	{

		//			MyDebug("%s,%s",UintName,TempUnitList[i].Name);
		if(TempUnitList[i].Name == UintName)
		{
			return TempUnitList[i];
		}
	}

	return tmp;
}


//遍历任务
int FindWay::RootQuest(DWORD RootExit,DWORD Root/*,CString TaskName*/)
{
	//RootQuest(Hp_IterateBase+0x14d0,(*(DWORD*)(Hp_IterateBase+0x14e8)));
	TaskAAA tt;
	if (Root==*(DWORD*)RootExit)
	{
		return 0;
	}
	if(Root != RootExit)
	{
		DWORD PickObj = *(DWORD*)(Root + 0x14);

		TaskTemp.Taskid = *(DWORD*)(PickObj);

		TaskTemp.TaskName = TEXT((LPCWSTR)(PickObj + 0x108));

		//if(TaskName==TaskTemp.TaskName)
		//{
			MyDebug("Name:%s-ID:%08X",TaskTemp.TaskName,TaskTemp.Taskid);
		//	LocalTaskid=TaskTemp.Taskid;
		//	return TaskTemp.Taskid;
		//}

	}

	DWORD LeftRoot = *(DWORD*) Root;
	DWORD RightRoot = *(DWORD*) (Root +0x4);
	RootQuest(RootExit,LeftRoot/*,TaskName*/);
	RootQuest(RootExit,RightRoot/*,TaskName*/);
	//return 1;
}

void FindWay::RootAllObject()
{
	//RootQuest(Hp_IterateBase+0x14d0,(*(DWORD*)(Hp_IterateBase+0x14e8)));
	//RootNpc(Hp_IterateBase+0x20c,(*(DWORD*)(Hp_IterateBase+0x224)));
	//RootPick(Hp_BianLiBeiBao,(*(DWORD*)(Hp_BianLiBeiBao+0x20)));
	RootPet( ((*(DWORD*)0xc21034)+0x3c),((*(DWORD*)(*(DWORD*)0xc21034)+0x44)) );
}


/////////////////////////////
//遍历任务
int FindWay::RootID(DWORD Root)
{
	//RootQuest(Hp_IterateBase+14d0,(*(DWORD*)(Hp_IterateBase+0x14e8)));
	
	if (Root == 0)
	{
		return 0;
	}
	if(Root != 0)
	{
		DWORD PickObj = *(DWORD*)(Root + 0x14);
		MyDebug("ID:%08X",PickObj);
	}

	DWORD LeftRoot = *(DWORD*) (Root+0x8);
	DWORD RightRoot = *(DWORD*) (Root +0xc);
	RootID(LeftRoot);
	RootID(RightRoot);
	return 1;
}




//遍历背包
DWORD  BaseCall::RootPick(DWORD RootExit,DWORD Root)
{
	//gg.RootPick(0x00BAB0D0,(*(DWORD*)(0x00BAB0D0+0x20)));;
	if (Root==*(DWORD*)RootExit)
	{
		return 0;
	}
	if(Root != RootExit)
	{
		DWORD PickObj = *(DWORD*)(Root + 0x18);
		DWORD PickName = *(DWORD*)(PickObj + 0x30);
		DWORD PickNumber = *(DWORD*)(PickObj + 0x26);
		CString Picknn;
		Picknn.Format("%08X",PickNumber);
		Picknn = Picknn.Right(4);
		DWORD PickId = *(DWORD*)(PickObj + 0x4);
		CString GameObjName,PickType;
		GameObjName = TEXT((LPCWSTR)(PickName+0x1c0));
		PickType =TEXT((LPCWSTR)(PickName+0x180));
		MyDebug("名字：%s------ID:%08X--------类型：%s-------数量：%s",GameObjName,PickId,PickType,Picknn);
	}

	DWORD LeftRoot = *(DWORD*) Root;
	DWORD RightRoot = *(DWORD*) (Root +0x4);
	RootPick(RootExit,LeftRoot);
	RootPick(RootExit,RightRoot);
	return 1;
}

//[0xC21034]+44
DWORD  BaseCall::RootPet(DWORD RootExit,DWORD Root)
{
	//RootPet( ((*(DWORD*)0xc21034)+0x3c),((*(DWORD*)(*(DWORD*)0xc21034)+0x44)) )

	if (Root==*(DWORD*)RootExit || Root == 0)
	{
		return 0;
	}

	if(Root != RootExit)
	{
		DWORD ID = *(DWORD*)(Root+0x10);
		MyDebug("%08X",ID);
	}


	DWORD LeftRoot = *(DWORD*) (Root+0x4);
	DWORD RightRoot = *(DWORD*) (Root +0x8);
	RootPet(RootExit,LeftRoot);
	RootPet(RootExit,RightRoot);
	return 1;
}

DWORD Tp = 0;

void BaseCall::TTTTT()
{
	DWORD W1 = 0;

	Tp = Hp_QuestTargt + 0xa8;
	W1 = *(DWORD*)Tp;
	RootTaskYJ(W1);

	Tp = Hp_QuestTargt + 0xb0;
	W1 = *(DWORD*)Tp;
	RootTaskYJ(W1);

	Tp = Hp_QuestTargt + 0xb8;
	W1 = *(DWORD*)Tp;
	RootTaskYJ(W1);

	Tp = Hp_QuestTargt + 0xc0;
	W1 = *(DWORD*)Tp;
	RootTaskYJ(W1);
}


DWORD BaseCall::RootTaskYJ(DWORD Root)
{
	
	if (Root == Tp) return 0;

	DWORD DX = *(DWORD*)(Root + 0x8);
	DWORD Dd = *(DWORD*)(DX + 0x4);
	CString NN;
	NN = _TEXT((LPCWSTR)(Dd + 0x108));
	

	MyDebug("%08X,%26s,%08X,%08X,%08X,%08X,%08X,%08X,%08X,%08X,%08X,%08X,%08X,%08X,%08X,",
			*(DWORD*)DX,NN,*(DWORD*)(DX+0xc),*(DWORD*)(DX+0x10),*(DWORD*)(DX+0x14),*(DWORD*)(DX+0x18),
			*(DWORD*)(DX+0x1c),*(DWORD*)(DX+0x20),*(DWORD*)(DX+0x24),*(DWORD*)(DX+0x28),*(DWORD*)(DX+0x2c),
			*(DWORD*)(DX+0x30),*(DWORD*)(DX+0x34),*(DWORD*)(DX+0x38),*(DWORD*)(DX+0x3c));
	
	
	RootTaskYJ(*(DWORD*)Root);

	return 0; 
}



/*

DWORD BaseCall::bl(DWORD Addrx)
{
	DWORD V1;
	DWORD V2;

	V1 = *(DWORD*)(Addrx + 0xc);
	if (0 != V1)
	{
		V2 = *(DWORD*)(V1 + 0x8);

		if (0 == V2)
		{
			return V1;
		}
		else
		{
			do
			{
				V1 = V2;
				V2 = *(DWORD*)(V1 + 0x8);

			}while(V2 != 0);

			return V1;
		}
	}
	else
	{
		V1 = *(DWORD*)(Addrx + 0x4);
		V2 = *(DWORD*)(V1 + 0xC);
		
		if (0 == (V1 - V2))
		{
			do
			{
				V2 = V1;
				V1 = *(DWORD*)(V1 + 0x4);

			}while(V2 == *(DWORD*)(V1 + 0xc));
		}
		if (V1 == V2)
		{
			V1 = V2;
		}
		return V1;
	}
}


void BaseCall::bll(DWORD xx)
{
	DWORD de = bl(xx);
	MyDebug("%08X",de);
}*/



DWORD xx[5];
DWORD v1 = *(DWORD*)Hp_Pet + 0x3c;
DWORD PetCount = *(DWORD*)(*(DWORD*)Hp_Pet + 0x4c);

void BaseCall::Bl()
{
	DWORD df;
	xx[0] = *(DWORD*)(v1 + 0x4);
	xx[1] = *(DWORD*)(v1 + 0x8);
	xx[2] = *(DWORD*)(v1 + 0xc);
	if (PetCount == 4)
	{
		for(int i = 0; i < 3; i++)
		{
			DWORD dddd =  Bll(xx[i]);
			if (0 != dddd)
			{
				xx[3] = dddd;
			}
			else
			{
				xx[3] = 1;
			}
		}
	}

	if (PetCount == 5)
	{
		for(int i = 0; i < 3; i++)
		{
			DWORD dddd =  Bll(xx[i]);
			if (0 != dddd)
			{
				xx[3] = dddd;
			}
			else
			{
				xx[3] = 1;
			}
		}

		for(int i = 0; i < 4; i++)
		{
			DWORD dddd =  Bll(xx[i]);
			if (0 != dddd)
			{
				xx[4] = dddd;
			}
			else
			{
				xx[4] = 1;
			}
		}
		if (xx[4] == 1)
		{
			DWORD dddd =  Bll(xx[3]);
			if (0 != dddd)
			{
				xx[4] = dddd;
			}
			else
			{
				xx[4] = 0;
			}
		}
		

	}
	
	for (int i = 0; i < 5; i++)
	{
		MyDebug("%08X",xx[i]);
	}
}
DWORD BaseCall::Bll(DWORD dx)
{
	DWORD hh = *(DWORD*)(dx + 0x4);
	if (hh == xx[0] || hh == 0 || hh == xx[1] || hh == xx[2] || hh == v1 || hh == xx[3]) {} else{return hh;}
	hh = *(DWORD*)(dx + 0x8);
	if (hh == xx[0] || hh == 0 || hh == xx[1] || hh == xx[2] || hh == v1 || hh == xx[3]) {} else{return hh;}
	hh = *(DWORD*)(dx + 0xc);
	if (hh == xx[0] || hh == 0 || hh == xx[1] || hh == xx[2] || hh == v1 || hh == xx[3]) {} else{return hh;}
	return 0;
	
}