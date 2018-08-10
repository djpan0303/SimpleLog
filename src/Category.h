#ifndef _SIMPLELOG_CATEGORY_HH
#define _SIMPLELOG_CATEGORY_HH

#include <Appender.h>
#include <LoggingEvent.h>
#include <Priority.h>
#include <map>
#include <vector>
#include <cstdarg>
#include <stdexcept>
#include <memory>
#include <queue>


namespace SimpleLog {

typedef std::map<std::string, Appender*> AppenderMap;

class Category {
public: 
		Category(Appender *appender=NULL, Priority::Value priority = Priority::NOTSET);
        ~Category();
        void setPriority(Priority::Value priority);
        void setAppenderPriority(std::string &appenderName, Priority::Value priority);
        Priority::Value getPriority();
        bool addAppender(Appender* appender);
        void removeAppender(Appender* appender);
        void callAppenders(const LoggingEvent& event) throw();
		void removeAllAppenders();


        void log(Priority::Value priority, const char* stringFormat, ...) throw();
        void log(Priority::Value priority, const std::string& message) throw();
        void logva(Priority::Value priority, const char* stringFormat, va_list va) throw();
         
        void debug(const char* stringFormat, ...) throw(); 
        void debug(const char *file, const char *func, const int line, const char* stringFormat, ...) throw();
        void debug(const std::string& message) throw();
        inline bool isDebugEnabled() throw() { 
            return isPriorityEnabled(Priority::DEBUG);
        };
        
 
        void info(const char* stringFormat, ...) throw(); 
        void info(const char *file, const char *func, const int line, const char* stringFormat, ...) throw();
        void info(const std::string& message) throw();
        inline bool isInfoEnabled() throw() { 
            return isPriorityEnabled(Priority::INFO);
        };

 
        void notice(const char* stringFormat, ...) throw(); 
        void notice(const char *file, const char *func, const int line, const char* stringFormat, ...) throw();
        void notice(const std::string& message) throw();
        inline bool isNoticeEnabled() throw() { 
            return isPriorityEnabled(Priority::NOTICE);
        };

  
        void warn(const char* stringFormat, ...) throw();
        void warn(const char *file, const char *func, const int line, const char* stringFormat, ...) throw();
        void warn(const std::string& message) throw();
        inline bool isWarnEnabled() throw() { 
            return isPriorityEnabled(Priority::WARN);
        };
  
        void error(const char* stringFormat, ...) throw(); 
        void error(const char *file, const char *func, const int line, const char* stringFormat, ...) throw();
        void error(const std::string& message) throw();
        inline bool isErrorEnabled() throw() { 
            return isPriorityEnabled(Priority::ERROR);
        };
 
        void crit(const char* stringFormat, ...) throw(); 
        void crit(const char *file, const char *func, const int line, const char* stringFormat, ...) throw();
        void crit(const std::string& message) throw();
        inline bool isCritEnabled() throw() { 
            return isPriorityEnabled(Priority::CRIT);
        };
        
        void alert(const char* stringFormat, ...) throw();  
        void alert(const char *file, const char *func, const int line, const char* stringFormat, ...) throw();
        void alert(const std::string& message) throw(); 
        inline bool isAlertEnabled() throw() { 
            return isPriorityEnabled(Priority::ALERT);
        };
        
        void emerg(const char* stringFormat, ...) throw();
        void emerg(const char *file, const char *func, const int line, const char* stringFormat, ...) throw();
        void emerg(const std::string& message) throw();
        inline bool isEmergEnabled() throw() { 
            return isPriorityEnabled(Priority::EMERG);
        };
        
        void fatal(const char* stringFormat, ...) throw();
        void fatal(const char *file, const char *func, const int line, const char* stringFormat, ...) throw();
        void fatal(const std::string& message) throw();
        inline bool isFatalEnabled() throw() 
		{ 
            return isPriorityEnabled(Priority::FATAL);
        };
        

	private: 
		typedef std::shared_ptr<LoggingEvent> LoggingEventShrPtr;
		void queue_push(LoggingEventShrPtr event);
		//LoggingEventShrPtr queue_pop();
		bool isPriorityEnabled(Priority::Value prio);
        void _logUnconditionally(Priority::Value priority, 
                                         const char* format, 
                                         va_list arguments) throw();

        void _logUnconditionally2(Priority::Value priority, 
                                          const std::string& message) throw();
                                          
		void _logUnconditionally3(	const char *file, 
											   	const char *func,
												const int line,
											   	Priority::Value priority, 
									 			const char* format, 
									 			va_list arguments) throw();

        volatile Priority::Value _priority;
        AppenderMap _appenderMap;
        Mutex	_appenderMapMutex;
		std::queue<std::string> _queue;
    };

}
#endif // _SIMPLELOG_CATEGORY_HH
