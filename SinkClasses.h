#pragma once
#include "FilterClasses.h"
#include "StreamClasses.h"
class Sink 
{
    private:
    Stream *streamPointer;
    Filter *filterPoiter;

    public:
    //двата конструктора за двата различни случая (не можем да имаме stream и filter едновремено)
    Sink(Stream* stream);
    Sink(Filter* filter);

    Stream* getStreamPointer();
    Filter* getFilterPointer();

    void printEverything();
};

class FileSink : public Sink
{
private:
    const char* filename;

public:
    FileSink(Stream* stream, const char* filename);
    FileSink(Filter* filter, const char* filename);

    void saveTextDataToFile();
};