#pragma once
#include "afxcmn.h"


// CModuleDlg 对话框

class CModuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModuleDlg)

public:
	CModuleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModuleDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void showAllModule();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_moduleList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	int m_edit;
	afx_msg void OnBnClickedButton2();
};
