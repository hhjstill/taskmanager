#pragma once


// CRscDlg 对话框

class CRscDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRscDlg)

public:
	CRscDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRscDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGRSC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
