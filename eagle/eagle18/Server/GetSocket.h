#pragma once

// CGetSocket ����Ŀ��

/*���ڽӿͻ��˵�socket���൱������֮ǰ��ServerSocket*/
class CGetSocket : public CSocket
{
public:
	CGetSocket();
	CGetSocket(CWnd*);

	virtual ~CGetSocket();
	virtual void OnAccept(int nErrorCode);
	// ������ָ��
	CWnd* m_pParentWnd;
};


