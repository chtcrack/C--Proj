#pragma once


class Login
{
public:
	Login(void);
	~Login(void);
	
	void SelectServer(CString AreaName,CString ServerName);//选择大区和服务器
	void WriteUserName(CString UserName);//游戏启动前写入用户名
	void InputPassWord(CString PassWord);//输入密码并登录
	 bool CheckHaveChart(CString CharName);//检查是否包含角色名的角色
	 void  CreatChar(CString Job);//创建角色,压入一个参数,职业名
	 void EnterGame();//进入游戏
	 
private:
	void SelectAreaCall(DWORD AreaId,DWORD Serverid);
	void SelectServerCall(DWORD Ipa);//使用call选择服务器
	
	void InputPassWordCall(DWORD Keycode);//输入密码Call
	void ClickZuoBiao(DWORD ZuoBiao);//左键点击坐标处
	 char * IpBuff;
	 CString Testip;
};
