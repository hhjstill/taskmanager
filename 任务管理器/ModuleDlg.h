#pragma once
#include "afxcmn.h"


// CModuleDlg �Ի���

class CModuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModuleDlg)

public:
	CModuleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModuleDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void showAllModule();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_moduleList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	int m_edit;
	afx_msg void OnBnClickedButton2();
};
