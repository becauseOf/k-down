class Thread {
public:
   Thread();
   virtual ~Thread();
   int start();//�߳���������
   void stop();
   static void sleep(unsigned int);//�õ�ǰ�߳����߸���ʱ�䣬��λΪ����

private:
   HANDLE threadHandle;//����ÿ���߳�
   bool started;
   unsigned int threadID;
};