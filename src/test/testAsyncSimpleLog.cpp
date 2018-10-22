#include <SimpleLog.h>
#include <FileAppender.h>
#include <BasicLayout.h>
#include <unistd.h>
#include <pthread.h>

using namespace SLog;
SimpleLog logger;


void *svc(void *arg)
{
	SL_LOG_INFO(logger, "thread test.should see theadId:0x%lx", pthread_self());
	return 0;
}


int main()
{
#ifdef ASYNC_LOG
	Appender *appender = new FileAppender("fileappender", "AsyncSimpleLog-test.log", new BasicLayout(), false);
	logger.addAppender(appender);

	SL_LOG_INFO(logger, "hello, %s", "world");
	SL_LOG_INFO(logger, "hello, john");

	pthread_t pid;
	pthread_create(&pid, NULL, svc, NULL);
	pthread_join(pid, NULL);
	
	sleep(1);
	logger.shutdown();
#endif
}
