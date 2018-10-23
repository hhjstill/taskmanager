// CleanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "CleanDlg.h"
#include "afxdialogex.h"


// CCleanDlg �Ի���

IMPLEMENT_DYNAMIC(CCleanDlg, CDialogEx)

CCleanDlg::CCleanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, m_cleanEdit(_T(""))
{

}

CCleanDlg::~CCleanDlg()
{
}

void CCleanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cleanEdit);
}


BEGIN_MESSAGE_MAP(CCleanDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CCleanDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CCleanDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL2, &CCleanDlg::OnBnClickedCancel2)
END_MESSAGE_MAP()


// CCleanDlg ��Ϣ�������


void CCleanDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}


void CCleanDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFolderPickerDialog fileDlg;
	fileDlg.DoModal();
	//��ȡ�ļ���·��
	CString path;
	path = fileDlg.GetPathName();
	if (wcslen(path))
	{
		m_cleanEdit = path;
		UpdateData(FALSE);
	}
}


void CCleanDlg::OnBnClickedCancel2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!wcslen(m_cleanEdit))
	{
		MessageBox(L"��ѡ����Ҫ������ļ���!");
		return;
	}
	else
	{
		CString str;
		str.Format(L"ȷ��Ҫ����:%s", m_cleanEdit);
		int nRes = MessageBox(str + L"?", L"����", MB_YESNO);
		if (IDNO == nRes)
			return;
	}
	cleanFile(m_cleanEdit);
}
void CCleanDlg::cleanFile(const CString& path)
{
	WIN32_FIND_DATA wd{};
	HANDLE hFile = FindFirstFile(path + "\\*", &wd);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	do {
		if(wcscmp(wd.cFileName, L".") == 0 || wcscmp(wd.cFileName, L"..") == 0)
			continue;
		if (isRubish(wd.cFileName))
		{
			DeleteFile(path + L"\\" + wd.cFileName);
		}
		if (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			cleanFile(path + L"\\" + wd.cFileName);
	} while (FindNextFile(hFile, &wd));
}

BOOL CCleanDlg::isRubish(const CString& path)
{
	wchar_t tBuf[8]{};
	
	int nIndex = path.GetLength() - 4;
	int i = 0;
	while (i != 4)
	{
		tBuf[i] = path[nIndex];
		i++;
		nIndex++;
	}
	if (wcscmp(tBuf, L".txt") == 0)
		return TRUE;
	return FALSE;
}