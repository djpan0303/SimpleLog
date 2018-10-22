#include <LoggingEvent.h>

namespace SLog {
    
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

	LoggingEvent::LoggingEvent(const LoggingEvent &e)
	{
		logPoint = e.logPoint;
		message = e.message; 
		priority = e.priority;
		threadName = e.threadName;
		timeStamp = e.timeStamp;
	}
}
