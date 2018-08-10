#include <memory>
#include <sstream>
#include <BasicLayout.h>
#include <Priority.h>

namespace SimpleLog {

    BasicLayout::BasicLayout() 
	{
    }
    
    BasicLayout::~BasicLayout() 
	{
    }

    std::string BasicLayout::format(const LoggingEvent& event) 
	{
        std::ostringstream message;

        const std::string& priorityName = Priority::getPriorityName(event.priority);
        message << priorityName << "|" << event.timeStamp.getFormatTimeStamp() << "|"
				<< event.threadName << "|" << event.logPoint << "|" 
                << event.message << std::endl;

        return message.str();
    }
}
