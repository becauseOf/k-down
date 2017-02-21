// DlgDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include"SendSocket.h"
#include"GetSocket.h"
#include"Search.h"//�������ڵ���
#include<afxtempl.h>//������
#include "btnst.h"

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
	int iCount;//����Ŀ
	char cFileName[50];//�ļ���
	char cFileContent[1024];//�ļ����ݻ��ļ����·��
	int iIndex;//ƫ����
	int istatus;//����״̬
	char cMD5[33];//MD5
	char cIP[16];//IP��ַ
	char cMAC[33];//MAC��ַ
};
// CDlgDlg �Ի���
class CDlgDlg : public CDialog
{
// ����
public:
	CDlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DOWNLOAD };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CBrush m_brBK;


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonFeedback();
	afx_msg void OnBnClickedButtonPrivacy();
	afx_msg void OnBnClickedButtonNewassignment();

	CListCtrl m_listShow;
	afx_msg void OnBnClickedButtonDelete();
	// ���ڽ���socket��Ϣ����Ϣ�������ļ�������ȡ���
	void RevMsg(CSendSocket* pSocket);
	// ���û������ˣ������������ɾ�����ͷ��ڴ棬����ʾ�����û�����������������
	void ClientQuit(CSendSocket* pSocket);
	
	// �൱��֮ǰ��serversocket�����ڽӿͻ���
	CGetSocket* m_pGetSocket;
	// ���ڽ��ܿͻ������ӣ���������ӦSocket�������������
	void AddClient(void);
	// ����������Socket�����ö˿ڲ���ʼ����
	bool CreateServer(void);


//��Ա����
public:
	//���ڱ���ͻ��˵�����
	CList<CSendSocket*,CSendSocket*> m_listClient;

	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonNowdownload();
	afx_msg void OnBnClickedButtonUpload();
	// ���ӵ�������
	bool ConnectServer(void);
	// �������������Socket���൱��CChatSocket
	CSendSocket* m_pSendSocket;
	// ������IP��ַ
	CString m_csServerIP;
	//�ļ����·��
	CString m_csFilePath;
	//�����ļ�����Щ�Ѵ���
	char* bBlock;
	int iCount;
	afx_msg void OnBnClickedButtonSetip();
	// ��ñ���MAC��ַ
	CString GetMAC(void);
	// ��ȡ����IP��ַ
	bool GetIP(CString &IP);
	virtual BOOL DestroyWindow();
	// ����IP��ַ
	CString m_csIP;
	// ����MAC��ַ
	CString m_csMAC;
	// ָ���������ڵ�ָ��
	CSearch* m_pSearch;
	// �����������е��ļ���������������
	void DealSearch(CString FileName);
	// ���ڷ��ļ��������û����׽���
	CSendSocket* m_pGiveSocket;
	// ������������
	void DealDownload(CString FileName,CString MD5,int iFileSize);
	// �ж��Ƿ���������
	bool m_bDownloading;
	afx_msg void OnBnClickedButtonPause();
	// �����ļ���·��
	CString m_csGiveFilePath;
	// �����ļ���·��
	CString m_csSaveFilePath;
	// ��ʼ�����أ���ʼ��m_bBlock����
	void InitDownload(int iFileSize,CString);
	// ������ͻ�����ȡ�ļ�
	void AskForFile(void);
	// ����Ҫ���ص��ļ���
	CString m_csSaveFileName;
	// Ҫ���صĿ���
	int m_iCount;
	//Ҫ���ص��ļ���MD5ֵ������д0��1��
	CString m_csMD5;
	// ����������
	CProgressCtrl progress;
	// �ж��Ƿ��������
	bool m_bFinish;
	CButtonST m_btnSearch;
	CButtonST m_btnSet;
	CButtonST m_btnFeedback;
	CButtonST m_btnUpload;
	CButtonST m_btnIP;
	CButtonST m_btnStart;
	CButtonST m_btnPause;
	CButtonST m_btnDelete;
	CButtonST m_btnMy;
	CButtonST m_btnNow;
	CButtonST m_btnPrivacy;
	CButtonST m_btnCan;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButtonST m_btnProgress;
	afx_msg void OnBnClickedButtonRecyclebin();
};
