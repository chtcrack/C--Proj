#pragma once
#include "PSkinBase.h"
#include "Hook.h"
#include "ReadWriteIni.h"
typedef struct MyOb
{
	DWORD myObj;//����
	DWORD myX;//X���� + 148
	DWORD myY;
	DWORD myZ;
	DWORD myState;//״̬���ߣ�ͣ����֣�
	DWORD myHp;//+8e0Ѫֵ
	DWORD myDj;//+754�ȼ�
}PmyObj;
typedef struct MapObject
{
CString MapName;
DWORD MapId;
}Mapo;

extern CString MapTempName;
extern int LocalTaskid;

class BaseCall
{
public:
	Mapo MapObjectTemp[256];
	///////////////////////
	HookNode* node;

	//////////////////////
	int FuBenId;
	bool IsFuBen;
	
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
		void  zeor()
		{
			D1 = 0;
			D2 = 0;
			D3 = 0;
			D4 = "";
			D5 = 0;
			D6 = 0;
			D7 = 0;
			D8 = 0;
		}
	}BaseType;
	//����
	PmyObj MyObj();
	PmyObj CharObj;

void hhh();
	void dd5();
		DWORD ddd(DWORD qq);
	DWORD Bll(DWORD dx);
		void Bl();
	DWORD RootTaskYJ(DWORD Root);
		void  TTTTT();

DWORD  RootPet(DWORD RootExit,DWORD Root);
DWORD  RootPick(DWORD RootExit,DWORD Root);
void Test();



	void WanNengCall(DWORD myAddr);

	void WanNengCall0(DWORD myAddr);

	
	/*
	if((cs == "CloseMap"))
	{
	GuoTu = true;
	}
	if((cs == "MapLoadComplete"))
	{
	GuoTu = false;
	}
	if((cs == "PlayerAddItem"))
	{
	IsSouSL = true;
	}
	*/
	void SetHook();	

	void UnSetHook();	
		void  RootDiTu(DWORD RootExit,DWORD Root,DWORD Mapid);
private:


};




typedef struct tagUnit
{
	DWORD		Base;
	DWORD		DiTu;
	DWORD		X;
	DWORD		Y;
	DWORD		Z;
	CString Name;
	DWORD		UnitId;
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
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
class FindWay:public BaseCall
{
public:
	DWORD XX,YY,ZZ;
	

int RootID(DWORD Root);

	UNIT MapStruct;


void BackToCity();


DWORD  RootNpc(DWORD RootExit,DWORD Root);
	CString GetNowMapName();

	int GetNowMapId();

	bool IsReach();



	void Nxunlu(DWORD X,DWORD Y,DWORD Z);


	//Ѱ·��ר������Ѱ·����
	void FindToXYZ(DWORD MapId,DWORD X,DWORD Y,DWORD Z);


	void FindToNpc(CString NPCName);


	//��������idѰ·������id�������ǽ����񣬽���true ,����false��
	void FindToTaskID(int TaskId,bool Finshed);

	void FindByTaskName(CString TaskName);



	void Nxunlu();


	void MoveObj(CString AnyName);


	void MoveObj(int X,int Y, int Z);


	void GoToMap(CString MapName);


	void FindWayMap(CString MapName);
void JinFuBen(int myFuBenId,int FuBenType);
protected:

	
	

	//���븱��������InDex��
	void ChuFuBen(int myFuBenId);


	//���ص�ͼ�����������,id)
	UNIT GetUnitByName(CString UintName,int MapId);


	//���ص�ͼ����������֣�
	


	/*
	//���е�ͼ�Ķ���
	typedef struct tagUnit
	{
	DWORD		Base;
	DWORD		DiTu;
	DWORD		X;
	DWORD		Y;
	DWORD		Z;
	CString Name;
	DWORD		UnitId;
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

	}UNIT;*/


	typedef struct Taskstr
	{
		int Taskid;
		CString TaskName;
	}TaskAAA;
protected:
	int TempUnitCount;
	UNIT TempUnitList[2048];
	TaskAAA TaskTemp;


protected:

	
	



	//������ͼ����
	int ListUnit();



	//������ͼ����
	//DWORD  RootNpc(DWORD RootExit,DWORD Root);





	//��������
	

public:
	void RootAllObject();
	UNIT GetUnitByName(CString UintName);
	//�����Ŀ�꣨����ID,true�ӣ�
DWORD QuestTarget(DWORD myId,bool IsJ);
int RootQuest(DWORD RootExit,DWORD Root/*,CString TaskName*/);



};

