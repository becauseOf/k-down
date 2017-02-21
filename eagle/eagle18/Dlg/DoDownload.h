class DoDownload{
private:
	BOOL FileCut(File *fl, FILE *flread);//文件分割以便多线程下载
	BOOL FileCombine(File *fl, FILE *flwrite);//文件组合，生成目标文件

public:
public:
	CString  szHostAddr;      // Host地址.
	int      nHostPort;       // Host端口号.
	CString  szHttpAddr;      // Http文件地址.
	CString  szHttpFilename;  // Http文件名.
	CString  szDesFilename;   // 下载后的文件名.
	DWORD    nStart;          // 分割的起始位置.
	DWORD    nEnd;            // 分割的起始位置.
public:
	void openThread();//开启下载线程
	void ParseURL(CString URL,CString &host,CString &path,CString &filename)//解析 URL，返回其组成部分
	BOOL HttpDownLoad(CString strHostAddr,int nHostPort,CString strHttpAddr,CString strHttpFilename,CString strWriteFileName,int nThread);//进行下载
	SOCKET DoConnect(CString host ,int port);//进行网络连接
	bool fnDownload(CString strUrl,CString strWriteFileName,unsigned long *& downloaded,unsigned long & totalSize,int nThread);//判断是否完成下载
	static DWORD GetFileLength(char *httpHeader);//得到文件大小
};