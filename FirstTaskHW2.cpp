#include <iostream>
#include <string.h>
#include <fstream>
#include <cstring>

class Stream
{
    private:
    char* array = nullptr;
    int size;
    int capacity;

    public:
    Stream(int capacity)
    {
        this->capacity = capacity;
        this->array = new char[capacity];
        this->size = 0;
    }

    Stream()
    {
        this->capacity = 10;
        this->array = new char[capacity];
        this->size = 0;
    }

    Stream(const Stream& other)
    {
        this->capacity = other.capacity;
        array = new char[capacity];
        this->size = other.size;
        for(int i = 0; i < size; ++i) 
        {
            *(array + i) = other.array[i];
        }
    }

    ~Stream()
    {
        delete[] array;
    }

    char getCharUserInput()
    {
        return std::cin.get();
    }

    virtual char* readInput()
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

    char* getArray()
    {
        return array;
    }

    char* getArray() const
    {
        return array;
    }

    int sizeOfArray()
    {
        return this->size;
    }

    int sizeOfArray() const
    {
        return this->size;
    }

    void incrementSize()
    {
        size++;
    }

    int capacityOfArray()
    {
        return this->capacity;
    }

    void addElement(const char value)
    {
        if(size == capacity)
        {
            expandArray();
        }
        *(array + size) = value;
        size++;
    }

    void expandArray()
    {
        if (capacity == UINT32_MAX)
        {
            return;
        }
        char* tempArray = new char[capacity * 2];
        capacity = capacity * 2;
        for (int i = 0; i < size; i++)
        {
            *(tempArray + i) = *(array + i);
        }
        delete[] array;
        array = tempArray;
    }

    void printElements()
    {
        for (int i = 0; i < this->size; i++)
        {
            std::cout << *(array + i);
        }
    }

    char &operator[] (int index)
    {
        if(index > size)
        {
            return *array;
        }
        return *(array + index);
    }

    Stream& operator=(const Stream& other) 
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
                *(array + i ) = other.array[i];
            }
            return *this;
        }
    }
};

class Filter
{
    private:
    //Stream stream;
    const Stream& stream;
    const char* wordToBeFound;
    char* dataFromStream;

    public:
    Filter(Stream& stream, const char* wordToBeFound) : stream(stream), wordToBeFound(wordToBeFound), dataFromStream(stream.readInput())
    {
    }

    char* searchWordInInput() 
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

    const Stream& getStream() 
    {
        return (this->stream);
    }

    int isSubstring(char* partOf, char* string)
    {
        /*
        int m = strlen(partOf);
        int n = strlen(string);
        for (int i = 0; i < n - m; i++)
        {
            int j;
            for (j = 0; j < m; j++)
            {
                if(string[i + j] != partOf[j])
                {
                    break;
                }
            }
            if(j == m)
            {
                return i;
            }
        }
        return std::string::npos;
        */
       return 1;
    }

    /*
    //Filter(Stream& object, char arr[]) //: stream(object)
    {
        wordToBeFound = arr;
        size = strlen(arr);
        for (int i = 0; i < size; i++)
        {
            wordToBeFound[i] = arr[i];
        }

        int i = 0;
        //ASCII кодът на enter
        while(stream[i] != '13')
        {
            i++;
        }
        //i - индексът на началото на втория ред
        //обхождане на всеки един ред и проверяване дали съдържа нашия низ, след което извеждане на тези редове
        for (int n = 0; n <= i; n++)
        {
            if(int res = isSubstring(wordToBeFound, ))
        }
    }
    */
};

class Sink 
{
    private:
    Stream *streamPointer;
    Filter *filterPoiter;

    public:
    //двата конструктора за двата различни случая (не можем да имаме stream и filter едновремено)
    Sink(Stream* stream) : streamPointer(stream), filterPoiter(nullptr) {}

    Sink(Filter* filter) : streamPointer(nullptr), filterPoiter(filter) {}

    Stream* getStreamPointer()
    {
        return streamPointer;
    }

    Filter* getFilterPointer()
    {
        return filterPoiter;
    }

    void printEverything() 
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
};

class EmptyStream : public Stream
{
    public:
    EmptyStream() : Stream(0) 
    {
    }

    char returnEof()
    {
        return EOF;
    }
};

class ConstStream : public Stream
{
    public:
    ConstStream(const char* data) : Stream(strlen(data))
    {
        int size = strlen(data);
        for(int i = 0; i < size; ++i)
        {
            *(this->getArray() + i) = data[i];
        }
    }
};

class RandomStream : public Stream
{
    private:
    inline static char* symbols;
    inline static int size;
    inline static int capacity;

    public:
    RandomStream(int numChars) : Stream(numChars) 
    {
        this->capacity = 10;
        symbols = new char[capacity];
        this->size = 0;

        addElement('s');
        addElement('g');
        addElement('k');
        addElement('q');
        addElement('m');

        for(int i = 0; i < numChars; ++i)
        {
            *(this->getArray() + i) = *(symbols + (rand() % size));
        }
    }

    void addElement(const char value)
    {
        if(size == capacity)
        {
            expandArray();
        }
        *(symbols + size) = value;
        size++;
    }

    void expandArray()
    {
        if (capacity == UINT32_MAX)
        {
            return;
        }
        char* tempArray = new char[capacity * 2];
        capacity = capacity * 2;
        for (int i = 0; i < size; i++)
        {
            *(tempArray + i) = *(symbols + i);
        }
        delete[] symbols;
        symbols = tempArray;
    }

    void changeSymbols(const char* newSymbols)
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

    ~RandomStream()
    {
        delete[] symbols;
    }

    RandomStream(const RandomStream& other)
    {
        this->capacity = other.capacity;
        symbols = new char[capacity];
        this->size = other.size;
        for(int i = 0; i < size; ++i) 
        {
            *(symbols + i) = other.symbols[i];
        }
    }

    RandomStream& operator=(const RandomStream& other) 
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
};

class FileStream : public Stream
{
public:
    FileStream(const char* filename) : Stream(0)
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
};

class CopyFilter : public Filter
{
public:
    CopyFilter(Stream& stream, const char* wordToBeFound) : Filter(stream, wordToBeFound)
    {
    }

    char* getOriginalContent()
    {
        return this->getStream().getArray();
    }

    void printOriginalStream()
    {
        std::cout << getOriginalContent() << std::endl;
    }
};

class CapitaliseFilter : public Filter
{
public:
    CapitaliseFilter(Stream& stream, const char* wordToBeFound) : Filter(stream, wordToBeFound)
    {
    }

    char* capitaliseWords()
    {
        char* originalContent = this->getStream().getArray();
        char* result = new char[strlen(originalContent) + 1];
        bool newWord = true;

        for (int i = 0; originalContent[i] != '\0'; ++i)
        {
            if (std::isalpha(originalContent[i]))
            {
                if (newWord)
                {
                    result[i] = std::toupper(originalContent[i]);
                    newWord = false;
                }
                else
                {
                    result[i] = std::tolower(originalContent[i]);
                }
            }
            else
            {
                result[i] = originalContent[i];
                if (originalContent[i] == ' ')
                {
                    newWord = true;
                }
            }
        }
        result[strlen(originalContent)] = '\0';
        return result;
    }

    void printCapitalisedStream()
    {
        std::cout << capitaliseWords() << std::endl;
    }
};

class FunctionFilter : public Filter
{
private:
    inline static char* (*encodingFunction)(char*);

public:
    FunctionFilter(Stream& stream, const char* wordToBeFound) : Filter(stream, wordToBeFound)
    {
    }

    char* applyEncodingFunction()
    {
        char* originalContent = this->getStream().getArray();
        char* result = encodingFunction(originalContent);
        return result;
    }

    static void setEncodingFunction(char* (*function)(char*))
    {
        encodingFunction = function;
    }
};

class FileSink : public Sink
{
private:
    const char* filename;

public:
    FileSink(Stream* stream, const char* filename) : Sink(stream), filename(filename) {}

    FileSink(Filter* filter, const char* filename) : Sink(filter), filename(filename) {}

    void saveTextDataToFile()
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
};

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
    //test for Stream class
    Stream stream;
    std::cout << "Input text data and terminate by CTRL + D:\n";
    char* input = stream.readInput();

    //test for Filter class
    //Filter filter(stream, "kargov");
    //std::cout << filter.searchWordInInput() << std::endl;
    
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


    return 0;
}