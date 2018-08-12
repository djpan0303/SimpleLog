#ifndef __SIMPLELOG_SIMPLELOG_H__
#define __SIMPLELOG_SIMPLELOG_H__

#include <Category.h>

#define SL_LOG_DEBUG(logger, format, ...) \
	logger.debug(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_INFO(logger, format, ...) \
	logger.info(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_NOTICE(logger, format, ...) \
	logger.notice(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_WARN(logger, format, ...) \
	logger.warn(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_ERROR(logger, format, ...) \
	logger.error(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_CRIT(logger, format, ...) \
	logger.crit(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_ALERT(logger, format, ...) \
	logger.alert(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_EMERG(logger, format, ...) \
	logger.emerg(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_FATAL(logger, format, ...) \
	logger.fatal(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#endif //__SIMPLELOG_SIMPLELOG_H__
