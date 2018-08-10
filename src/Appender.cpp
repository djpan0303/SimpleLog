#include <Appender.h>
#include <iostream>

namespace SimpleLog {
	static int appenders_nifty_counter; // zero initialized at load time
	static char appenderMapStorage_buf[sizeof(Appender::AppenderMapStorage)]; // memory for the nifty-counter singleton object
	Appender::AppenderMapStorage &Appender::_appenderMapStorageInstance = reinterpret_cast<Appender::AppenderMapStorage&> (appenderMapStorage_buf); // memory for placement new

	Appender::AppenderMapStorage::AppenderMapStorage()  { 
		_allAppenders = new AppenderMap(); 
	}
	Appender::AppenderMapStorage::~AppenderMapStorage() { 
		_deleteAllAppenders(); 
		delete _allAppenders; 
	}
	
	Appender::AppenderMapStorageInitializer::AppenderMapStorageInitializer() {
		 if (appenders_nifty_counter++ == 0) {
			 new (&_appenderMapStorageInstance) AppenderMapStorage(); // placement new
		 }
 	}
	Appender::AppenderMapStorageInitializer::~AppenderMapStorageInitializer() {
		if (--appenders_nifty_counter == 0) {
			(&_appenderMapStorageInstance)->~AppenderMapStorage ();
		}
	}

    /* assume _appenderMapMutex locked */
    Appender::AppenderMap& Appender::_getAllAppenders() {
		return *_appenderMapStorageInstance._allAppenders;
    }

    Appender* Appender::getAppender(const std::string& name) {
        ScopedLock lock(_appenderMapStorageInstance._appenderMapMutex);
        AppenderMap& allAppenders = Appender::_getAllAppenders();
        AppenderMap::iterator i = allAppenders.find(name);
        return (allAppenders.end() == i) ? NULL : ((*i).second);
    }
    
    void Appender::_addAppender(Appender* appender) {
        //REQUIRE(_allAppenders.find(appender->getName()) == _getAllAppenders().end())
        ScopedLock lock(_appenderMapStorageInstance._appenderMapMutex);
        _getAllAppenders()[appender->getName()] = appender;
    }

    void Appender::_removeAppender(Appender* appender) {
        ScopedLock lock(_appenderMapStorageInstance._appenderMapMutex);
		//private called from destructor only, but may be triggered by client code in several treads
        _getAllAppenders().erase(appender->getName());
    }
    
    bool Appender::reopenAll() {
        ScopedLock lock(_appenderMapStorageInstance._appenderMapMutex);
        bool result = true;
        AppenderMap& allAppenders = _getAllAppenders();
        for(AppenderMap::iterator i = allAppenders.begin(); i != allAppenders.end(); i++) {
            result = result && ((*i).second)->reopen();
        }
        
        return result;
    }
    
    void Appender::closeAll() {
        ScopedLock lock(_appenderMapStorageInstance._appenderMapMutex);
        AppenderMap& allAppenders = _getAllAppenders();
        for(AppenderMap::iterator i = allAppenders.begin(); i != allAppenders.end(); i++) {
            ((*i).second)->close();
        }
    }
    
    void Appender::_deleteAllAppenders() {
		// deleting each appenders will cause a lock on Appender::_appenderMapMutex to be obtained again within destructor. to avoid nested locks:
		std::vector<Appender*> appenders;
		{
			ScopedLock lock(_appenderMapStorageInstance._appenderMapMutex);
			AppenderMap& allAppenders = _getAllAppenders();
			appenders.reserve(allAppenders.size());
			for(AppenderMap::iterator i = allAppenders.begin(); i != allAppenders.end(); ) {
				Appender* app = (*i).second;
				++i;
				appenders.push_back(app);
			}
		    allAppenders.clear();
		}
		_deleteAllAppendersWOLock(appenders);
	}    

    void Appender::_deleteAllAppendersWOLock(std::vector<Appender*> &appenders) {
    /* assume Appender::_appenderMapMutex not locked */
        AppenderMap& allAppenders = _getAllAppenders();
        for(std::vector<Appender*>::iterator i = appenders.begin(); i != appenders.end(); ++i) {
            Appender *app = (*i);
            delete (app);
        }
    }    

    Appender::Appender(const std::string& name) :
        _name(name) {
        _addAppender(this);
    }
    
    Appender::~Appender() {
        _removeAppender(this);
    }
}
