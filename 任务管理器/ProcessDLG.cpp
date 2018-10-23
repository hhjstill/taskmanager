// ProcessDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "ProcessDLG.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

// CProcessDLG �Ի���

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


// CProcessDLG ��Ϣ�������


BOOL CProcessDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_processList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_processList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 80);
	m_processList.InsertColumn(1, _T("������"), LVCFMT_CENTER, 300);
	m_processList.InsertColumn(2, _T("PID"), LVCFMT_CENTER, 140);
	//��ʾ���н���
	showAllProcess();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
//��ʾ���н��� �������6112��һ��32λ����,�е� �е�.32λ��64λ����,,���Ǹо�������������������Щ��
void CProcessDLG::showAllProcess()
{
	//��������32λ��,û��64 ��.���ǵ�.
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
//����ѡ�н��� û����,����.���԰���pid�Ÿ���,Ȼ��һ��һ���Ա�,��,����,�и����̶���ʲô�����.���Ƿ����ڴ��.CreateHeap,���API�ͻ�Ϊ���̴�����.���Ǹ���̬�����ڴ�Ķ�������
//�������ÿ������֮�仹�Ƕ����İ�?�ǵ�.ÿһ�����̶���4G�Ŀռ�(32λ����),�Ƕ�����...�����������,,�����CPU��ʱ�й���û�а�.
//��������ô����ÿ�����̶���4G��Ŷ..����,���������ϸ����<windows�ں��龰����>������  ë�²�?����������ü� ����
//��ͷ,������������Ҫ������������,����Ķ���,������,��� ����  �������������.
//�������������һ�����,�ȸ���˵,�����������,���������������ÿ���ţ�ƵĶ�.
//Ŀǰ����������Ǳ����x64��,�����64λ,ȥ��ѯ32λ���̵�ģ���ʱ���鲻��.
//��������32λ�ĳ���,����64λ�Ľ���ģ��..�ұ����32λ��32λ���鲻����..����,�����bug,������api�ĵ��ǲ�õ���.32λ��64λ���ܻ�����ϵͳ����.
//˵���Կ�ʹ,�������ǰ������ϸ�������...�㿴���ģ���������..
void CProcessDLG::exitSelProcess(UINT nChoice)
{
	//�õ�ѡ�н���ID
	TCHAR tBuf[32]{};
	m_processList.GetItemText(nChoice - 1, 2, tBuf, _countof(tBuf));
	int nPid = -1;
	swscanf_s(tBuf, L"%d", &nPid);
	//��������
	HANDLE hPro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, nPid);
	if (!hPro)
	{
		//MessageBox(_T("��ȡ���̾��ʧ��"));
		return;
	}
	TerminateProcess(hPro, 0);
	CloseHandle(hPro);
	//������ʾ����
	Sleep(1);
	m_processList.DeleteAllItems();
	showAllProcess();
}


void CProcessDLG::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos;
	pos = m_processList.GetFirstSelectedItemPosition();
	int nChoice = (int)pos;
	if (nChoice == 0)
	{
		MessageBox(_T("����ѡ��һ��"));
		return;
	}
	exitSelProcess(nChoice);
}


void CProcessDLG::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}


//void CProcessDLG::OnRButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	MessageBox(L"right");
//}


//void CProcessDLG::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//	TrackPopupMenu(,)
//}
