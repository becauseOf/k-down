//�����������



       /*static void UTF_8ToUnicode(wchar_t* pOut,char *pText);// ��UTF-8ת����Unicode
       static void UnicodeToUTF_8(char* pOut,wchar_t* pText);//Unicode ת����UTF-8
       static void UnicodeToGB2312(char* pOut,wchar_t uData);// ��Unicode ת����GB2312 
       static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 ת����Unicode
       static void GB2312ToUTF_8(string& pOut,char *pText, int pLen);//GB2312 תΪUTF-8
       static void UTF_8ToGB2312(string &pOut, char *pText, int pLen);//UTF-8 תΪGB2312*/


	   //CStringת��char����
	   static void CStringToCharP(CString str,char* bufChar){
		   /*WideCharToMultiByte
	��������: �ú���ӳ��һ��unicode�ַ�����һ�����ֽ��ַ���
	Int WideCharToMultiByte(
		UNIT codepage,//ָ��ִ��ת���Ĵ���ҳ
		DWORD DWFLAGS,//��������ж���Ŀ��ƣ���Ӱ��ʹ���˶������ŵ��ַ�
		LPCWSTR ipwidecharstr,//ָ��Ҫת��Ϊ���ֽ��ַ����Ļ�����
		int cchwidechar��//ָ���ɲ���ipwidecharstrָ��Ļ��������ַ�����
		LPSTR ipmultibytestr��//ָ����ܱ�ת���ַ����Ļ�����
		int cchmultibyte��//ָ���ɲ���ipwidecharstrָ��Ļ��������ַ�����
		LPCSTR ipdefaultchar��//����һ������ת���Ŀ��ַ����������ʹ��pdefaultchar����ָ����ַ�
		LPBOOL pfuseddefaultchar//������һ���ַ�����ת��Ϊ�������ֽ���ʽ�������ͻ�����������Ϊtrue
		)��
	����ֵ������������гɹ�������cchmultibyte��Ϊ�㣬����ֵ����ipmultibytestrָ��Ļ�������д����ֽ���������������гɹ�������cchmultibyte��Ϊ�㣬����ֵ�ǽ��յ���ת���ַ����Ļ�������������ֽ����������������ʧ�ܣ�����ֵΪ�㡣
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

	
	