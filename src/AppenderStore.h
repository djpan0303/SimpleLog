#ifndef __SIMPLELOG_APPENDER_STORE_H__
#define __SIMPLELOG_APPENDER_STORE_H__
#include <Appender.h>
#include <PThreads.h>
#include <map>
namespace SLog {

typedef std::map<std::string, Appender*> AppenderMap;

class AppenderStore {
public:
	bool addAppender(Appender* appender);
	void removeAppender(Appender* appender);
	void callAppenders(const LoggingEvent& event) throw();
	void removeAllAppenders();
    void setAppenderPriority(std::string &appenderName, Priority::Value priority);
private:
    AppenderMap _appenderMap;
    Mutex	_appenderMapMutex;
};

}
#endif //__SIMPLELOG_APPENDER_STORE_H__
