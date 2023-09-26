#pragma once
#include <iostream>
class CustomString
{
    private:
    char* array = nullptr;
    int size;
    int capacity;

    public:
    CustomString();
    CustomString(int capacity);
    CustomString(const char* str);
    CustomString(const CustomString& other);
    CustomString& operator=(const CustomString& other);
    ~CustomString();

    void setData(const char* str);
    char* readInput();

    char* getArray();
    char* getArray() const;
    int sizeOfArray() const;
    int capacityOfArray();

    void incrementSize();
    void addElement(const char value);
    void expandArray();
    void printElements();
    char operator[] (int index) const;
};