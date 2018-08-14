#include <AppenderStore.h>

namespace SimpleLog {
    bool AppenderStore::addAppender(Appender* appender) 
    {
        if (appender == NULL)
        {
			throw std::invalid_argument("NULL appender");
			return false;
        }

        ScopedLock lock(_appenderMapMutex);
    	std::string name = appender->getName();
        AppenderMap::iterator i = _appenderMap.find(name);
        if (i == _appenderMap.end()) 
        {
            _appenderMap[name] = appender;
            return true;
        }
        else
        {
        	//TODO: throw exception
			return false;
        }    

    }
    
    void AppenderStore::removeAllAppenders() 
    {
        ScopedLock lock(_appenderMapMutex);
        for (AppenderMap::iterator it = _appenderMap.begin();
             it != _appenderMap.end(); it++) 
       	{
            delete it->second;
        }
        _appenderMap.clear();           

    }

    void AppenderStore::removeAppender(Appender* appender) 
    {
        ScopedLock lock(_appenderMapMutex);
		std::string name = appender->getName();
		AppenderMap::iterator it = _appenderMap.find(name);
		if (it != _appenderMap.end()) 
		{
			_appenderMap.erase(it);
		}

	}

    void AppenderStore::callAppenders(const LoggingEvent& event) throw() 
    {
        ScopedLock lock(_appenderMapMutex);
        for(AppenderMap::const_iterator it = _appenderMap.begin();
            it != _appenderMap.end(); it++) 
       	{
            (it->second)->doAppend(event);
        }
    }

	void AppenderStore::setAppenderPriority(std::string &appenderName, Priority::Value priority)
	{
        ScopedLock lock(_appenderMapMutex);
		AppenderMap::iterator i = _appenderMap.find(appenderName);
		 if (i != _appenderMap.end()) 
		 {
			// TODO:set priority field in appeder
		 }
	}
}
