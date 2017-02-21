//解决编码问题



       /*static void UTF_8ToUnicode(wchar_t* pOut,char *pText);// 把UTF-8转换成Unicode
       static void UnicodeToUTF_8(char* pOut,wchar_t* pText);//Unicode 转换成UTF-8
       static void UnicodeToGB2312(char* pOut,wchar_t uData);// 把Unicode 转换成GB2312 
       static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 转换成Unicode
       static void GB2312ToUTF_8(string& pOut,char *pText, int pLen);//GB2312 转为UTF-8
       static void UTF_8ToGB2312(string &pOut, char *pText, int pLen);//UTF-8 转为GB2312*/


	   //CString转到char数组
	   static void CStringToCharP(CString str,char* bufChar){
		   /*WideCharToMultiByte
	函数功能: 该函数映射一个unicode字符串到一个多字节字符串
	Int WideCharToMultiByte(
		UNIT codepage,//指定执行转换的代码页
		DWORD DWFLAGS,//允许你进行额外的控制，会影响使用了读音符号的字符
		LPCWSTR ipwidecharstr,//指定要转换为宽字节字符串的缓冲区
		int cchwidechar，//指定由参数ipwidecharstr指向的缓冲区的字符个数
		LPSTR ipmultibytestr，//指向接受被转换字符串的缓冲区
		int cchmultibyte，//指定由参数ipwidecharstr指向的缓冲区的字符个数
		LPCSTR ipdefaultchar，//遇到一个不能转换的宽字符，函数变回使用pdefaultchar参数指向的字符
		LPBOOL pfuseddefaultchar//至少有一个字符不能转换为其他多字节形式，函数就会把这个变量设为true
		)；
	返回值：如果函数运行成功，并且cchmultibyte不为零，返回值是由ipmultibytestr指向的缓冲区中写入的字节数；如果函数运行成功，并且cchmultibyte不为零，返回值是接收到待转换字符串的缓冲区所必需的字节数。如果函数运行失败，返回值为零。
	*/
			int iByteLen = WideCharToMultiByte(CP_ACP,
				0,
				str,
				str.GetLength(),
				NULL,
				0,
				NULL,
				NULL);
			WideCharToMultiByte(CP_ACP,0,str,str.GetLength(),bufChar,iByteLen,NULL,NULL);
			bufChar[iByteLen]='\0';
			return;
		}

	
	