#pragma once

string* getValue() {
    cout << "Value: ";
    string* line = new string;
    cin >> *line;
    return line;
}

int getIndex() {
    cout << "Index: ";
    int index = 0;
    cin >> index;
    return index;
}

string getFileName() {
    cout << "File name: ";
    string line;
    cin >> line;
    return line;
}

int menu() {
    List<string,3> list;
    int answer = 0;
    do
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << endl;
        cout << "* Choose command:" << endl;
        cout << "* 1 - Add(val); 2 - Earse(index); 3 - Insert(val, index); 4 - Extract(index);" << endl;
        cout << "* 5 - SaveTxt(fname); 6 - LoadTxt(fname); 7 - SaveBin(fname); 8 - LoadBin(fname);" << endl;
        cout << "* 9 - Print(); 10 - PrintDeref(); 11 - Sort(); 12 - ReverseSort(); 13 - Balance();" << endl;
        cout << "* 0 - Exit" << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << endl;
        cout << endl << "Command: ";
        cin >> answer;
        switch ( answer )
        {
            case 1:
            {
                list.add(getValue());
                break;
            }
            case 2:
            {
                list.earse(getIndex());
                break;
            }
            case 3:
            {
                list.insert(getValue(),getIndex());
                break;
            }
            case 4:
            {
                list.extract(getIndex());
                break;
            }
            case 5:
            {
                list.saveTxt(getFileName());
                break;
            }
            case 6:
            {
                list.loadTxt(getFileName());
                break;
            }
            case 7:
            {
                list.saveBin(getFileName());
                break;
            }
            case 8:
            {
                list.loadBin(getFileName());
                break;
            }
            case 9:
            {
                list.print();
                break;
            }
            case 10:
            {
                list.printDeref();
                break;
            }
            case 11:
            {
                list.sort();
                break;
            }
            case 12:
            {
                list.sortReverse();
                break;
            }
            case 13:
            {
                list.balance();
                break;
            }
            default:
            {
                cout << "Wring command index" << endl << endl;
            };
        }
    } while (answer != 0);


    // Return
    return 0;
}

