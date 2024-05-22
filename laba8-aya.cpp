#include <iostream>
using namespace std;


template<typename T>
class SmartPtr {
private:
    T* ptr;

public:
    SmartPtr(T* p = nullptr) : ptr(p) {}

    ~SmartPtr() {
        delete ptr;
    }

    SmartPtr(const SmartPtr& other) = delete;

    SmartPtr& operator=(const SmartPtr& other) = delete;

    SmartPtr(SmartPtr&& other) {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    SmartPtr& operator=(SmartPtr&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T* get() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }
};

int main() {
    SmartPtr<int> ptr1(new int(42));
    SmartPtr<int> ptr2(move(ptr1));

    if (ptr1.get() == nullptr) {
        cout << "ptr1 is now empty\n";
    }

    *ptr2 = 100;
    
    cout << "*ptr2: " << *ptr2 << endl;

    return 0;
}
