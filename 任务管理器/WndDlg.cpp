// WndDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "WndDlg.h"
#include "afxdialogex.h"


// CWndDlg �Ի���

IMPLEMENT_DYNAMIC(CWndDlg, CDialogEx)

CWndDlg::CWndDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_WND, pParent)
{

}

CWndDlg::~CWndDlg()
{
}

void CWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_wndList);
}


BEGIN_MESSAGE_MAP(CWndDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CWndDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWndDlg ��Ϣ�������
BOOL CALLBACK wndProc(HWND hWnd, LPARAM lParam)
{
	CListCtrl* pCtr = (CListCtrl*)(lParam);
	static UINT nIndex = 0;
	TCHAR tBuf[64]{};
	GetWindowText(hWnd, tBuf, _countof(tBuf));
	BOOL isShow = IsWindowVisible(hWnd);
	int nLen = wcslen(tBuf);
	if (isShow == TRUE && nLen != 0)
	{
		CString str;
		str.Format(L"%d", nIndex + 1);
		pCtr->InsertItem(nIndex, _T(""));
		pCtr->SetItemText(nIndex, 0, str);
		pCtr->SetItemText(nIndex, 1, tBuf);
		str.Format(L"%d", hWnd);
		pCtr->SetItemText(nIndex, 2, str);
		nIndex++;
	}

	return TRUE;
}
void CWndDlg::showAllWnd()
{
	EnumWindows(wndProc, (LPARAM)&m_wndList);
}

BOOL CWndDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_wndList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 80);
	m_wndList.InsertColumn(1, _T("������"), LVCFMT_CENTER, 300);
	m_wndList.InsertColumn(2, _T("���ֵ"), LVCFMT_CENTER, 140);
	//��ʾ���д���
	showAllWnd();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CWndDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
	
}
