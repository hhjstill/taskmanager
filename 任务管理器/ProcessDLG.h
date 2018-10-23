#pragma once
#include "afxcmn.h"


// CProcessDLG 对话框

class CProcessDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessDLG)

public:
	CProcessDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProcessDLG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void showAllProcess();
	void exitSelProcess(UINT nChoice);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_processList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
