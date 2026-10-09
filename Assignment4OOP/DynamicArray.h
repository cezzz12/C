//
// Created by Cezar on 26.03.2025.
//
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#pragma once
#include <stdexcept>
template <typename T>
class DynamicArray {
private:
    T* elements;
    int size;
    int capacity;

    void resize(int newCapacity) {
        T* newElements = new T[newCapacity];
        int elementsToCopy = (size < newCapacity) ? size : newCapacity;

        for (int i = 0; i < elementsToCopy; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
        size = elementsToCopy;
    }

public:
    DynamicArray() : elements(nullptr), size(0), capacity(0) {}

    DynamicArray(int initialCapacity) : size(0), capacity(initialCapacity) {
        elements = (initialCapacity > 0) ? new T[capacity] : nullptr;
    }

    DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity) {
        elements = new T[capacity];
        for (int i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }

    ~DynamicArray() {
        delete[] elements;
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            capacity = other.capacity;

            elements = new T[capacity];
            for (int i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    void add(const T& element) {
        if (size == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity);
        }
        elements[size++] = element;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < size - 1; ++i) {
            elements[i] = elements[i + 1];
        }
        --size;
        if (size > 0 && size < capacity / 4) {
            resize(capacity / 2);
        }
    }

    void clear() {
        size = 0;
    }

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    bool isEmpty() const { return size == 0; }

    T* begin() { return elements; }
    T* end() { return elements + size; }
    const T* begin() const { return elements; }
    const T* end() const { return elements + size; }
};
#endif //DYNAMICARRAY_H
