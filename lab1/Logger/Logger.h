#pragma once

class Logger {
public:
    // Constructors
    Logger() {
        this->logname = "log.txt";
        file.open(string("../Logs/") + this->logname,ios::app);
        if(!file.is_open()) {
            file.close();
            cout << "File not opened" << endl;
        }
        cout << "Constructor w/o arguments called" << endl;
    }
    Logger(string logname) {
        this->logname = logname;
        file.open(string("../Logs/") + this->logname,ios::app);
        if(!file.is_open()) {
            file.close();
            cout << "File not opened" << endl;
        }
        cout << "Constructor w/ arguments called" << endl;
    }
    Logger(Logger const &old) {
        this->logname = old.logname;
        file.open(string("../Logs/") + this->logname,ios::app);
        if(!file.is_open()) {
            file.close();
            cout << "File not opened" << endl;
        }
        cout << "Constructor for copying called" << endl;
    }
    // Destructor
    ~Logger() {
        file.close();
        cout << "Destructor called" << endl;
    }
    // Getters
    string getLogName() { return logname; }
    // Setters
    void setLogname(string logname) {this->logname = logname; }
    // Methods
    void warning(string str) {
        if (file.is_open()) {file << A.getSystemTimeInString() << " - "<< "[ WARNING ] - " << str << endl;}
    }
    void error(string str) {
        if (file.is_open()) {file << A.getSystemTimeInString() << " - "<< "[ ERROR ] - " << str << endl;}
    }
    void info(string str) {
        if (file.is_open()) {file << A.getSystemTimeInString() << " - "<< "[ INFO ] - " << str << endl;}
    }
    void clear() {
        ofstream  ofs(string("../Logs/") + this->logname, ios::trunc | ios::out);
    }
    void getLog() {
        string line;
        ifstream file(string("../Logs/") + this->logname);
        if (file.is_open())
        {
            while (getline(file, line))
            {
                cout << line << endl;
            }
        }
    }
    void getLogSince(T time) {
        string line;
        ifstream file(string("../Logs/") + this->logname);
        if (file.is_open())
        {
            while (getline(file, line))
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
    }
    void getLastLogs(int count) {
        int logCount = 0;
        string line;
        ifstream file(string("../Logs/") + this->logname);
        if (file.is_open()) {
            while (getline(file, line)) {
                logCount++;
            }
            if (logCount <= count) {
                this->getLog();
            }
            else {
                int i = 0;
                ifstream file(string("../Logs/") + this->logname);
                while (getline(file, line)) {
                    if (i >= (logCount - count)) {
                        cout << line << endl;
                    }
                    i++;
                }
            }
        }
    }
private:
    Time A;
    fstream file;
    string logname;
};