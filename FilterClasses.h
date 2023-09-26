#pragma once
#include "StreamClasses.h"

class Filter
{
    private:
    //Stream stream;
    const Stream& stream;
    const char* wordToBeFound;
    char* dataFromStream;

    public:
    Filter(Stream& stream, const char* wordToBeFound);
    Filter(Stream& stream);

    char* searchWordInInput();
    const Stream& getStream();
};

class CopyFilter : public Filter
{
public:
    CopyFilter(Stream& stream);
    char* getOriginalContent();
};

class CapitaliseFilter : public Filter
{
public:
    CapitaliseFilter(Stream& stream, const char* wordToBeFound);
    void capitaliseWords();
};

class FunctionFilter : public Filter
{
private:
    inline static char* (*encodingFunction)(char*);

public:
    FunctionFilter(Stream& stream, const char* wordToBeFound);
    FunctionFilter(Stream& stream);

    char* applyEncodingFunction();
    static void setEncodingFunction(char* (*function)(char*));
};

