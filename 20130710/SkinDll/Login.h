#pragma once


class Login
{
public:
	Login(void);
	~Login(void);
	
	void SelectServer(CString AreaName,CString ServerName);//ѡ������ͷ�����
	void WriteUserName(CString UserName);//��Ϸ����ǰд���û���
	void InputPassWord(CString PassWord);//�������벢��¼
	 bool CheckHaveChart(CString CharName);//����Ƿ������ɫ���Ľ�ɫ
	 void  CreatChar(CString Job);//������ɫ,ѹ��һ������,ְҵ��
	 void EnterGame();//������Ϸ
	 
private:
	void SelectAreaCall(DWORD AreaId,DWORD Serverid);
	void SelectServerCall(DWORD Ipa);//ʹ��callѡ�������
	
	void InputPassWordCall(DWORD Keycode);//��������Call
	void ClickZuoBiao(DWORD ZuoBiao);//���������괦
	 char * IpBuff;
	 CString Testip;
};
