#pragma once
#include "afxcmn.h"


// CFileDlg �Ի���

class CFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileDlg)

public:
	CFileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void showAllFile(const CString& path);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_fileList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
};
