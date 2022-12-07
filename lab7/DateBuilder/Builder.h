#pragma once

class Builder {
public:
    virtual void reset() = 0;
    virtual void setYear(int val) = 0;
    virtual void setMonth(int val) = 0;
    virtual void setDay(int val) = 0;
    virtual void setHour(int val)= 0;
    virtual void setMinute(int val) = 0;
    virtual void setSecond(int val) = 0;
    virtual void setMsecond(int val)= 0;
};