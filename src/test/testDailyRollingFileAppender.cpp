#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <ctime>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>
#include <cstring>
#include <unistd.h>
#include <dirent.h>
#include <DailyRollingFileAppender.h>
#include <Category.h>
#include <OstreamAppender.h>

using namespace SimpleLog;
using namespace std;
static const char* const test_message = "message";
static const char* const daily_file_prefix = "dailyrolling_file.log";
static const char* const nestedDir = "nesteddir";
const char* const nesteddirname = "nesteddir/";


class DailyRollingTest {
	DailyRollingFileAppender* dailyApp, *nestedDirDailyApp;
    Category root;
public:
	bool remove_impl(const char* filename)
	{
	   int res = remove(filename);

	   if (res != 0 && errno != ENOENT)
		  cout << "Can't remove file '" << filename << "'.\n";

	   return res == 0 || (res != 0 && errno == ENOENT);
	}

	bool remove_files()
	{
//	   if (!remove_impl(daily_file_prefix))
//		  return false;

	   return true;
	}

	bool setup()
	{
	   if (!remove_files())
		  return false;

	   dailyApp = new DailyRollingFileAppender(std::string("daily-rolling-appender"), std::string(daily_file_prefix), (unsigned int)1);
	   nestedDirDailyApp = new DailyRollingFileAppender(std::string("nesteddir-daily-rolling-appender"), std::string(nesteddirname).append(daily_file_prefix), 1);
	   root.addAppender(dailyApp);
	   root.addAppender(nestedDirDailyApp);
	   root.setPriority(Priority::DEBUG);

	   return true;
	}

	void make_log_files()
	{
       root.info("message 1");
       root.info("message 2");
       root.info("message 3");
	   root.info("The message before rolling over attempt");
	   dailyApp->rollOver();
	   nestedDirDailyApp->rollOver();
	}

	bool exists(const char* filename)
	{
	   FILE* f = fopen(filename, "r");
	   if (f == NULL)
	   {
		  cout << "File '" << filename << "' doesn't exists.\n";
		  return false;
	   }

	   fclose(f);

	   return true;
	}

	bool check_log_files()
	{
	   bool result = exists(daily_file_prefix);

	   return result && remove_files();
	}
};

int testOnlyDailyRollingFileAppender() {
	DailyRollingTest dailyTest;
	   if (!dailyTest.setup())
	   {
	      cout << "Setup has failed. Check for permissions on files " << daily_file_prefix << "*'.\n";
	      return -1;
	   }

	   dailyTest.make_log_files();

	   if (dailyTest.check_log_files())
	      return 0;
	   else
	      return -1;
}

int main()
{
	int res = testOnlyDailyRollingFileAppender();
	return res;
}
