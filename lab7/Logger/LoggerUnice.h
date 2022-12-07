#pragma once

class LoggerUnice : public LoggerConsole {
public:
    // Отложенная инициализация static после main
    static LoggerUnice& instance() {
        static LoggerUnice singleton;
        return singleton;
    }
private:
    LoggerConsole Logger;

    LoggerUnice() = default;
    LoggerUnice(const LoggerUnice&) = default;
    LoggerUnice& operator = (const LoggerUnice&) = default;
};