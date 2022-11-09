#include "includes.h"

int main() {

    // Time and Date test
    Time A;
    Time B;
    // Deualt output
    cout << A.c_str() << " - A time" << endl;
    cout << B.c_str() << " - B time"  << endl;
    // Output after method
    B.addTimeByMs(50000);
    cout << B.c_str()<< " - B time +50sec"  << endl;
    // = overloading
    B = A;
    cout << B.c_str()<< " - B time = A time"  << endl;
    // == and != overloading
    cout << "A == B is " << (A == B) << endl;
    cout << "A != B is " << (A != B) << endl;
    // + overloading
    cout << (A + B).c_str() << " - A + B time" << endl;
    // to chae*/string
    char* str = A;
    cout << str << " - A to char*" << endl;
    cout << (string)B << " - B to string explicit" << endl;

    // Logger test

    // << overloading in LoggerConsole
    LoggerConsole Log;
    cout << "Console Log Using <<" << endl;
    Log << "Log using overloaded bitwise shift operator";
    Log << "Log 2";
    Log << "Log 3";
    Log << "Log 4";
    Log.getLog();
    // LoggerConsole to string
    cout << "Console Log to string" << endl;
    cout << (string)Log << endl;

    // << overloading in LoggerFile
    LoggerFile LogF("OverloadLog.txt");
    LogF.clear();
    LogF << "Log using overloaded bitwise shift operator";
    LogF << "LogF 2";
    LogF << "LogF 3";
    // LoggerConsole to string
    cout << "File Log to string" << endl;
    cout << (string)LogF << endl;

    // Return
    return 0;
}
