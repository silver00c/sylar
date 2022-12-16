#include <iostream>
#include "../sylar/log.h"
#include "../sylar/util.h"

/*
������һ����־��
�������־����أ�����������־����صļ���Ĭ��DEBUG������������־�ĸ�ʽ��
����ȡ�����������������õĺ���ݼ��������ͬ����ص���־��
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

    SYLAR_LOG_INFO(logger) << "test macro";//INFO����̫��ֻ�����������̨������������ļ���DEBUG<INFO<ERROR��
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
        ��ȡ������������
    */

    SYLAR_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");
    /*������������̣�
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
