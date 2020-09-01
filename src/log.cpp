/**
 * @author clark
 * @email haixuanwo_clark@hotmail.com
 * @date 2020-08-29
 * @brief 日志库的中间层接口
 */

#include "log.h"

// 初始化日志对象
CLog Log(LOG_TARGET_ALL, DEBUG, "%d{%d %b %Y %H:%M:%S} [%p] %c %m%n");

CLog::CLog(LogOutTarget_E logOutTarget, Level_E level, const char *logFormat)
{
    log_init(logOutTarget, level, logFormat);
}

int CLog::log_init(LogOutTarget_E logOutTarget, Level_E level, const char *logFormat)
{

	trace_log.setPriority(level);	                // 设置日志优先级

	auto getLayout = [=]()
	{
		log4cpp::PatternLayout* layout = new log4cpp::PatternLayout();
		layout->setConversionPattern(logFormat);    // 设置日志格式
		return layout;
	};

    if (LOG_TARGET_STDOUT == logOutTarget || LOG_TARGET_ALL == logOutTarget)
    {
    	log4cpp::Appender *consoleAppender = new log4cpp::OstreamAppender("console", &std::cout);
    	consoleAppender->setLayout(getLayout());    // 控制台标准输出
        trace_log.addAppender(consoleAppender);
    }

    if (LOG_TARGET_FILE == logOutTarget || LOG_TARGET_ALL == logOutTarget)
    {
    	log4cpp::Appender *fileAppender = new log4cpp::FileAppender("default", "txh.log");
    	fileAppender->setLayout(getLayout());       // 日志文件txh.log
        trace_log.addAppender(fileAppender);
    }

    if (LOG_TARGET_SYSLOG == logOutTarget || LOG_TARGET_ALL == logOutTarget)
    {
    	log4cpp::SyslogAppender* syslogAppender = new log4cpp::SyslogAppender("syslog", "txh");
    	syslogAppender->setLayout(getLayout());     // linux日志/var/log/syslog
        trace_log.addAppender(syslogAppender);
    }

    return 0;
}

int CLog::print(Level_E level, const char * stringFormat, ...)
{
    va_list va;
    char log_buf[4096] = {0};

    va_start(va, stringFormat);
    vsprintf(log_buf, stringFormat, va);

    switch(level)
    {
        case DEBUG:
            trace_log.debug("%s", log_buf);
            break;
        case INFO:
            trace_log.info("%s", log_buf);
            break;
        case NOTICE:
            trace_log.notice("%s", log_buf);
            break;
        case WARN:
            trace_log.warn("%s", log_buf);
            break;
        case ERROR:
            trace_log.error("%s", log_buf);
            break;
        case CRIT:
            trace_log.crit("%s", log_buf);
            break;
        case ALERT:
            trace_log.alert("%s", log_buf);
            break;
        case FATAL:
            trace_log.fatal("%s", log_buf);
            break;
        default:
            break;
    }

    va_end(va);
    return 0;
}

int CLog::log_uninit()
{
    log4cpp::Category::shutdown();
}

CLog::~CLog()
{
    log_uninit();
}

