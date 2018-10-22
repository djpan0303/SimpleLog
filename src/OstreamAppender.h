#ifndef _SIMPLELOG_OSTREAMAPPENDER_HH
#define _SIMPLELOG_OSTREAMAPPENDER_HH

#include <string>
#include <iostream>
#include <LayoutAppender.h>

namespace SLog {

    /**
     * OstreamAppender appends LoggingEvents to ostreams.
     **/
    class OstreamAppender : public LayoutAppender {
        public:
        OstreamAppender(const std::string& name, std::ostream* stream=&std::cout);
        OstreamAppender(const std::string& name, Layout *layout=NULL);
        virtual ~OstreamAppender();
        
        virtual bool reopen();
        virtual void close();

        protected:
        virtual void _append(const LoggingEvent& event);

        std::ostream* _stream;
    };
}

#endif // _SIMPLELOG_OSTREAMAPPENDER_HH
