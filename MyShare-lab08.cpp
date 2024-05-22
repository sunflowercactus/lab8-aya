#include <iostream>

using namespace std;

template<typename T>
class MyShared {
private:
    T* ptr;
    int* count;

public:
    MyShared(T* ptr) : ptr(ptr), count(new int(1)) {}

    MyShared(const MyShared& other) : ptr(other.ptr), count(other.count) {
        (*count)++;
    }

    ~MyShared() {
        (*count)--;
        if ((*count) == 0) {
            delete ptr;
            delete count;
            cout << "Memory freed!" << endl;
        }
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }
};

template<typename T, typename... Args>
MyShared<T> Make_MyShared(Args&&... args) {
    return MyShared<T>(new T(std::forward<Args>(args)...));
}

class MyClass {
public:
    void hello() {
        cout << "Hello from MyClass!" << endl;
    }
};

int main() {
    auto ptr1 = Make_MyShared<MyClass>();
    auto ptr2 = ptr1;

    cout << "Using ptr1: ";
    ptr1->hello();

    cout << "Using ptr2: ";
    ptr2->hello();

    return 0;
}
