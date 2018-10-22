#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <SimpleLog.h>
#include <FileAppender.h>

using namespace SLog;

int main()
{

	SimpleLog cat1(new FileAppender("fileAppender", "file_appender.log"));
	cat1.info("test1");

	SimpleLog cat2(new FileAppender("fileAppender", "file_appender.log"));
	cat2.info("test2");


	SimpleLog cat3(new FileAppender("fileAppender", "file_appender1.log"));
	cat3.info("test3");

	SimpleLog cat4(new FileAppender("fileAppender", "file_appender1.log", NULL, false));
	cat4.info("test4");
}
