#pragma once

void LoggerConsoleIteratorTest() {
    LoggerConsole A;
    A.error("1");
    A.info("2");
    A.warning("3");
    LoggerConsoleIterator it = LoggerConsoleIterator(&A);
    for (it.first(); !it.end(); it.next()) {
        cout << it.current() << endl;
    }
}

void LoggerFileIteratorTest() {
    LoggerFile A;
    A.clear();
    A.error("1");
    A.warning("2");
    A.info("3");
    LoggerFileIterator it = LoggerFileIterator(&A);
    for (it.first(); !it.end(); it.next()) {
        cout << it.current() << endl;
    }
}

void LoggerUniceTest() {
    cout << "Logger A: " << endl;
    LoggerUnice& A = LoggerUnice::instance();
    A.error("123");
    A.getLog();

    cout << "Logger B: " << endl;
    LoggerUnice&B = LoggerUnice::instance();
    B.info("123");
    B.getLog();
    cout << "Logger A: " << endl;
    A.getLog();
    cout << "A and B are the same obj" << endl;
}

void DateBuilderTest() {
    DateBuilderDirector dir;
    DateBuilder builder;

    dir.constructBirthdayDate(&builder);
    Date a = builder.getResult();
    cout << a << endl;

    dir.constructNSKFoundationDate(&builder);
    Date b = builder.getResult();
    cout << b << endl;
}