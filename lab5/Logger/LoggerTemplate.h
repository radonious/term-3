#pragma once

template <typename T>
class LoggerTemplate {
public:
     LoggerTemplate() {
         logs.push_back((string)time.c_str() + " - LoggerTemplate with object sizeof: " + to_string(sizeof(obj)) + " bytes created");
     }
     ~LoggerTemplate() {
         cout << "" << endl;
         logs.push_back((string)time.c_str() + " - LoggerTemplate with object destructed");
         getLogs();
     }
     void getLogs() {
         for(auto &i : logs) {
             cout << i << endl;
         }
     }
    T getObj() {
        logs.push_back((string)time.c_str() + " - object has copied");
        return obj;
     }
     T* modifyObj() {
         logs.push_back((string)time.c_str() + " - object has modifyed");
         return &obj;
     }
private:
    T obj;
    vector <string> logs;
    Time time;
};