// CleanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "CleanDlg.h"
#include "afxdialogex.h"


// CCleanDlg 对话框

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


// CCleanDlg 消息处理程序


void CCleanDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void CCleanDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CFolderPickerDialog fileDlg;
	fileDlg.DoModal();
	//获取文件夹路径
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
	// TODO: 在此添加控件通知处理程序代码
	if (!wcslen(m_cleanEdit))
	{
		MessageBox(L"请选择需要清理的文件夹!");
		return;
	}
	else
	{
		CString str;
		str.Format(L"确定要清理:%s", m_cleanEdit);
		int nRes = MessageBox(str + L"?", L"警告", MB_YESNO);
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