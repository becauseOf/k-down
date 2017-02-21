// ServerDlg.h : 头文件
//

#pragma once
#include"SendSocket.h"
#include"GetSocket.h"
#include<afxtempl.h>//链表类
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
	int iCount;//块数目或可用资源数
	char cFileName[50];//文件名
	char cFileContent[1024];//文件内容或文件存放路径
	int iIndex;//偏移量
	int istatus;//传输状态
	char cMD5[33];//MD5
	char cIP[16];//IP地址
	char cMAC[33];//MAC地址
};
// CServerDlg 对话框
class CServerDlg : public CDialog
{
// 构造
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 用于保存服务器指针
	CGetSocket* m_pGetSocket;
	// 用于添加客户端至链表
	void AddClient();
	// 用于处理各种消息
	void RevMsg(CSendSocket* pSocket);
	//客户端指针链表
	CList<CSendSocket*,CSendSocket*> m_listClient;
	// 客户端断开连接
	void ClientQuit(CSendSocket* pSocket);
	virtual BOOL DestroyWindow();
};
