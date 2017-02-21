// ServerDlg.h : ͷ�ļ�
//

#pragma once
#include"SendSocket.h"
#include"GetSocket.h"
#include<afxtempl.h>//������
//�˿ں�
#define MYPORT 8000
#define SERVERPORT 6000
//һ������ļ����ݴ�С
#define SEND_BLOCK 1024
//��Ϣ����
#define MT_LOGIN 0
#define MT_LOGOUT 1
#define MT_SEARCH 2
#define MT_DOWNREQUEST 3
#define MT_GIVEFILE 4
#define MT_SENDFILE 5
#define MT_SENDFILE_REQUEST 6
#define MT_SENDFILE_INIT 7
#define MT_UPLOAD 8
#define MT_SEARCH_RETURN 9

//��Ϣ�ṹ�嶨��
struct STRUCT_MSG{
	int iMsgType;//��Ϣ����  0-����  1-�ǳ�  2-�����ļ�����  3-�����ļ����� 4-�������û����ļ�����  5-�ļ����� 6-�ļ����䣨Ҫ��7-�����������ļ���С���ͻ��˳�ʼ���� 8-��������ϴ��ļ��б� 9-���������б�
	int iFileSize;//�ļ���С
	int iCount;//����Ŀ�������Դ��
	char cFileName[50];//�ļ���
	char cFileContent[1024];//�ļ����ݻ��ļ����·��
	int iIndex;//ƫ����
	int istatus;//����״̬
	char cMD5[33];//MD5
	char cIP[16];//IP��ַ
	char cMAC[33];//MAC��ַ
};
// CServerDlg �Ի���
class CServerDlg : public CDialog
{
// ����
public:
	CServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ���ڱ��������ָ��
	CGetSocket* m_pGetSocket;
	// ������ӿͻ���������
	void AddClient();
	// ���ڴ��������Ϣ
	void RevMsg(CSendSocket* pSocket);
	//�ͻ���ָ������
	CList<CSendSocket*,CSendSocket*> m_listClient;
	// �ͻ��˶Ͽ�����
	void ClientQuit(CSendSocket* pSocket);
	virtual BOOL DestroyWindow();
};
