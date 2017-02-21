class DuanDian_Download: public Thread
{
public:
	ChineseCode chineseCode;
	bool startDownload(Thread thr[i]);//开始下载
	bool addDownloadTask(const char* remoteUrl, const char* localFolder);//添加下载任务
	DownloadHelper();
	virtual ~DownloadHelper();
    bool stopDownload(Thread thr[i]);//暂停下载
	//下载完成后调用的函数
	void onFinish();
private:
	bool exist(int index);//判断下载列表的文件是否已经存在
	vector<string> downloadListRemoteURLs;//文件网络url路径
	vector<string> downloadListLocalFolders;//文件在本地保存的路径
};