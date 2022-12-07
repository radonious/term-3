#pragma once

class LoggerIterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool end() = 0;
    virtual string current() = 0;
};