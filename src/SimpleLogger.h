#ifndef _SIMPLELOG_SIMPLE_LOGGER_HH
#define _SIMPLELOG_SIMPLE_LOGGER_HH

#include <SimpleLog.h>
#include <stdio.h>

extern SLog::SimpleLog g_simple_logger;

#define LOG_DEBUG(format, ...) \
		g_simple_logger.debug(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);
	
#define LOG_INFO(format, ...) \
		g_simple_logger.info(__FILE__,__func__,	__LINE__, format, ##__VA_ARGS__);
	
#define LOG_NOTICE(format, ...) \
		g_simple_logger.notice(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);
	
#define LOG_WARN(format, ...) \
		g_simple_logger.warn(__FILE__,__func__,	__LINE__, format, ##__VA_ARGS__);
	
#define LOG_ERROR(format, ...) \
		g_simple_logger.error(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);
	
#define LOG_CRIT(format, ...) \
		g_simple_logger.crit(__FILE__,__func__,	__LINE__, format, ##__VA_ARGS__);
	
#define LOG_ALERT(format, ...) \
		g_simple_logger.alert(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);
	
#define LOG_EMERG(format, ...) \
		g_simple_logger.emerg(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);
	
#define LOG_FATAL(format, ...) \
		g_simple_logger.fatal(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);


#endif // _SIMPLELOG_SIMPLE_LOGGER_HH