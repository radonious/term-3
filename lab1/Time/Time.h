#pragma once
#include <sstream>

// Константы для работы со временем
#define SEC_PER_DAY   86400
#define SEC_PER_HOUR  3600
#define SEC_PER_MIN   60
#define MSEC_PER_SEC 1000

// Структура для хранения времени
struct T { // public по умолчанию
    int hour;
    int minute;
    int second;
    int msecond;
} typedef T;

// Класс
class Time { // private по умолчанию
public:
    // Конструктор по умолчанию
    Time() {
        struct timeval utime{};
        gettimeofday(&utime, nullptr);
        this->time.hour = (utime.tv_sec % SEC_PER_DAY) / SEC_PER_HOUR + 7; // +7 UTC NSK
        this->time.minute = (utime.tv_sec % SEC_PER_DAY % SEC_PER_HOUR) / SEC_PER_MIN;
        this->time.second = utime.tv_sec % SEC_PER_DAY % SEC_PER_HOUR % SEC_PER_MIN;
        this->time.msecond = utime.tv_usec / MSEC_PER_SEC;
        cout << "Constructor w/o arguments called" << endl;
    }
    //Конструктор с параметрами
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
    // Конструктор окпирования
    Time(Time const &old) {
        this->time = old.time;
        cout << "Constructor for copying called" << endl;
    }
    // Деструктор
    ~Time() {
        cout << "Destructor called" << endl;
    }
    // Геттеры
    int getTimeHour() { return time.hour; }
    int getTimeMinute() { return time.minute; }
    int getTimeSecond() { return time.second; }
    int getTimeMsecond() { return time.msecond; }
    // Получение времени
    T getTime() { return time; }
    //Сеттеры
    void setTimeHour(int hour) {this->time.hour = hour; }
    void setTimeMinute(int minute) {this->time.minute = minute; }
    void setTimeSecond(int second) {this->time.second = second; }
    void setTimeMsecond(int msecond) {this->time.msecond = msecond; }
    // Изменение времени
    void setTime(T time) { this->time = time; }
    // Вывод объекта класса в виде си-строки
    char* c_str() {
        int size[4];
        if (time.hour < 10) size[0] = 1; else size[0] = 2;
        if (time.minute < 10) size[1] = 1; else size[1] = 2;
        if (time.second < 10) size[2] = 1; else size[2] = 2;
        if (time.msecond < 10) size[3] = 1; else if (time.msecond < 100) size[3] = 2; else size[3] = 3;
        char* str = new char[13];
        int move = 0;
        sprintf(str + move, "%d", time.hour); move += size[0];
        sprintf(str + move, "%c", ':'); move += 1;
        sprintf(str + move, "%d", time.minute); move += size[1];
        sprintf(str + move, "%c", ':'); move += 1;
        sprintf(str + move, "%d", time.second); move += size[2];
        sprintf(str + move, "%c", '.'); move += 1;
        sprintf(str + move, "%d", time.msecond); move += size[3];
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
    string getSystemTimeInString() {
        T t = this->getSystemTime();
        stringstream ss;
        ss << t.hour << ":" << t.minute << ":" << t.second << "." << t.msecond;
        return ss.str();
    }
    // Вычитание миллисекунд
    void subTimeByMs(int ms) {
        int msec = time.msecond + time.second * 1000 + time.minute * 60 * 1000 + time.hour * 60 * 60 * 1000 - ms;
        if (msec > 0) {
            time.msecond = msec % 1000;
            time.second = msec / 1000 % 60;
            time.minute = msec / 1000 / 60 % 60;
            time.hour = msec / 1000 / 60 / 60 % 24;
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