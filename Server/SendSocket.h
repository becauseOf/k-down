#pragma once

// CSendSocket ����Ŀ��

/*���ڽӷ�����Ϣ��Socket���൱������֮ǰ��ChatSocket*/

class CSendSocket : public CSocket
{
public:
	CSendSocket();
	CSendSocket(CWnd*);

	virtual ~CSendSocket();
	virtual void OnReceive(int nErrorCode);
	// ������ָ��
	CWnd* m_pParentWnd;
	virtual void OnClose(int nErrorCode);
	CString m_csIP;
};


