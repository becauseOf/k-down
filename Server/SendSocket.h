#pragma once

// CSendSocket 命令目标

/*用于接发送消息的Socket，相当于我们之前的ChatSocket*/

class CSendSocket : public CSocket
{
public:
	CSendSocket();
	CSendSocket(CWnd*);

	virtual ~CSendSocket();
	virtual void OnReceive(int nErrorCode);
	// 父窗口指针
	CWnd* m_pParentWnd;
	virtual void OnClose(int nErrorCode);
	CString m_csIP;
};


