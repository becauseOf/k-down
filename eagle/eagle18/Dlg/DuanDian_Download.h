class DuanDian_Download: public Thread
{
public:
	ChineseCode chineseCode;
	bool startDownload(Thread thr[i]);//��ʼ����
	bool addDownloadTask(const char* remoteUrl, const char* localFolder);//�����������
	DownloadHelper();
	virtual ~DownloadHelper();
    bool stopDownload(Thread thr[i]);//��ͣ����
	//������ɺ���õĺ���
	void onFinish();
private:
	bool exist(int index);//�ж������б���ļ��Ƿ��Ѿ�����
	vector<string> downloadListRemoteURLs;//�ļ�����url·��
	vector<string> downloadListLocalFolders;//�ļ��ڱ��ر����·��
};