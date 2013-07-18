#pragma once


enum
{
	NPC=0,
	TASKBYID,
	TASKBYNAME,
	MAPID,
	MAPNAME,
	XYZ,
	MONSTER,
};


enum
{
	Start=100,
	Finding,
	LostSelf,
	FindDone,
};



typedef struct tagFWay
{
	int type;
	CString NpcName;
	CString MonsterName;
	int X,Y,Z;
	int MapId;
	CString MapName;
	int TaskId;
	CString TaskName;
}FWAY;

void FindWay(FWAY & tag )
{


	int Stu;

	while(1)
	{


		switch(Stu)
		{
		case NPC:
			{
				MyDebug("FindWay by NPC %s ",tag.NpcName);

				break;

			}
		case TASKBYID:
			{
				MyDebug("FindWay by  TASKBYID %d ",tag.TaskId);

				break;
			}
		case TASKBYNAME:
			{
				MyDebug("FindWay by  TASKBYName %s ",tag.TaskName);
			}
		case XYZ:
			{
				MyDebug("FindWay by MAPNAME, XYZ-%s-%d,%d,%d ",tag.MapName,tag.X,tag.Y,tag.Z);
			}

		case MONSTER:
			{
				MyDebug("FindWay by  MONSTERName %s ",tag.MonsterName);
			}

		default:
			{
				break;
			}


		}



		Sleep(1000);
	}

}