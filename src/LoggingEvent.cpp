#include <LoggingEvent.h>

namespace SimpleLog {
    
    LoggingEvent::LoggingEvent(const std::string& logPoint_, 
                               const std::string& message_,
                               Priority::Value priority_) :
        logPoint(logPoint_),
        message(message_),
        priority(priority_),
        threadName(getThreadId()) 
	{
    }

    LoggingEvent::LoggingEvent(const std::string& message_,
                               Priority::Value priority_) :
        message(message_),
        priority(priority_),
        threadName(getThreadId()) 
	{
    }
}
