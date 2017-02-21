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
//解决一直出现的警告 warning C4146: unary minus operator applied to unsigned type...
// 引入ADO库文件 不能放在#endif后，不能放在afxwin.h前
#import "dll\msado15.dll" no_namespace rename("EOF","adoEOF") rename("BOF","adoBOF")
#pragma   warning(pop)

class CDBConnection  
{
public:
	// 得到连接指针
	_ConnectionPtr GetConnection();
	// 关闭数据库连接指针
	void Close();
	
public:
	// 释放comm
	static void releaseComm();
	// 初始化comm
	static bool initComm();

private:
	// comm初始化的标志
	static bool m_bInitComm;

public:
	CDBConnection(const CString &dbName, const CString &ip, const CString &user, \
		const CString &pwd, const UINT &port);
	virtual ~CDBConnection();

protected:
	// 连接数据库
	virtual BOOL ConnDB();
	// 得到连接字符串
	virtual CString GetConnString() = 0;

protected:
	CString m_szdbName;			// 数据库名
	CString m_szUser;			// 用户名
	CString m_szPwd;			// 密码
	CString m_szIP;				// 服务器IP地址
	UINT m_nPort;				// 服务器的端口号

private:
	_ConnectionPtr m_pConn;		// 数据库连接指针 

};

// SqlServer 的连接类
class CMSSqlConn : public CDBConnection  
{
protected:
	// 实现了父类中的GetConnString函数
	CString GetConnString();

public:
	CMSSqlConn(const CString &dbName, const CString &ip = _T("127.0.0.1"), 
		const CString &user = _T("sa"), const CString &pwd = _T("123"), 
					   const UINT &port = 1433);
	virtual ~CMSSqlConn();

};

#endif // !defined(AFX_DBCONNECTION_H__5FF39193_A950_4E6A_AE34_D39A76C1E5A3__INCLUDED_)
