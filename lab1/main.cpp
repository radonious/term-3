#include "includes.h"

int main() {
    // Time test
    cout << "- - - - - - Class Time test" << endl;
    Time A;


    cout << "   System time" << endl;
    T time = A.getTime();
    cout << time.hour << "h | " << time.minute << "m | " << time.second << "s | " << time.msecond << "ms" << endl;
    char* str = A.c_str();


    cout << "   C_str" << endl;
    cout << str << endl;


    cout << "   Sub Time by 40001 ms" << endl;
    A.subTimeByMs(40001);
    time = A.getTime();
    cout << time.hour << "h | " << time.minute << "m | " << time.second << "s | " << time.msecond << "ms" << endl;


    // Logger test
    cout << "- - - - - - Class Logger test" << endl;
    Logger B;
    B.clear();
    B.error("Total crash.");
    B.info("DB collected.");
    B.warning("User's password is wrong");
    cout << "   Get all logs" << endl;
    B.getLog();


    cout << "   Get loge since t1" << endl;
    T t1;
    t1.hour = 9;
    t1.minute = 4;
    t1.second = 0;
    B.getLogSince(t1);


    cout << "   Get N last logs" << endl;
    B.getLastLogs(2);


    // Return
    return 0;
}
