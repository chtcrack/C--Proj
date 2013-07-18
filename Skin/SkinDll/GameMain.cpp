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
	int Mapidtag ;//��ǰ���ڵ�ͼid
	CString MapTempName;
	int LocalTaskid;
	


	int Stu=tag.type;

	switch(Stu)//��ȡĿ�����ڵ�ͼ����Ŀ������
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
			//��ȡĿ���ͼ��
			TempBasecall.RootDiTu((DWORD)(Hp_IterateBase + 0x1e8),(*(DWORD*)(Hp_IterateBase+0x200)),tag.MapId);
			TagetMapName=MapTempName;
			tag.X=0;
			tag.Y=0;
			tag.Z=0;
			break;
		}
	case MAPNAME:
		{
			//��ȡĿ���ͼ��
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
			//��ȡĿ���ͼ��	
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
			//��ȡĿ���ͼ��
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
			//��ȡĿ���ͼ��
			break;
		}
	default:
		{
			break;
		}
	}


	CmaPid=getini("����.ini","����",TagetMapName);
	int TargetMapidtag = _ttoi(CmaPid);//Ŀ�����ڵ�ͼid



	while(TempWay.IsReach())
	{
	NowMapName=TempWay.GetNowMapName();
	CmaPid=getini("����.ini","����",NowMapName);
	Mapidtag = _ttoi(CmaPid);//��ǰ���ڵ�ͼid


	switch(Mapidtag)//��ǰ���ڵ�ͼ����
	{
	case 9://��ֱ�ӽ���ĸ���
		{
			switch( TargetMapidtag)//Ŀ�����ڵ�ͼ����
			{
			case 1://��ͨ��ͼ
				{	
					//�س�
					TempWay.BackToCity();
					//˲�Ƶ�Ŀ��
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
			case 9://ֱ�ӽ��븱��
				{
					//ֱ�ӽ��븱��
					TempWay.JinFuBen(TargetMapidtag,0);
					break;
				}
			case 8://�Ի��ĸ���
				{
					//�س�
						TempWay.BackToCity();
					//˲�Ƶ��Ի�npc��ͼ
						CString FnpcName=("����.ini","����",TagetMapName);
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
	case 8://��Ի��ĸ���
		{
			switch( TargetMapidtag)
			{
			case 1:
				{
					//�س�
					TempWay.BackToCity();
					//˲�Ƶ�Ŀ��
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
					//	�س�
					TempWay.BackToCity();
					//	ֱ�ӽ��븱��
					TempWay.JinFuBen(TargetMapidtag,0);
					break;
				}
			case 8:
				{
					//	�س�
					TempWay.BackToCity();
					//˲�Ƶ��Ի�npc��ͼ
					CString FnpcName=("����.ini","����",TagetMapName);
					TempWay.FindToNpc(FnpcName);
					break;
				}
				break;
			}
		}
	case 1://���ͼ
		{
			switch( TargetMapidtag)
			{
			case 1:
				{
					//˲�Ƶ�Ŀ��
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
					//	ֱ�ӽ��븱��
					TempWay.JinFuBen(TargetMapidtag,0);
					
					//˲�Ƶ�Ŀ��
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
					//˲�Ƶ��Ի�npc��ͼ
					CString FnpcName=("����.ini","����",TagetMapName);
					TempWay.FindToNpc(FnpcName);
					//˲�Ƶ�Ŀ��
					//˲�Ƶ�Ŀ��
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

//Ѱ·����
case TASKBYID:
	{
		//��ȡ��ǰ��ͼ,�ж�
		Stu = FUBENBOOL;

		Stu = //���ͼ;
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



///�����ж�
case FUBENBOOL:
	{
		Stu = //��������
		break;
	}

case CANZHIJIFUEBN:
	{
		//�ж��ǳ����ǽ�
		//��������
	}
case NORMALMAP:
	{
		//�Ի�
	}
case TALKFUBEN:
	{
		//�س�
	}

//���ͼ�ж�
case DADITU:
	{
		//�ж�Ŀ��
		//�ڴ�ͼ˲ Stu = DADITU + 1;
		//����Stu = FUBENBOOL
	}
case DADITU+1:
	{
		///˲
	}


default:
	{
		break;
	} 

}


*/
