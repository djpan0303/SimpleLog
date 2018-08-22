#include <unistd.h>
#include <iostream>
#include <Category.h>
#include <Priority.h>
#include <BasicLayout.h>
#include <OstreamAppender.h>

using namespace SimpleLog;

int main()
{
    SimpleLog::Category cat(new OstreamAppender("appender", new BasicLayout()));
	cat.info("hello world");
	#ifdef ASYNC_LOG
	sleep(1);
	#endif
	cat.shutdown();
}
