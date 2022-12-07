#pragma once

class TimingInterface {
public:
    virtual char* c_str() = 0;
    virtual void subByMs(int ms) = 0;
    virtual void addByMs(int ms) = 0;
};
