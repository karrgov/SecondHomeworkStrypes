#pragma once
#include <iostream>
class Stream
{
    private:
    char* array = nullptr;
    int size;
    int capacity;

    public:
    Stream();
    Stream(int capacity);
    Stream(const char* str);
    Stream(const Stream& other);
    Stream& operator=(const Stream& other);
    ~Stream();

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

class EmptyStream : public Stream
{
    public:
    EmptyStream() : Stream() {}
    EmptyStream(const EmptyStream& other) = delete;
	EmptyStream& operator=(const EmptyStream& other) = delete;

    void setData(const char* str) = delete;
	void readInput() = delete;

	char operator[](int pos) const { return '\0'; }
};

class ConstStream : public Stream {
public:
	ConstStream(const char* str = "\0") : Stream(str) {}

	void setData(const char* str) = delete;
	void readInput() = delete;
};

class RandomStream : public Stream
{
    private:
    inline static char* symbols;
    inline static int size;
    inline static int capacity;

    public:
    RandomStream(int numChars);
    RandomStream(const RandomStream& other);
    RandomStream& operator=(const RandomStream& other);
    ~RandomStream();

    static void addElement(const char value);
    static void expandArray();
    static void changeSymbols(const char* newSymbols);
    static void setSymbols();
};

class FileStream : public Stream
{
    public:
    FileStream(const char* fileName);
    char* readFile(const char* fileName);
};

