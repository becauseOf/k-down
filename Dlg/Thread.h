class Thread {
public:
   Thread();
   virtual ~Thread();
   int start();//线程启动函数
   void stop();
   static void sleep(unsigned int);//让当前线程休眠给定时间，单位为毫秒

private:
   HANDLE threadHandle;//处理每个线程
   bool started;
   unsigned int threadID;
};