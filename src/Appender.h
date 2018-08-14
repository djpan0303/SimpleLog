#ifndef _SIMPLELOG_APPENDER_HH
#define _SIMPLELOG_APPENDER_HH

#include <string>
#include <map>
#include <set>
#include <vector>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <Priority.h>
#include <Layout.h>
#include <LoggingEvent.h>


namespace SimpleLog { 
    class Appender {
    protected:
        Appender(const std::string& name);
        
    public:
        virtual ~Appender();
        virtual void doAppend(const LoggingEvent& event) = 0;
        virtual bool reopen() = 0;
        virtual void close() = 0;
        virtual bool requiresLayout() const = 0;
        virtual void setLayout(Layout* layout) = 0;
        inline const std::string& getName() const { return _name; };    
        virtual void setThreshold(Priority::Value priority) = 0;
        virtual Priority::Value getThreshold() = 0; 
	private:
        const std::string _name;
    };
}

#endif // _SIMPLELOG_APPENDER_HH
