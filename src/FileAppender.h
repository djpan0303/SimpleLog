#ifndef _SIMPLELOG_FILEAPPENDER_HH
#define _SIMPLELOG_FILEAPPENDER_HH

#include <LayoutAppender.h>
#include <string>
#include <stdarg.h>

namespace SLog {

    class FileAppender : public LayoutAppender {
        public:

        FileAppender(const std::string& name, const std::string& fileName,
                     Layout *out=NULL, bool append = true, mode_t mode = 00644);
        FileAppender(const std::string& name, int fd);
        virtual ~FileAppender();
        
        virtual bool reopen();

        virtual void close();
        virtual void setAppend(bool append);

        virtual bool getAppend() const;

        virtual void setMode(mode_t mode);

        virtual mode_t getMode() const;

        protected:
        virtual void _append(const LoggingEvent& event);

        const std::string _fileName;
        int _fd;
        int _flags;
        mode_t _mode;
    };
}

#endif // _SIMPLELOG_FILEAPPENDER_HH
