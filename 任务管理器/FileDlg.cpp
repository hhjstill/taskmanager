// FileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "FileDlg.h"
#include "afxdialogex.h"
#include <Psapi.h>

// CFileDlg 对话框

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


// CFileDlg 消息处理程序


BOOL CFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_fileList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_fileList.InsertColumn(0, _T("文件名"), LVCFMT_CENTER, 240);
	m_fileList.InsertColumn(1, _T("文件大小"), LVCFMT_CENTER, 120);
	m_fileList.InsertColumn(2, _T("创建时间"), LVCFMT_CENTER, 160);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CFileDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFolderPickerDialog fileDlg;
	fileDlg.DoModal();

	//选择相应文件夹获取文件夹路径
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
		// 将文件时间转换成本地的文件时间
		FileTimeToLocalFileTime(&wd.ftCreationTime,
			&wd.ftCreationTime);
		SYSTEMTIME st = { 0 };
		// 将文件时间转换系统时间
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
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_fileList.GetFirstSelectedItemPosition();
	if (!pos)
	{
		MessageBox(L"必须选择一个文件");
		return;
	}
	int nChoice = (int)pos - 1;
	CString path = m_fileList.GetItemText(nChoice, 0);
	CString str;
	str.Format(L"确定删除:%s?", path);
	int nRes = MessageBox(str,_T("警告"),MB_YESNO);
	if (IDYES == nRes)
		MessageBox(L"删除成功!");
}
