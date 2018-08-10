#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <Category.h>
#include <FileAppender.h>

using namespace SimpleLog;

int main()
{
	{
		Category cat(new FileAppender("fileAppender", "file_appender.log"));
		cat.info("test1");
	}
	{
		Category cat(new FileAppender("fileAppender", "file_appender.log"));
		cat.info("test2");
	}
	{
		Category cat(new FileAppender("fileAppender", "file_appender1.log"));
		cat.info("test3");
	}
	{
		Category cat(new FileAppender("fileAppender", "file_appender1.log", NULL, false));
		cat.info("test4");
	}
}
