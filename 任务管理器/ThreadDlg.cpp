// ThreadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "ThreadDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CThreadDlg 对话框

IMPLEMENT_DYNAMIC(CThreadDlg, CDialogEx)

CThreadDlg::CThreadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, m_threadEdit(0)
{

}

CThreadDlg::~CThreadDlg()
{
}

void CThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_threadEdit);
	DDX_Control(pDX, IDC_LIST1, m_threadList);
}


BEGIN_MESSAGE_MAP(CThreadDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CThreadDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CThreadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CThreadDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK3, &CThreadDlg::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK4, &CThreadDlg::OnBnClickedOk4)
END_MESSAGE_MAP()


// CThreadDlg 消息处理程序


BOOL CThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_threadList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_threadList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 80);
	m_threadList.InsertColumn(1, _T("优先级"), LVCFMT_CENTER, 300);
	m_threadList.InsertColumn(2, _T("线程ID"), LVCFMT_CENTER, 140);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CThreadDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void CThreadDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_threadList.DeleteAllItems();
	showAllThread();
}

void CThreadDlg::showAllThread()
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (INVALID_HANDLE_VALUE == hSnap)
	{
		MessageBox(L"线程快照句柄创建失败");
		return;
	}
	THREADENTRY32 te{ sizeof(THREADENTRY32) };
	BOOL bSucceed = Thread32First(hSnap, &te);
	if (!bSucceed)
	{
		MessageBox(L"找不到第一个线程");
		return;
	}
	int nIndex = 0;
	CString str;
	do {
		if (te.th32OwnerProcessID == m_threadEdit)
		{
			str.Format(L"%d", nIndex + 1);
			m_threadList.InsertItem(nIndex, _T(""));
			m_threadList.SetItemText(nIndex, 0, str);
			str.Format(L"%d", te.tpBasePri);
			m_threadList.SetItemText(nIndex, 1, str);
			str.Format(L"%d", te.th32ThreadID);
			m_threadList.SetItemText(nIndex, 2, str);
			nIndex++;
		}
	} while (Thread32Next(hSnap, &te));
}

void CThreadDlg::OnBnClickedOk2()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_threadList.GetFirstSelectedItemPosition();
	if (!pos)
	{
		MessageBox(L"必须选择一个线程!");
		return;
	}
	CString str;
	str = m_threadList.GetItemText((int)pos - 1, 2);
	int nRes = MessageBox(L"确定挂起线程(ID):" + str + L"?",_T("警告"), MB_YESNO);
	if (IDYES == nRes)
	{
		int nId = -1;
		swscanf_s(str, L"%d", &nId);
		HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, nId);
		if (!hThread)
		{
			MessageBox(_T("获取线程句柄失败"));
			return;
		}
		SuspendThread(hThread);
	}
}


void CThreadDlg::OnBnClickedOk3()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_threadList.GetFirstSelectedItemPosition();
	if (!pos)
	{
		MessageBox(L"必须选择一个线程!");
		return;
	}
	CString str;
	str = m_threadList.GetItemText((int)pos - 1, 2);
	int nRes = MessageBox(L"确定恢复线程(ID):" + str + L"?", _T("警告"), MB_YESNO);
	if (IDYES == nRes)
	{
		int nId = -1;
		swscanf_s(str, L"%d", &nId);
		HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, nId);
		if (!hThread)
		{
			MessageBox(_T("获取线程句柄失败"));
			return;
		}
		ResumeThread(hThread);
	}
}


void CThreadDlg::OnBnClickedOk4()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_threadList.GetFirstSelectedItemPosition();
	if (!pos)
	{
		MessageBox(L"必须选择一个线程!");
		return;
	}
	CString str;
	str = m_threadList.GetItemText((int)pos - 1, 2);
	int nRes = MessageBox(L"确定结束线程(ID):" + str + L"?", _T("警告"), MB_YESNO);
	if (IDYES == nRes)
	{
		int nId = -1;
		swscanf_s(str, L"%d", &nId);
		HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, nId);
		if (!hThread)
		{
			MessageBox(_T("获取线程句柄失败"));
			return;
		}
		TerminateThread(hThread, 0);
		m_threadList.DeleteAllItems();
		showAllThread();
	}
}
