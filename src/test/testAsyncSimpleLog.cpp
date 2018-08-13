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
		SL_LOG_INFO(logger, "thread test.should see theadId:%ld", thread_id());
		return 0;
	}
}; 

int main()
{
	Appender *appender = new FileAppender("fileappender", "AsyncSimpleLog-test.log", new BasicLayout(), false);
	logger.addAppender(appender);
	logger.init();
	logger.run();

	SL_LOG_INFO(logger, "hello, %s", "world");
	SL_LOG_INFO(logger, "hello, john");

	TestThread t;
	t.init();
	t.run();
	t.stop();
	sleep(2);
	logger.stop();
}
