
// ���������Dlg.h : ͷ�ļ�
//

#pragma once


// C���������Dlg �Ի���
class C���������Dlg : public CDialogEx
{
// ����
public:
	C���������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
