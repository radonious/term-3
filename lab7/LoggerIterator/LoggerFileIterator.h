#pragma once

class LoggerFileIterator : public LoggerIterator {
public:
    typedef typename vector<string>::iterator it_type;

    LoggerFileIterator(LoggerFile* Logger) {
        string line;
        ifstream file(string("../Logs/") + Logger->logname);
        if (file.is_open())
        {
            while (getline(file, line))
            {
                arr.push_back(line);
            }
        }
    }
    void first() {
        index = arr.begin();
    }
    void next() {
        index++;
    }
    bool end() {
        return (index == arr.end());
    }
    string current() {
        return *index;
    }
private:
    vector<string> arr;
    it_type index;
};