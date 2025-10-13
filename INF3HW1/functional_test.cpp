#include "SmartPtr.h"
#include <iostream>

struct Test {
    int value;
    Test(int v) : value(v) { std::cout << "Test(" << v << ") created\n"; }
    ~Test() { std::cout << "Test(" << value << ") destroyed\n"; }
};

int main() {
    {
        SmrtPtr<Test> p1(new Test(42));
        std::cout << "p1 use_count: " << p1.use_count() << "\n";

        SmrtPtr<Test> p2 = p1;
        std::cout << "p1 use_count after copy: " << p1.use_count() << "\n";
        std::cout << "p2 use_count: " << p2.use_count() << "\n";

        SmrtPtr<Test> p3;
        p3 = p2;
        std::cout << "p3 use_count after assignment: " << p3.use_count() << "\n";

        GetGlobalStorage<Test>().debugPrint();

        std::cout << "p1 value: " << p1->value << "\n";
        (*p2).value = 100;
        std::cout << "p3 value after modification: " << p3->value << "\n";
    }

    std::cout << "After scope, storage should be empty:\n";
    GetGlobalStorage<Test>().debugPrint();

    return 0;
}
