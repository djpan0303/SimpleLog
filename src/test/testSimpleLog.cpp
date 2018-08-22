#include <unistd.h>
#include <SimpleLog.h>
#include <FileAppender.h>
#include <BasicLayout.h>
#include <OSThread.h>

using namespace SimpleLog;

class TestThread : public Thread {
public:
	int svc()
	{
		Category logger2(new FileAppender("fileappender", "SimpleLog-test1.log", new BasicLayout(), false));
		SL_LOG_INFO(logger2, "thread test.should see theadId:0x%lx", thread_id());
		#ifdef ASYNC_LOG
		usleep(500000);
		#endif
		return 0;
	}
}; 

int main()
{
	Category logger(new FileAppender("fileappender", "SimpleLog-test.log", NULL, false));
	SL_LOG_INFO(logger, "hello, %s", "world");
	SL_LOG_INFO(logger, "hello, john");
	Category logger1(new FileAppender("fileappender", "SimpleLog-test1.log", new BasicLayout(), false));
	SL_LOG_INFO(logger1, "hello, %s", "world");
	SL_LOG_INFO(logger1, "hello, john");
	
	TestThread t;
	t.init();
	t.run();	
	t.stop();
	#ifdef ASYNC_LOG
	sleep(2);
	#endif
	
}
