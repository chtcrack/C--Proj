// DebugExeDlg.h : ͷ�ļ�
//

#pragma once
#include "../SkinDll/Ini.h"
void CheckAccount();
// CDebugExeDlg �Ի���
class CDebugExeDlg : public CDialog
{
// ����
public:
	CDebugExeDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
CString m_strPath;//ѡ��Ŀ¼����ļ�·��
// �Ի�������
	enum { IDD = IDD_DEBUGEXE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
