// GetSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg.h"
#include "GetSocket.h"
#include"DlgDlg.h"

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
		((CDlgDlg*)m_pParentWnd)->AddClient();
	}
	CSocket::OnAccept(nErrorCode);
}
