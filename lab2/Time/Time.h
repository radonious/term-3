#pragma once

// Const
#define SEC_PER_YEAR 31536000
#define SEC_PER_MONTH 2678400
#define SEC_PER_DAY   86400
#define SEC_PER_HOUR  3600
#define SEC_PER_MIN   60
#define MSEC_PER_SEC 1000

// Struct for time
struct T { // public по умолчанию
    int hour;
    int minute;
    int second;
    int msecond;
} typedef T;

// Classes
class Time { // private по умолчанию
public:
    // Defualt constructor
    Time() {
        struct timeval utime{};
        gettimeofday(&utime, nullptr);
        this->time.hour = (utime.tv_sec % SEC_PER_DAY) / SEC_PER_HOUR + 7; // +7 UTC NSK
        this->time.minute = (utime.tv_sec % SEC_PER_DAY % SEC_PER_HOUR) / SEC_PER_MIN;
        this->time.second = utime.tv_sec % SEC_PER_DAY % SEC_PER_HOUR % SEC_PER_MIN;
        this->time.msecond = utime.tv_usec / MSEC_PER_SEC;
        cout << "Constructor w/o arguments called" << endl;
    }
    // Constructor w/ parametrs
    Time(int hour, int minute, int second, int msecond) {
        if (hour >= 0 && hour < 24) {this->time.hour = hour % 24;} else {this->time.hour = 0;}
        if (minute >= 0 && minute < 60) {this->time.minute = minute % 60;} else {this->time.minute = 0;}
        if (second >= 0 && second < 60) {this->time.second = second % 60;} else {this->time.second = 0;}
        if (msecond >= 0 && msecond < 1000) {this->time.msecond = msecond % 1000;} else {this->time.msecond = 0;}
        cout << "Constructor w/ arguments #1 called" << endl;
    }
    Time(T time) {
        this->time = time;
        cout << "Constructor w/ arguments #2 called" << endl;
    }
    // Coping constructor
    Time(Time const &old) {
        this->time = old.time;
        cout << "Constructor for copying called" << endl;
    }
    // Destructor
    ~Time() {
        cout << "Destructor called" << endl;
    }
    // Getters
    int getTimeHour() { return time.hour; }
    int getTimeMinute() { return time.minute; }
    int getTimeSecond() { return time.second; }
    int getTimeMsecond() { return time.msecond; }
    // Получение времени
    T getTime() { return time; }
    //Setter
    void setTimeHour(int hour) {this->time.hour = hour; }
    void setTimeMinute(int minute) {this->time.minute = minute; }
    void setTimeSecond(int second) {this->time.second = second; }
    void setTimeMsecond(int msecond) {this->time.msecond = msecond; }
    // Изменение времени
    void setTime(T time) { this->time = time; }
    // Вывод объекта класса в виде си-строки
    char* c_str() {
        char* str = new char[13];
        sprintf(str,"%d:%d:%d.%d\0", time.hour,time.minute,time.second,time.msecond);
        return str;
    }
    // Получение системного времени
    T getSystemTime() {
        struct timeval time{};
        T t;
        gettimeofday(&time, nullptr);
        t.hour = (time.tv_sec % SEC_PER_DAY) / SEC_PER_HOUR + 7; // +7 UTC NSK
        t.minute = (time.tv_sec % SEC_PER_DAY % SEC_PER_HOUR) / SEC_PER_MIN;
        t.second = time.tv_sec % SEC_PER_DAY % SEC_PER_HOUR % SEC_PER_MIN;
        t.msecond = time.tv_usec / MSEC_PER_SEC;
        return t;
    }
    // Вычитание миллисекунд
    void subTimeByMs(int ms) {
        try {
            int msec = time.msecond + time.second * 1000 + time.minute * 60 * 1000 + time.hour * 60 * 60 * 1000 - ms;
            if (ms > msec) {
                throw exception("Division by zero!");
            }
            if (ms < 0) {
                throw "0";
            }
            if (msec > 0) {
                time.msecond = msec % 1000;
                time.second = msec / 1000 % 60;
                time.minute = msec / 1000 / 60 % 60;
                time.hour = msec / 1000 / 60 / 60 % 24;
            }
        }
        catch(const exception& err) {
            cout << err.what() << endl;
            time.msecond = 0;
            time.second = 0;
            time.minute = 0;
            time.hour = 0;
        }
    }
    // Прибавление миллисекунд
    void addTimeByMs(int ms) {
        int msec = time.msecond + time.second * 1000 + time.minute * 60 * 1000 + time.hour * 60 * 60 * 1000 + ms;
        if (msec > 0) {
            time.msecond = msec % 1000;
            time.second = msec / 1000 % 60;
            time.minute = msec / 1000 / 60 % 60;
            time.hour = msec / 1000 / 60 / 60 % 24;
        }
    }
    static T addTime(T t1, T t2) {
        T t3;
        t3.msecond = (t1.msecond + t2.msecond) % 1000;
        t3.second = (t1.second + t2.second) % 60 + (t1.msecond + t2.msecond) / 1000;
        t3.minute = (t1.minute + t2.minute) % 60 + (t1.second + t2.second) / 60;
        t3.hour = (t1.hour + t2.hour)  + (t1.minute + t2.minute) / 60;

        return t3;
    }

    static T difTime(T t1, T t2) {
        T t3;
        int msec;
        if (t1.hour > t2.hour) {
            msec = (t1.msecond + t1.second * 1000 + t1.minute * 60 * 1000 + t1.hour * 60 * 60 * 1000) -
                   (t2.msecond + t2.second * 1000 + t2.minute * 60 * 1000 + t2.hour * 60 * 60 * 1000);
        } else {
            msec = (t2.msecond + t2.second * 1000 + t2.minute * 60 * 1000 + t2.hour * 60 * 60 * 1000) -
                   (t1.msecond + t1.second * 1000 + t1.minute * 60 * 1000 + t1.hour * 60 * 60 * 1000);
        }
        t3.msecond = msec % 1000;
        t3.second = msec / 1000 % 60;
        t3.minute = msec / 1000 / 60 % 60;
        t3.hour = msec / 1000 / 60 / 60 % 24;

        return t3;
    }

private:
    T time;
};

