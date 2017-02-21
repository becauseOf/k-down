// DBConnection.cpp: implementation of the DBConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DBConnection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// 初始化comm
bool CDBConnection::initComm()
{
	try{
        if (!::CoInitialize(NULL))
		{
			AfxMessageBox(_T("Init Comm failed!"));
			return false;
		}

		m_bInitComm = true;
	}
	catch (_com_error &e)
	{
		::AfxMessageBox(e.Description());
		return false;
	}

	return true;
}

// 释放comm
void CDBConnection::releaseComm()
{
	try
	{
		::CoUninitialize();
		m_bInitComm = false;
	}
	catch (_com_error &e)
	{
		::AfxMessageBox(e.Description());
	}
}

bool CDBConnection::m_bInitComm = false;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBConnection::CDBConnection(const CString &dbName, const CString &ip, const CString &user, 
						   const CString &pwd, const UINT &port)
{
	m_pConn = NULL;
	m_szdbName = dbName;
	m_nPort = port;
	m_szUser = user;
	m_szPwd = pwd;
	m_szIP = ip;
}

CDBConnection::~CDBConnection()
{
	try{
		Close();

		if (CDBConnection::m_bInitComm)
		{
			CDBConnection::releaseComm();
		}
	}
	catch (_com_error &e)
	{
		::AfxMessageBox(e.Description());
	}
}

// 得到连接指针
_ConnectionPtr CDBConnection::GetConnection()
{
	try
	{
		if (!CDBConnection::m_bInitComm)
		{
			CDBConnection::initComm();
		}

		if (NULL == m_pConn && ConnDB())
		{
			return m_pConn;
		}
	}
	catch (_com_error &e)
	{
		::AfxMessageBox(e.Description());
		return FALSE;
	}

	return NULL;
}

// 连接数据库
BOOL CDBConnection::ConnDB()
{
	try 
	{
		if (NULL != m_pConn)	return TRUE;
		
		if (FAILED(m_pConn.CreateInstance("ADODB.Connection")))
		{ 
			AfxMessageBox(_T("Create Instance failed!"));
			return FALSE;
		}
		
		CString szConnStr = GetConnString();
		
		if (FAILED(m_pConn->Open((_bstr_t)szConnStr, "", "", adModeUnknown))) 
		{
			m_pConn.Release();		
			return FALSE;
		}
	}
	catch (CException* e)
	{
		return FALSE;
	}
	catch (_com_error &e)
	{
		::AfxMessageBox(e.Description());
		return FALSE;
	}
	
	return TRUE;
}

// 关闭数据库连接指针
void CDBConnection::Close()
{
	try
	{
		if (NULL != m_pConn && m_pConn->State != adStateClosed)
		{
			m_pConn->Close();
			m_pConn.Release();
		}
	}
	catch (_com_error &e)
	{
		::AfxMessageBox(e.Description());
	}
}


//////////////////////////////////////////////////////////////////////
// CMSSqlConn Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSSqlConn::CMSSqlConn(const CString &dbName, const CString &ip, const CString &user, 
					 const CString &pwd, const UINT &port)
		: CDBConnection(dbName, ip, user, pwd, port)
{

}

CMSSqlConn::~CMSSqlConn()
{

}

CString CMSSqlConn::GetConnString()
{
	CString szConnStr;
	szConnStr.Format(_T("Provider=SQLOLEDB.1;Persist Security Info=False;User ID=sa;Password=123;Data Source=YUTING\\SQLEXPRESS"),
		m_szdbName);

	return szConnStr;
}
