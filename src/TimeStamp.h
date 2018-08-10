#ifndef _SIMPLELOG_TIMESTAMP_HH
#define _SIMPLELOG_TIMESTAMP_HH

#include <string>

namespace SimpleLog {
    class TimeStamp {
        public:
        /**
           Constructs a TimeStamp representing 'now'.
        **/
        TimeStamp();

        TimeStamp(unsigned long seconds, unsigned long microSeconds = 0);

        inline long getSeconds() const 
		{
            return _seconds;
        };

        inline long getMilliSeconds() const 
		{
            return _microSeconds / 1000;
        };

        inline long getMicroSeconds() const 
		{
            return _microSeconds;
        };

		std::string getFormatTimeStamp() const;	

        /**
           Returns a TimeStamp representing the time at which the application
           started.
        **/
        static inline const TimeStamp& getStartTime() 
		{
            return _startStamp;
        };

        protected:
        static TimeStamp _startStamp;

        long _seconds;
        long _microSeconds;
    };
}

#endif // _SIMPLELOG_TIMESTAMP_HH

