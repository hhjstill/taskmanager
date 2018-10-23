
// 任务管理器Dlg.h : 头文件
//

#pragma once


// C任务管理器Dlg 对话框
class C任务管理器Dlg : public CDialogEx
{
// 构造
public:
	C任务管理器Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	double FILETME2Double(const _FILETIME& fileTime);
	int getCpuLoad();
	void adjustPrivilege();
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
private:
	CMenu m_menu;
public:
	afx_msg void onClickMenuProcess();
	afx_msg void onClickMenuOpen();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void onClickMenuShutdown();
	afx_msg void OnClickLock();
	afx_msg void OnClickRestart();
	afx_msg void On32781();
};
