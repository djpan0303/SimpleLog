#include <Category.h>
#include <Priority.h>
#include <BasicLayout.h>
#include <iostream>
#include <OstreamAppender.h>

using namespace SimpleLog;

int main()
{
    SimpleLog::Category *cat = new Category(new OstreamAppender("appender", new BasicLayout()));
	cat->info("hello world");
}
