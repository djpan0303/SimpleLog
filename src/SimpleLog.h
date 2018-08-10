#ifndef __SIMPLELOG_SIMPLELOG_H__
#define __SIMPLELOG_SIMPLELOG_H__

#define SL_LOG_DEBUG(logger, fmt, ...) \
	logger.debug(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_INFO(logger, fmt, ...) \
	logger.info(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_NOTICE(logger, fmt, ...) \
	logger.notice(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_WARN(logger, fmt, ...) \
	logger.warn(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_ERROR(logger, fmt, ...) \
	logger.error(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_CRIT(logger, fmt, ...) \
	logger.crit(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_ALERT(logger, fmt, ...) \
	logger.alert(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_EMERG(logger, fmt, ...) \
	logger.emerg(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#define SL_LOG_FATAL(logger, fmt, ...) \
	logger.fatal(__FILE__,__func__,  __LINE__, format, ##__VA_ARGS__);

#endif //__SIMPLELOG_SIMPLELOG_H__
