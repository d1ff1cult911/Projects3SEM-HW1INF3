#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <unordered_map>
#include <cassert>
#include <iostream>
#include <functional>

// ======================================================
//  ХРАНИЛИЩЕ
// ======================================================
template <typename T>
class ObjectStorage {
private:
    std::unordered_map<T*, size_t> refCounts;

public:
    void add(T* ptr) {
        if (!ptr) return;
        refCounts[ptr] = 1;
    }

    void addRef(T* ptr) {
        if (ptr && refCounts.count(ptr))
            ++refCounts[ptr];
    }

    void release(T* ptr) {
        if (!ptr) return;
        auto it = refCounts.find(ptr);
        if (it != refCounts.end()) {
            if (--(it->second) == 0) {
                refCounts.erase(it);
            }
        }
    }

    size_t getCount(T* ptr) const {
        if (ptr && refCounts.count(ptr))
            return refCounts.at(ptr);
        return 0;
    }

    size_t size() const { return refCounts.size(); }

    void debugPrint() const {
        std::cout << "Active objects: " << refCounts.size() << "\n";
    }
};

// ======================================================
//  Глобальный доступ к хранилищу
// ======================================================
template <typename T>
ObjectStorage<T>& GetGlobalStorage() {
    static ObjectStorage<T> storage;
    return storage;
}

// ======================================================
//  SMART PTR
// ======================================================
template <typename T>
class SmrtPtr {
private:
    T* ptr;
    std::function<void(T*)> deleter;

    void addRef() {
        if (ptr)
            GetGlobalStorage<T>().addRef(ptr);
    }

    void release() {
        if (ptr) {
            size_t count = GetGlobalStorage<T>().getCount(ptr);
            GetGlobalStorage<T>().release(ptr);
            if (count == 1 && deleter)  // удаляем только когда последний владелец
                deleter(ptr);
            ptr = nullptr;
        }
    }

public:
    // Конструкторы
    SmrtPtr() : ptr(nullptr), deleter(nullptr) {}

    explicit SmrtPtr(T* p) : ptr(p), deleter([](T* p){ delete p; }) {
        if (ptr)
            GetGlobalStorage<T>().add(ptr);
    }

    SmrtPtr(T* p, std::function<void(T*)> d) : ptr(p), deleter(d) {
        if (ptr)
            GetGlobalStorage<T>().add(ptr);
    }

    SmrtPtr(const SmrtPtr& other) : ptr(other.ptr), deleter(other.deleter) {
        addRef();
    }

    SmrtPtr(SmrtPtr&& other) noexcept
        : ptr(other.ptr), deleter(std::move(other.deleter)) {
        other.ptr = nullptr;
    }

    // Присваивания
    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            deleter = other.deleter;
            addRef();
        }
        return *this;
    }

    SmrtPtr& operator=(SmrtPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            deleter = std::move(other.deleter);
            other.ptr = nullptr;
        }
        return *this;
    }

    SmrtPtr& operator=(std::nullptr_t) noexcept {
        release();
        return *this;
    }

    // Деструктор
    ~SmrtPtr() { release(); }

    // Методы доступа
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }

    size_t use_count() const { return GetGlobalStorage<T>().getCount(ptr); }

    explicit operator bool() const { return ptr != nullptr; }
};

#endif // SMARTPTR_H
