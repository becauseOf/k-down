class DoDownload{
private:
	BOOL FileCut(File *fl, FILE *flread);//�ļ��ָ��Ա���߳�����
	BOOL FileCombine(File *fl, FILE *flwrite);//�ļ���ϣ�����Ŀ���ļ�

public:
public:
	CString  szHostAddr;      // Host��ַ.
	int      nHostPort;       // Host�˿ں�.
	CString  szHttpAddr;      // Http�ļ���ַ.
	CString  szHttpFilename;  // Http�ļ���.
	CString  szDesFilename;   // ���غ���ļ���.
	DWORD    nStart;          // �ָ����ʼλ��.
	DWORD    nEnd;            // �ָ����ʼλ��.
public:
	void openThread();//���������߳�
	void ParseURL(CString URL,CString &host,CString &path,CString &filename)//���� URL����������ɲ���
	BOOL HttpDownLoad(CString strHostAddr,int nHostPort,CString strHttpAddr,CString strHttpFilename,CString strWriteFileName,int nThread);//��������
	SOCKET DoConnect(CString host ,int port);//������������
	bool fnDownload(CString strUrl,CString strWriteFileName,unsigned long *& downloaded,unsigned long & totalSize,int nThread);//�ж��Ƿ��������
	static DWORD GetFileLength(char *httpHeader);//�õ��ļ���С
};