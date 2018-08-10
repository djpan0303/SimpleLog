#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <dirent.h>
#include <DailyRollingFileAppender.h>
#include <Category.h>

namespace SimpleLog {

	unsigned int DailyRollingFileAppender::maxDaysToKeepDefault = 30;

    DailyRollingFileAppender::DailyRollingFileAppender(const std::string& name,
                                             const std::string& fileName, 
											 Layout *layout,
                                             unsigned int maxDaysToKeep,
                                             bool append,
                                             mode_t mode) :
        FileAppender(name, fileName, layout, append, mode),
        _maxDaysToKeep(maxDaysToKeep != 0 ? maxDaysToKeep : maxDaysToKeepDefault) 
	{
		struct stat statBuf;
		int res;
		time_t t;

		// obtain last modification time
		res = ::stat(fileName.c_str(), &statBuf);
		if (res < 0) 
		{
			t = time(NULL);
		} 
		else 
		{
			t = statBuf.st_mtime;
		}

		localtime_r(&t, &_logsTime);
	}

    DailyRollingFileAppender::DailyRollingFileAppender(const std::string name,
                                             const std::string fileName, 
                                             unsigned int maxDaysToKeep,
                                             bool append,
                                             mode_t mode) :
        FileAppender(name, fileName, NULL, append, mode),
        _maxDaysToKeep(maxDaysToKeep != 0 ? maxDaysToKeep : maxDaysToKeepDefault) 
	{
		struct stat statBuf;
		int res;
		time_t t;

		// obtain last modification time
		res = ::stat(fileName.c_str(), &statBuf);
		if (res < 0) 
		{
			t = time(NULL);
		} 
		else 
		{
			t = statBuf.st_mtime;
		}

		localtime_r(&t, &_logsTime);
	}
	void DailyRollingFileAppender::setMaxDaysToKeep(unsigned int maxDaysToKeep) 
	{
		_maxDaysToKeep = maxDaysToKeep;
	}

	unsigned int DailyRollingFileAppender::getMaxDaysToKeep() const 
	{
		return _maxDaysToKeep;
	}

	void DailyRollingFileAppender::rollOver()
	{
		std::ostringstream filename_s;
		int res_close = ::close(_fd);
		if (res_close != 0) 
		{
			std::cerr << "Error closing file " << _fileName << std::endl;
		}
		filename_s << _fileName << "." << _logsTime.tm_year + 1900 << "-"
						<< std::setfill('0') << std::setw(2) << _logsTime.tm_mon + 1 << "-"
						<< std::setw(2) << _logsTime.tm_mday << std::ends;
		const std::string lastFn = filename_s.str();
		int res_rename = ::rename(_fileName.c_str(), lastFn.c_str());
		if (res_rename != 0) 
		{
			std::cerr << "Error renaming file " << _fileName << " to " << lastFn << std::endl;
		}

		_fd = ::open(_fileName.c_str(), _flags, _mode);
		if (_fd == -1) 
		{
			std::cerr << "Error opening file " << _fileName << std::endl;
		}

		const time_t oldest = time(NULL) - _maxDaysToKeep * 60 * 60 * 24;


#define PATHDELIMITER "\\"

		// iterate over files around log file and delete older with same prefix
		const std::string::size_type last_delimiter = _fileName.rfind(PATHDELIMITER);
		const std::string dirname((last_delimiter == std::string::npos)? "." : _fileName.substr(0, last_delimiter));
		const std::string filname((last_delimiter == std::string::npos)? _fileName : _fileName.substr(last_delimiter+1, _fileName.size()-last_delimiter-1));

		struct dirent **entries;
		int nentries = scandir(dirname.c_str(), &entries, 0, alphasort);
		if (nentries < 0)
			return;
		for (int i = 0; i < nentries; i++) 
		{
			struct stat statBuf;
			const std::string fullfilename = dirname + PATHDELIMITER + entries[i]->d_name;
			int res = ::stat(fullfilename.c_str(), &statBuf);
			if ((res == -1) || (!S_ISREG(statBuf.st_mode))) 
			{
				free(entries[i]);
				continue;
			}
			if (statBuf.st_mtime < oldest && strstr(entries[i]->d_name, filname.c_str())) 
			{
				std::cout << " Deleting " << fullfilename.c_str() << std::endl;
				::unlink(fullfilename.c_str());
			}
			free(entries[i]);
		}
		free(entries);
	}

	void DailyRollingFileAppender::_append(const SimpleLog::LoggingEvent &event)
	{
		struct tm now;
		time_t t = time(NULL);

		bool timeok = localtime_r(&t, &now) != NULL;

		if (timeok) 
		{
			if ((now.tm_mday != _logsTime.tm_mday) ||
				(now.tm_mon != _logsTime.tm_mon) ||
				(now.tm_year != _logsTime.tm_year)) 
			{
				rollOver();
				_logsTime = now;
			}
		}
		SimpleLog::FileAppender::_append(event);
	}
}
