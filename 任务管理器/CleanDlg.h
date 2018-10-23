#pragma once


// CCleanDlg 对话框

class CCleanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCleanDlg)

public:
	CCleanDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCleanDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void cleanFile(const CString& path);
	BOOL isRubish(const CString& path);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CString m_cleanEdit;
	afx_msg void OnBnClickedCancel2();
};
