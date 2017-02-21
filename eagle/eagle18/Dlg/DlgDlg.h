// DlgDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include"SendSocket.h"
#include"GetSocket.h"
#include"Search.h"//搜索窗口的类
#include<afxtempl.h>//链表类
#include "btnst.h"

//端口号
#define MYPORT 8000
#define SERVERPORT 6000
//一个块的文件内容大小
#define SEND_BLOCK 1024
//消息类型
#define MT_LOGIN 0
#define MT_LOGOUT 1
#define MT_SEARCH 2
#define MT_DOWNREQUEST 3
#define MT_GIVEFILE 4
#define MT_SENDFILE 5
#define MT_SENDFILE_REQUEST 6
#define MT_SENDFILE_INIT 7
#define MT_UPLOAD 8
#define MT_SEARCH_RETURN 9
//消息结构体定义
struct STRUCT_MSG{
	int iMsgType;//消息类型  0-登入  1-登出  2-搜索文件请求  3-下载文件请求 4-给其他用户发文件请求  5-文件传输 6-文件传输（要求）7-服务器返回文件大小，客户端初始化块 8-向服务器上传文件列表 9-搜索返回列表
	int iFileSize;//文件大小
	int iCount;//块数目
	char cFileName[50];//文件名
	char cFileContent[1024];//文件内容或文件存放路径
	int iIndex;//偏移量
	int istatus;//传输状态
	char cMD5[33];//MD5
	char cIP[16];//IP地址
	char cMAC[33];//MAC地址
};
// CDlgDlg 对话框
class CDlgDlg : public CDialog
{
// 构造
public:
	CDlgDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DOWNLOAD };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CBrush m_brBK;


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonFeedback();
	afx_msg void OnBnClickedButtonPrivacy();
	afx_msg void OnBnClickedButtonNewassignment();

	CListCtrl m_listShow;
	afx_msg void OnBnClickedButtonDelete();
	// 用于接收socket消息，消息可以是文件、请求等……
	void RevMsg(CSendSocket* pSocket);
	// 有用户下线了，将其从链表中删除并释放内存，并提示其他用户，及反馈给服务器
	void ClientQuit(CSendSocket* pSocket);
	
	// 相当于之前的serversocket，用于接客户端
	CGetSocket* m_pGetSocket;
	// 用于接受客户端连接，并创建对应Socket，并添加至链表
	void AddClient(void);
	// 创建服务器Socket，设置端口并开始监听
	bool CreateServer(void);


//成员变量
public:
	//用于保存客户端的链表
	CList<CSendSocket*,CSendSocket*> m_listClient;

	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonNowdownload();
	afx_msg void OnBnClickedButtonUpload();
	// 连接到服务器
	bool ConnectServer(void);
	// 与服务器交互的Socket，相当于CChatSocket
	CSendSocket* m_pSendSocket;
	// 服务器IP地址
	CString m_csServerIP;
	//文件存放路径
	CString m_csFilePath;
	//保存文件块哪些已传完
	char* bBlock;
	int iCount;
	afx_msg void OnBnClickedButtonSetip();
	// 获得本机MAC地址
	CString GetMAC(void);
	// 获取本机IP地址
	bool GetIP(CString &IP);
	virtual BOOL DestroyWindow();
	// 本机IP地址
	CString m_csIP;
	// 本机MAC地址
	CString m_csMAC;
	// 指向搜索窗口的指针
	CSearch* m_pSearch;
	// 将搜索窗口中的文件名发送至服务器
	void DealSearch(CString FileName);
	// 用于发文件给其他用户的套接字
	CSendSocket* m_pGiveSocket;
	// 处理下载请求
	void DealDownload(CString FileName,CString MD5,int iFileSize);
	// 判断是否正在下载
	bool m_bDownloading;
	afx_msg void OnBnClickedButtonPause();
	// 发出文件的路径
	CString m_csGiveFilePath;
	// 保存文件的路径
	CString m_csSaveFilePath;
	// 初始化下载，初始化m_bBlock数组
	void InitDownload(int iFileSize,CString);
	// 向各个客户端索取文件
	void AskForFile(void);
	// 保存要下载的文件名
	CString m_csSaveFileName;
	// 要下载的块数
	int m_iCount;
	//要下载的文件的MD5值（用于写0和1）
	CString m_csMD5;
	// 进度条控制
	CProgressCtrl progress;
	// 判断是否下载完成
	bool m_bFinish;
	CButtonST m_btnSearch;
	CButtonST m_btnSet;
	CButtonST m_btnFeedback;
	CButtonST m_btnUpload;
	CButtonST m_btnIP;
	CButtonST m_btnStart;
	CButtonST m_btnPause;
	CButtonST m_btnDelete;
	CButtonST m_btnMy;
	CButtonST m_btnNow;
	CButtonST m_btnPrivacy;
	CButtonST m_btnCan;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButtonST m_btnProgress;
	afx_msg void OnBnClickedButtonRecyclebin();
};
