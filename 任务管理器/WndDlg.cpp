// WndDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "WndDlg.h"
#include "afxdialogex.h"


// CWndDlg 对话框

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


// CWndDlg 消息处理程序
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

	// TODO:  在此添加额外的初始化
	m_wndList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 80);
	m_wndList.InsertColumn(1, _T("窗口名"), LVCFMT_CENTER, 300);
	m_wndList.InsertColumn(2, _T("句柄值"), LVCFMT_CENTER, 140);
	//显示所有窗口
	showAllWnd();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CWndDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
	
}
