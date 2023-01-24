#pragma once

template<typename T, int len>
class InnerList {

public:
    InnerList() {
        obj = NULL;
        next = NULL;
    }
    InnerList(T* data) {
        obj = data;
        next = NULL;
    }
    ~InnerList() = default;

    int innerLength() {
        int i = 0;
        for (InnerList* tmp = this; tmp != NULL; tmp = tmp->next) {
            i++;
        }
        return i;
    }

    bool haveEmptyObj() {
        InnerList* current = this;
        while (current != NULL) {
            if (current->obj == NULL) {
                return 1;
            }
            current = current->next;
        }
        return 0;
    }

    void innerPushBack(T* val) {
         if (this->obj == NULL) {
            this->obj = val;
        }
        else {
            if (this->next == NULL) {
                next = new InnerList();
            }
            next->innerPushBack(val);
        }
    }

    T* at(int index) {
        int cur_index= 0;
        InnerList* current = this;

        while(cur_index != index) {
            current = current->next;
            cur_index++;
        }

        return current->obj;
    }

    void earse(int index) {
        int cur_index= 0;
        InnerList* current = this;

        while(cur_index != index) {
            current = current->next;
            cur_index++;
        }

        current->obj = nullptr;
    }

    T* extractLast() {
        int cur_index= 0;
        InnerList* current = this;
        InnerList* prev = this;
        T* tmp;
        while(current->next != NULL && current->obj != NULL) {
            prev = current;
            current = current->next;
        }
        if (current->obj == NULL) {
            tmp = prev->obj;
            prev->obj = nullptr;
        }
        else {
            tmp = current->obj;
            current->obj = nullptr;
        }
        return tmp;
    }

    T* removeLast() {
        InnerList* current = this;
        InnerList* prev = current;
        T* tmp;
        while(current->next != NULL ) {
            prev = current;
            current = current->next;
        }
        tmp = current->obj;
        prev->next = NULL;
        return tmp;
    }

    void insert(T* val, int index, T** tmp) {
        int cur_index= 0;
        InnerList* current = this;

        while(cur_index != index) {
            current = current->next;
            cur_index++;
        }

        *tmp = current->obj;
        current->obj = val;
    }

    T* extract(int index) {
        int cur_index= 0;
        InnerList* current = this;

        while(cur_index != index) {
            current = current->next;
            cur_index++;
        }
        T* tmp = current->obj;
        current->obj = nullptr;
        return tmp;
    }

    friend bool operator< (const InnerList& left, const InnerList& right) {
        return left.obj < right.obj;
    }
    friend bool operator> (const InnerList& left, const InnerList& right) { return right < left; }

private:
    T* obj;
    InnerList* next;
};