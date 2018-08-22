#include <SimpleLog.h>
#include <FileAppender.h>
#include <BasicLayout.h>
#include <OSThread.h>
#include <unistd.h>

using namespace SimpleLog;
Category logger;

class TestThread : public Thread {
public:
	int svc()
	{
		SL_LOG_INFO(logger, "thread test.should see theadId:0x%lx", thread_id());
		return 0;
	}
}; 

int main()
{
#ifdef ASYNC_LOG
	Appender *appender = new FileAppender("fileappender", "AsyncSimpleLog-test.log", new BasicLayout(), false);
	logger.addAppender(appender);

	SL_LOG_INFO(logger, "hello, %s", "world");
	SL_LOG_INFO(logger, "hello, john");

	TestThread t;
	t.init();
	t.run();
	t.stop();
	sleep(1);
	logger.shutdown();
#endif
}
