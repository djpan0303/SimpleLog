/*
 * Priority.h
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _SIMPLELOG_PRIORITY_HH
#define _SIMPLELOG_PRIORITY_HH

#include <string>
#include <stdexcept>


namespace SLog {

    class Priority {
        public:

		static const int MESSAGE_SIZE; // = 8;


        typedef enum {EMERG  = 0, 
		      FATAL  = 0,
                      ALERT  = 100,
                      CRIT   = 200,
                      ERROR  = 300, 
                      WARN   = 400,
                      NOTICE = 500,
                      INFO   = 600,
                      DEBUG  = 700,
                      NOTSET = 800
        } PriorityLevel;


        typedef int Value;

        static const std::string& getPriorityName(int priority) throw();
	

        static Value getPriorityValue(const std::string& priorityName);
    };
}

#endif // _SIMPLELOG_PRIORITY_HH
