#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <OstreamAppender.h>

namespace SimpleLog {
 
    OstreamAppender::OstreamAppender(const std::string& name, std::ostream* stream): 
        LayoutAppender(name),
        _stream(stream) 
	{
    }

    OstreamAppender::OstreamAppender(const std::string& name, Layout *layout): 
        LayoutAppender(name),
        _stream(&std::cout) 
	{
		if(layout != NULL)
		{
			setLayout(layout);
		}
    }
    OstreamAppender::~OstreamAppender() 
	{
        close();
    }

    void OstreamAppender::close() 
	{
    }

    void OstreamAppender::_append(const LoggingEvent& event) 
	{
        (*_stream) << _getLayout().format(event);
        if (!_stream->good()) {
            // XXX help! help!
        }
    }

    bool OstreamAppender::reopen() 
	{
        return true;
    }      
}
