#pragma once

enum
{
	Hp_myObj = 0xC19E28,//人物jiz0xBBB118

	Hp_myZt = 0x0109bb5c,//人物状态机子

	Hp_IterateObj = 0x00C19DE0,//遍历地面对象基址
	Hp_IterateBase = 0xC16018,//遍历机子mov edx


	Hp_NeiGua = 0xBFD448,//开启内挂+02ce；1开启0关闭

	Hp_SouZaiMap = 0xBFD290,//所在地图[[0xBFA0F0]] = MapId

	///PublicClass

	Hp_BianLiBeiBao = 0x00C192F0,//遍历背包机子；
	Hp_BaoGuoDiZhi = 0x00C191E8,//包裹地址

	Hp_wnEcx = 0xBDDF68,
	Hp_wnEcxq = 0xBDDF80,

	Hp_wnCall0 = 0xAA0378,
	Hp_wnEdx = 0xA9F724,
	Hp_wnCall1 = 0xA9F710,

	Hp_wnCall = 0x00898EF0,//万能callcall 00879BD0
	Hp_wnCallq = 0x005A7990,


	////////////////


	///ChaoZuo
	Hp_CFuBenIndex = 0x00C256C8,//出副本时候的ID
	////////////////////////


	//UiOperating

	ShouShenRu = 0x00AAC008,//包裹头
	myShop = 0x00AC5CB8,//自商店头
	myPet = 0x00AC1B14,///宠物头
	myMove = 0x00AABE04,//寻
	myJsWc = 0x00AE855C,//接受完成
	///////////////

	//QuestTacking mov eax,0xBC5CC0
	Hp_QuestTargt = 0xC25110,//任务机子
};