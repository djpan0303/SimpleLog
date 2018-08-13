#ifndef _SIMPLELOG_LOGGINGEVENT_HH
#define _SIMPLELOG_LOGGINGEVENT_HH

#include <string>
#include <Priority.h>
#include <TimeStamp.h>
#include <PThreads.h>

namespace SimpleLog {
    struct LoggingEvent {
    public:
        LoggingEvent(const std::string& logPoint, const std::string& message, Priority::Value priority);
        LoggingEvent(const std::string& message, Priority::Value priority);
		LoggingEvent(const LoggingEvent &);
        std::string logPoint;
        std::string message;
        Priority::Value priority;
        std::string threadName;
        TimeStamp timeStamp;
    };
}

#endif // _SIMPLELOG_LOGGINGEVENT_HH
