// GetSocket.cpp : ʵ���ļ�
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


// CGetSocket ��Ա����

void CGetSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_pParentWnd !=NULL){
		((CServerDlg*)m_pParentWnd)->AddClient();
	}
	CSocket::OnAccept(nErrorCode);
}
