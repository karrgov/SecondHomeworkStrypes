#define _CRT_SECURE_NO_WARNINGS
#include "CustomString.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <fstream>
#include <exception>

CustomString::CustomString(int capacity)
{
    this->capacity = capacity;
    this->array = new char[capacity];
    this->size = 0;
}

CustomString::CustomString()
{
    this->capacity = 10;
    this->array = new char[capacity];
    this->size = 0;
    *(this->array + size++) = '\0';
}

CustomString::CustomString(const char* str) : CustomString() 
{
    setData(str);
}

CustomString::CustomString(const CustomString& other)
{
    this->capacity = other.capacity;
    array = new char[capacity];
    this->size = other.size;
    for(int i = 0; i < size; ++i) 
    {
        *(array + i) = other.array[i];
    }
}

CustomString::~CustomString()
{
    delete[] array;
}

void CustomString::setData(const char* str) 
{
    if (str == nullptr) 
    {
        str = "";
    }

    int strLength = strlen(str) + 1;
    while (strLength > capacity) 
    {
        expandArray();
    }

    strcpy(array, str);
    size = strLength;
}

char* CustomString::readInput()
{
    char ch;
    while (std::cin.get(ch)) 
    {
        if (size == capacity) 
        {
            expandArray();
        }
        array[size++] = ch;
    }

    if (capacity <= size)
    {
        expandArray();
    }

    array[size] = '\0';
    return array;
}

char* CustomString::getArray()
{
    return array;
}

char* CustomString::getArray() const
{
    return array;
}

int CustomString::sizeOfArray() const
{
    return this->size;
}

void CustomString::incrementSize()
{
    size++;
}

int CustomString::capacityOfArray()
{
    return this->capacity;
}

void CustomString::addElement(const char value)
{
    if(size == capacity)
    {
        expandArray();
    }
    *(array + size) = value;
    size++;
}

void CustomString::expandArray()
{
    char* tempArray = new char[capacity * 2];
    capacity = capacity * 2;
    for (int i = 0; i < size; i++)
    {
        *(tempArray + i) = *(array + i);
    }
    delete[] array;
    array = tempArray;
}

char CustomString::operator[] (int index) const
{
    assert(index >= 0 && index < size);
    return *(array + index);
}

CustomString& CustomString::operator=(const CustomString& other) 
{
    if (this != &other) 
    {
        setData(other.array);
    }
    return *this;
}
