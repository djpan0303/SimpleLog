#include <unistd.h>
#include <iostream>
#include <libgen.h>
#include <Category.h>
#include <StringUtil.h>

namespace SimpleLog {
	void* thread_proc(void* arg)
	{
		Category* thread = reinterpret_cast<Category*>(arg);
		
		while(true)
		{
			thread->svc();	
		}
	
		return NULL;
	}


    Category::Category(Appender *appender, Priority::Value priority) : 
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

    Category::~Category() 
    {
        _appenderStore.removeAllAppenders();
        shutdown();
    }


	void Category::shutdown()
	{
	}

    void Category::setPriority(Priority::Value priority) 
    {
        if (priority > Priority::NOTSET) 
        {
            throw std::invalid_argument("cannot set priority NOTSET on Root Category");
        }

        _priority = priority;
        // TODO:add pririty field to appeder
        
    }

	bool Category::addAppender(Appender* appender)
	{
		return _appenderStore.addAppender(appender);	
	}

	void Category::removeAppender(Appender* appender)
	{
		 _appenderStore.removeAppender(appender);
	}
	void Category::removeAllAppenders()
	{
		#ifdef ASYNC_LOG
		while(_logQueue.size() > 0)
		{
			usleep(300000);
		}
		#endif
		 _appenderStore.removeAllAppenders();
	}

    Priority::Value Category::getPriority() 
    {
    	return _priority;
    }


    bool Category::isPriorityEnabled(Priority::Value prio)
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

    void Category::_logUnconditionally(Priority::Value priority, 
                                       const char* format, 
                                       va_list arguments) throw() 
     {
        _logUnconditionally2(priority, StringUtil::vform(format, arguments));
    }
    
    void Category::_logUnconditionally2(Priority::Value priority, 
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
    
	void Category::_logUnconditionally3(const char *file, 
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

    void Category::log(Priority::Value priority, 
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

    void Category::log(Priority::Value priority, 
                       const std::string& message) throw() 
    { 
        if (isPriorityEnabled(priority))
            _logUnconditionally2(priority, message);
    }
    
    void Category::logva(Priority::Value priority, 
                         const char* stringFormat,
                         va_list va) throw() 
    { 
        if (isPriorityEnabled(priority)) 
        {
            _logUnconditionally(priority, stringFormat, va);
        }
    }

    void Category::debug(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::DEBUG, stringFormat);
    }

    void Category::debug(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::DEBUG, stringFormat);
    }

    
    void Category::debug(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::DEBUG))
            _logUnconditionally2(Priority::DEBUG, message);
    }
    
    void Category::info(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::INFO, stringFormat);
    }

    void Category::info(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::INFO, stringFormat);
    }

    
    void Category::info(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::INFO))
            _logUnconditionally2(Priority::INFO, message);
    }
    
    void Category::notice(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::NOTICE, stringFormat);
    }

    void Category::notice(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::NOTICE, stringFormat);
    }

    
    void Category::notice(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::NOTICE))
            _logUnconditionally2(Priority::NOTICE, message);
    }
   

    void Category::warn(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::WARN, stringFormat);
    }

    
    void Category::warn(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::WARN))
            _logUnconditionally2(Priority::WARN, message);
    }
    
    void Category::error(const char* stringFormat, ...) throw() 
    {
        log_func_tmpl(Priority::ERROR, stringFormat);
    }

    void Category::error(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::ERROR, stringFormat);
    }

    
    void Category::error(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::ERROR))
            _logUnconditionally2(Priority::ERROR, message);
    }

    void Category::crit(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::CRIT, stringFormat);
    }

    void Category::crit(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::CRIT, stringFormat);
    }

    void Category::crit(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::CRIT))
            _logUnconditionally2(Priority::CRIT, message);
    }

    void Category::alert(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::ALERT, stringFormat);
    }

    void Category::alert(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::ALERT, stringFormat);
    }

    
    void Category::alert(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::ALERT))
            _logUnconditionally2(Priority::ALERT, message);
    }

    void Category::emerg(const char* stringFormat, ...) throw() 
    { 
        log_func_tmpl(Priority::EMERG, stringFormat);
    }

    void Category::emerg(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::EMERG, stringFormat);
    }

    
    void Category::emerg(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::EMERG))
            _logUnconditionally2(Priority::EMERG, message);
    }

    void Category::fatal(const char* stringFormat, ...) throw() 
    { 
    	log_func_tmpl(Priority::FATAL, stringFormat);
    }
    
    void Category::fatal(const char *file, const char *func, const int line, const char* stringFormat, ...) throw()
    { 
        log_func_tmpl3(file, func, line, Priority::FATAL, stringFormat);
    }

    void Category::fatal(const std::string& message) throw() 
    { 
        if (isPriorityEnabled(Priority::FATAL))
            _logUnconditionally2(Priority::FATAL, message);
    }


	void Category::svc()
	{
#ifdef ASYNC_LOG

		LoggingEventShrPtr p = _logQueue.pop();
		LoggingEvent event(*(p.get()));
		_appenderStore.callAppenders(event);
#endif
	}

} 

