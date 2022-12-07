#pragma once

class Date : public Time {
public:
    // Defualt constructor
    Date() {
        time_t now = std::time(0);
        tm *ltm = localtime(&now);
        this->date.year = ltm->tm_year + 1900;
        this->date.month = ltm->tm_mon + 1;
        this->date.day = ltm->tm_mday;
        this->date.hour = ltm->tm_hour;
        this->date.minute = ltm->tm_min;
        this->date.second =  ltm->tm_sec;

        struct timeval utime{};
        gettimeofday(&utime, nullptr);
        this->date.msecond = utime.tv_usec / 1000;
        //cout << "Constructor w/o arguments called" << endl;
    }
    // Constructor w/ parametrs
    Date(int year, int month, int day, int hour, int minute, int second, int msecond) {
        if (year >= 0) this->date.year = year; else this->date.year = -year;
        if (month >= 1 && month < 12) {this->date.month = month;} else {this->date.month = month % 12;}
        if (day >= 1 && day < 31) {this->date.day = day;} else {this->date.day = day % 31;}
        if (hour >= 0 && hour < 24) {this->date.hour = hour;} else {this->date.hour = hour % 24;}
        if (minute >= 0 && minute < 60) {this->date.minute = minute;} else {this->date.minute = minute % 60;}
        if (second >= 0 && second < 60) {this->date.second = second;} else {this->date.second = second % 60;}
        if (msecond >= 0 && msecond < 1000) {this->date.msecond = msecond;} else {this->date.msecond = msecond % 1000;}
        //cout << "Constructor w/ arguments #1 called" << endl;
    }
    Date(DT date) {
        this->date = date;
        //cout << "Constructor w/ arguments #2 called" << endl;
    }
    // Coping constructor
    Date(Date const &old) {
        this->date = old.date;
        //cout << "Constructor for copying called" << endl;
    }
    // Destructor
    ~Date() {
        //cout << "Destructor called" << endl;
    }
    // Getters
    int getDateYear() { return date.year; }
    int getDateMonth() { return date.month; }
    int getDateDay() { return date.day; }
    int getDateHour() { return date.hour; }
    int getDateMinute() { return date.minute; }
    int getDateSecond() { return date.second; }
    int getDateMsecond() { return date.msecond; }
    // Получение времени
    DT getDate() { return date; }
    //Setter
    void setDateYear(int year) {this->date.year = year; }
    void setDateMonth(int month) {this->date.month = month; }
    void setDateDay(int day) {this->date.day = day; }
    void setDateHour(int hour) {this->date.hour = hour; }
    void setDateMinute(int minute) {this->date.minute = minute; }
    void setDateSecond(int second) {this->date.second = second; }
    void setDateMsecond(int msecond) {this->date.msecond = msecond; }
    // Изменение времени
    void setDate(DT date) { this->date = date; }

    // Вывод объекта класса в виде си-строки
    char* c_str() {
        char* str = new char[24];
        sprintf(str,"%d/%d/%d %d:%d:%d.%d", date.year,date.month,date.day,date.hour,date.minute,date.second,date.msecond);
        return str;
    }
    // Получение системноой даты и времени
    static DT getSystemDate() {
        DT t;
        time_t now = std::time(0);
        tm *ltm = localtime(&now);
        t.year = ltm->tm_year + 1900;
        t.month = ltm->tm_mon + 1;
        t.day = ltm->tm_mday;
        t.hour = ltm->tm_hour;
        t.minute = ltm->tm_min;
        t.second =  ltm->tm_sec;

        struct timeval utime{};
        gettimeofday(&utime, nullptr);
        t.msecond = utime.tv_usec / 1000;

        return t;
    }

    static DT add(DT t1, DT t2) {
        DT t3;
        t3.msecond = (t1.msecond + t2.msecond) % 1000;
        t3.second = (t1.second + t2.second) % 60 + (t1.msecond + t2.msecond) / 1000;
        t3.minute = (t1.minute + t2.minute) % 60 + (t1.second + t2.second) / 60;
        t3.hour = (t1.hour + t2.hour) % 24  + (t1.minute + t2.minute) / 60;
        t3.day = (t1.day + t2.day) % 31 + (t1.hour + t2.hour) / 24;
        t3.month = (t1.month + t2.month) % 12  + (t1.day + t2.day) / 31;
        t3.year = (t1.year + t2.year)  + (t1.month + t2.month) / 12;

        return t3;
    }

    static DT dif(DT t1, DT t2) {
        try{
            if (t1.year < t2.year) {throw invalid_argument("t2 is bigger than t1.");}
            DT t3;
            int msec = (t1.msecond + t1.second * 1000 + t1.minute * 60 * 1000 + t1.hour * 60 * 60 * 1000 +
                        t1.day * 24 * 60 * 60 * 1000 + t1.month * 31 * 24 * 60 * 60 * 1000 + t1.year * 12 * 31 * 24 * 60 * 60 * 1000) -
                       (t2.msecond + t2.second * 1000 + t2.minute * 60 * 1000 + t2.hour * 60 * 60 * 1000 + t2.day * 24 * 60 * 60 * 1000 +
                        t2.month * 31 * 24 * 60 * 60 * 1000 + t2.year * 12 * 31 * 24 * 60 * 60 * 1000);
            t3.msecond = msec % 1000;
            t3.second = msec / 1000 % 60;
            t3.minute = msec / 1000 / 60 % 60;
            t3.hour = msec / 1000 / 60 / 60 % 24;
            t3.day = msec / 1000 / 60 / 60 / 24 % 31;
            t3.month = msec / 1000 / 60 / 60 / 24 / 31 % 12;
            t3.year = msec / 1000 / 60 / 60 / 24 / 31 / 12;
            return t3;
        }
        catch (const invalid_argument &err) {
            cout << err.what() << endl;
            DT t3;
            int msec = (t2.msecond + t2.second * 1000 + t2.minute * 60 * 1000 + t2.hour * 60 * 60 * 1000 +
                        t2.day * 24 * 60 * 60 * 1000 + t2.month * 31 * 24 * 60 * 60 * 1000 + t2.year * 12 * 31 * 24 * 60 * 60 * 1000) -
                       (t1.msecond + t1.second * 1000 + t1.minute * 60 * 1000 + t1.hour * 60 * 60 * 1000 + t1.day * 24 * 60 * 60 * 1000 +
                        t1.month * 31 * 24 * 60 * 60 * 1000 + t1.year * 12 * 31 * 24 * 60 * 60 * 1000);
            t3.msecond = msec % 1000;
            t3.second = msec / 1000 % 60;
            t3.minute = msec / 1000 / 60 % 60;
            t3.hour = msec / 1000 / 60 / 60 % 24;
            t3.day = msec / 1000 / 60 / 60 / 24 % 31;
            t3.month = msec / 1000 / 60 / 60 / 24 / 31 % 12;
            t3.year = msec / 1000 / 60 / 60 / 24 / 31 / 12;
            return t3;
        }
    }

    char* toBinFile(string filename) {
        ofstream fileB(string("../Logs/") + filename, ios::binary);
        if (fileB.is_open())
        {
            fileB.write((char*)&date.day,sizeof(int));
            fileB.write((char*)&date.month,sizeof(int));
            fileB.write((char*)&date.year,sizeof(int));
            fileB.write((char*)&date.hour,sizeof(int));
            fileB.write((char*)&date.minute,sizeof(int));
            fileB.write((char*)&date.second,sizeof(int));
            fileB.write((char*)&date.msecond,sizeof(int));
        }
        fileB.close();
    }
    // Перегрузка операторов
    Date& operator =(const Date& other) {
        date = other.date;
        return *(this);
    }

    bool operator ==(const Date& other) {
        return (date == other.date) ? 1 : 0;
    }

    bool operator !=(const Date& other) {
        return (date != other.date) ? 1 : 0;
    }

    friend Date operator +(const Date& left, const Date& right);

    operator char*() {
        return this->c_str();
    }

    explicit operator string() {
        return this->c_str();
    }

    friend ostream& operator<<(ostream& os, const Date& dt) {
        os << dt.date.day << '/' << dt.date.month << '/' << dt.date.year << ' ' <<
           dt.date.hour << ':' << dt.date.minute << ':' << dt.date.second << '.' << dt.date.msecond << endl;
        return os;
    }

    friend istream& operator>>(istream& os, Date& dt) {
        os >> dt.date.day >> dt.date.month >> dt.date.year >>
        dt.date.hour >> dt.date.minute >> dt.date.second >> dt.date.msecond;
        return os;
    }

private:
    DT date;
};

Date operator +(const Date& left, const Date& right) {
    return Date(left.date.year + right.date.year,
                left.date.month + right.date.month,
                left.date.day + right.date.day,
                left.date.hour + right.date.hour,
                left.date.minute + right.date.minute,
                left.date.second + right.date.second,
                left.date.msecond + right.date.msecond);
}

