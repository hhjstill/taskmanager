#pragma once


// CRscDlg �Ի���

class CRscDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRscDlg)

public:
	CRscDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRscDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGRSC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
