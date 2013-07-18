// DebugExeDlg.h : 头文件
//

#pragma once
#include "../SkinDll/Ini.h"
void CheckAccount();
// CDebugExeDlg 对话框
class CDebugExeDlg : public CDialog
{
// 构造
public:
	CDebugExeDlg(CWnd* pParent = NULL);	// 标准构造函数
	
CString m_strPath;//选择目录后的文件路径
// 对话框数据
	enum { IDD = IDD_DEBUGEXE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
