#pragma once


// MainDlg �Ի���

class MainDlg : public CDialog
{
	DECLARE_DYNAMIC(MainDlg)

public:
	MainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MainDlg();

// �Ի�������
	enum { IDD = IDD_MAINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonGuaji();
	afx_msg void OnBnClickedButtonTest();
};
