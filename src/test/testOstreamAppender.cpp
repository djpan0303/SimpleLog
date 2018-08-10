#include <stdio.h>
#include <iostream>
#include <Category.h>
#include <Appender.h>
#include <OstreamAppender.h>
#include <Priority.h>

using namespace SimpleLog;

void testLogva(Category& category, Priority::Value priority, const char* stringFormat, ...)
{
    va_list va;
    va_start(va, stringFormat);
    category.logva(priority, stringFormat, va);
    va_end(va);
} /* end testLogva */


void testMultiAppenders(Category& root)
{
    Appender* appender = new OstreamAppender("appender", &std::cout);
    Appender* appender2 = new OstreamAppender("appender2", &std::cout);
    Appender* appender3 = new OstreamAppender("appender3", &std::cout);

    root.setPriority(Priority::ERROR);

    // clear root's initial appender
    root.removeAllAppenders();

    root.addAppender(appender);
    root.addAppender(appender2);
    root.addAppender(appender3);

    // dump a message - should see three on the screen
    std::cout << "You should see three lines of \"root error #1\"" << std::endl;
    root.error("root error #1");
    std::cout << "Did you?" << std::endl;

    // clear all appenders
    root.removeAllAppenders();

    // dump a message - should not see it on the screen
    std::cout << "You should not see any lines of  \"root error #2\"" << std::endl;
    root.error("root error #2");
    std::cout << "Did you?" << std::endl;



    // add three appenders to root category
    appender = new OstreamAppender("appender", &std::cout);
    appender2 = new OstreamAppender("appender2", &std::cout);

    root.addAppender(appender);
    root.addAppender(appender2);

    // test removing valid and invalid
    root.removeAppender(appender);
    root.removeAppender(appender2);

} /* end testMultiAppenders() */

void testSingleAppender(Category& root)
{
    Appender* appender = new OstreamAppender("appender", &std::cout);    
	root.addAppender(appender);
    root.info("you should see me");
    root.removeAppender(appender);
    root.info("you should not see me");
}

int main(int argc, char** argv) 
{    
    Category root;
    testSingleAppender(root);
    testMultiAppenders(root);

    char lengthy1[] = "Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. Test for variable-arguments lists overflow. ";
    testLogva(root, Priority::ERROR, "This contains really lengthy strings which should be logged well (%d bytes): %s", sizeof(lengthy1), lengthy1);

    return 0;
}
