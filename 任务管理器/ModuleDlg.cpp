// ModuleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������.h"
#include "ModuleDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#include <PSAPI.H>

// CModuleDlg �Ի���

IMPLEMENT_DYNAMIC(CModuleDlg, CDialogEx)

CModuleDlg::CModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_edit(0)
{

}

CModuleDlg::~CModuleDlg()
{
}

void CModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_moduleList);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CModuleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CModuleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CModuleDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CModuleDlg ��Ϣ�������


BOOL CModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_moduleList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_moduleList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 80);
	m_moduleList.InsertColumn(1, _T("ģ��·��"), LVCFMT_CENTER, 300);
	m_moduleList.InsertColumn(2, _T("ģ���С"), LVCFMT_CENTER, 140);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
void CModuleDlg::showAllModule()
{
	HANDLE hProcess = NULL;
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, m_edit);
	if (!hProcess)
	{
		MessageBox(_T("��ȡ���̾��ʧ��"));
		return;
	}
	//��ȡ�ý�������ģ����
	//��Щ������㲻��ԭ��,��������ôȥ��..����,�������API,û��ʲôԭ���,�������ŵ��þͺ���.Ҫ˵ԭ��,���ǽ��������кܶ�ģ��.������~
	//����,�ǰ� 32λ��64λ���ܻ���,64λ��Ҳ���ܲ�32�İ�?��,�Բ�,�������API��Ƶ���ٵ�.��ʦ��������64λ��,����Ϊ64λϵͳ����64λ���̶�,���Լ����Ƕ����Բ�.
	//�����Ҳ��������Щģ�鶼��64λ��?����,���Ǻö������ʾ��ʲô32.dll��.����,��һ��64λ��dll,���ֽ�**_32.dll.������,��32λ�Ľ�ʲô����Ŷ..��Ҫ�������Ի���
	//C:\Program Files C:\Windows\System32 ���Ŀ¼�¶���64λ��,�����ж�ö඼��32
	//C:\Windows\SysWOW64 ���Ŀ¼����32λdll���ڵ�Ŀ¼
	//��ȡ�����в���,����һ��Ŀ����,�Ժ�ȥд��ЩAPI,Ȼ�������ȫ��ȡ���Ĵ��� ����
	//������һƪ��д���������.
	//����д���е��,,������װ
	//https://github.com/rwfpl/rewolf-wow64ext  ��������ṩ�˷���,����ʵ��32λ��64λ����.��ʱ�侫�����Կ�һ�����Ĵ���.Ҫ��
	//It enables x86 applications to read, write and enumerate memory of a native x64 applications.  �������,�Ϳ��԰ѳ�������32λ��,Ȼ�����е�32λ��64λ�����Բ���.
	//����ʵʱ����İ�,����,���ǰ�..��ö�Ӣ���������, ����,�࿴���ͺ���,.��һЩ��רҵ�ʻ�.Ҫ��,��ȥ�о��о���ˣ.��,��������������ϵͳ��ʵ�ֻ���,��������װ��һ���ӿ�.ͦ������.����ϵͳ����
	//ԭ����ͽ�ͻ��ϵͳ���ư�,����˵����ϵͳֻ�ṩ����Щ�ӿ�,��Ҫ�Ǹ��������Щ���нӿڱ����ԭ��,�Ϳ���������Ӷ�����װ���Լ��Ľӿ�?�ǰ� �ǰ�.
	//windows�ܶ��ĵ�,�ܶ���������,ֻ���ݹٷŻ�����յ��.���Լ���һЩ�����õĺ�ˬ,���ǲ��Ὺ�Žӿڸ����.�ĵ�Ҳû��.����,������˾͸�����.
	//ԭ�������ǲ�ˬwindows����,����  ����,д��ҵ�,���ƽ��,����վ��,,�������ֲ�ˬ��������,������,�Բ�,��Ҳ������һԱ��,��ʲô��ˬ����˵����,���㿪������ ����.
	//�������дһ������,дһ���ٵķ�����,Ȼ��ͻ��˲�֪���Ǽٵ�,�������������ĵ��Զ���֪������ôһ��������.
	/*
	TCP    0.0.0.0:135            0.0.0.0:0              LISTENING
	TCP    0.0.0.0:445            0.0.0.0:0              LISTENING
	TCP    0.0.0.0:1536           0.0.0.0:0              LISTENING
	TCP    0.0.0.0:1537           0.0.0.0:0              LISTENING
	TCP    0.0.0.0:1538           0.0.0.0:0              LISTENING
	TCP    0.0.0.0:1539           0.0.0.0:0              LISTENING
	TCP    0.0.0.0:1540           0.0.0.0:0              LISTENING
	TCP    0.0.0.0:1541           0.0.0.0:0              LISTENING
	TCP    0.0.0.0:1542           0.0.0.0:0              LISTENING
	TCP    0.0.0.0:5040           0.0.0.0:0              LISTENING
	TCP    0.0.0.0:7680           0.0.0.0:0              LISTENING
	TCP    0.0.0.0:49152          0.0.0.0:0              LISTENING
	TCP    0.0.0.0:49153          0.0.0.0:0              LISTENING
	TCP    0.0.0.0:49154          0.0.0.0:0              LISTENING
	TCP    0.0.0.0:49155          0.0.0.0:0              LISTENING
	��Щ�˿������������Ϊ������,���е�server����,Ȼ��ȴ�����������.
	���д��һ����,���￴�����˿ڵ�,û�ж˿�.
	��..�������,�㶼������?����,��������..����..��ʵ������и���������,ֻ�������м���?��ʵ��û������ϵͳ�ṩ��api,�Լ�ʵ����һ��������.����ϵͳ������.ʵ����tcpЭ��.
	����?û�а�,�ҿ�û������,����,��ܳ,����������ڶ���̫�����˰����Ѻ�.��ʵ����,����֪ʶ���е��.��������,��,�������������..������,,���������������ȥ,Ȼ���Լ����ͻ���
	����ȥ������?��.����.Ȼ��������֪������ȥ��.����,������ţ����,����һ��T����Դ����������.����
	����,��Ҫȥ���о���,ÿ��������˵��Щ����ֵֹĶ���,���������ǼӸ��о����������.����,˵����Ҳ�����˶�,,,�Ƚ������.Ҫ��Ҫ�� 
	����.��Ҫ��.΢����˵��
	����,88
	*/
	HMODULE hModules[0x2000]{};
	DWORD dwNeed = 0;
	BOOL bRet = EnumProcessModulesEx(hProcess, hModules, sizeof(hModules), &dwNeed, LIST_MODULES_ALL);
	DWORD dwModuleCnt = dwNeed / sizeof(HMODULE);
	MODULEINFO mi{};
	TCHAR tBuf[128]{};
	CString	str;
	m_moduleList.DeleteAllItems();
	for (UINT i = 0; i < dwModuleCnt; i++)
	{
		GetModuleFileNameEx(hProcess, hModules[i], tBuf, _countof(tBuf));
		GetModuleInformation(hProcess, hModules[i], &mi, sizeof(MODULEINFO));
		str.Format(L"%d", i + 1);
		m_moduleList.InsertItem(i, _T(""));
		m_moduleList.SetItemText(i, 0, str);
		m_moduleList.SetItemText(i, 1, tBuf);
		str.Format(L"%dKB", mi.SizeOfImage / 1024);
		m_moduleList.SetItemText(i, 2, str);
	}
}
//��ƭ��..ƭ��ɶ�Ӱ�.�����õ�ģ�鰡.�����ʼ����32λ�����,ɶ�Ӷ�û��,Ȼ����ʦ˵����64��,������32

void CModuleDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}


void CModuleDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	showAllModule();
}
