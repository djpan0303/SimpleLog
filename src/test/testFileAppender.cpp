#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <Category.h>
#include <FileAppender.h>

using namespace SimpleLog;

int main()
{

	Category cat1(new FileAppender("fileAppender", "file_appender.log"));
	cat1.info("test1");

	Category cat2(new FileAppender("fileAppender", "file_appender.log"));
	cat2.info("test2");


	Category cat3(new FileAppender("fileAppender", "file_appender1.log"));
	cat3.info("test3");

	Category cat4(new FileAppender("fileAppender", "file_appender1.log", NULL, false));
	cat4.info("test4");

#ifdef ASYNC_LOG
    usleep(500000);
#endif

}
