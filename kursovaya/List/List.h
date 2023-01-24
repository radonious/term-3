#pragma once

template<typename T, int len>
class List {
public:
    List() {
        inner_list = InnerList<T,len>();
        next = NULL;
    }
    ~List() = default;

    void print() {
        cout << " - - Defualt Output - - " << endl;
        List* current = this;
        int index = 0;
        while (current != NULL) {
            int inner_length = current->inner_list.innerLength();
            for (int i = 0; i < inner_length; i++) {
                cout << index << " : " << at(index) << endl;
                index++;
            }
            cout << endl;
            current = current->next;
        }
    }

    void printDeref() {
        cout  << " - - Dereferenced output - - " << endl;
        List* current = this;
        int index = 0;
        while (current != NULL) {
            int inner_length = current->inner_list.innerLength();
            for (int i = 0; i < inner_length; i++) {
                if (at(index) == NULL) {
                    cout << index << " : " << at(index) << " : " << "NaN" << endl;
                }
                else {
                    cout << index << " : " << at(index) << " : " << *at(index) << endl;
                }
                index++;
            }
            cout << endl;
            current = current->next;
        }
    }

    // Добавление
    void add(T* val) {
        if (len < 1) {
            cout << "Wrong list length" << endl;
            return;
        }
        if (this->inner_list.haveEmptyObj()) {
            this->inner_list.innerPushBack(val);
        }
        else if (this->inner_list.innerLength() >= len) {
            if (this->next == NULL) {
                this->next = new List<T,len>();
            }
            this->next->add(val);
        }
        else {
            this->inner_list.innerPushBack(val);
        }
    }

    // Удаление
    void earse(int index) {
        if (index < 0) {
            cout << "[Index out of range] : index < 0, deleted [0]" << endl;
            return earse(0);
        }
        if (index > this->maxLogic()) {
            cout << "[Index out of range] : index > max, deleted [max]" << endl;
            return earse(maxLogic());
        }

        List* current = this;
        int current_min_index = 0;
        int current_max_index = 0;
        while (current->next != NULL) {
            current_min_index = current_max_index;
            current_max_index += current->inner_list.innerLength();
            if (current_max_index > index) {
                break;
            }
            current = current->next;
        }

        current->inner_list.earse(index % (current_max_index - current_min_index));
    }

    // Включение
    void insert(T* val, int index) {
        if (index < 0) {
            cout << "[Index out of range] : index < 0, inserted to [0]" << endl;
            return insert(val,0);
        }

        if (index > this->maxLogic()) {
            return add(val);
        }

        if (index > this->maxLogic() + 1) {
            cout << "[Index out of range] : index > max, inserted [max] (equal to add)" << endl;
            return add(val);
        }

        List* current = this;
        int current_min_index = 0;
        int current_max_index = 0;
        while (current->next != NULL) {
            current_min_index = current_max_index;
            current_max_index += current->inner_list.innerLength();
            if (current_max_index > index) {
                break;
            }
            current = current->next;
        }
        T* tmp;
        current->inner_list.insert(val,index % (current_max_index - current_min_index), &tmp);
        if (tmp == NULL) {
            return;
        }
        else {
            this->insert(tmp, index + 1);
        }
    }

    //Извлечение
    T* extract(int index) {
        if (index < 0) {
            cout << "[Index out of range] : index < 0, extracted [0]" << endl;
            return extract(0);
        }
        if (index > this->maxLogic()) {
            cout << "[Index out of range] : index > max, extracted [max]" << endl;
            return extract(maxLogic());
        }

        List* current = this;
        int current_min_index = 0;
        int current_max_index = 0;
        while (current->next != NULL) {
            current_min_index = current_max_index;
            current_max_index += current->inner_list.innerLength();
            if (current_max_index > index) {
                break;
            }
            current = current->next;
        }

        T* res = current->inner_list.extract(index % (current_max_index - current_min_index));
        int i = 0;
        int max = maxLogic();
        while (index + 1 + i <= max) {
            this->add(at(index + 1 + i));
            this->earse(index + 1 + i);
            i++;
        }
        if (index + 1 + i >= max) {
            removeLast();
        }
        return res;
    }

    // Сортировка
    void sort() {
        int l = maxLogic();
        while (l != 0) {
            T* max = at(0);
            int max_index = 0;
            for (int i = 0;  i <= l; i++) {
                if (at(i) == NULL) {
                    max_index = i;
                    max = at(i);
                    break;
                }
                if (*at(i) >= *max) {
                    max = at(i);
                    max_index = i;
                }
            }
            T* tmp = extract(l);
            insert(max,l);
            extract(max_index);
            insert(tmp, max_index);
            l--;
        }
    }

    // Сортировка
    void sortReverse() {
        int l = maxLogic();
        while (l != 0) {
            T* min = at(0);
            int min_index = 0;
            for (int i = 0;  i <= l; i++) {
                if (at(i) == NULL) {
                    min_index = i;
                    min = at(i);
                    break;
                }
                if (*at(i) <= *min) {
                    min = at(i);
                    min_index = i;
                }
            }
            T* tmp = extract(l);
            insert(min,l);
            extract(min_index);
            insert(tmp, min_index);
            l--;
        }
    }

    // Загрузка из текстового файла
    void loadTxt(string filename) {
        if (!is_same<T*,string*>::value) {
            cout << "Incorrect template data type. It must be string." << endl;
            return;
        }
        string line;
        ifstream file;
        file.open("../"+ filename);
        if (!file.is_open()) {
            cout << "Can not open file" << endl;
            return;
        }
        while(getline(file,line)) {
            T* data = new string(line);
            add(data);
        }
        file.close();
    }

    // Сохранение в текстовый файл
    void saveTxt(string filename) {
        if (!is_same<T*,string*>::value) {
            cout << "Incorrect template data type. It must be string." << endl;
            return;
        }
        ofstream file;
        file.open("../"+ filename);
        if (!file.is_open()) {
            cout << "Can not open/create file" << endl;
            return;
        }
        for(int i = 0; i <= maxLogic(); i++) {
            file << *at(i) << endl;
        }
        file.close();
    }

    void loadBin(string filename) {
        if (!is_same<T*,string*>::value) {
            cout << "Incorrect template data type. It must be string." << endl;
            return;
        }
        ifstream fileBin("../" + filename, ios::binary);
        if (!fileBin.is_open()) {
            cout << "Can not open file.";
            return;
        }
        while (fileBin.peek() != EOF) {
            size_t l;
            fileBin.read((char*)&l,sizeof(l));
            char* buf = new char[l];
            fileBin.read(buf, l);
            string line;
            line = buf;
            delete[] buf;
            T* data = new string(line);
            add(data);
        }
        fileBin.close();
    }

    void saveBin(string filename) {
        if (!is_same<T*,string*>::value) {
            cout << "Incorrect template data type. It must be string." << endl;
            return;
        }
        ofstream fileBin("../" + filename, ios::binary);
        if (!fileBin.is_open()) {
            cout << "Can not open/create file.";
            return;
        }
        for(int i = 0; i <= maxLogic(); i++) {
            string line = *at(i);
            size_t l = line.length() + 1;
            fileBin.write((char*)&l,sizeof(l));
            fileBin.write((char*)line.c_str(), l);
        }
        fileBin.close();
    }

    void balance() {
        List* current = this;
        List* last = this;
        int last_length;
        int length = 0;
        while (last->next != NULL) {
            length++;
            last = last->next;
        }
        last_length = last->inner_list.innerLength();
        int average = (length * len + last_length) / (length + 1);
        if (last_length >= average) { return; }
        else {
            int diff = 1;
            while (last_length != average) {
                if (diff > length ) { diff = 1; }
                current = this;
                for (int i = 0; i < (length - diff); i++) {
                    current = current->next;
                }
                last->inner_list.innerPushBack(current->removeLastInInner());
                diff++;
                last_length++;
            }
        }
    }

    //Operators
    T operator[] (const int i) { return *at(i); }
private:
    InnerList<T, len> inner_list;
    List* next;

    int length() {
        int i = 0;
        for (List* tmp = this; tmp != NULL; tmp = tmp->next) {
            i++;
        }
        return i;
    }

    int maxLogic() {
        int i = -1;
        List* current;

        for (current = this; current->next != NULL; current = current->next) {
            if (current->inner_list.innerLength() < len) {
                i += current->inner_list.innerLength();
            }
            else if (current->inner_list.innerLength() == len) {
                i += len;
            }
        }

        i += current->inner_list.innerLength();

        return i;
    }

    T* at(int index) {
        if (index < 0) {
            cout << "[Index out of range] : index < 0, returned [0]" << endl;
            return this->at(0);
        }
        if (index > this->maxLogic()) {
            cout << "[Index out of range] : index > max, returned [max]" << endl;
            return this->at(maxLogic());
        }
        List* current = this;
        int current_min_index = 0;
        int current_max_index = 0;
        while (current->next != NULL) {
            current_min_index = current_max_index;
            current_max_index += current->inner_list.innerLength();
            if (current_max_index > index) {
                break;
            }
            current = current->next;
        }
        return current->inner_list.at(index % (current_max_index - current_min_index));
    }

    T* removeLastInInner() {
        return this->inner_list.removeLast();
    }

    void removeLast() {
        List* current = this;
        List* prev = this;
        while (current->next != NULL) {
            prev = current;
            current = current->next;
        }
        if (current->inner_list.at(0) == NULL && current->inner_list.innerLength() == 1) {
            prev->next = NULL;
            return;
        }
        current->inner_list.removeLast();
    }
};