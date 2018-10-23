// ModuleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "任务管理器.h"
#include "ModuleDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#include <PSAPI.H>

// CModuleDlg 对话框

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


// CModuleDlg 消息处理程序


BOOL CModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_moduleList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_moduleList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 80);
	m_moduleList.InsertColumn(1, _T("模块路径"), LVCFMT_CENTER, 300);
	m_moduleList.InsertColumn(2, _T("模块大小"), LVCFMT_CENTER, 140);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CModuleDlg::showAllModule()
{
	HANDLE hProcess = NULL;
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, m_edit);
	if (!hProcess)
	{
		MessageBox(_T("获取进程句柄失败"));
		return;
	}
	//获取该进程所有模块句柄
	//这些玩意儿搞不懂原理,就晓得这么去用..哈哈,这个调用API,没有什么原理的,就是照着调用就好了.要说原理,就是进程里面有很多模块.哈哈哈~
	//哈哈,是吧 32位和64位不能互查,64位的也不能查32的啊?嗯,卧槽,这个吉尔API设计的真操蛋.老师让你编译成64位的,是因为64位系统里面64位进程多,所以假象是都可以查.
	//就是我查出来的这些模块都是64位的?嗯嗯,但是好多后面显示的什么32.dll嘛.哈哈,有一个64位的dll,名字叫**_32.dll.哈哈哈,那32位的叫什么名字哦..不要被名字迷惑了
	//C:\Program Files C:\Windows\System32 这个目录下都是64位的,但是有多好多都是32
	//C:\Windows\SysWOW64 这个目录才是32位dll所在的目录
	//这取名字有病啊,我有一个目标了,以后去写这些API,然后把名字全部取成四川话 哈哈
	//给你找一篇我写的这个文章.
	//好像写的有点简单,,劲霸男装
	//https://github.com/rwfpl/rewolf-wow64ext  这个工具提供了方法,可以实现32位和64位互查.有时间精力可以看一下他的代码.要得
	//It enables x86 applications to read, write and enumerate memory of a native x64 applications.  有了这个,就可以把程序编译成32位的,然后所有的32位和64位都可以查了.
	//还带实时翻译的啊,哈哈,不是啊..这好多英语早就忘了, 哈哈,多看看就好了,.有一些是专业词汇.要得,我去研究研究其耍.嗯,这个代码就是逆向系统的实现机制,最后把它封装了一个接口.挺厉害的.打破系统限制
	//原来这就叫突破系统限制啊,就是说本来系统只提供了这些接口,你要是搞清楚了这些已有接口背后的原理,就可以在上面加东西封装成自己的接口?是啊 是啊.
	//windows很恶心的,很多事情上面,只许州官放火不许百姓点灯.它自己用一些特性用的很爽,但是不会开放接口给你的.文档也没有.于是,逆向的人就干这事.
	//原来逆向是不爽windows的人,哈哈  哈哈,写外挂的,搞破解的,黑网站的,,都是这种不爽情绪爆棚,哈哈哈,卧槽,你也是其中一员啊,有什么不爽可以说出来,给你开导开导 哈哈.
	//我最近在写一个东西,写一个假的服务器,然后客户端不知道是假的,甚至连服务器的电脑都不知道有这么一个服务器.
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
	这些端口是你电脑上作为服务器,运行的server程序,然后等待别人来连接.
	最近写的一个是,这里看不到端口的,没有端口.
	啊..别个连了,你都看不到?嗯嗯,不明觉厉..哈哈..其实是真的有个服务器的,只是你再中间搞鬼?其实是没有依赖系统提供的api,自己实现了一个服务器.所以系统看不见.实现了tcp协议.
	断了?没有啊,我看没动静了,哈哈,我艹,这玩意儿现在对我太高深了啊不友好.其实不难,不过知识点有点多.慢慢来嘛,嗯,这个东西是拿来..我想象,,是整到别个电脑上去,然后自己当客户端
	连上去搞事情?嗯.哈哈.然后他并不知道连上去了.哈哈,这样就牛逼了,把它一个T的资源都拷出来啊.哈哈
	哈哈,我要去搞研究了,每次听到你说这些奇奇怪怪的东西,都有种尿涨加搞研究的心情哈哈.哈哈,说的我也尿涨了额,,,先解决了账.要得要得 
	闪了.嗯要得.微信上说嘛
	嗯呢,88
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
//你骗我..骗你啥子啊.可以拿到模块啊.可是最开始我是32位编译的,啥子都没得,然后老师说换成64的,那试试32

void CModuleDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void CModuleDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	showAllModule();
}
