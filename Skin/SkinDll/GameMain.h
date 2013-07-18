#pragma once
#include "AsmBase.h"



/*
enum
{
	NPC=0,
	TASKBYID = 10,
	TASKBYNAME = 20,
	MAPID = 30,
	MAPNAME = 40,
	XYZ = 50,
	MONSTER = 60,
};
*/

enum
{
	NPC=0,
	TASKBYID = 10,
	TASKBYNAME = 20,
	MAPID = 30,
	MAPNAME = 40,
	XYZ = 50,
	MONSTER = 60,
	CANZHIJIFUEBN=100,
	NORMALMAP=200,
	TALKFUBEN=300,

	FUBENBOOL = 400,
};


enum
{
	Start=100,
	Finding = 200,
	LostSelf = 300,
	FindDone = 400,
};



typedef struct tagFWay
{
	int type;
	CString Name;
	int X,Y,Z;
	int MapId;
	CString MapName;
	int TaskId;
	CString TaskName;
}FWAY;

void GoToObject(FWAY & tag );

void FindWayTimer1(FWAY & tag );