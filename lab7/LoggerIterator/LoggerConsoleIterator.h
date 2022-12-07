#pragma once

class LoggerConsoleIterator : public LoggerIterator {
public:
    typedef typename vector<char*>::iterator it_type;

    LoggerConsoleIterator(LoggerConsole* Logger) {
        this->Logger = Logger;
        index = Logger->arr.begin();
    }
    void first() {
        index = Logger->arr.begin();
    }
    void next() {
        index++;
    }
    bool end() {
        return (index == Logger->arr.end());
    }
    string current() {
        return *index;
    }
private:
    LoggerConsole* Logger;
    it_type index;
};