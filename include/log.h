/**
 * @author clark
 * @email haixuanwo_clark@hotmail.com
 * @date 2020-08-29
 * @brief 日志库的中间层接口
 */

#ifndef LOG_H_
#define LOG_H_

// 日志库头文件
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/PropertyConfigurator.hh"
#include "log4cpp/SyslogAppender.hh"
#include "log4cpp/LoggingEvent.hh"
#include <log4cpp/PatternLayout.hh>
#include <unistd.h>

typedef enum
{
    EMERG  = 0,
	FATAL  = 0,
    ALERT  = 100,
    CRIT   = 200,
    ERROR  = 300,
    WARN   = 400,
    NOTICE = 500,
    INFO   = 600,
    DEBUG  = 700,
    NOTSET = 800
}Level_E;

typedef enum
{
    LOG_TARGET_STDOUT = 0,     // 标准输出
    LOG_TARGET_FILE,           // 文件
    LOG_TARGET_SYSLOG,         // syslog
    LOG_TARGET_ALL,            // 三个目标都输出
}LogOutTarget_E;

/**
 * @brief 日志功能类，实现日志输出等级控制与日志输出目标控制功能
 */
class CLog
{
public:
    CLog(LogOutTarget_E logOutTarget, Level_E level, const char *logFormat);
    int log_init(LogOutTarget_E logOutTarget, Level_E level, const char *logFormat);
    int print(Level_E level, const char * stringFormat, ...);
    int log_uninit();
    ~CLog();
private:
    log4cpp::Category& trace_log = log4cpp::Category::getInstance(std::string("txh"));
};

extern CLog Log;

#define CLOG_DEBUG(stringFormat, arg...)   Log.print(DEBUG, stringFormat, ##arg)
#define CLOG_INFO(stringFormat, arg...)    Log.print(INFO, stringFormat, ##arg)
#define CLOG_NOTICE(stringFormat, arg...)  Log.print(NOTICE, stringFormat, ##arg)
#define CLOG_WARN(stringFormat, arg...)    Log.print(WARN, stringFormat, ##arg)
#define CLOG_ERROR(stringFormat, arg...)   Log.print(ERROR, stringFormat, ##arg)
#define CLOG_CRIT(stringFormat, arg...)    Log.print(CRIT, stringFormat, ##arg)
#define CLOG_ALERT(stringFormat, arg...)   Log.print(ALERT, stringFormat, ##arg)
#define CLOG_FATAL(stringFormat, arg...)   Log.print(FATAL, stringFormat, ##arg)

/*
单元测试用例 test case
1、日志等级[ok]
2、输出目标[ok]
3、不同日志格式   [ok]
4、长时间挂机测试
*/

#endif

