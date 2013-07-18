#include "StdAfx.h"
#include ".\gamemain.h"
#include "ReadWriteIni.h"
#include "AsmBase.h"
void FindWayTimer1(FWAY & tag )
{

	FindWay FindObject;
	int Stu = tag.type;

	while(1)
	{

		switch(Stu)
		{
		case NPC:
			{
				MyDebug("FindWay by NPC %s ",tag.Name);
				
				FindObject.FindToNpc(tag.Name);
				Stu = 1;
				break;
			}
		case 1:
			{
				if(FindObject.IsReach())
				{
					Stu  = 999;
				}
				else
				{
					Stu = NPC;
				}
				break;
			}
		case TASKBYID:
			{
				MyDebug("FindWay by  TASKBYID %d ",tag.TaskId);
				FindObject.FindToTaskID(tag.TaskId,true);
				Stu = 11;
				break;
			}
		case 11:
			{
				if(FindObject.IsReach())
				{
					Stu  = 999;
				}
				else
				{
					Stu = TASKBYID;
				}
				break;
			}
		case TASKBYNAME:
			{

				MyDebug("FindWay by  TASKBYName %s ",tag.TaskName);
				FindObject.FindByTaskName(tag.TaskName);
				Stu = 21;

			}
		case 21:
			{
				if(FindObject.IsReach())
				{
					Stu  = 999;
				}
				else
				{
					Stu = TASKBYNAME;
				}
				break;
			}
		case XYZ:
			{
				FindObject.FindToXYZ(tag.MapId,tag.X,tag.Y,tag.Z);
				MyDebug("FindWay by MAPNAME, XYZ-%s-%d,%d,%d ",tag.MapName,tag.X,tag.Y,tag.Z);
				Stu = 51;
			}
		case 51:
			{
				if(FindObject.IsReach())
				{
					Stu  = 999;
				}
				else
				{
					Stu = XYZ;
				}
				break;
			}
		case MONSTER:
			{
				FindObject.FindToNpc(tag.Name);
				Stu = 61;
				MyDebug("FindWay by  MONSTERName %s ",tag.Name);
			}
		case 61:
			{
				if(FindObject.IsReach())
				{
					Stu  = 999;
				}
				else
				{
					Stu = MONSTER;
				}
				break;
			}

		case 999:
			//Stu = 999;
			return;
			break;
		default:
			{
				break;
			}
		}

		Sleep(1000);
	}

}





void GoToObject(FWAY & tag )
{
	FindWay TempWay;
	BaseCall TempBasecall;
	CString NowMapName,TagetMapName;
	CString CmaPid;
	int Mapidtag ;//当前所在地图id
	CString MapTempName;
	int LocalTaskid;
	


	int Stu=tag.type;

	switch(Stu)//获取目标所在地图名和目标坐标
	{
	case TASKBYID:
		{
			DWORD TaskPtr=0;
			TaskPtr=TempWay.QuestTarget(tag.TaskId,true);

			TempBasecall.RootDiTu((DWORD)(Hp_IterateBase + 0x1e8),(*(DWORD*)(Hp_IterateBase+0x200)),*(DWORD*)(TaskPtr+0x8));
			TagetMapName=MapTempName;
			tag.X=*(DWORD*)(TaskPtr+0xC);
			tag.Y=*(DWORD*)(TaskPtr+0x10);
			tag.Z=*(DWORD*)(TaskPtr+0x14);
			
			break;
		}
	case TASKBYNAME:
		{
			TempWay.RootQuest(Hp_IterateBase+0x14d0,(*(DWORD*)(Hp_IterateBase+0x14e8))/*,tag.TaskName*/);
			
			DWORD TaskPtr=0;
			TaskPtr=TempWay.QuestTarget(LocalTaskid,true);

			TempBasecall.RootDiTu((DWORD)(Hp_IterateBase + 0x1e8),(*(DWORD*)(Hp_IterateBase+0x200)),*(DWORD*)(TaskPtr+0x8));
			TagetMapName=MapTempName;
			tag.X=*(DWORD*)(TaskPtr+0xC);
			tag.Y=*(DWORD*)(TaskPtr+0x10);
			tag.Z=*(DWORD*)(TaskPtr+0x14);
			break;
		}
			
			
		
	case MAPID:
		{
			//获取目标地图名
			TempBasecall.RootDiTu((DWORD)(Hp_IterateBase + 0x1e8),(*(DWORD*)(Hp_IterateBase+0x200)),tag.MapId);
			TagetMapName=MapTempName;
			tag.X=0;
			tag.Y=0;
			tag.Z=0;
			break;
		}
	case MAPNAME:
		{
			//获取目标地图名
			TagetMapName=tag.MapName;
			tag.X=0;
			tag.Y=0;
			tag.Z=0;
			break;
		}
	case XYZ:
		{
			if (tag.MapId==0)
			{
			TagetMapName=TempWay.GetNowMapName();
			}
			else
			{

			TempBasecall.RootDiTu((DWORD)(Hp_IterateBase + 0x1e8),(*(DWORD*)(Hp_IterateBase+0x200)),tag.MapId);
			TagetMapName=MapTempName;
			
			
			
			}
			//获取目标地图名	
			break;
		}
	case MONSTER:
		{
			
			UNIT temp = TempWay.GetUnitByName(tag.Name);
			
			 TempWay.RootDiTu((DWORD)(Hp_IterateBase + 0x1e8),(*(DWORD*)(Hp_IterateBase+0x200)),temp.DiTu);
			TagetMapName=MapTempName;
			tag.X=temp.X;
			tag.Y=temp.Y;
			tag.Z=temp.Z;
			//获取目标地图名
			break;
		}
	case NPC:
		{
			
			//TempWay.RootNpc(Hp_IterateBase+0x20c,(*(DWORD*)(Hp_IterateBase+0x224)));
			UNIT temp = TempWay.GetUnitByName(tag.Name);

			TempWay.RootDiTu((DWORD)(Hp_IterateBase + 0x1e8),(*(DWORD*)(Hp_IterateBase+0x200)),temp.DiTu);
			TagetMapName=MapTempName;
			tag.X=temp.X;
			tag.Y=temp.Y;
			tag.Z=temp.Z;
			//获取目标地图名
			break;
		}
	default:
		{
			break;
		}
	}


	CmaPid=getini("副本.ini","副本",TagetMapName);
	int TargetMapidtag = _ttoi(CmaPid);//目标所在地图id



	while(TempWay.IsReach())
	{
	NowMapName=TempWay.GetNowMapName();
	CmaPid=getini("副本.ini","副本",NowMapName);
	Mapidtag = _ttoi(CmaPid);//当前所在地图id


	switch(Mapidtag)//当前所在地图类型
	{
	case 9://可直接进入的副本
		{
			switch( TargetMapidtag)//目标所在地图类型
			{
			case 1://普通地图
				{	
					//回城
					TempWay.BackToCity();
					//瞬移到目标
					if (tag.X==0 && tag.Y==0 && tag.Z==0)
					{
						TempWay.FindWayMap(TagetMapName);
					}
					
					else
					{
					TempWay.FindToXYZ(TargetMapidtag,tag.X,tag.Y,tag.Z);
					}
					break;
				}
			case 9://直接进入副本
				{
					//直接进入副本
					TempWay.JinFuBen(TargetMapidtag,0);
					break;
				}
			case 8://对话的副本
				{
					//回城
						TempWay.BackToCity();
					//瞬移到对话npc进图
						CString FnpcName=("副本.ini","其他",TagetMapName);
						TempWay.FindToNpc(FnpcName);
					break;
				}
			default:
				{
					break;
				}
			}
			break;
		}
	case 8://需对话的副本
		{
			switch( TargetMapidtag)
			{
			case 1:
				{
					//回城
					TempWay.BackToCity();
					//瞬移到目标
					if (tag.X==0 && tag.Y==0 && tag.Z==0)
					{
						TempWay.FindWayMap(TagetMapName);
					}

					else
					{
						TempWay.FindToXYZ(TargetMapidtag,tag.X,tag.Y,tag.Z);
					}
					break;
				}
			case 9:
				{
					//	回城
					TempWay.BackToCity();
					//	直接进入副本
					TempWay.JinFuBen(TargetMapidtag,0);
					break;
				}
			case 8:
				{
					//	回城
					TempWay.BackToCity();
					//瞬移到对话npc进图
					CString FnpcName=("副本.ini","其他",TagetMapName);
					TempWay.FindToNpc(FnpcName);
					break;
				}
				break;
			}
		}
	case 1://大地图
		{
			switch( TargetMapidtag)
			{
			case 1:
				{
					//瞬移到目标
					if (tag.X==0 && tag.Y==0 && tag.Z==0)
					{
						TempWay.FindWayMap(TagetMapName);
					}

					else
					{
						TempWay.FindToXYZ(TargetMapidtag,tag.X,tag.Y,tag.Z);
					}
					break;
				}

			case 9:
				{
					//	直接进入副本
					TempWay.JinFuBen(TargetMapidtag,0);
					
					//瞬移到目标
					if (tag.X==0 && tag.Y==0 && tag.Z==0)
					{
						TempWay.FindWayMap(TagetMapName);
					}

					else
					{
						TempWay.FindToXYZ(TargetMapidtag,tag.X,tag.Y,tag.Z);
					}
					break;
				}

			case 8:
				{
					break;
					//瞬移到对话npc进图
					CString FnpcName=("副本.ini","其他",TagetMapName);
					TempWay.FindToNpc(FnpcName);
					//瞬移到目标
					//瞬移到目标
					if (tag.X==0 && tag.Y==0 && tag.Z==0)
					{
						TempWay.FindWayMap(TagetMapName);
					}

					else
					{
						TempWay.FindToXYZ(TargetMapidtag,tag.X,tag.Y,tag.Z);
					}
				}

			}
		}
	default:
		{
			break;
		}
	}
	Sleep(5000);
	}
}


/*
int Stu;
switch(Stu)
{

//寻路类型
case TASKBYID:
	{
		//获取当前地图,判断
		Stu = FUBENBOOL;

		Stu = //大地图;
		break;
	}
case TASKBYNAME:
	{
		break;
	}
case MAPID:
	{
		break;
	}
case MAPNAME:
	{
		break;
	}
case XYZ:
	{
		break;
	}
case MONSTER:
	{
		break;
	}



///副本判断
case FUBENBOOL:
	{
		Stu = //副本类型
		break;
	}

case CANZHIJIFUEBN:
	{
		//判断是出还是进
		//副本操作
	}
case NORMALMAP:
	{
		//对话
	}
case TALKFUBEN:
	{
		//回城
	}

//大地图判断
case DADITU:
	{
		//判断目标
		//在大图瞬 Stu = DADITU + 1;
		//副本Stu = FUBENBOOL
	}
case DADITU+1:
	{
		///瞬
	}


default:
	{
		break;
	} 

}


*/
