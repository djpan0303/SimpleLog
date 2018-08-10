/*
 * BasicLayout.h
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _SIMPLELOG_BASICLAYOUT_HH
#define _SIMPLELOG_BASICLAYOUT_HH

#include <Layout.h>

namespace SimpleLog {

    /**
     * BasicLayout is a simple fixed format Layout implementation. 
     **/
    class BasicLayout : public Layout {
        public:
        BasicLayout();
        virtual ~BasicLayout();
        virtual std::string format(const LoggingEvent& event);
    };        
}

#endif // _SIMPLELOG_BASICLAYOUT_HH
