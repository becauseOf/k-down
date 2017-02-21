// SendSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg.h"
#include "SendSocket.h"
#include"DlgDlg.h"

// CSendSocket

CSendSocket::CSendSocket()
: m_pParentWnd(NULL)
, m_csIP(_T(""))
{
	m_pParentWnd=NULL;
}
CSendSocket::CSendSocket(CWnd* pWnd)

{
	m_pParentWnd=pWnd;
}

CSendSocket::~CSendSocket()
{
}


// CSendSocket 成员函数

void CSendSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_pParentWnd!=NULL)
		((CDlgDlg*)m_pParentWnd)->RevMsg(this);
	CSocket::OnReceive(nErrorCode);
}
