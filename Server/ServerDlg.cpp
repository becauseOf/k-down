// ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include"SolveCode.h"
#include "DBConnection.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerDlg �Ի���




CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CServerDlg::IDD, pParent)
, m_pGetSocket(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CServerDlg ��Ϣ�������

BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//����Socket
	m_pGetSocket = new CGetSocket(this);
	//��������
	if(!m_pGetSocket->Create(SERVERPORT)){
		AfxMessageBox(_T("����������ʧ�ܣ�"));
		return false;
	}


	//����
	m_pGetSocket->Listen();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ������ӿͻ���������
void CServerDlg::AddClient()
{
	CSendSocket* pSocket = new CSendSocket(this);
	if(!m_pGetSocket->Accept(*pSocket)){
		AfxMessageBox(_T("���ӿͻ���ʧ�ܣ�"));
		delete pSocket;
		pSocket = NULL;
	}else{
		m_listClient.AddTail(pSocket);
		AfxMessageBox(_T("�ɹ�����ͻ��ˣ�"));
	}

}

// ���ڴ��������Ϣ
void CServerDlg::RevMsg(CSendSocket* pSocket)
{
	STRUCT_MSG revMsg;
	memset(&revMsg,0,sizeof(revMsg));
	pSocket->Receive((char*)&revMsg,sizeof(revMsg)+1);
	switch(revMsg.iMsgType){
		//�յ����ǵ�¼
	case MT_LOGIN:
		{
			CString csIP = CA2W(revMsg.cIP);
			CString csMAC = CA2W(revMsg.cMAC);
			pSocket->m_csIP = csIP;
			AfxMessageBox(_T("����ͻ���IP��ַΪ��")+csIP+_T("��ӦMAC��ӦΪ��")+csMAC);
			break;
		}
		//�յ����ǵǳ�
	case MT_LOGOUT:
		{//��ClientQuit��������д��
			break;
		}
		//�յ������ϴ�����
	case MT_UPLOAD:
		{
			CString csIP = CA2W(revMsg.cIP);
			CString csMAC = CA2W(revMsg.cMAC);
			CString csFileName = CA2W(revMsg.cFileName);
			CString csFilePath = CA2W(revMsg.cFileContent);
			CString csMD5 = CA2W(revMsg.cMD5);
			int iFileSize = revMsg.iFileSize;
			//���ݿ��������ｫ�����ֵ�ӵ����ݿ���
			//AfxMessageBox(_T("����ͻ����ϴ���һ���ļ���IP��ַΪ��")+csIP+_T("��ӦMAC��ӦΪ��")+csMAC+_T("�ļ���Ϊ��")+csFileName+_T("��ӦMD5Ϊ��")+csMD5+_T("��Ӧ·��Ϊ��")+csFilePath);
			CMSSqlConn sqlConn(_T("DB_DS"));
			// �õ����ݿ�����
			_ConnectionPtr pConn = sqlConn.GetConnection();
			_CommandPtr pCommand; 
			pCommand.CreateInstance(_T("ADODB.Command")); 

			//��MAC��ַ��IP��ַ���ļ�MD5���ļ������ļ��Ĵ洢·���Լ��ļ���С�������ݿ�
			CString cssql_file;
			cssql_file.Format(_T("insert into TEST2 values('%s','%s','%s','%s','%s','%d')"),csMAC,csIP,csMD5,csFileName,csFilePath,iFileSize);

			try
			{		
				_variant_t vNULL; 
				vNULL.vt = VT_ERROR;
				vNULL.scode = DISP_E_PARAMNOTFOUND;										// ����Ϊ�޲��� 
				pCommand->ActiveConnection = pConn;										// �ǳ��ؼ���һ�䣬�����������Ӹ�ֵ���� 
				pCommand->CommandText = (_bstr_t)cssql_file;							// �����ִ�	
				_RecordsetPtr pRecordset = pCommand->Execute(&vNULL,&vNULL,adCmdText);	// ִ��sql���

				// �ͷż�¼��
				pRecordset->Close();
			}
			catch (CException* e)
			{
				return;
			}
			catch (_com_error &e)
			{
				::AfxMessageBox(e.Description());
				return;
			}
			break;
		}
		//�յ�������������
	case MT_SEARCH:
		{
			
			CString csFileName1 = CA2W(revMsg.cFileName);
			CMSSqlConn sqlConn(_T("DB_DS"));
			// �õ����ݿ�����
			_ConnectionPtr pConn = sqlConn.GetConnection();
			_CommandPtr pCommand; 
			pCommand.CreateInstance(_T("ADODB.Command")); 

			//�����ݿ������ļ�������ȡ��Ӧ��Դ��Ϣ
			CString cssql_file;
			cssql_file.Format(_T("select * from TEST2 where FileName = '%s' "),csFileName1);
			try
			{
				_variant_t vNULL; 
				vNULL.vt = VT_ERROR;
				vNULL.scode = DISP_E_PARAMNOTFOUND;										// ����Ϊ�޲��� 
				pCommand->ActiveConnection = pConn;										// �ǳ��ؼ���һ�䣬�����������Ӹ�ֵ���� 
				pCommand->CommandText = (_bstr_t)cssql_file;									// �����ִ�	
				_RecordsetPtr pRecordset = pCommand->Execute(&vNULL,&vNULL,adCmdText);	// ִ��sql���
				// ������¼��
				CString csTemp_MAC;
				CString csTemp_IP;
				CString csTemp_MD5;
				CString csTemp_FileName;
				CString csTemp_FilePath;
				int FileSize;
				while (!pRecordset->GetadoEOF())
				{		
					csTemp_MAC = (char*)( _bstr_t(pRecordset->GetCollect(_T("MAC"))));
					csTemp_MAC.TrimLeft();
					csTemp_MAC.TrimRight();

					csTemp_IP = (char*)( _bstr_t(pRecordset->GetCollect(_T("IP"))));
					csTemp_IP.TrimLeft();
					csTemp_IP.TrimRight();

					csTemp_MD5 = (char*)( _bstr_t(pRecordset->GetCollect(_T("MD5"))));
					csTemp_MD5.TrimLeft();
					csTemp_MD5.TrimRight();

					csTemp_FileName = (char*)( _bstr_t(pRecordset->GetCollect(_T("FileName"))));
					csTemp_FileName.TrimLeft();
					csTemp_FileName.TrimRight();

					csTemp_FilePath = (char*)( _bstr_t(pRecordset->GetCollect(_T("FilePath"))));
					csTemp_FilePath.TrimLeft();
					csTemp_FilePath.TrimRight();

					FileSize = atoi( _bstr_t(pRecordset->GetCollect(_T("FileSize"))));
					pRecordset->MoveNext();
					//������д���ݿ�Ĳ����Լ������ļ��б�Ĵ��룬���Է�������Ȼ��ֵ�𣿲�Ȼ���ض��ٸ��ѵ�����Դ��
					CString csFileName = csTemp_FileName;//���ݿ�Ҫ��������ļ�����ֵ
					int iFileSize = FileSize;//���ļ���С��ֵ
					int iZiYuanShu = 1;//�Կ�����Դ��ֵ��������Դ�����ļ�����Ӧ��MD5��Ӧ�������û���Ŀ��
					CString csMD5 = csTemp_MD5;//����Ӧ�ļ�MD5���и�ֵ
					STRUCT_MSG returnMsg;
					memset(&returnMsg,0,sizeof(returnMsg));
					returnMsg.iMsgType = MT_SEARCH_RETURN;

					CStringToCharP(csFileName,returnMsg.cFileName);
					returnMsg.iFileSize = iFileSize;
					returnMsg.iCount = iZiYuanShu;
					CStringToCharP(csMD5,returnMsg.cMD5);
					pSocket->Send((char*)&returnMsg,sizeof(returnMsg)+1);
					AfxMessageBox(_T("�ͻ���Ҫ��������")+csFileName1);

				}
				// �ͷż�¼��
				pRecordset->Close();
			}
			catch (CException* e)
			{
				return;
			}
			catch (_com_error &e)
			{
				::AfxMessageBox(e.Description());
				return;
			}
		
		break;
	}
	//�յ������пͻ���Ҫ�����ص�����
	case MT_DOWNREQUEST:
		{
			CString csMD5 = CA2W(revMsg.cMD5);
			//����������ҳ���ǰ�����û���IP���������csMD5
			CMSSqlConn sqlConn(_T("DB_DS"));
			// �õ����ݿ�����
			_ConnectionPtr pConn = sqlConn.GetConnection();
			_CommandPtr pCommand; 
			pCommand.CreateInstance(_T("ADODB.Command")); 

			//�ҳ�MD5��Ӧ�ļ���Ϣ
			CString cssql_file;
			cssql_file.Format(_T("select * from TEST2 where MD5 = '%s' "),csMD5);
			try
			{
				_variant_t vNULL; 
				vNULL.vt = VT_ERROR;
				vNULL.scode = DISP_E_PARAMNOTFOUND;										// ����Ϊ�޲��� 
				pCommand->ActiveConnection = pConn;										// �ǳ��ؼ���һ�䣬�����������Ӹ�ֵ���� 
				pCommand->CommandText = (_bstr_t)cssql_file;									// �����ִ�	
				_RecordsetPtr pRecordset = pCommand->Execute(&vNULL,&vNULL,adCmdText);	// ִ��sql���
				CString csTemp_IP;
                while (!pRecordset->GetadoEOF())
				{		
					csTemp_IP = (char*)( _bstr_t(pRecordset->GetCollect(_T("IP"))));
					csTemp_IP.TrimLeft();
					csTemp_IP.TrimRight();
				    pRecordset->MoveNext();
				
			//��ӵ����Դ�Ŀͻ��˷�����Ϣ��Ҫ�����������ϴ������ļ��Ŀͻ���
			STRUCT_MSG downloadMsg;
			memset(&downloadMsg,0,sizeof(downloadMsg));
			downloadMsg.iMsgType = MT_GIVEFILE;
			strcpy(downloadMsg.cFileName,revMsg.cFileName);//���ļ�����ȥ��Ŀ�����ý��ܵĿͻ���֪���Լ���Ҫ���յ��ļ����ļ���
			//CStringToCharp(csFilePath,downloadMsg.cFileContent)//��·����ȥ���÷��ļ��Ŀͻ���֪�����ĸ��ļ������ﻹ���ÿͻ����Լ��������ļ��ɣ��Ͼ��㷨����
			strcpy(downloadMsg.cMD5,revMsg.cMD5);//����һ�䣬�ÿͻ��˶�����Ӧ�ļ�·��
			strcpy(downloadMsg.cIP,revMsg.cIP);//Ŀ��IP��ַ
			//����������ҳ���ǰ�����û���IP,Ҫ�󷵻��û�������С�ڻ����3����Ϊ���ﲻ��д�㷨�����Ծ��޶���3���ɣ�
			CString csIP= csTemp_IP;
			//��ÿ��ӵ�и��ļ����û����͸���Ϣ
			POSITION pos=m_listClient.GetHeadPosition();
			while(pos!=NULL){
				CSendSocket* pSocket=m_listClient.GetAt(pos);
				
					if(csIP == pSocket->m_csIP)//���IPƥ�䣬����Ϣ
					{
						pSocket->Send((char*)&downloadMsg,sizeof(downloadMsg)+1);
					}
				
				m_listClient.GetNext(pos);
			}
                // �ͷż�¼��
				pRecordset->Close();
				}
			}
			catch (CException* e)
			{
				return;
			}
			catch (_com_error &e)
			{
				::AfxMessageBox(e.Description());
				return;
			}
		
			break;
		}

}
}
// �ͻ��˶Ͽ�����
void CServerDlg::ClientQuit(CSendSocket* pSocket)
{
	POSITION pos = m_listClient.Find(pSocket);
	if(pos != NULL)
	{
		//���б����Ƴ�
		m_listClient.RemoveAt(pos);
		CString csMsg;
		CString csIP;
		csIP = pSocket->m_csIP;
		//������дɾ�����ݿ�����Ӧ��¼�Ĵ���


		//�ͷ��˳���Socketָ�����
		pSocket->Close();
		delete pSocket;
		pSocket = NULL;

		//������ʾ�ͻ��˳���
		csMsg.Format(_T("ϵͳ��ʾ��%s ������"), csIP);
		AfxMessageBox(csMsg);

	}
}
//���ٴ��ڵ��õĺ������رն˿ڣ��ͷ��ڴ�
BOOL CServerDlg::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_pGetSocket)
	{
		m_pGetSocket->Close();
		delete m_pGetSocket;
		m_pGetSocket = NULL;
	}
	return CDialog::DestroyWindow();
}
