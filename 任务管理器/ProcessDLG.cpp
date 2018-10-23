// ProcessDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "ProcessDLG.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

// CProcessDLG 对话框

IMPLEMENT_DYNAMIC(CProcessDLG, CDialogEx)

CProcessDLG::CProcessDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CProcessDLG::~CProcessDLG()
{
}

void CProcessDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_processList);
}


BEGIN_MESSAGE_MAP(CProcessDLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CProcessDLG::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CProcessDLG::OnBnClickedButton3)
	ON_WM_RBUTTONUP()
	
END_MESSAGE_MAP()


// CProcessDLG 消息处理程序


BOOL CProcessDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_processList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_processList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 80);
	m_processList.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, 300);
	m_processList.InsertColumn(2, _T("PID"), LVCFMT_CENTER, 140);
	//显示所有进程
	showAllProcess();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
//显示所有进程 比如这个6112是一个32位进程,有的 有的.32位和64位都有,,但是感觉这个比任务管理器上少些呢
void CProcessDLG::showAllProcess()
{
	//好像是有32位的,没的64 的.不是的.
	PROCESSENTRY32 pe{ sizeof(PROCESSENTRY32) };
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL b = Process32First(hSnap, &pe);
	int nIndex = 0;
	CString str;
	m_processList.DeleteAllItems();
	if (b)
	{
		do {
			str.Format(L"%d", nIndex + 1);
			m_processList.InsertItem(nIndex, _T(""));
			m_processList.SetItemText(nIndex, 0, str);
			m_processList.SetItemText(nIndex, 1, pe.szExeFile);
			str.Format(L"%d", pe.th32ProcessID);
			m_processList.SetItemText(nIndex, 2, str);
			nIndex++;
		} while (Process32Next(hSnap, &pe));
	}
}
//结束选中进程 没法数,差不多吧.可以按照pid排个序,然后一个一个对比,嗯,对了,有个进程堆是什么玩意儿.堆是分配内存的.CreateHeap,这个API就会为进程创建堆.是那个动态分配内存的堆吗嗯嗯
//这玩意儿每个进程之间还是独立的啊?是的.每一个进程都有4G的空间(32位程序),是独立的...又听到这个了,,这个跟CPU分时有关吗没有啊.
//那它是怎么做到每个进程都有4G的哦..哈哈,这个问题详细答案在<windows内核情景分析>第三章  毛德操?嗯这名字真好记 哈哈
//对头,这个任务管理器要我们做个算了,界面的东西,慢慢整,妈的 哈哈  界面最恶心人了.
//做任务管理器有一个大坑,先给你说,你把这个解决了,比他们做界面做好看的牛逼的多.
//目前你这个程序是编译成x64的,编译成64位,去查询32位进程的模块的时候会查不到.
//如果编译成32位的程序,会差不到64位的进程模块..我编译成32位的32位都查不到了..哈哈,这个是bug,慢慢查api文档是查得到的.32位和64位不能互查是系统限制.
//说起都脑壳痛,反正就是按照书上给的做的...你看这个模块遍历的嘛..
void CProcessDLG::exitSelProcess(UINT nChoice)
{
	//得到选中进程ID
	TCHAR tBuf[32]{};
	m_processList.GetItemText(nChoice - 1, 2, tBuf, _countof(tBuf));
	int nPid = -1;
	swscanf_s(tBuf, L"%d", &nPid);
	//结束进程
	HANDLE hPro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, nPid);
	if (!hPro)
	{
		//MessageBox(_T("获取进程句柄失败"));
		return;
	}
	TerminateProcess(hPro, 0);
	CloseHandle(hPro);
	//重新显示进程
	Sleep(1);
	m_processList.DeleteAllItems();
	showAllProcess();
}


void CProcessDLG::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos;
	pos = m_processList.GetFirstSelectedItemPosition();
	int nChoice = (int)pos;
	if (nChoice == 0)
	{
		MessageBox(_T("必须选择一项"));
		return;
	}
	exitSelProcess(nChoice);
}


void CProcessDLG::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


//void CProcessDLG::OnRButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	MessageBox(L"right");
//}


//void CProcessDLG::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//	TrackPopupMenu(,)
//}
