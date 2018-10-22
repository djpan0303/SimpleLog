#ifndef _SIMPLELOG_LAYOUT_HH
#define _SIMPLELOG_LAYOUT_HH

#include <LoggingEvent.h>
#include <string>

namespace SLog {

/**
 * Extend this abstract class to create your own log layout format.
 **/
    class Layout {
        public:
        /**
         * Destructor for Layout.
         **/
        virtual ~Layout() { };

        /**
         * Formats the LoggingEvent data to a string that appenders can log.
         * Implement this method to create your own layout format.
         * @param event The LoggingEvent.
         * @returns an appendable string.
         **/
        virtual std::string format(const LoggingEvent& event) 
		{
			return event.message+std::string("\n");
		}
    };        
}

#endif // _SIMPLELOG_LAYOUT_HH
