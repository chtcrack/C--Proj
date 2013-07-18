#pragma once

enum
{
	Hp_myObj = 0xC1AE28,//人物jiz0xBBB118

	Hp_myZt = 0x0109ab5c,//人物状态机子

	Hp_IterateObj = 0x00C1ADE0,//遍历地面对象基址
	Hp_IterateBase = 0xC17018,//遍历机子mov edx0xC17018


	Hp_NeiGua = 0xBFE448,//开启内挂+02ce；1开启0关闭

	Hp_SouZaiMap = 0xBFE290,//所在地图[[0xBFA0F0]] = MapId

	///PublicClass

	Hp_BianLiBeiBao = 0xC1A2F0,//遍历背包机子；
	Hp_BaoGuoDiZhi = 0x00C1A1E8,//包裹地址

	Hp_wnEcx = 0xBE0F70,
	Hp_wnEcxq = 0xBE0F88,

	Hp_wnCall0 = 0xAA3378,
	Hp_wnEdx = 0xAA271C,
	Hp_wnCall1 = 0xAA2708,

	Hp_wnCall = 0x0089A160,//万能callcall 00879BD0
	Hp_wnCallq = 0x005A8160,


	////////////////


	///ChaoZuo
	Hp_CFuBenIndex = 0x00C266C8,//出副本时候的ID
	////////////////////////


	//UiOperating

	ShouShenRu = 0x00AAD010,//包裹头
	myShop = 0x00AC6CD4,//自商店头
	myPet = 0x00AC2B30,///宠物头
	myMove = 0x00AACE0C,//寻[1412] 00AACE0C
	myJsWc = 0x00AE957C,//接受完成
	///////////////

	//QuestTacking mov eax,0xBC5CC0
	Hp_QuestTargt = 0xC282C0,//任务机子


	Hp_Pet = 0xC21034,
};


