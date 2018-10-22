#include <SimpleLogger.h>
#include <OstreamAppender.h>
#include <BasicLayout.h>
using namespace SLog;

SimpleLog g_simple_logger(new OstreamAppender("appender", new BasicLayout()));

