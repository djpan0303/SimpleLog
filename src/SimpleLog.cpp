#include <unistd.h>
#include <iostream>
#include <libgen.h>
#include <SimpleLog.h>
#include <StringUtil.h>

namespace SLog {

	void* thread_proc(void* arg)
	{
		SimpleLog* thread = reinterpret_cast<SimpleLog*>(arg);
		
		while(true)
		{
			thread->svc();	
		}
	
		return NULL;
	}


    SimpleLog::SimpleLog(Appender *appender, Priority::Value priority) : 
		_priority(priority)
    {
		if(appender != NULL)
		{
			_appenderStore.addAppender(appender);
		}
		
		#ifdef ASYNC_LOG
		pthread_t thread;
		int ret = pthread_create(&thread , NULL, thread_proc, this);
		if(ret != 0)
		{
			//throw 
		}
		#endif
    }

    SimpleLog::~SimpleLog() 
    {
    	shutdown();
        _appenderStore.removeAllAppenders();
    }


	void SimpleLog::shutdown()
	{
		#ifdef ASYNC_LOG
		while(_logQueue.size() > 0)
		{
			usleep(300000);
		}
		#endif
	}

    void SimpleLog::setPriority(Priority::Value priority) 
    {
        if (priority > Priority::NOTSET) 
        {
            throw std::invalid_argument("cannot set priority NOTSET on Root SimpleLog");
        }

        _priority = priority;
        // TODO:add pririty field to appeder
        
    }

	bool SimpleLog::addAppender(Appender* appender)
	{
		return _appenderStore.addAppender(appender);	
	}

	void SimpleLog::removeAppender(Appender* appender)
	{
		 _appenderStore.removeAppender(appender);
	}
	void SimpleLog::removeAllAppenders()
	{
		 _appenderStore.removeAllAppenders();
	}

    Priority::Value SimpleLog::getPriority() 
    {
    	return _priority;
    }


    bool SimpleLog::isPriorityEnabled(Priority::Value prio)
    {
		return prio <= _priority;
    }

    #define log_func_tmpl3(file, func, line, prio, stringFormat) do{\
		if (prio < _priority)\
		{ \
            va_list va; \
            va_start(va,stringFormat); \
            _logUnconditionally3(file, func, line, prio, stringFormat, va); \
            va_end(va); \
        } \
    }while(0)
    
	#define log_func_tmpl(prio, stringFormat) do{\
		if (isPriorityEnabled(prio)) \
        { \
            va_list va; \
            va_start(va,stringFormat); \
            _logUnconditionally(prio, stringFormat, va); \
            va_end(va); \
        } \
    }while(0)

    void SimpleLog::_logUnconditionally(Priority::Value priority, 
                                       const char* format, 
                                       va_list arguments) throw() 
     {
        _logUnconditionally2(priority, StringUtil::vform(format, arguments));
    }
    
    void SimpleLog::_logUnconditionally2(Priority::Value priority, 
                                        const std::string& message) throw() 
    {
#ifdef ASYNC_LOG
		std::shared_ptr<LoggingEvent> event(new LoggingEvent(message, priority));
		_logQueue.push(event);
#else
		LoggingEvent event(message, priority);
        _appenderStore.callAppenders(event);
#endif
    }
    
	void SimpleLog::_logUnconditionally3(const char *file, 
										const char *func,
										const int line,
										Priority::Value priority, 
										const char* format, 
										va_list arguments) throw()
	{
		std::string logPoint = std::string(basename(const_cast<char *>(file)))+std::string("@")+std::string(func)+std::string("@")+std::to_string(line);
#ifdef ASYNC_LOG
		std::shared_ptr<LoggingEvent> event(new LoggingEvent(logPoint, StringUtil::vform(format, arguments), priority));
		_logQueue.push(event);
#else
		LoggingEvent event(logPoint, StringUtil::vform(format, arguments), priority);
		_appenderStore.callAppenders(event);
#endif
	}

    void SimpleLog::log(Priority::Value priority, 
                       const char* stringFormat, ...) throw() 
    { 
        if (isPriorityEnabled(priority)) 
        {
            va_list va;
            va_start(va, stringFormat);
            _logUnconditionally(priority, stringFormat, va);
            va_end(va);
        }
    }

    void SimpleLog::log(Priority::Value priority, 
                       const std::string& message) throw() 
    { 
        if (isPriorityEnabled(priority))
            _logUnconditionally2(priority, message);
    }
    
    void SimpleLog::logva(Priority::Value priority, 
                         const char* stringFormat,
                         va_list va) throw() 
    { 
        if (isPriorityEnabled(priority)) 
        {
            _logUnconditionally(priority, stringFormat, va);
        }
    }

    void SimpleLog::debug(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::DEBUG, stringFormat);
    }

    void SimpleLog::debug(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::DEBUG, stringFormat);
    }

    
    void SimpleLog::debug(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::DEBUG))
            _logUnconditionally2(Priority::DEBUG, message);
    }
    
    void SimpleLog::info(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::INFO, stringFormat);
    }

    void SimpleLog::info(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::INFO, stringFormat);
    }

    
    void SimpleLog::info(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::INFO))
            _logUnconditionally2(Priority::INFO, message);
    }
    
    void SimpleLog::notice(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::NOTICE, stringFormat);
    }

    void SimpleLog::notice(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::NOTICE, stringFormat);
    }

    
    void SimpleLog::notice(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::NOTICE))
            _logUnconditionally2(Priority::NOTICE, message);
    }
   

    void SimpleLog::warn(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::WARN, stringFormat);
    }

    
    void SimpleLog::warn(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::WARN))
            _logUnconditionally2(Priority::WARN, message);
    }
    
    void SimpleLog::error(const char* stringFormat, ...) throw() 
    {
        log_func_tmpl(Priority::ERROR, stringFormat);
    }

    void SimpleLog::error(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::ERROR, stringFormat);
    }

    
    void SimpleLog::error(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::ERROR))
            _logUnconditionally2(Priority::ERROR, message);
    }

    void SimpleLog::crit(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::CRIT, stringFormat);
    }

    void SimpleLog::crit(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::CRIT, stringFormat);
    }

    void SimpleLog::crit(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::CRIT))
            _logUnconditionally2(Priority::CRIT, message);
    }

    void SimpleLog::alert(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::ALERT, stringFormat);
    }

    void SimpleLog::alert(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::ALERT, stringFormat);
    }

    
    void SimpleLog::alert(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::ALERT))
            _logUnconditionally2(Priority::ALERT, message);
    }

    void SimpleLog::emerg(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::EMERG, stringFormat);
    }

    void SimpleLog::emerg(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::EMERG, stringFormat);
    }

    
    void SimpleLog::emerg(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::EMERG))
            _logUnconditionally2(Priority::EMERG, message);
    }

    void SimpleLog::fatal(const char* stringFormat, ...) throw() 
    { 
    	log_func_tmpl(Priority::FATAL, stringFormat);
    }
    
    void SimpleLog::fatal(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::FATAL, stringFormat);
    }

    void SimpleLog::fatal(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::FATAL))
            _logUnconditionally2(Priority::FATAL, message);
    }


	void SimpleLog::svc()
	{
#ifdef ASYNC_LOG

		LoggingEventShrPtr p = _logQueue.pop();
		LoggingEvent event(*(p.get()));
		_appenderStore.callAppenders(event);
#endif
	}

} 

