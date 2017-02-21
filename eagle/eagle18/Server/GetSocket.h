#pragma once

// CGetSocket 命令目标

/*用于接客户端的socket，相当于我们之前的ServerSocket*/
class CGetSocket : public CSocket
{
public:
	CGetSocket();
	CGetSocket(CWnd*);

	virtual ~CGetSocket();
	virtual void OnAccept(int nErrorCode);
	// 父窗口指针
	CWnd* m_pParentWnd;
};


