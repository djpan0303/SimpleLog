#include <unistd.h>
#include <iostream>
#include <SimpleLog.h>
#include <Priority.h>
#include <BasicLayout.h>
#include <OstreamAppender.h>

using namespace SLog;

int main()
{
    SimpleLog cat(new OstreamAppender("appender", new BasicLayout()));
	cat.info("hello world");
	cat.shutdown();
}
