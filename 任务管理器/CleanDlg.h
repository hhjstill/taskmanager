#pragma once


// CCleanDlg �Ի���

class CCleanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCleanDlg)

public:
	CCleanDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCleanDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void cleanFile(const CString& path);
	BOOL isRubish(const CString& path);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CString m_cleanEdit;
	afx_msg void OnBnClickedCancel2();
};
