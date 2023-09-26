#define _CRT_SECURE_NO_WARNINGS
#include "StreamClasses.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <fstream>
#include <exception>

Stream::Stream(int capacity)
{
    this->capacity = capacity;
    this->array = new char[capacity];
    this->size = 0;
}

Stream::Stream()
{
    this->capacity = 10;
    this->array = new char[capacity];
    this->size = 0;
    *(this->array + size++) = '\0';
}

Stream::Stream(const char* str) : Stream() 
{
    setData(str);
}

Stream::Stream(const Stream& other)
{
    this->capacity = other.capacity;
    array = new char[capacity];
    this->size = other.size;
    for(int i = 0; i < size; ++i) 
    {
        *(array + i) = other.array[i];
    }
}

Stream::~Stream()
{
    delete[] array;
}

void Stream::setData(const char* str) 
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

char* Stream::readInput()
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

char* Stream::getArray()
{
    return array;
}

char* Stream::getArray() const
{
    return array;
}

int Stream::sizeOfArray() const
{
    return this->size;
}

void Stream::incrementSize()
{
    size++;
}

int Stream::capacityOfArray()
{
    return this->capacity;
}

void Stream::addElement(const char value)
{
    if(size == capacity)
    {
        expandArray();
    }
    *(array + size) = value;
    size++;
}

void Stream::expandArray()
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

char Stream::operator[] (int index) const
{
    assert(index >= 0 && index < size);
    return *(array + index);
}

Stream& Stream::operator=(const Stream& other) 
{
    if (this != &other) 
    {
        setData(other.array);
    }
    return *this;
}

void RandomStream::setSymbols()
{
    addElement('s');
    addElement('g');
    addElement('k');
    addElement('q');
    addElement('m');
}

RandomStream::RandomStream(int numChars) : Stream(numChars) 
{
    this->capacity = 10;
    symbols = new char[capacity];
    this->size = 0;

    for(int i = 0; i < numChars; ++i)
    {
        *(this->getArray() + i) = *(symbols + (rand() % size));
    }
}

void RandomStream::addElement(const char value)
{
    if(size == capacity)
    {
        expandArray();
    }
    *(symbols + size) = value;
    size++;
}

void RandomStream::expandArray()
{
    char* tempArray = new char[capacity * 2];
    capacity = capacity * 2;
    for (int i = 0; i < size; i++)
    {
        *(tempArray + i) = *(symbols + i);
    }
    delete[] symbols;
    symbols = tempArray;
}

void RandomStream::changeSymbols(const char* newSymbols)
{
    int newSize = strlen(newSymbols);
    char* tempArray = new char[newSize + 1];
    strncpy(tempArray, newSymbols, newSize);
    tempArray[newSize] = '\0';
    size = newSize;
    capacity = newSize;
    delete[] symbols;
    symbols = tempArray;
}

RandomStream::~RandomStream()
{
    delete[] symbols;
}

RandomStream::RandomStream(const RandomStream& other)
{
    this->capacity = other.capacity;
    symbols = new char[capacity];
    this->size = other.size;
    for(int i = 0; i < size; ++i) 
    {
        *(symbols + i) = other.symbols[i];
    }
}

RandomStream& RandomStream::operator=(const RandomStream& other) 
{
    if (this == &other) 
    {
        return *this;
    } 
    else 
    {
        if (capacity < other.size) 
        {
            expandArray();
        } 
        size = other.size;
        for(int i = 0; i < size; ++i) 
        {
            *(symbols + i ) = other.symbols[i];
        }
        return *this;
    }
}

FileStream::FileStream(const char* filename) : Stream(0)
{
    std::ifstream file(filename);

    if (!file)
    {
        std::cerr << "Could not open the file you've chose: " << filename << std::endl;
        return;
    }
    char ch;
    while (file.get(ch))
    {
        if (this->sizeOfArray() == this->capacityOfArray())
        {
            expandArray();
        }
        this->incrementSize();
        *(this->getArray() + this->sizeOfArray()) = ch;
    }
    file.close();
}

char* FileStream::readFile(const char* fileName) 
{
    std::ifstream file(fileName);
    if (!file.is_open()) 
    {
        std::cerr << "Could not open the file you've chose: " << fileName << std::endl;
        return nullptr;
    }

    char buff[1025]; // max characters on a line(1024) plus '\0'
    char* tempData = new char[1];
    tempData[0] = '\0';
    try {
        while (file.getline(buff, 1025)) {
            int size = strlen(tempData) + strlen(buff) + 2; // '\n' and '\0'
            char* currData = new char[size];
            strcpy(currData, tempData);
            strcat(currData, buff);
            currData[size - 2] = '\n';
            currData[size - 1] = '\0';
            delete[] tempData;
            tempData = currData;
        }
    }
    catch (...) 
    {
        delete[] tempData;
        throw;
    }
    return tempData;
}

FileStream::FileStream(const char* fileName) 
{
    char* tempData = readFile(fileName);
    if (tempData) 
    {
        Stream::setData(tempData);
        delete[] tempData;
    }
}
