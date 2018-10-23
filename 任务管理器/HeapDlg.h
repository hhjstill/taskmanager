#pragma once
#include "afxcmn.h"


// CHeapDlg 对话框

class CHeapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHeapDlg)

public:
	CHeapDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHeapDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void showAllHeap();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_heapList;
	virtual BOOL OnInitDialog();
	int m_heapEdit;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
