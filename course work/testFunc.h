#pragma once

void InnerListTest1() {
    InnerList<int,3> list;
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    list.innerPushBack(&a1);
    list.innerPushBack(&a2);
    list.innerPushBack(&a3);
    cout << "Len: " << list.innerLength() << endl;
}

void ListTest1() {
    string a0 = "000000000";
    string a1 = "11111";
    string a2 = "22222222";
    string a3 = "33";
    string a4 = "44444444444";

    List<string,3> list;
    list.add(&a0);
    list.add(&a1);
    list.add(&a2);
    list.add(&a3);
    list.add(&a4);
    list.printDeref();
    list.earse(0);
    list.printDeref();
}

void Bintest1() {
    List<string,3> list;
    list.loadBin("text2.bin");
    list.printDeref();
}

void BalanceTest1() {
    string a0 = "asdasd";
    string a1 = "11111";
    string a2 = "22222222";
    string a3 = "33";
    string a4 = "44444444444";
    string a5 = "5555";

    List<string,12> list;
    list.loadTxt("text.txt");
    list.printDeref();
    list.balance();
    list.printDeref();
    cout << list[18] << endl;
}