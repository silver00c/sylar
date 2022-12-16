#include <iostream>
#include "../sylar/log.h"
#include "../sylar/util.h"

/*
·生成一个日志器
·添加日志输出地（可以设置日志输出地的级别，默认DEBUG；可以设置日志的格式）
·获取输出流进行输出（调用的宏根据级别输出不同输出地的日志）
*/
int main(int argc, char** argv) {
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));

    sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("./log.txt"));
    sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);

    file_appender->setLevel(sylar::LogLevel::ERROR);

    logger->addAppender(file_appender);

    // sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__, __LINE__, 0, sylar::GetThreadId(), sylar::GetFiberId(), time(0)));
    // event->getSS() << "hello sylar log";
    
    // logger->log(sylar::LogLevel::DEBUG, event);
    std::cout << "hello sylar log" << std::endl;

    SYLAR_LOG_INFO(logger) << "test macro";//INFO级别太低只能输出到控制台，不能输出到文件（DEBUG<INFO<ERROR）
    SYLAR_LOG_ERROR(logger) << "test macro error";
    /*  SYLAR_LOG_ERROR(logger) << "test macro error";
        |
        SYLAR_LOG_LEVEL(logger, sylar::LogLevel::ERROR)
        |
        if(logger->getLevel() <= level) \
            sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, \
                __FILE__, __LINE__, 0, sylar::GetThreadId(), \
            sylar::GetFiberId(), time(0)))).getSS()
        |
        获取输出流进行输出
    */

    SYLAR_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");
    /*梳理下这个流程：
        SYLAR_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");
        |
        SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::ERROR, fmt, __VA_ARGS__)
        |
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, \
                __FILE__, __LINE__, 0, sylar::GetThreadId(),\
            sylar::GetFiberId(), time(0)))).getEvent()->format(fmt, __VA_ARGS__)
        |
        LogEvent::format(const char* fmt, va_list al)
    */

    auto l = sylar::LoggerMgr::GetInstance()->getLogger("xx");
    SYLAR_LOG_INFO(l) << "xxx";
    return 0;
}
