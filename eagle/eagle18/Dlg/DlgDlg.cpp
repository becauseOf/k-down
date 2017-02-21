// DlgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg.h"
#include "DlgDlg.h"
#include "Feedback.h"
#include "NewAssignment.h"
#include "PrivacyDialog.h"
#include "PrivacyPassword.h"
#include "Setting.h"
#include "Search.h"
#include"SolveCode.h"
#include"SetIP.h"
#include"getMD5.h"
//#include "TipDelete.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDlgDlg 对话框




CDlgDlg::CDlgDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDlgDlg::IDD, pParent)
, m_pGetSocket(NULL)
, m_pSendSocket(NULL)
, m_csServerIP(_T(""))
, m_csIP(_T(""))
, m_csMAC(_T(""))
, m_pSearch(NULL)
, m_pGiveSocket(NULL)
, m_bDownloading(false)
, m_csGiveFilePath(_T(""))
, m_csSaveFilePath(_T(""))
, m_csSaveFileName(_T(""))
, m_iCount(0)
, m_bFinish(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_csServerIP=_T("127.0.0.1");
}

void CDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_MISSION, m_listShow);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOADPROGRESS, progress);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDC_BUTTON_SETTING, m_btnSet);
	DDX_Control(pDX, IDC_BUTTON_FEEDBACK, m_btnFeedback);
	DDX_Control(pDX, IDC_BUTTON_UPLOAD, m_btnUpload);
	DDX_Control(pDX, IDC_BUTTON_SETIP, m_btnIP);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_btnPause);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BUTTON_MYDOWNLOAD, m_btnMy);
	DDX_Control(pDX, IDC_BUTTON_NOWDOWNLOAD, m_btnNow);
	DDX_Control(pDX, IDC_BUTTON_PRIVACY, m_btnPrivacy);
	DDX_Control(pDX, IDC_BUTTON_RECYCLEBIN, m_btnCan);
	DDX_Control(pDX, IDC_BUTTON1, m_btnProgress);
}

BEGIN_MESSAGE_MAP(CDlgDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CDlgDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_FEEDBACK, &CDlgDlg::OnBnClickedButtonFeedback)
	ON_BN_CLICKED(IDC_BUTTON_PRIVACY, &CDlgDlg::OnBnClickedButtonPrivacy)
	ON_BN_CLICKED(IDC_BUTTON_NEWASSIGNMENT, &CDlgDlg::OnBnClickedButtonNewassignment)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgDlg::OnBnClickedButtonDelete)

	ON_BN_CLICKED(IDC_BUTTON_START, &CDlgDlg::OnBnClickedButtonStart)
	//	ON_BN_CLICKED(IDC_BUTTON1, &CDlgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_NOWDOWNLOAD, &CDlgDlg::OnBnClickedButtonNowdownload)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CDlgDlg::OnBnClickedButtonUpload)
	ON_BN_CLICKED(IDC_BUTTON_SETIP, &CDlgDlg::OnBnClickedButtonSetip)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CDlgDlg::OnBnClickedButtonPause)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_RECYCLEBIN, &CDlgDlg::OnBnClickedButtonRecyclebin)
END_MESSAGE_MAP()


// CDlgDlg 消息处理程序

BOOL CDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//设置背景图片
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_BK2);
	m_brBK.CreatePatternBrush(&bmp);
	bmp.DeleteObject();

	//搜索按钮
	m_btnSearch.SetIcon(IDI_ICON_SEARCH2,IDI_ICON_SEARCH1);
	m_btnSearch.DrawTransparent(TRUE);

	//设置按钮
	m_btnSet.SetIcon(IDI_ICON_SET2,IDI_ICON_SET1);
	m_btnSet.DrawTransparent(TRUE);

	//反馈按钮
	m_btnFeedback.SetIcon(IDI_ICON_FEEDBACK2,IDI_ICON_FEEDBACK);
	m_btnFeedback.DrawTransparent(TRUE);

	//上传按钮
	m_btnUpload.SetIcon(IDI_ICON_UPLOAD2,IDI_ICON_UPLOAD1);
	m_btnUpload.DrawTransparent(TRUE);

	//设置IP按钮
	m_btnIP.SetIcon(IDI_ICON_IP2,IDI_ICON_IP1);
	m_btnIP.DrawTransparent(TRUE);

	//开始按钮
	m_btnStart.SetIcon(IDI_ICON_START1,IDI_ICON_OK);
	m_btnStart.DrawTransparent(TRUE);

	//暂停按钮
	m_btnPause.SetIcon(IDI_ICON_PAUSE1,IDI_ICON_PAUSE2);
	m_btnPause.DrawTransparent(TRUE);

	//删除按钮
	m_btnDelete.SetIcon(IDI_ICON_DELETE2,IDI_ICON_DELETE1);
	m_btnDelete.DrawTransparent(TRUE);

	//我的下载按钮
	m_btnMy.SetIcon(IDI_ICON_MY);
	m_btnMy.DrawTransparent(TRUE);

	//正在下载按钮
	m_btnNow.SetIcon(IDI_ICON_NOW);
	m_btnNow.DrawTransparent(TRUE);

	//隐私空间按钮
	m_btnPrivacy.SetIcon(IDI_ICON_PRIVACY);
	m_btnPrivacy.DrawTransparent(TRUE);

	//回收站按钮
	m_btnCan.SetIcon(IDI_ICON_CAN);
	m_btnCan.DrawTransparent(TRUE);

	//下载进度按钮
	m_btnProgress.DrawTransparent(TRUE);
	m_btnProgress.DrawBorder(FALSE);


	//为人物列表添加行头
	m_listShow.InsertColumn(1,_T("文件名"),0,200,-1);
	m_listShow.InsertColumn(2,_T("文件大小"),0,68,-1);
	m_listShow.InsertColumn(3,_T("进度"),0,68,-1);
	m_listShow.InsertColumn(4,_T("速度"),0,90,-1);
	// 为列表视图控件添加全行选中和栅格风格   
	m_listShow.SetExtendedStyle(m_listShow.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	m_bDownloading = false;
	//获取默认保存的路径
	GetPrivateProfileString(_T("DownloadPath"),_T("DownloadPath"),_T(""),m_csSaveFilePath.GetBuffer(MAX_PATH),MAX_PATH,_T("..//DownloadPath.xiangsong"));
	m_bFinish = false;
	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDlgDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//进入设置界面
void CDlgDlg::OnBnClickedButtonSetting()
{
	CSetting set2;
	set2.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
//进入反馈界面
void CDlgDlg::OnBnClickedButtonFeedback()
{
	CFeedback feedback;
	feedback.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgDlg::OnBnClickedButtonPrivacy()
{
	CPrivacyDialog privacy;
	privacy.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
//新建任务，已经不需要这个函数了
void CDlgDlg::OnBnClickedButtonNewassignment()
{
	INT_PTR iRes;
	CNewAssignment new1;
	iRes = new1.DoModal();
	if(iRes == IDCANCEL)
	{
		return;
	}
	//获取新建任务的文件名
	CString newFileName = new1.m_csFileName;
	//测试用
	m_csFilePath=new1.m_csDownloadPath+_T("1.zip");

	//获取当前行数
	int nRowCount = m_listShow.GetItemCount();
	LPCTSTR fileSize;
	fileSize = _T("8TB");

	m_listShow.InsertItem(nRowCount,newFileName);//第一个参数是从0开始的
	m_listShow.SetItemText(nRowCount,1,fileSize);//第一个参数同上，第二个参数是列数，也是从0开始的

	// TODO: 在此添加控件通知处理程序代码
}
//删除任务
void CDlgDlg::OnBnClickedButtonDelete()
{
	/*	INT_PTR iRes;
	CTipDelete tip;
	iRes = tip.DoModal();
	if(iRes == IDCANCEL)
	{
	return;
	}
	*/
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR iRes;
	iRes = MessageBox(_T("确定删除任务？"),_T("提示"),MB_OKCANCEL|MB_ICONQUESTION);
	if(iRes == IDCANCEL)
		return;
	//删除列表中的项
	//首先得到有多少行
	int nRowCount = m_listShow.GetItemCount();
	//没有行就不用删
	if(nRowCount < 1)
		return;

	//没选中也不删
	POSITION pos = m_listShow.GetFirstSelectedItemPosition();
	if(pos == NULL){
		AfxMessageBox(_T("未选中！"));
		return;
	}
	/*//删除一条记录
	m_listShow.DeleteItem(int(pos)-1);
	*/
	//遍历选中记录并删除，不能从前面开始删除，要从后面哦
	for(int i = nRowCount-1; i >= 0;i--){
		if(m_listShow.GetItemState(i,LVIS_SELECTED))
			m_listShow.DeleteItem(i);
	}
	//如果正在下载，则断开连接
	if(m_bDownloading)
	{
		m_pGetSocket->Close();
	}

}

// 用于接收socket消息，消息可以是文件、请求等……
void CDlgDlg::RevMsg(CSendSocket* pSocket)
{
	STRUCT_MSG revMsg;
	memset(&revMsg,0,sizeof(revMsg));
	pSocket->Receive((char*)&revMsg,sizeof(revMsg)+1);

	switch(revMsg.iMsgType)
	{
		//收到的是文件内容
	case MT_SENDFILE:
		{
			CFile file;
			if(!file.Open(m_csSaveFilePath+m_csSaveFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite)){
				AfxMessageBox(_T("读入文件失败！"));
				return;
			}
			file.Seek(revMsg.iIndex * SEND_BLOCK,CFile::begin);
			file.Write(revMsg.cFileContent,revMsg.iFileSize); 
			bBlock[revMsg.iIndex]='1';
			file.Close();
			progress.SetPos(revMsg.iIndex); //设置当前进度条的位置
			AskForFile();
			break;
		}
		//收到的是要求发送的文件块的偏移量
	case MT_SENDFILE_REQUEST:
		{
			CFile file;
			if(!file.Open(m_csGiveFilePath,CFile::modeRead))
			{
				AfxMessageBox(_T("读入文件失败！"));
				return;
			}
			STRUCT_MSG sendMsg;
			memset(&sendMsg,0,sizeof(sendMsg));
			sendMsg.iMsgType = MT_SENDFILE;
			sendMsg.iIndex = revMsg.iIndex;


			file.Seek(sendMsg.iIndex * SEND_BLOCK,CFile::begin);

			int iSize = file.Read(sendMsg.cFileContent,SEND_BLOCK);
			sendMsg.iFileSize = iSize;
			pSocket->Send((char*)&sendMsg,sizeof(sendMsg)+1);
			file.Close();
			Sleep(10);
			break;
		}
		/*//收到的是传文件初始化要求
		case MT_SENDFILE_INIT:
		{
		bBlock = new bool[revMsg.iCount];
		for(int i =0 ; i <revMsg.iCount ; i++)
		bBlock[i]=false;
		iCount = revMsg.iCount;
		break;
		}*/
		//收到的是搜索返回的文件列表
	case MT_SEARCH_RETURN:
		{
			int iZiYuanShu = revMsg.iCount;
			int iFileSize = revMsg.iFileSize;
			CString csFileSize;
			csFileSize.Format(_T("%d"),iFileSize);
			CString csZiYuanShu;
			csZiYuanShu.Format(_T("%d"),iZiYuanShu);
			CString csFileName = CA2W(revMsg.cFileName);
			CString csMD5 = CA2W(revMsg.cMD5);
			int iRow = m_pSearch->m_SearchList.GetItemCount();
			//添加列表
			m_pSearch->m_SearchList.InsertItem(iRow,csFileName);
			m_pSearch->m_SearchList.SetItemText(iRow,1,csFileSize);
			m_pSearch->m_SearchList.SetItemText(iRow,2,csZiYuanShu);
			m_pSearch->m_SearchList.SetItemText(iRow,3,csMD5);
			break;
		}
	case MT_GIVEFILE:
		{
			CString csIP = CA2W(revMsg.cIP);

			//AfxMessageBox(csIP);//测试用
			m_pGiveSocket = new CSendSocket(this);
			m_pGiveSocket->Create();
			if(!m_pGiveSocket->Connect(csIP,MYPORT))
			{
				AfxMessageBox(_T("连接接收文件客户端失败！"));
				return;
			}
			//之后就开始发文件了
			//保存要发送文件的路径
			GetPrivateProfileString(CA2W(revMsg.cMD5),_T("FilePath"),_T(""),m_csGiveFilePath.GetBuffer(MAX_PATH),MAX_PATH,_T("..//Upload.wrc"));
			AfxMessageBox(_T("给")+csIP+_T("发")+m_csGiveFilePath);
			break;
		}
	}

}

// 有用户下线了，将其从链表中删除并释放内存，及反馈给服务器
void CDlgDlg::ClientQuit(CSendSocket* pSocket)
{
}


// 用于接受客户端连接，并创建对应Socket，并添加至链表
void CDlgDlg::AddClient(void)
{
	CSendSocket* pSocket = new CSendSocket(this);
	if(!m_pGetSocket->Accept(*pSocket)){
		AfxMessageBox(_T("连接客户端失败！"));
		delete pSocket;
		pSocket = NULL;
	}else{
		m_listClient.AddTail(pSocket);
		//AfxMessageBox(_T("成功接入客户端！"));
		//在这里就可以向各个客户端askforfile了
		AskForFile();
		m_bDownloading= true;
	}
}

// 创建服务器Socket，设置端口并开始监听
bool CDlgDlg::CreateServer(void)
{
	//创建Socket
	m_pGetSocket = new CGetSocket(this);
	//创建服务
	if(!m_pGetSocket->Create(MYPORT)){
		AfxMessageBox(_T("创建服务器失败！"));
		return false;
	}


	//监听
	m_pGetSocket->Listen();
	return true;
}

void CDlgDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//如果正在下载，则不作任何改变
	if(m_bDownloading)
	{
		return;
	}
	//如果不在下载，则读取文件名、MD5以及块数，然后发送给服务器请求下载
	CString csCount;
	GetPrivateProfileString(_T("Downloading"),_T("FileName"),_T(""),m_csSaveFileName.GetBuffer(MAX_PATH),MAX_PATH,_T("..\\Downloading.lyt"));
	GetPrivateProfileString(_T("Downloading"),_T("MD5"),_T(""),m_csMD5.GetBuffer(MAX_PATH),MAX_PATH,_T("..\\Downloading.lyt"));
	GetPrivateProfileString(_T("Downloading"),_T("Count"),_T(""),csCount.GetBuffer(MAX_PATH),MAX_PATH,_T("..\\Downloading.lyt"));
	m_iCount = _ttoi(csCount);
	if ( m_csSaveFileName!=_T("") )
	{
		//重新开始服务器
		CreateServer();
		STRUCT_MSG downloadMsg;
		memset(&downloadMsg,0,sizeof(downloadMsg));
		downloadMsg.iMsgType = MT_DOWNREQUEST;
		GetIP(m_csIP);
		CStringToCharP(m_csIP,downloadMsg.cIP);
		CStringToCharP(m_csMD5,downloadMsg.cMD5);//传MD5是让服务器的数据库搜索相应数据
		CFile file;
		file.Open(m_csSaveFilePath + m_csMD5 , CFile::modeRead);
		file.Read(bBlock,m_iCount);
		file.Close();
		//初始化进度条
		progress.SetRange(0,m_iCount);//设定进度条开始位置和结束位置,这里的设置并不十分合理，因为参数是short，所以最多只能分65535块
		progress.SetStep(1);//设定每次增加的大小	
		m_pSendSocket->Send((char*)&downloadMsg,sizeof(downloadMsg)+1);
	}
}

//搜索
void CDlgDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	CSearch s(this);
	m_pSearch = &s;
	m_pSearch->DoModal();
}
//已经不需要这个函数了
void CDlgDlg::OnBnClickedButtonNowdownload()
{
	// TODO: 在此添加控件通知处理程序代码
	//下面的注释是测试所用，测试失败……
	/*m_pSendSocket = m_listClient.GetHead();
	//m_listShow.DeleteAllItems();
	STRUCT_MSG init;
	init.iMsgType = MT_SENDFILE_INIT;
	CFile file;
	file.Open(m_csFilePath,CFile::modeRead);

	init.iCount = (DWORD)file.GetLength()/SEND_BLOCK;
	m_pSendSocket->Send((char*)&init,sizeof(init)+1);
	STRUCT_MSG first;
	first.iMsgType = MT_SENDFILE_REQUEST;
	first.iIndex = 0;
	first.iCount = (DWORD)file.GetLength();
	first.iFileSize = (DWORD)file.GetLength();
	m_pSendSocket->Send((char*)&first,sizeof(first)+1);*/
}

//上传函数
void CDlgDlg::OnBnClickedButtonUpload()
{
	// TODO: 在此添加控件通知处理程序代码
	//可调用GetPrivateProfileString从..//Download.ini中获取 文件名文件大小和存放路径
	//if(!m_pSendSocket)
	//{
	//	AfxMessageBox(_T("未连接服务器！"));
	//	return;
	//}

	TCHAR szFilter[] = (_T("所有文件(*.*)|*.*||"));
	CFileDialog filedialog(true,_T("0"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);
	CString csFilePath;
	CString csFileName;
	int iFileSize;
	if( IDOK == filedialog.DoModal())
	{
		csFilePath = filedialog.GetPathName();
		csFileName = filedialog.GetFileName();
	}
	else
	{
		return;
	}
	CFile file;
	file.Open(csFilePath,CFile::modeRead);
	iFileSize = file.GetLength();
	file.Close();
	CString csMD5 = getMd5(csFilePath);//在这里写MD5函数
	STRUCT_MSG upLoadMsg;
	memset(&upLoadMsg,0,sizeof(upLoadMsg));
	upLoadMsg.iMsgType = MT_UPLOAD;
	//转类型后赋值
	CStringToCharP(csFileName,upLoadMsg.cFileName);
	CStringToCharP(csFilePath,upLoadMsg.cFileContent);
	CStringToCharP(m_csIP,upLoadMsg.cIP);
	CStringToCharP(m_csMAC,upLoadMsg.cMAC);
	CStringToCharP(csMD5,upLoadMsg.cMD5);
	upLoadMsg.iFileSize = iFileSize;
	m_pSendSocket->Send((char*)&upLoadMsg,sizeof(upLoadMsg)+1);

	WritePrivateProfileString(csMD5,_T("FilePath"),csFilePath,_T("..\\Upload.wrc"));


}

// 连接到服务器
bool CDlgDlg::ConnectServer(void)
{
	m_pSendSocket = new CSendSocket(this);
	m_pSendSocket->Create();
	if(!m_pSendSocket->Connect(m_csServerIP,SERVERPORT))
	{
		AfxMessageBox(_T("连接服务器失败！"));
		return false;
	}
	return true;
}

void CDlgDlg::OnBnClickedButtonSetip()
{
	// TODO: 在此添加控件通知处理程序代码
	CSetIP ci;
	ci.DoModal();
	m_csServerIP = ci.m_csIP;
	if(!ConnectServer())
		return;
	Sleep(500);

	STRUCT_MSG sendMsg;
	memset(&sendMsg,0,sizeof(sendMsg));
	sendMsg.iMsgType = MT_LOGIN;

	GetIP(m_csIP);
	m_csMAC=GetMAC();
	CStringToCharP(m_csIP,sendMsg.cIP);
	CStringToCharP(m_csMAC,sendMsg.cMAC);
	m_pSendSocket->Send((char*)&sendMsg,sizeof(sendMsg)+1);
}

// 获得本机MAC地址
CString CDlgDlg::GetMAC(void)
{
	int i=0;
	CString str;
	PIP_ADAPTER_INFO pAdapterInfo;ULONG ulOutbufLen = sizeof(IP_ADAPTER_INFO);//注意是ULONG类型,而非PULONG类型
	pAdapterInfo = ( IP_ADAPTER_INFO *)malloc( sizeof(IP_ADAPTER_INFO) );//为其动态分配内存,若大小不够,后面会有调整

	if ( ERROR_BUFFER_OVERFLOW == GetAdaptersInfo( pAdapterInfo, &ulOutbufLen) )
	{//MSDN上介绍,因为获取的消息,可能超过预先设置的缓冲区长度,造成返回,而一旦返回获取的资料将为空,此处为防止这种情况发生,
		free(pAdapterInfo);//可以测试一下结果,去掉这部分代码后,返回值为空.此处重构,直到成功
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutbufLen); //第1次大小不够,第2次返回所需长度
	}
	if ( ERROR_SUCCESS == GetAdaptersInfo( pAdapterInfo, &ulOutbufLen ))//MSDN上是那样写,也可写成NO_ERROR,都正确



		str.Format(_T("%02x-%02x-%02x-%02x-%02x-%02x\n"),
		pAdapterInfo->Address[0], //注意此处是数组格式,网上有的没有[0][1]等,str.Format格式就是sprintf的MFC版
		pAdapterInfo->Address[1],
		pAdapterInfo->Address[2],
		pAdapterInfo->Address[3],
		pAdapterInfo->Address[4],
		pAdapterInfo->Address[5]);//,pAdapterInfo->Address[6],如果你想知道第7个是个什么值?可以一试,但是值为00(即空值)

	//m_Mac.SetWindowText(str);

	return str;
}

// 获取本机IP地址
bool CDlgDlg::GetIP(CString &IP)
{
	WSADATA wsadata;
	if(0 != WSAStartup(MAKEWORD(2, 2), &wsadata))   //初始化
	{
		//AfxMessageBox("初始化网络环境失败!");
		return false;
	}
	char szHostName[MAX_PATH + 1];
	gethostname(szHostName, MAX_PATH);  //得到计算机名
	hostent *p = gethostbyname(szHostName); //从计算机名得到主机信息
	if(p == NULL)
	{
		//AfxMessageBox("得到本机网络信息失败!");
		return false;
	}
	//m_strName = szHostName;       //保存主机名
	//int nCount = 0;                 //保存主机地址
	char *pIP = inet_ntoa(*(in_addr *)p->h_addr_list[0]);//将32位IP转化为字符串IP
	//CString m_strAddr = pIP;             //保存主机IP地址
	//AfxMessageBox(m_strAddr);
	IP = pIP;
	//UpdateData(FALSE);          //显示各个数据
	WSACleanup();               //释放Winsock API
	return true;
}

BOOL CDlgDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_pGetSocket)
	{
		m_pGetSocket->Close();
		delete m_pGetSocket;
		m_pGetSocket = NULL;
	}

	if(m_bDownloading)
	{
		//写配置文件
		Sleep(1000);
		CFile file;
		file.Open(m_csSaveFilePath+m_csMD5,CFile::modeWrite|CFile::modeNoTruncate);
		file.Write(bBlock,m_iCount+1);
		file.Close();

	}
	if(m_pGiveSocket)
	{
		m_pGiveSocket->Close();
		delete m_pGiveSocket;
		m_pGiveSocket = NULL;
	}
	if(m_pSendSocket)
	{
		m_pSendSocket->Close();
		delete m_pSendSocket;
		m_pSendSocket = NULL;
	}
	return CDialog::DestroyWindow();
}

// 将搜索窗口中的文件名发送至服务器
void CDlgDlg::DealSearch(CString FileName)
{
	if(!m_pSendSocket)
	{
		AfxMessageBox(_T("未连接服务器！"));
		return;
	}
	STRUCT_MSG searchMsg;
	memset(&searchMsg,0,sizeof(searchMsg));
	searchMsg.iMsgType = MT_SEARCH;
	CStringToCharP(FileName,searchMsg.cFileName);
	m_pSendSocket->Send((char*)&searchMsg,sizeof(searchMsg)+1);
}

// 处理下载请求
void CDlgDlg::DealDownload(CString FileName,CString MD5,int iFileSize)
{
	//自己先创建一个套接字用于接发文件的客户端
	CreateServer();
	//初始化下载
	InitDownload(iFileSize,MD5);
	//保存要下载的文件名
	m_csSaveFileName = FileName;//这里的文件名是接收客户端的文件名，不是发送客户端的，而上面的路径是发送客户端的
	//之后发消息给服务器，让服务器发消息给其他客户端，要求他们发文件
	STRUCT_MSG downloadMsg;
	memset(&downloadMsg,0,sizeof(downloadMsg));
	downloadMsg.iMsgType = MT_DOWNREQUEST;
	//CStringToCharP(FilePath,downloadMsg.cFileContent);//传路径过去是让其他客户端直接打开这个路径的文件即可，减少工作量.这里现在改为读配置文件了
	CStringToCharP(m_csIP,downloadMsg.cIP);
	CStringToCharP(MD5,downloadMsg.cMD5);//传MD5是让服务器的数据库搜索相应数据
	//CStringToCharP(FileName,downloadMsg.cFileName);//这里的文件名是接收客户端的文件名，不是发送客户端的，而上面的路径是发送客户端的
	m_pSendSocket->Send((char*)&downloadMsg,sizeof(downloadMsg)+1);

}

void CDlgDlg::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	//如果正在下载，则断开连接
	if(m_bDownloading)
	{
		m_pGetSocket->Close();
		m_listClient.RemoveAll();
		//写配置文件
		Sleep(1000);
		CFile file;
		file.Open(m_csSaveFilePath+m_csMD5,CFile::modeWrite|CFile::modeNoTruncate);
		file.Write(bBlock,m_iCount+1);
		file.Close();
		m_bDownloading = false;
		//写配置文件，保存文件名、MD5、以及总的块数
		CString csCount;
		csCount.Format(_T("%d"),m_iCount);
		WritePrivateProfileString(_T("Downloading"),_T("FileName"),m_csSaveFileName,_T("..\\Downloading.lyt"));
		WritePrivateProfileString(_T("Downloading"),_T("MD5"),m_csMD5,_T("..\\Downloading.lyt"));
		WritePrivateProfileString(_T("Downloading"),_T("Count"),csCount,_T("..\\Downloading.lyt"));
		 m_bFinish = false;
	}


}

// 初始化下载，初始化bBlock数组
void CDlgDlg::InitDownload(int iFileSize,CString MD5)
{
	int iCount = iFileSize / SEND_BLOCK;
	if(iFileSize % SEND_BLOCK > 0)
	{
		iCount++;
	}
	m_iCount = iCount;
	m_csMD5=MD5;
	bBlock = new char[iCount];
	for(int i = 0; i<iCount;i++)
	{
		bBlock[i] = '0';
	}
	bBlock[iCount] = '\0'; 
	CFile file;
	file.Open(m_csSaveFilePath+MD5,CFile::modeCreate|CFile::modeWrite);
	file.Write(bBlock,iCount+1);
	file.Close();
	//初始化进度条
	progress.SetRange(0,m_iCount);//设定进度条开始位置和结束位置,这里的设置并不十分合理，因为参数是short，所以最多只能分65535块
	progress.SetStep(1);//设定每次增加的大小	

}

// 向各个客户端索取文件
void CDlgDlg::AskForFile(void)
{
	m_bDownloading= false;
	POSITION pos=m_listClient.GetHeadPosition();
	while(pos!=NULL)
	{
		CSendSocket* pSocket=m_listClient.GetAt(pos);
		for(int i = 0; i< m_iCount;i++)
		{
			if('0' == bBlock[i])//如果这个块没有就索要
			{
				STRUCT_MSG downloadMsg;
				memset(&downloadMsg,0,sizeof(downloadMsg));
				downloadMsg.iMsgType = MT_SENDFILE_REQUEST;
				downloadMsg.iIndex = i;
				pSocket->Send((char*)&downloadMsg,sizeof(downloadMsg)+1);
				//bBlock[i]='1';//不知道顺序，所以这句不知道需不需要
				Sleep(10);
				m_bDownloading = true;
				break;
			}
			m_bFinish = true;
		}
		m_listClient.GetNext(pos);
	}
	
	if((!m_bDownloading)&& (m_bFinish == true))
	{
		Sleep(1000);
		CFile file;
		file.Open(m_csSaveFilePath+m_csMD5,CFile::modeWrite|CFile::modeNoTruncate);
		file.Write(bBlock,m_iCount+1);
		file.Close();
		WritePrivateProfileString(_T("Downloading"),_T("FileName"),_T(""),_T("..\\Downloading.lyt"));
		WritePrivateProfileString(_T("Downloading"),_T("MD5"),_T(""),_T("..\\Downloading.lyt"));
		WritePrivateProfileString(_T("Downloading"),_T("Count"),_T(""),_T("..\\Downloading.lyt"));
		AfxMessageBox(_T("Done"));
		m_bFinish = true;
		if(!m_pGetSocket)
			return;
		m_pGetSocket->Close();
		delete m_pGetSocket;
		m_pGetSocket = NULL;
	}

}

HBRUSH CDlgDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if(pWnd == this)
	{
		return m_brBK;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CDlgDlg::OnBnClickedButtonRecyclebin()
{
	// TODO: 在此添加控件通知处理程序代码
}
