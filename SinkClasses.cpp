#define _CRT_SECURE_NO_WARNINGS
#include "SinkClasses.h"
#include <cstring>
#include <fstream>

//двата конструктора за двата различни случая (не можем да имаме stream и filter едновремено)
Sink::Sink(Stream* stream) : streamPointer(stream), filterPoiter(nullptr) {}

Sink::Sink(Filter* filter) : streamPointer(nullptr), filterPoiter(filter) {}

Stream* Sink::getStreamPointer()
{
    return streamPointer;
}

Filter* Sink::getFilterPointer()
{
    return filterPoiter;
}

void Sink::printEverything() 
{
    if (streamPointer != nullptr) 
    {
        std::cout << streamPointer->readInput() << std::endl;
    } 
    else 
    {
        std::cout << filterPoiter->searchWordInInput() << std::endl;
    } 
}

FileSink::FileSink(Stream* stream, const char* filename) : Sink(stream), filename(filename) 
{

}

FileSink::FileSink(Filter* filter, const char* filename) : Sink(filter), filename(filename) 
{

}

void FileSink::saveTextDataToFile()
{
    std::ofstream outputFile(filename);

    if (!outputFile)
    {
        std::cerr << "Could not open the file you've chose: " << filename << std::endl;
        return;
    }

    if (this->getStreamPointer() != nullptr)
    {
        const char* content = this->getStreamPointer()->readInput();
        outputFile << content;
    }
    else if (this->getFilterPointer() != nullptr)
    {
        const char* content = this->getFilterPointer()->searchWordInInput();
        outputFile << content;
    }

    outputFile.close();
}