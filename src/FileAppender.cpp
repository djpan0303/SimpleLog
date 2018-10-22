#include <unistd.h>
#include <memory>
#include <stdio.h>
#include <time.h>
#include <FileAppender.h>
#include <SimpleLog.h>

namespace SLog {

    FileAppender::FileAppender(const std::string& name, 
                               const std::string& fileName,
							   Layout *layout,
                               bool append,
                               mode_t mode) : 
            LayoutAppender(name),
            _fileName(fileName),
            _flags(O_CREAT | O_APPEND | O_WRONLY),
            _mode(mode) 
	{
        if (append == false)
		{
            _flags |= O_TRUNC;
		}
		if(layout != NULL)
		{
			setLayout(layout);
		}
        _fd = ::open(_fileName.c_str(), _flags, _mode);
    }
    

    FileAppender::FileAppender(const std::string& name, int fd) :
        LayoutAppender(name),
        _fileName(""),
        _fd(fd),
        _flags(O_CREAT | O_APPEND | O_WRONLY),
        _mode(00644) 
	{

    }
    
    FileAppender::~FileAppender() 
	{
        close();
    }

    void FileAppender::close() 
	{
        if (_fd!=-1) 
		{
            ::close(_fd);
            _fd=-1;
        }
    }

    void FileAppender::setAppend(bool append) 
	{
        if (append) 
		{
            _flags &= ~O_TRUNC;
        } 
		else 
		{
            _flags |= O_TRUNC;
        }
    }

    bool FileAppender::getAppend() const 
	{
        return (_flags & O_TRUNC) == 0;
    }

    void FileAppender::setMode(mode_t mode) 
	{
        _mode = mode;
    }

    mode_t FileAppender::getMode() const 
	{
        return _mode;
    }

    void FileAppender::_append(const LoggingEvent& event) 
	{
        std::string message(_getLayout().format(event));
        if (!::write(_fd, message.data(), message.length())) 
		{
            // XXX help! help!
        }
    }

    bool FileAppender::reopen() 
	{
        if (_fileName == "") 
		{
			return false;
		}

		int fd = ::open(_fileName.c_str(), _flags, _mode);
		if (fd < 0)
		{
			return false;
		}

		if (_fd != -1)
		{
			::close(_fd);
		}
		_fd = fd;
		return true;
    }
}
