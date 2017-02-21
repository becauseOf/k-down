// DBConnection.h: interface for the CDBConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBCONNECTION_H__5FF39193_A950_4E6A_AE34_D39A76C1E5A3__INCLUDED_)
#define AFX_DBCONNECTION_H__5FF39193_A950_4E6A_AE34_D39A76C1E5A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma   warning(push)   
#pragma   warning(disable:4146) 
//���һֱ���ֵľ��� warning C4146: unary minus operator applied to unsigned type...
// ����ADO���ļ� ���ܷ���#endif�󣬲��ܷ���afxwin.hǰ
#import "dll\msado15.dll" no_namespace rename("EOF","adoEOF") rename("BOF","adoBOF")
#pragma   warning(pop)

class CDBConnection  
{
public:
	// �õ�����ָ��
	_ConnectionPtr GetConnection();
	// �ر����ݿ�����ָ��
	void Close();
	
public:
	// �ͷ�comm
	static void releaseComm();
	// ��ʼ��comm
	static bool initComm();

private:
	// comm��ʼ���ı�־
	static bool m_bInitComm;

public:
	CDBConnection(const CString &dbName, const CString &ip, const CString &user, \
		const CString &pwd, const UINT &port);
	virtual ~CDBConnection();

protected:
	// �������ݿ�
	virtual BOOL ConnDB();
	// �õ������ַ���
	virtual CString GetConnString() = 0;

protected:
	CString m_szdbName;			// ���ݿ���
	CString m_szUser;			// �û���
	CString m_szPwd;			// ����
	CString m_szIP;				// ������IP��ַ
	UINT m_nPort;				// �������Ķ˿ں�

private:
	_ConnectionPtr m_pConn;		// ���ݿ�����ָ�� 

};

// SqlServer ��������
class CMSSqlConn : public CDBConnection  
{
protected:
	// ʵ���˸����е�GetConnString����
	CString GetConnString();

public:
	CMSSqlConn(const CString &dbName, const CString &ip = _T("127.0.0.1"), 
		const CString &user = _T("sa"), const CString &pwd = _T("123"), 
					   const UINT &port = 1433);
	virtual ~CMSSqlConn();

};

#endif // !defined(AFX_DBCONNECTION_H__5FF39193_A950_4E6A_AE34_D39A76C1E5A3__INCLUDED_)
