
// ���������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "���������Dlg.h"
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


// C���������Dlg �Ի���



C���������Dlg::C���������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C���������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C���������Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C���������Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C���������Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C���������Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C���������Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C���������Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C���������Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &C���������Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &C���������Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &C���������Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &C���������Dlg::OnBnClickedButton11)
	ON_COMMAND(ID_32773, &C���������Dlg::onClickMenuProcess)
	ON_COMMAND(ID_32771, &C���������Dlg::onClickMenuOpen)
	ON_COMMAND(ID_32779, &C���������Dlg::onClickMenuShutdown)
	ON_COMMAND(ID_32782, &C���������Dlg::OnClickLock)
	ON_COMMAND(ID_32780, &C���������Dlg::OnClickRestart)
	ON_COMMAND(ID_32781, &C���������Dlg::On32781)
END_MESSAGE_MAP()


// C���������Dlg ��Ϣ������� ������?�����е㿨,�� ���ﲻ��..����,����ô�������һ����ȵ�= =���� �ö���
//go~en ,�Ҿ�û�ܽ�����Щ��,ֱ��Ū�˸�������...�������������  ��,ţ�ư�,�ֱ��ĺ�,�ҿ����ǵĶ��кÿ��Ľ��氡,,,�����Ҳ���д������.����,�ÿ��Ľ���û��
// �Ҳ����ǲ����ò���32λ������Ϣ?�����ð�..

BOOL C���������Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_menu);

	//************************************
	BOOL b = RegisterHotKey(m_hWnd, 0x1234, MOD_CONTROL | MOD_ALT, 'h');
	if (!b)
		MessageBox(L"ע��ʧ��", L"��ʾ", 0);
	//************************************

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C���������Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C���������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C���������Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CProcessDLG* proDlg = new CProcessDLG;
	proDlg->Create(IDD_DIALOG1);
	proDlg->ShowWindow(SW_SHOW);
}


void C���������Dlg::OnBnClickedButton2()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWndDlg* wndDlg = new CWndDlg;
	wndDlg->Create(IDD_DIALOG_WND);
	wndDlg->ShowWindow(SW_SHOW);
}


void C���������Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CModuleDlg* moduleDlg = new CModuleDlg;
	moduleDlg->Create(IDD_DIALOG2);
	moduleDlg->ShowWindow(SW_SHOW);
}


void C���������Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CHeapDlg* heapDlg = new CHeapDlg;
	heapDlg->Create(IDD_DIALOG3);
	heapDlg->ShowWindow(SW_SHOW);
}


void C���������Dlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDlg* fDlg = new CFileDlg;
	fDlg->Create(IDD_DIALOG4);
	fDlg->ShowWindow(SW_SHOW);
}


void C���������Dlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CThreadDlg* thDlg = new CThreadDlg;
	thDlg->Create(IDD_DIALOG5);
	thDlg->ShowWindow(SW_SHOW);
}


void C���������Dlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MEMORYSTATUS ms{};
	GlobalMemoryStatus(&ms);
	//�ڴ�ռ����
	DWORD dwLoad = ms.dwMemoryLoad;
	CString str;
	str.Format(L"%d", dwLoad);
	MessageBox(L"��ǰ�ڴ�ռ����Ϊ:" + str + L"%", L"��ʾ", 0);
}


void C���������Dlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int cpuLoad = getCpuLoad();
	CString str;
	str.Format(L"%d", cpuLoad);
	MessageBox(L"��ǰCPUռ����Ϊ:" + str + L"%", L"��ʾ", 0);
}

double C���������Dlg::FILETME2Double(const _FILETIME& fileTime)
{
	return double(fileTime.dwHighDateTime * 4.294967296e9) + double(fileTime.dwLowDateTime);
}

int C���������Dlg::getCpuLoad()
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


void C���������Dlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCleanDlg* cDlg = new CCleanDlg;
	cDlg->Create(IDD_DIALOG6);
	cDlg->ShowWindow(SW_SHOW);
	
}


void C���������Dlg::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}


void C���������Dlg::onClickMenuProcess()
{
	// TODO: �ڴ���������������
}


void C���������Dlg::onClickMenuOpen()
{
	// TODO: �ڴ���������������
	CFileDialog fDlg(TRUE);
	fDlg.DoModal();
	CString path = fDlg.GetPathName();
	if (!wcslen(path))
		return;
	STARTUPINFO si{};
	PROCESS_INFORMATION pi{};
	CreateProcess(path, 0, 0, 0, 0, 0, 0, 0, &si, &pi);
}


BOOL C���������Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_HOTKEY && pMsg->wParam == 0x1234)
	{
		if (::IsWindowVisible(m_hWnd) == TRUE)
			ShowWindow(SW_SHOW);
		else
			ShowWindow(SW_HIDE);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void C���������Dlg::onClickMenuShutdown()
{
	// TODO: �ڴ���������������
	adjustPrivilege();
	int nRes = MessageBox(L"ȷ��Ҫ�رռ����?", L"����", MB_YESNO);
	if (IDNO == nRes)
		return;
	ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0);
}
void C���������Dlg::adjustPrivilege()
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

void C���������Dlg::OnClickLock()
{
	// TODO: �ڴ���������������
	adjustPrivilege();
	LockWorkStation();
}


void C���������Dlg::OnClickRestart()
{
	// TODO: �ڴ���������������
	adjustPrivilege();
	int nRes = MessageBox(L"ȷ��Ҫ���������?", L"����", MB_YESNO);
	if (IDNO == nRes)
		return;
	ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
}


void C���������Dlg::On32781()
{
	// TODO: �ڴ���������������
	adjustPrivilege();
	int nRes = MessageBox(L"ȷ��Ҫע����?", L"����", MB_YESNO);
	if (IDNO == nRes)
		return;
	ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, 0);
}
