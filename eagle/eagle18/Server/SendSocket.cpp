// SendSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "SendSocket.h"
#include"ServerDlg.h"

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


// CSendSocket ��Ա����

void CSendSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_pParentWnd!=NULL)
		((CServerDlg*)m_pParentWnd)->RevMsg(this);
	CSocket::OnReceive(nErrorCode);
}

void CSendSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CServerDlg*)m_pParentWnd)->ClientQuit(this);

	CSocket::OnClose(nErrorCode);
}
