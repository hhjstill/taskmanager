// ThreadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "ThreadDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CThreadDlg �Ի���

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


// CThreadDlg ��Ϣ�������


BOOL CThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_threadList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_threadList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 80);
	m_threadList.InsertColumn(1, _T("���ȼ�"), LVCFMT_CENTER, 300);
	m_threadList.InsertColumn(2, _T("�߳�ID"), LVCFMT_CENTER, 140);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CThreadDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}


void CThreadDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_threadList.DeleteAllItems();
	showAllThread();
}

void CThreadDlg::showAllThread()
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (INVALID_HANDLE_VALUE == hSnap)
	{
		MessageBox(L"�߳̿��վ������ʧ��");
		return;
	}
	THREADENTRY32 te{ sizeof(THREADENTRY32) };
	BOOL bSucceed = Thread32First(hSnap, &te);
	if (!bSucceed)
	{
		MessageBox(L"�Ҳ�����һ���߳�");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_threadList.GetFirstSelectedItemPosition();
	if (!pos)
	{
		MessageBox(L"����ѡ��һ���߳�!");
		return;
	}
	CString str;
	str = m_threadList.GetItemText((int)pos - 1, 2);
	int nRes = MessageBox(L"ȷ�������߳�(ID):" + str + L"?",_T("����"), MB_YESNO);
	if (IDYES == nRes)
	{
		int nId = -1;
		swscanf_s(str, L"%d", &nId);
		HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, nId);
		if (!hThread)
		{
			MessageBox(_T("��ȡ�߳̾��ʧ��"));
			return;
		}
		SuspendThread(hThread);
	}
}


void CThreadDlg::OnBnClickedOk3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_threadList.GetFirstSelectedItemPosition();
	if (!pos)
	{
		MessageBox(L"����ѡ��һ���߳�!");
		return;
	}
	CString str;
	str = m_threadList.GetItemText((int)pos - 1, 2);
	int nRes = MessageBox(L"ȷ���ָ��߳�(ID):" + str + L"?", _T("����"), MB_YESNO);
	if (IDYES == nRes)
	{
		int nId = -1;
		swscanf_s(str, L"%d", &nId);
		HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, nId);
		if (!hThread)
		{
			MessageBox(_T("��ȡ�߳̾��ʧ��"));
			return;
		}
		ResumeThread(hThread);
	}
}


void CThreadDlg::OnBnClickedOk4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_threadList.GetFirstSelectedItemPosition();
	if (!pos)
	{
		MessageBox(L"����ѡ��һ���߳�!");
		return;
	}
	CString str;
	str = m_threadList.GetItemText((int)pos - 1, 2);
	int nRes = MessageBox(L"ȷ�������߳�(ID):" + str + L"?", _T("����"), MB_YESNO);
	if (IDYES == nRes)
	{
		int nId = -1;
		swscanf_s(str, L"%d", &nId);
		HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, nId);
		if (!hThread)
		{
			MessageBox(_T("��ȡ�߳̾��ʧ��"));
			return;
		}
		TerminateThread(hThread, 0);
		m_threadList.DeleteAllItems();
		showAllThread();
	}
}
