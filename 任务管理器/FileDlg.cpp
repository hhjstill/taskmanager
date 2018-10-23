// FileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "FileDlg.h"
#include "afxdialogex.h"
#include <Psapi.h>

// CFileDlg �Ի���

IMPLEMENT_DYNAMIC(CFileDlg, CDialogEx)

CFileDlg::CFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

CFileDlg::~CFileDlg()
{
}

void CFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_fileList);
}


BEGIN_MESSAGE_MAP(CFileDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CFileDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CFileDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileDlg ��Ϣ�������


BOOL CFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_fileList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_fileList.InsertColumn(0, _T("�ļ���"), LVCFMT_CENTER, 240);
	m_fileList.InsertColumn(1, _T("�ļ���С"), LVCFMT_CENTER, 120);
	m_fileList.InsertColumn(2, _T("����ʱ��"), LVCFMT_CENTER, 160);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CFileDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFolderPickerDialog fileDlg;
	fileDlg.DoModal();

	//ѡ����Ӧ�ļ��л�ȡ�ļ���·��
	CString path = fileDlg.GetPathName();
	if (!path.GetLength())
	{
		return;
	}
	m_fileList.DeleteAllItems();
	showAllFile(path);
}
void CFileDlg::showAllFile(const CString& path)
{

	WIN32_FIND_DATA wd{};
	HANDLE hFile = FindFirstFile(path + "\\*", &wd);
	if (hFile == INVALID_HANDLE_VALUE)
		return;
	CString str;
	int nIndex = 0;
	//m_fileList.DeleteAllItems();
	do {
		if (wcscmp(wd.cFileName, L".") == 0 || wcscmp(wd.cFileName, L"..") == 0)
			continue;

		m_fileList.InsertItem(nIndex, _T(""));
		m_fileList.SetItemText(nIndex, 0, path + "\\" + wd.cFileName);

		str.Format(L"%dKB", wd.nFileSizeLow / 1024);
		m_fileList.SetItemText(nIndex, 1, str);
		// ���ļ�ʱ��ת���ɱ��ص��ļ�ʱ��
		FileTimeToLocalFileTime(&wd.ftCreationTime,
			&wd.ftCreationTime);
		SYSTEMTIME st = { 0 };
		// ���ļ�ʱ��ת��ϵͳʱ��
		FileTimeToSystemTime(&wd.ftCreationTime, &st);
		str.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		m_fileList.SetItemText(nIndex, 2, str);
		nIndex++;
		
		if (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			showAllFile(path + L"\\" + wd.cFileName);
		}
		
	} while (FindNextFile(hFile, &wd));
}

void CFileDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_fileList.GetFirstSelectedItemPosition();
	if (!pos)
	{
		MessageBox(L"����ѡ��һ���ļ�");
		return;
	}
	int nChoice = (int)pos - 1;
	CString path = m_fileList.GetItemText(nChoice, 0);
	CString str;
	str.Format(L"ȷ��ɾ��:%s?", path);
	int nRes = MessageBox(str,_T("����"),MB_YESNO);
	if (IDYES == nRes)
		MessageBox(L"ɾ���ɹ�!");
}
