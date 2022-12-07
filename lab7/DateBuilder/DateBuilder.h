#pragma once

class DateBuilder : public Builder{
public:
    void reset() { obj = Date(0,0,0,0,0,0,0); }
    void setYear(int val) { obj.setDateYear(val); };
    void setMonth(int val) { obj.setDateMonth(val); };
    void setDay(int val) { obj.setDateDay(val); };
    void setHour(int val) { obj.setDateHour(val); };
    void setMinute(int val) { obj.setDateMinute(val); };
    void setSecond(int val) { obj.setDateSecond(val); };
    void setMsecond(int val) { obj.setDateMsecond(val); };
    Date getResult() { return obj; }
private:
    Date obj;
};