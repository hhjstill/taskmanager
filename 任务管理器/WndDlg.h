#pragma once
#include "afxcmn.h"


// CWndDlg �Ի���

class CWndDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWndDlg)

public:
	CWndDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWndDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void showAllWnd();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_wndList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
