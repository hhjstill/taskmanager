#pragma once
#include "afxcmn.h"


// CHeapDlg �Ի���

class CHeapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHeapDlg)

public:
	CHeapDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHeapDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void showAllHeap();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_heapList;
	virtual BOOL OnInitDialog();
	int m_heapEdit;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
