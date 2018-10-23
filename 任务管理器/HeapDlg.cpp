// HeapDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "HeapDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

// CHeapDlg �Ի���

IMPLEMENT_DYNAMIC(CHeapDlg, CDialogEx)

CHeapDlg::CHeapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_heapEdit(0)
{

}

CHeapDlg::~CHeapDlg()
{
}

void CHeapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_heapList);
	DDX_Text(pDX, IDC_EDIT1, m_heapEdit);
}


BEGIN_MESSAGE_MAP(CHeapDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CHeapDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CHeapDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CHeapDlg ��Ϣ�������


BOOL CHeapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_heapList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_heapList.InsertColumn(0, _T("��ID"), LVCFMT_CENTER, 80);
	m_heapList.InsertColumn(1, _T("�Ѵ�С"), LVCFMT_CENTER, 320);
	m_heapList.InsertColumn(1, _T("�ѵ�ַ"), LVCFMT_CENTER, 120);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CHeapDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}


void CHeapDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_heapList.DeleteAllItems();
	showAllHeap();
}
void CHeapDlg::showAllHeap()
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, m_heapEdit);
	if (INVALID_HANDLE_VALUE == hSnap)
	{
		MessageBox(L"�ѿ��վ������ʧ��");
		return;
	}
	HEAPLIST32 hl{ sizeof(HEAPLIST32) };
	HEAPENTRY32 he{ sizeof(HEAPENTRY32) };
	BOOL bSecceed = Heap32ListFirst(hSnap, &hl);
	if (!bSecceed)
	{
		MessageBox(L"�Ҳ�����");
		return;
	}
	CString str;
	int nIndex = 0;
	do {
		//str.Format(L"%d", nIndex + 1);
		//m_heapList.InsertItem(nIndex, str);
		//str.Format(L"%d", he.th32HeapID);
		//m_heapList.SetItemText(nIndex, 1, str);
		//nIndex++;
		bSecceed = Heap32First(&he, m_heapEdit, hl.th32HeapID);
		if (!bSecceed)
		{
			//MessageBox(L"�Ҳ�����");
			return;
		}
		//do {
			str.Format(L"%ld", he.th32HeapID);
			m_heapList.InsertItem(nIndex, str);
			str.Format(L"0x%x", he.dwAddress);
			m_heapList.SetItemText(nIndex, 1, str);
			str.Format(L"%dB", he.dwBlockSize);
			m_heapList.SetItemText(nIndex, 2, str);
			nIndex++;
		//} while (Heap32Next(&he));
	} while (Heap32ListNext(hSnap, &hl));
}