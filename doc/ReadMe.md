# 1 日志格式
默认无格式
BasicLayout:日志的级别|时间日期(具体到毫秒)|线程ID(以16进制打印)|文件@函数@行号

# 2 支持多个输出端
可以同时输出到本地文件、TCP、udp、终端。每个输出端都可以做不同的格式设置等配置
## 2.1 可配置项
## 2.1.1 日志级别
所有的输出端都可以配置级别。
日志的级别越高，在代码中出现的频率就越少。

## 2.1.2 本地文件配置项
本地文件支持三种写方式：按天数保留日志文件(DaillyRollingFileAppender)、按文件大小保留一定个数日志文件(RollingFileAppender)、任意写(FileAppender)。

# 3 支持异步写
默认开启单独的线程写日志
要关闭请注释ASYNC_LOG

# 4 解决的需求
满足本地console日志输出，本地文件保存，远端UDP推送

# 5 使用方法
* step 1
如果使用同步方式写日志，需要修改Config.h
如果修改日志缓冲区，需要修改Config.h
如果需要修改日志输出端和格式，需要修改SimpleLogger.h。SimpleLogger.h中定义了默认的全局logger。

* step 2
#include <SimpleLogger.h>

* step 3
使用SimpleLogger.h中的LOG_XXX即可
