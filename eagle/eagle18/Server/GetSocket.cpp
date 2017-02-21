// GetSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "GetSocket.h"
#include"ServerDlg.h"

// CGetSocket

CGetSocket::CGetSocket()
: m_pParentWnd(NULL)
{
	m_pParentWnd=NULL;
}
CGetSocket::CGetSocket(CWnd* pWnd)
{
	m_pParentWnd=pWnd;
}
CGetSocket::~CGetSocket()
{
}


// CGetSocket 成员函数

void CGetSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_pParentWnd !=NULL){
		((CServerDlg*)m_pParentWnd)->AddClient();
	}
	CSocket::OnAccept(nErrorCode);
}
