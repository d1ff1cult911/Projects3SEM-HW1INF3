#include "SmartPtr.h"
#include <iostream>
#include <string>

struct Dummy {
    std::string name;
    Dummy(std::string n) : name(std::move(n)) {
        std::cout << "Construct: " << name << "\n";
    }
    ~Dummy() {
        std::cout << "Destruct: " << name << "\n";
    }
};

void basicTests() {
    std::cout << "\n--- Basic tests ---\n";
    {
        SmrtPtr<Dummy> a(new Dummy("A"));
        SmrtPtr<Dummy> b = a;

        std::cout << "use_count (a): " << a.use_count() << "\n";
        std::cout << "use_count (b): " << b.use_count() << "\n";
    }
    GetGlobalStorage<Dummy>().debugPrint(); // должно быть 0
}

void moveAndNullptrTests() {
    std::cout << "\n--- Move and nullptr tests ---\n";
    {
        SmrtPtr<Dummy> a(new Dummy("X"));
        SmrtPtr<Dummy> b = std::move(a);
        std::cout << "a valid? " << static_cast<bool>(a) << "\n";
        std::cout << "b valid? " << static_cast<bool>(b) << "\n";
        b = nullptr;
    }
    GetGlobalStorage<Dummy>().debugPrint();
}

void arrayTests() {
    std::cout << "\n--- Array test (custom deleter) ---\n";
    {
        SmrtPtr<int> arrTest(new int[4]{1, 2, 3, 4}, [](int* p){
            std::cout << "Custom array deleter called!\n";
            delete[] p;
        });

        for (int i = 0; i < 4; ++i)
            std::cout << "arr[" << i << "] = " << arrTest.get()[i] << "\n";
    }
    GetGlobalStorage<int>().debugPrint();
}

int main() {
    basicTests();
    moveAndNullptrTests();
    arrayTests();

    std::cout << "\nAll tests completed.\n";
    return 0;
}
