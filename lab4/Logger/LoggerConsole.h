#pragma once

class LoggerConsole : public Logger {
public:
// Constructors
    LoggerConsole() {
        cout << "Constructor w/o arguments called" << endl;
    }
    LoggerConsole(LoggerConsole const &old) {
        this->arr = old.arr;
        cout << "Constructor for copying called" << endl;
    }
    // Destructor
    ~LoggerConsole() {
        cout << "Destructor called" << endl;
    }
    // Methods
    char* getLogName() {
        return logname;
    }
    void setLogname(char* logname) {
        this->logname = logname;
    }
    void warning(const char* s2) {
        const char* s1 = A.c_str();
        int buf = strlen(s1) + strlen(s2) + 17 + 1;
        char* res = new  char[buf];
        sprintf(res, "%s - [ WARNING ] - %s", s1,s2);
        arr.push_back(res);
    }
    void error(const char* s2) {
        const char* s1 = A.c_str();
        int buf = strlen(s1) + strlen(s2) + 15 + 1;
        char* res = new  char[buf];
        sprintf(res, "%s - [ ERROR ] - %s", s1,s2);
        arr.push_back(res);
    }
    void info(const char* s2) {
        const char* s1 = A.c_str();
        int buf = strlen(s1) + strlen(s2) + 14 + 1;
        char* res = new  char[buf];
        sprintf(res, "%s - [ INFO ] - %s", s1,s2);
        arr.push_back(res);
    }
    void clear() {
        arr.clear();
    }
    void getLog() {
        for (auto i : arr) {
            cout << i << endl;
        }
    }
    void getLogSince(T time) {
        for (auto line : arr)
        {
            int hour = 0, minute = 0, second = 0, msecond = 0;
            string tmp = "";
            int i = 0;
            while (line[i] != ' ') {
                if (line[i] == ':' || line[i] == '.') {
                    if (hour == 0) {hour = stoi(tmp);}
                    else if (minute == 0) {minute = stoi(tmp);}
                    else if (second == 0) {second = stoi(tmp);}
                    else if (msecond == 0) {msecond = stoi(tmp);}
                    tmp = "";
                }
                else {
                    tmp.push_back(line[i]);
                }
                i++;
            }
            if (time.hour < hour ) {
                cout << line << endl;
            }
            else if (time.hour == hour ) {
                if (time.minute < minute) {
                    cout << line << endl;
                }
                else if(time.minute == minute) {
                    if (time.second < second) {
                        cout << line << endl;
                    }
                    else if (time.second == second){
                        if(time.msecond <= msecond) {
                            cout << line << endl;
                        }
                    }
                }
            }
        }
    }
    void getLastLogs(int count) {
    try {
        if (count == 0) {throw invalid_argument("count equal zero.");}
        if (count < 0) {throw out_of_range("count less than zero.");}
        for (int i = count; i > 0; i--) {
            cout << arr.at(arr.size() - i) << endl;
        }
    }
    catch (const out_of_range &err) {
        cout << err.what() << endl;
        for (int i = -count; i > 0; i--) {
            cout << arr.at(arr.size() - i) << endl;
        }
    }
    catch (const invalid_argument &err) {
        cout << err.what() << endl;
        return;
    }
    }

    // Перегрузка операторов
    void operator <<(const char* str) {
        int buf = strlen(str) + 9 + 1;
        char* res = new  char[buf];
        sprintf(res, "[ << ] - %s", str);
        arr.push_back(res);
    }

    operator string () {
        string res;
        for (string i : arr) {
            res += i + "\n";
        }
        return res;
    }

private:
    char* logname = "console";
    Time A;
    vector <char*> arr;
};