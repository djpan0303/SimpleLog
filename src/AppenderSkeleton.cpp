/*
 * AppenderSkeleton.cpp
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include <AppenderSkeleton.h>

namespace SLog {

    AppenderSkeleton::AppenderSkeleton(const std::string& name) :
        Appender(name),
        _threshold(Priority::NOTSET){
    }

    AppenderSkeleton::~AppenderSkeleton() {
    }
    
    bool AppenderSkeleton::reopen() {
        return true;
    }
    
    void AppenderSkeleton::doAppend(const LoggingEvent& event) {
        if ((Priority::NOTSET == _threshold) || (event.priority <= _threshold)) {
        	{
                _append(event);
            }
        }
    }

    void AppenderSkeleton::setThreshold(Priority::Value priority) {
        _threshold = priority;
    }
    
    Priority::Value AppenderSkeleton::getThreshold() {
        return _threshold;
    }
    
}

