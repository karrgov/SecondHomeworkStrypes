#define _CRT_SECURE_NO_WARNINGS
#include "FilterClasses.h"
#include <cassert>
#include <cstring>

Filter::Filter(Stream& stream, const char* wordToBeFound) : stream(stream), wordToBeFound(wordToBeFound), dataFromStream(stream.
getArray())
{

}

Filter::Filter(Stream& stream) : stream(stream), dataFromStream(stream.readInput())
{

}

char* Filter::searchWordInInput() 
{
    char* startLine = dataFromStream;
    char* endLine = nullptr;

    while ((endLine = strchr(startLine, '\n')) != nullptr) 
    {
        int length = endLine - startLine;
        char* substring = new char[length + 1];

        strncpy(substring, startLine, length);
        substring[length] = '\0';
        
        if (strstr(substring, wordToBeFound) != nullptr)
        {
            return substring;
        }
        startLine = endLine + 1;
        delete[] substring;
    }
    return nullptr;
}

const Stream& Filter::getStream() 
{
    return (this->stream);
}

CopyFilter::CopyFilter(Stream& stream) : Filter(stream) 
{

}

char* CopyFilter::getOriginalContent()
{
    return this->getStream().getArray();
}

CapitaliseFilter::CapitaliseFilter(Stream& stream, const char* wordToBeFound) : Filter(stream, wordToBeFound)
{
    capitaliseWords();
}

void CapitaliseFilter::capitaliseWords()
{
    char* originalContent = this->getStream().getArray();
    bool newWord = true;

    for (int i = 0; originalContent[i] != '\0'; ++i)
    {
        if (std::isalpha(originalContent[i]))
        {
            if (newWord)
            {
                std::toupper(originalContent[i]);
                newWord = false;
            }
            else
            {
                std::tolower(originalContent[i]);
            }
        }
        else
        {
            if (originalContent[i] == ' ')
            {
                newWord = true;
            }
        }
    }
}

FunctionFilter::FunctionFilter(Stream& stream, const char* wordToBeFound) : Filter(stream, wordToBeFound)
{
}

char* FunctionFilter::applyEncodingFunction()
{
    char* originalContent = this->getStream().getArray();
    char* result = encodingFunction(originalContent);
    return result;
}

void FunctionFilter::setEncodingFunction(char* (*function)(char*))
{
    if(!function)
    {
        std::cerr << "Encoding function is nullptr!" << std::endl;
    }
    encodingFunction = function;
}
