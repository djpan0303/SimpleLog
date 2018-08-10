#include <LayoutAppender.h>

namespace SimpleLog {

    LayoutAppender::LayoutAppender(const std::string& name) : 
            AppenderSkeleton(name),
            _layout(new Layout()) 
	{

    }
    
    LayoutAppender::~LayoutAppender() 
	{
        delete _layout;
    }

    bool LayoutAppender::requiresLayout() const 
	{
        return true;
    }

    void LayoutAppender::setLayout(Layout* layout) 
	{
		if (layout != _layout) 
		{
			Layout *oldLayout = _layout;
			_layout = (layout == NULL) ? new Layout() : layout;
			delete oldLayout;
		}
    }

    Layout& LayoutAppender::_getLayout() 
	{
        return *_layout;
    }
}
