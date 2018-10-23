
// 任务管理器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "任务管理器Dlg.h"
#include "afxdialogex.h"
#include "ProcessDLG.h"
#include "WndDlg.h"
#include "ModuleDlg.h"
#include "HeapDlg.h"
#include "FileDlg.h"
#include "ThreadDlg.h"
#include "CleanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C任务管理器Dlg 对话框



C任务管理器Dlg::C任务管理器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C任务管理器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C任务管理器Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C任务管理器Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C任务管理器Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C任务管理器Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C任务管理器Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C任务管理器Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C任务管理器Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &C任务管理器Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &C任务管理器Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &C任务管理器Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &C任务管理器Dlg::OnBnClickedButton11)
	ON_COMMAND(ID_32773, &C任务管理器Dlg::onClickMenuProcess)
	ON_COMMAND(ID_32771, &C任务管理器Dlg::onClickMenuOpen)
	ON_COMMAND(ID_32779, &C任务管理器Dlg::onClickMenuShutdown)
	ON_COMMAND(ID_32782, &C任务管理器Dlg::OnClickLock)
	ON_COMMAND(ID_32780, &C任务管理器Dlg::OnClickRestart)
	ON_COMMAND(ID_32781, &C任务管理器Dlg::On32781)
END_MESSAGE_MAP()


// C任务管理器Dlg 消息处理程序 卡不卡?好像有点卡,我 这里不卡..哈哈,那怎么回事那我换个热点= =嗯嗯 好多了
//go~en ,我就没管界面这些了,直接弄了个暴力的...哈哈哈哈哈这个  哇,牛逼啊,粗暴的很,我看他们的都有好看的界面啊,,,但是我不想写啊哈哈.哈哈,好看的界面没用
// 我猜想是不是拿不到32位进程信息?不晓得啊..

BOOL C任务管理器Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_menu);

	//************************************
	BOOL b = RegisterHotKey(m_hWnd, 0x1234, MOD_CONTROL | MOD_ALT, 'h');
	if (!b)
		MessageBox(L"注册失败", L"提示", 0);
	//************************************

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C任务管理器Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C任务管理器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C任务管理器Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CProcessDLG* proDlg = new CProcessDLG;
	proDlg->Create(IDD_DIALOG1);
	proDlg->ShowWindow(SW_SHOW);
}


void C任务管理器Dlg::OnBnClickedButton2()
{

	// TODO: 在此添加控件通知处理程序代码
	CWndDlg* wndDlg = new CWndDlg;
	wndDlg->Create(IDD_DIALOG_WND);
	wndDlg->ShowWindow(SW_SHOW);
}


void C任务管理器Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CModuleDlg* moduleDlg = new CModuleDlg;
	moduleDlg->Create(IDD_DIALOG2);
	moduleDlg->ShowWindow(SW_SHOW);
}


void C任务管理器Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CHeapDlg* heapDlg = new CHeapDlg;
	heapDlg->Create(IDD_DIALOG3);
	heapDlg->ShowWindow(SW_SHOW);
}


void C任务管理器Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDlg* fDlg = new CFileDlg;
	fDlg->Create(IDD_DIALOG4);
	fDlg->ShowWindow(SW_SHOW);
}


void C任务管理器Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CThreadDlg* thDlg = new CThreadDlg;
	thDlg->Create(IDD_DIALOG5);
	thDlg->ShowWindow(SW_SHOW);
}


void C任务管理器Dlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	MEMORYSTATUS ms{};
	GlobalMemoryStatus(&ms);
	//内存占用率
	DWORD dwLoad = ms.dwMemoryLoad;
	CString str;
	str.Format(L"%d", dwLoad);
	MessageBox(L"当前内存占用率为:" + str + L"%", L"提示", 0);
}


void C任务管理器Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	int cpuLoad = getCpuLoad();
	CString str;
	str.Format(L"%d", cpuLoad);
	MessageBox(L"当前CPU占用率为:" + str + L"%", L"提示", 0);
}

double C任务管理器Dlg::FILETME2Double(const _FILETIME& fileTime)
{
	return double(fileTime.dwHighDateTime * 4.294967296e9) + double(fileTime.dwLowDateTime);
}

int C任务管理器Dlg::getCpuLoad()
{
	_FILETIME idleTime, kernelTime, userTime;
	GetSystemTimes(&idleTime, &kernelTime, &userTime);
	HANDLE hEvent = CreateEvent(0, FALSE, FALSE, 0);
	WaitForSingleObject(hEvent, 1000);
	CloseHandle(hEvent);
	_FILETIME newIdleTime, newKernelTime, newUserTime;
	GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);
	double idle_Time = FILETME2Double(idleTime);
	double new_IdleTime = FILETME2Double(newIdleTime);
	double kernel_Time = FILETME2Double(kernelTime);
	double new_KernelTime = FILETME2Double(newKernelTime);
	double user_Time = FILETME2Double(userTime);
	double new_UserTime = FILETME2Double(newUserTime);

	return int(100.0 - (new_IdleTime - idle_Time) / (new_KernelTime + new_UserTime - kernel_Time - user_Time) * 100);
}


void C任务管理器Dlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	CCleanDlg* cDlg = new CCleanDlg;
	cDlg->Create(IDD_DIALOG6);
	cDlg->ShowWindow(SW_SHOW);
	
}


void C任务管理器Dlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void C任务管理器Dlg::onClickMenuProcess()
{
	// TODO: 在此添加命令处理程序代码
}


void C任务管理器Dlg::onClickMenuOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog fDlg(TRUE);
	fDlg.DoModal();
	CString path = fDlg.GetPathName();
	if (!wcslen(path))
		return;
	STARTUPINFO si{};
	PROCESS_INFORMATION pi{};
	CreateProcess(path, 0, 0, 0, 0, 0, 0, 0, &si, &pi);
}


BOOL C任务管理器Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_HOTKEY && pMsg->wParam == 0x1234)
	{
		if (::IsWindowVisible(m_hWnd) == TRUE)
			ShowWindow(SW_SHOW);
		else
			ShowWindow(SW_HIDE);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void C任务管理器Dlg::onClickMenuShutdown()
{
	// TODO: 在此添加命令处理程序代码
	adjustPrivilege();
	int nRes = MessageBox(L"确定要关闭计算机?", L"警告", MB_YESNO);
	if (IDNO == nRes)
		return;
	ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0);
}
void C任务管理器Dlg::adjustPrivilege()
{
	HANDLE hToken = NULL;
	HANDLE hPro = GetCurrentProcess();
	OpenProcessToken(hPro, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	TOKEN_PRIVILEGES tp{};
	LookupPrivilegeValue(0, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid);
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
}

void C任务管理器Dlg::OnClickLock()
{
	// TODO: 在此添加命令处理程序代码
	adjustPrivilege();
	LockWorkStation();
}


void C任务管理器Dlg::OnClickRestart()
{
	// TODO: 在此添加命令处理程序代码
	adjustPrivilege();
	int nRes = MessageBox(L"确定要重启计算机?", L"警告", MB_YESNO);
	if (IDNO == nRes)
		return;
	ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
}


void C任务管理器Dlg::On32781()
{
	// TODO: 在此添加命令处理程序代码
	adjustPrivilege();
	int nRes = MessageBox(L"确定要注销吗?", L"警告", MB_YESNO);
	if (IDNO == nRes)
		return;
	ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, 0);
}
