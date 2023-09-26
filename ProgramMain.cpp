#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <cstring>
#include <cassert>
#include "StreamClasses.h"
#include "FilterClasses.h"
#include "SinkClasses.h"

char* testEncodingFuncExample1(char* textData)
{
    int length = strlen(textData);
    for (int i = 0; i < length; i++)
    {
        if(*(textData + i) == '1')
        {
            *(textData + i) = '9';
        }
    }
    return textData;
}

char* testEncodingFuncExample2(char* textData)
{
    int length = strlen(textData);
    for (int i = 0; i < length; i++)
    {
        if(*(textData + i) == '9')
        {
            *(textData + i) = '1';
        }
    }
    return textData;
}

int main()
{
    try
    {
        //test for Stream class
        //Stream stream;
        //std::cout << "Input text data and terminate by Control + D:\n";
        //char* input = stream.readInput();

        //test for Filter class
        Stream stream("anasfnfkargov\n3adfssa\n2kargovdsfsandf");
        Filter filter(stream, "kargov");
        std::cout << filter.searchWordInInput() << std::endl;
        
        //test for Sink class
        //Sink sinkFilter(&filter);
        //sinkFilter.printEverything();
        //Sink sinkStream(&stream);
        //sinkStream.printEverything();

        //test for EmptyStream class
        //EmptyStream emptyTextStream;
        //std::cout << emptyTextStream.returnEof() << std::endl;

        //test for ConstStream class
        //ConstStream constantStream("helloworld123");

        //test for RandomStream class
        //RandomStream randomisedStream(13);
        //randomisedStream.changeSymbols("124345");

        //test for FileStream class
        //FileStream streamFromFile("safyhsfnfadnusf/nafnjasdf");

        //test for CopyFilter class
        //CopyFilter copyingFilter(stream, "kargov");
        //copyingFilter.printOriginalStream();

        //test for CapitaliseFilter class
        //CapitaliseFilter capitalisedFilterStream(stream, "kargov");
        //capitalisedFilterStream.printCapitalisedStream();

        //test for FunctionFilter class
        //FunctionFilter testStream(stream, "kargov");
        //testStream.setEncodingFunction(testEncodingFuncExample1);
        //std::cout << testStream.applyEncodingFunction() << std::endl;
        //testStream.setEncodingFunction(testEncodingFuncExample2);
        //std::cout << testStream.applyEncodingFunction() << std::endl;

        //test for FileSink class
        //FileSink streamToFile(&stream, "kargovTesting.txt");
        //streamToFile.saveTextDataToFile();
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }


    return 0;
}