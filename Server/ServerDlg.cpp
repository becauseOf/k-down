// ServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include"SolveCode.h"
#include "DBConnection.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerDlg 对话框




CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CServerDlg::IDD, pParent)
, m_pGetSocket(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//创建Socket
	m_pGetSocket = new CGetSocket(this);
	//创建服务
	if(!m_pGetSocket->Create(SERVERPORT)){
		AfxMessageBox(_T("创建服务器失败！"));
		return false;
	}


	//监听
	m_pGetSocket->Listen();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 用于添加客户端至链表
void CServerDlg::AddClient()
{
	CSendSocket* pSocket = new CSendSocket(this);
	if(!m_pGetSocket->Accept(*pSocket)){
		AfxMessageBox(_T("连接客户端失败！"));
		delete pSocket;
		pSocket = NULL;
	}else{
		m_listClient.AddTail(pSocket);
		AfxMessageBox(_T("成功接入客户端！"));
	}

}

// 用于处理各种消息
void CServerDlg::RevMsg(CSendSocket* pSocket)
{
	STRUCT_MSG revMsg;
	memset(&revMsg,0,sizeof(revMsg));
	pSocket->Receive((char*)&revMsg,sizeof(revMsg)+1);
	switch(revMsg.iMsgType){
		//收到的是登录
	case MT_LOGIN:
		{
			CString csIP = CA2W(revMsg.cIP);
			CString csMAC = CA2W(revMsg.cMAC);
			pSocket->m_csIP = csIP;
			AfxMessageBox(_T("接入客户端IP地址为：")+csIP+_T("对应MAC对应为：")+csMAC);
			break;
		}
		//收到的是登出
	case MT_LOGOUT:
		{//在ClientQuit函数那里写了
			break;
		}
		//收到的是上传请求
	case MT_UPLOAD:
		{
			CString csIP = CA2W(revMsg.cIP);
			CString csMAC = CA2W(revMsg.cMAC);
			CString csFileName = CA2W(revMsg.cFileName);
			CString csFilePath = CA2W(revMsg.cFileContent);
			CString csMD5 = CA2W(revMsg.cMD5);
			int iFileSize = revMsg.iFileSize;
			//数据库请在这里将上面的值加到数据库中
			//AfxMessageBox(_T("接入客户端上传了一个文件，IP地址为：")+csIP+_T("对应MAC对应为：")+csMAC+_T("文件名为：")+csFileName+_T("对应MD5为：")+csMD5+_T("对应路径为：")+csFilePath);
			CMSSqlConn sqlConn(_T("DB_DS"));
			// 得到数据库连接
			_ConnectionPtr pConn = sqlConn.GetConnection();
			_CommandPtr pCommand; 
			pCommand.CreateInstance(_T("ADODB.Command")); 

			//将MAC地址，IP地址，文件MD5，文件名，文件的存储路径以及文件大小存入数据库
			CString cssql_file;
			cssql_file.Format(_T("insert into TEST2 values('%s','%s','%s','%s','%s','%d')"),csMAC,csIP,csMD5,csFileName,csFilePath,iFileSize);

			try
			{		
				_variant_t vNULL; 
				vNULL.vt = VT_ERROR;
				vNULL.scode = DISP_E_PARAMNOTFOUND;										// 定义为无参数 
				pCommand->ActiveConnection = pConn;										// 非常关键的一句，将建立的连接赋值给它 
				pCommand->CommandText = (_bstr_t)cssql_file;							// 命令字串	
				_RecordsetPtr pRecordset = pCommand->Execute(&vNULL,&vNULL,adCmdText);	// 执行sql语句

				// 释放记录集
				pRecordset->Close();
			}
			catch (CException* e)
			{
				return;
			}
			catch (_com_error &e)
			{
				::AfxMessageBox(e.Description());
				return;
			}
			break;
		}
		//收到的是搜索请求
	case MT_SEARCH:
		{
			
			CString csFileName1 = CA2W(revMsg.cFileName);
			CMSSqlConn sqlConn(_T("DB_DS"));
			// 得到数据库连接
			_ConnectionPtr pConn = sqlConn.GetConnection();
			_CommandPtr pCommand; 
			pCommand.CreateInstance(_T("ADODB.Command")); 

			//在数据库搜索文件名，获取对应资源信息
			CString cssql_file;
			cssql_file.Format(_T("select * from TEST2 where FileName = '%s' "),csFileName1);
			try
			{
				_variant_t vNULL; 
				vNULL.vt = VT_ERROR;
				vNULL.scode = DISP_E_PARAMNOTFOUND;										// 定义为无参数 
				pCommand->ActiveConnection = pConn;										// 非常关键的一句，将建立的连接赋值给它 
				pCommand->CommandText = (_bstr_t)cssql_file;									// 命令字串	
				_RecordsetPtr pRecordset = pCommand->Execute(&vNULL,&vNULL,adCmdText);	// 执行sql语句
				// 遍历记录集
				CString csTemp_MAC;
				CString csTemp_IP;
				CString csTemp_MD5;
				CString csTemp_FileName;
				CString csTemp_FilePath;
				int FileSize;
				while (!pRecordset->GetadoEOF())
				{		
					csTemp_MAC = (char*)( _bstr_t(pRecordset->GetCollect(_T("MAC"))));
					csTemp_MAC.TrimLeft();
					csTemp_MAC.TrimRight();

					csTemp_IP = (char*)( _bstr_t(pRecordset->GetCollect(_T("IP"))));
					csTemp_IP.TrimLeft();
					csTemp_IP.TrimRight();

					csTemp_MD5 = (char*)( _bstr_t(pRecordset->GetCollect(_T("MD5"))));
					csTemp_MD5.TrimLeft();
					csTemp_MD5.TrimRight();

					csTemp_FileName = (char*)( _bstr_t(pRecordset->GetCollect(_T("FileName"))));
					csTemp_FileName.TrimLeft();
					csTemp_FileName.TrimRight();

					csTemp_FilePath = (char*)( _bstr_t(pRecordset->GetCollect(_T("FilePath"))));
					csTemp_FilePath.TrimLeft();
					csTemp_FilePath.TrimRight();

					FileSize = atoi( _bstr_t(pRecordset->GetCollect(_T("FileSize"))));
					pRecordset->MoveNext();
					//在这里写数据库的查找以及返回文件列表的代码，可以返回数组然后赋值吗？不然返回多少个搜到的资源呢
					CString csFileName = csTemp_FileName;//数据库要在这里对文件名赋值
					int iFileSize = FileSize;//对文件大小赋值
					int iZiYuanShu = 1;//对可用资源赋值（可用资源：该文件名对应的MD5对应的在线用户数目）
					CString csMD5 = csTemp_MD5;//对相应文件MD5进行赋值
					STRUCT_MSG returnMsg;
					memset(&returnMsg,0,sizeof(returnMsg));
					returnMsg.iMsgType = MT_SEARCH_RETURN;

					CStringToCharP(csFileName,returnMsg.cFileName);
					returnMsg.iFileSize = iFileSize;
					returnMsg.iCount = iZiYuanShu;
					CStringToCharP(csMD5,returnMsg.cMD5);
					pSocket->Send((char*)&returnMsg,sizeof(returnMsg)+1);
					AfxMessageBox(_T("客户端要求搜索：")+csFileName1);

				}
				// 释放记录集
				pRecordset->Close();
			}
			catch (CException* e)
			{
				return;
			}
			catch (_com_error &e)
			{
				::AfxMessageBox(e.Description());
				return;
			}
		
		break;
	}
	//收到的是有客户端要求下载的请求
	case MT_DOWNREQUEST:
		{
			CString csMD5 = CA2W(revMsg.cMD5);
			//在这里，数据找出当前在线用户的IP，用上面的csMD5
			CMSSqlConn sqlConn(_T("DB_DS"));
			// 得到数据库连接
			_ConnectionPtr pConn = sqlConn.GetConnection();
			_CommandPtr pCommand; 
			pCommand.CreateInstance(_T("ADODB.Command")); 

			//找出MD5对应文件信息
			CString cssql_file;
			cssql_file.Format(_T("select * from TEST2 where MD5 = '%s' "),csMD5);
			try
			{
				_variant_t vNULL; 
				vNULL.vt = VT_ERROR;
				vNULL.scode = DISP_E_PARAMNOTFOUND;										// 定义为无参数 
				pCommand->ActiveConnection = pConn;										// 非常关键的一句，将建立的连接赋值给它 
				pCommand->CommandText = (_bstr_t)cssql_file;									// 命令字串	
				_RecordsetPtr pRecordset = pCommand->Execute(&vNULL,&vNULL,adCmdText);	// 执行sql语句
				CString csTemp_IP;
                while (!pRecordset->GetadoEOF())
				{		
					csTemp_IP = (char*)( _bstr_t(pRecordset->GetCollect(_T("IP"))));
					csTemp_IP.TrimLeft();
					csTemp_IP.TrimRight();
				    pRecordset->MoveNext();
				
			//向拥有资源的客户端发送信息，要求他们连接上待接收文件的客户端
			STRUCT_MSG downloadMsg;
			memset(&downloadMsg,0,sizeof(downloadMsg));
			downloadMsg.iMsgType = MT_GIVEFILE;
			strcpy(downloadMsg.cFileName,revMsg.cFileName);//传文件名过去的目的是让接受的客户端知道自己的要接收的文件的文件名
			//CStringToCharp(csFilePath,downloadMsg.cFileContent)//传路径过去，让发文件的客户端知道发哪个文件。这里还是让客户端自己读配置文件吧，毕竟算法不行
			strcpy(downloadMsg.cMD5,revMsg.cMD5);//看上一句，让客户端读出对应文件路径
			strcpy(downloadMsg.cIP,revMsg.cIP);//目标IP地址
			//在这里，数据找出当前在线用户的IP,要求返回用户数量，小于或等于3（因为这里不会写算法，所以就限定死3个吧）
			CString csIP= csTemp_IP;
			//对每个拥有该文件的用户发送该消息
			POSITION pos=m_listClient.GetHeadPosition();
			while(pos!=NULL){
				CSendSocket* pSocket=m_listClient.GetAt(pos);
				
					if(csIP == pSocket->m_csIP)//如果IP匹配，则发消息
					{
						pSocket->Send((char*)&downloadMsg,sizeof(downloadMsg)+1);
					}
				
				m_listClient.GetNext(pos);
			}
                // 释放记录集
				pRecordset->Close();
				}
			}
			catch (CException* e)
			{
				return;
			}
			catch (_com_error &e)
			{
				::AfxMessageBox(e.Description());
				return;
			}
		
			break;
		}

}
}
// 客户端断开连接
void CServerDlg::ClientQuit(CSendSocket* pSocket)
{
	POSITION pos = m_listClient.Find(pSocket);
	if(pos != NULL)
	{
		//从列表中移除
		m_listClient.RemoveAt(pos);
		CString csMsg;
		CString csIP;
		csIP = pSocket->m_csIP;
		//在这里写删掉数据库中相应记录的代码


		//释放退出的Socket指针对象
		pSocket->Close();
		delete pSocket;
		pSocket = NULL;

		//界面显示客户退出了
		csMsg.Format(_T("系统提示：%s 下线了"), csIP);
		AfxMessageBox(csMsg);

	}
}
//销毁窗口调用的函数，关闭端口，释放内存
BOOL CServerDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_pGetSocket)
	{
		m_pGetSocket->Close();
		delete m_pGetSocket;
		m_pGetSocket = NULL;
	}
	return CDialog::DestroyWindow();
}
