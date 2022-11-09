#pragma once
// Интерфейс логгера
class Logger {
public:
    virtual string getLogName() = 0;
    virtual void setLogname(string logname) = 0;
    virtual void warning(const char* str) = 0;
    virtual void error(const char* str) = 0;
    virtual void info(const char* str) = 0;
    virtual void clear() = 0;
    virtual void getLog() = 0;
    virtual void getLogSince(T time) = 0;
    virtual void getLastLogs(int count) = 0;
};