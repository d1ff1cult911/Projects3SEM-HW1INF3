#include <iostream>
#include <string>
#include <unordered_map>
#include "SmartPtr.h"

struct Dummy {
    std::string name;
    Dummy(std::string n) : name(std::move(n)) {
        std::cout << "Construct: " << name << "\n";
    }
    ~Dummy() {
        std::cout << "Destruct: " << name << "\n";
    }
};

struct PtrEnv {
    SmrtPtr<Dummy> a;
    SmrtPtr<Dummy> b;
};

void printMenu() {
    std::cout << "\n=====================\n";
    std::cout << " SmartPtr Interactive Console\n";
    std::cout << "=====================\n";
    std::cout << "1. Создать объект A\n";
    std::cout << "2. Создать объект B\n";
    std::cout << "3. Копировать A -> B\n";
    std::cout << "4. Копировать B -> A\n";
    std::cout << "5. Обнулить A\n";
    std::cout << "6. Обнулить B\n";
    std::cout << "7. Показать состояние\n";
    std::cout << "8. Создать массив (с delete[])\n";
    std::cout << "9. Выйти\n";
    std::cout << "Выберите действие: ";
}

int main() {
    PtrEnv env;
    bool running = true;

    while (running) {
        printMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name;
                std::cout << "Введите имя для объекта A: ";
                std::cin >> name;
                env.a = SmrtPtr<Dummy>(new Dummy(name));
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Введите имя для объекта B: ";
                std::cin >> name;
                env.b = SmrtPtr<Dummy>(new Dummy(name));
                break;
            }
            case 3:
                env.b = env.a;
                std::cout << "Теперь B копирует A.\n";
                break;
            case 4:
                env.a = env.b;
                std::cout << "Теперь A копирует B.\n";
                break;
            case 5:
                env.a = nullptr;
                std::cout << "A обнулён.\n";
                break;
            case 6:
                env.b = nullptr;
                std::cout << "B обнулён.\n";
                break;
            case 7:
                std::cout << "\n-- Состояние --\n";
                std::cout << "A.use_count = " << env.a.use_count() << "\n";
                std::cout << "B.use_count = " << env.b.use_count() << "\n";
                GetGlobalStorage<Dummy>().debugPrint();
                break;
            case 8: {
                std::cout << "Создаётся массив из 3 элементов...\n";
                SmrtPtr<int> arr(new int[3]{10, 20, 30}, [](int* p) {
                    std::cout << "Custom array deleter called!\n";
                    delete[] p;
                });
                for (int i = 0; i < 3; ++i)
                    std::cout << "arr[" << i << "] = " << arr.get()[i] << "\n";
                std::cout << "Массив будет удалён после выхода из блока.\n";
                break;
            }
            case 9:
                running = false;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    std::cout << "\nВыход из пр9ограммы. Все SmartPtr будут уничтожены.\n";
    GetGlobalStorage<Dummy>().debugPrint();
    return 0;
}
