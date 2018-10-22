#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <RollingFileAppender.h>
#include <SimpleLog.h>

namespace SLog {

    RollingFileAppender::RollingFileAppender(const std::string& name,
                                             const std::string& fileName, 
											 Layout *layout,
                                             size_t maxFileSize, 
                                             unsigned int maxBackupIndex,
                                             bool append,
                                             mode_t mode) :
        FileAppender(name, fileName, layout, append, mode),
        _maxBackupIndex(maxBackupIndex > 0 ? maxBackupIndex : 1),
        _maxBackupIndexWidth((_maxBackupIndex > 0) ? log10((float)_maxBackupIndex)+1 : 1),
        _maxFileSize(maxFileSize) 
	{

    }

    RollingFileAppender::RollingFileAppender(const std::string& name,
                                             const std::string& fileName, 
                                             size_t maxFileSize, 
                                             unsigned int maxBackupIndex,
                                             bool append,
                                             mode_t mode) :
        FileAppender(name, fileName, NULL, append, mode),
        _maxBackupIndex(maxBackupIndex > 0 ? maxBackupIndex : 1),
        _maxBackupIndexWidth((_maxBackupIndex > 0) ? log10((float)_maxBackupIndex)+1 : 1),
        _maxFileSize(maxFileSize) 
	{

    }

    void RollingFileAppender::setMaxBackupIndex(unsigned int maxBackups) 
	{ 
        _maxBackupIndex = maxBackups; 
        _maxBackupIndexWidth = (_maxBackupIndex > 0) ? log10((float)_maxBackupIndex)+1 : 1;
    }
    
    unsigned int RollingFileAppender::getMaxBackupIndex() const 
	{ 
        return _maxBackupIndex; 
    }

    void RollingFileAppender::setMaximumFileSize(size_t maxFileSize) 
	{
        _maxFileSize = maxFileSize;
    }

    size_t RollingFileAppender::getMaxFileSize() const 
	{ 
        return _maxFileSize; 
    }

    void RollingFileAppender::rollOver() 
	{
        ::close(_fd);

		std::ostringstream filename_stream;
		filename_stream << _fileName << "." << std::setw( _maxBackupIndexWidth ) << std::setfill( '0' ) << _maxBackupIndex << std::ends;
		// remove the very last (oldest) file
		std::string last_log_filename = filename_stream.str();
		// std::cout << last_log_filename << std::endl; // removed by request on sf.net #140
		::remove(last_log_filename.c_str());
		
		// rename each existing file to the consequent one
		for(unsigned int i = _maxBackupIndex; i > 1; i--) 
		{
			filename_stream.str(std::string());
			filename_stream << _fileName << '.' << std::setw( _maxBackupIndexWidth ) << std::setfill( '0' ) << i - 1 << std::ends;  // set padding so the files are listed in order
			::rename(filename_stream.str().c_str(), last_log_filename.c_str());
			last_log_filename = filename_stream.str();
		}
		// new file will be numbered 1
		::rename(_fileName.c_str(), last_log_filename.c_str());
        _fd = ::open(_fileName.c_str(), _flags, _mode);
    }

    void RollingFileAppender::_append(const LoggingEvent& event) 
	{
        FileAppender::_append(event);
        off_t offset = ::lseek(_fd, 0, SEEK_END);
        if (offset < 0) 
		{
            // XXX we got an error, ignore for now
			return;
        } 

		if(static_cast<size_t>(offset) >= _maxFileSize) 
		{
			rollOver();
		}
    }
}
