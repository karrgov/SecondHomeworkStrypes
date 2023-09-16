#include <iostream>
#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
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

    char* readInput() //novo
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

    int sizeOfArray()
    {
        return this->size;
    }

    int sizeOfArray() const
    {
        return this->size;
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
                //*(array + i ) = other.(*(array + i));
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

    /*
    Filter(Stream& stream, const char* wordToBeFound) : stream(stream)
    {
        //this->stream = stream;
        this->wordToBeFound = wordToBeFound;
        this->dataFromStream = stream.readInput();
    }
    */

    char* searchInput() 
    {
        char* startLine = dataFromStream;
        char* endLine = nullptr;

        while ((endLine = strchr(startLine, '\n')) != nullptr) 
        {
            size_t length = endLine - startLine;
            char* substring = new char[length + 1];

            //#ifdef __STDC_LIB_EXT1__
            //strncpy_s(substring, length + 1, startLine, length);
            strncpy(substring, startLine, length);
            //#endif

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

    void printEverything() 
    {
        if (streamPointer != nullptr) 
        {
            std::cout << streamPointer->readInput() << std::endl;
        } 
        else 
        {
            std::cout << filterPoiter->searchInput() << std::endl;
        } 
    }
};


int main()
{
    Stream stream;
    std::cout << "Enter text (Ctrl+D to end input):\n";
    char* input = stream.readInput();

    Filter filter(stream, "kargov");
    std::cout << filter.searchInput() << std::endl;

    Sink sinkFilter(&filter);
    sinkFilter.printEverything();

    Sink sinkStream(&stream);
    sinkStream.printEverything();

    return 0;
}