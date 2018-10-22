#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <SimpleLog.h>
#include <RollingFileAppender.h>

using namespace SLog;
using namespace std;
static const char* const test_message = "message";

bool remove_impl(const char* filename)
{
   int res = remove(filename);
   
   if (res != 0 && errno != ENOENT)
      cout << "Can't remove file '" << filename << "'.\n";

   return res == 0 || (res != 0 && errno == ENOENT);
}

bool remove_files()
{
   if (!remove_impl("rolling_file.log"))
      return false;
   if (!remove_impl("rolling_file.log.1"))
      return false;
   if (!remove_impl("rolling_file.log.2"))
      return false;

   return true;
}

bool setup(SimpleLog& root)
{
   if (!remove_files())
      return false;

   root.addAppender(new RollingFileAppender("rolling-appender", "rolling_file.log", 40, 3));
   root.setPriority(Priority::DEBUG);

   return true;
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
   bool result = exists("rolling_file.log") &&
                 exists("rolling_file.log.1") &&
                 exists("rolling_file.log.2");

   return result;// && remove_files();
}

int main()
{
    SimpleLog cat;
   if (!setup(cat))
   {
      cout << "Setup has failed. Check for permissions on files 'rolling_file.log*'.\n";
      return -1;
   }

   cat.debug("test1111111111111");
   cat.debug("test2222222222222");
   cat.debug("test3333333333333");
   cat.debug("test4444444444444");
   cat.debug("test5555555555555");
   cat.debug("test6666666666666");
   cat.debug("test7");

   if (check_log_files())
      return 0;
   else 
      return -1;
}
