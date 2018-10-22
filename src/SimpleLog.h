#ifndef _SIMPLELOG_CATEGORY_HH
#define _SIMPLELOG_CATEGORY_HH

#include <map>
#include <cstdarg>
#include <stdexcept>
#include <memory>
#include <Appender.h>
#include <LoggingEvent.h>
#include <Priority.h>
#include <TMsgQueue.h>
#include <config.h>
#include <AppenderStore.h>

namespace SLog {

#define SL_LOG_DEBUG(logger, format, ...) \
		logger.debug(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);
	
#define SL_LOG_INFO(logger, format, ...) \
		logger.info(__FILE__,__func__,	__LINE__, format, ##__VA_ARGS__);
	
#define SL_LOG_NOTICE(logger, format, ...) \
		logger.notice(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);
	
#define SL_LOG_WARN(logger, format, ...) \
		logger.warn(__FILE__,__func__,	__LINE__, format, ##__VA_ARGS__);
	
#define SL_LOG_ERROR(logger, format, ...) \
		logger.error(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);
	
#define SL_LOG_CRIT(logger, format, ...) \
		logger.crit(__FILE__,__func__,	__LINE__, format, ##__VA_ARGS__);
	
#define SL_LOG_ALERT(logger, format, ...) \
		logger.alert(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);
	
#define SL_LOG_EMERG(logger, format, ...) \
		logger.emerg(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);
	
#define SL_LOG_FATAL(logger, format, ...) \
		logger.fatal(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

typedef std::shared_ptr<LoggingEvent> LoggingEventShrPtr;

class SimpleLog
{
public: 
		SimpleLog(Appender *appender=NULL, Priority::Value priority = Priority::NOTSET);
        ~SimpleLog();

        void shutdown();
        void setPriority(Priority::Value priority);
        Priority::Value getPriority();

		bool addAppender(Appender* appender);
		void removeAppender(Appender* appender);
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
        
		void svc();
	private: 
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
		AppenderStore _appenderStore;
#ifdef ASYNC_LOG
		TMsgQueue<LoggingEventShrPtr> _logQueue;		
#endif
    };
}
#endif // _SIMPLELOG_CATEGORY_HH
