#ifndef CLASSVECTOR_H
#define CLASSVECTOR_H

#include <string.h>
#include <iostream>
#include <stdlib.h>
#define MIN_MEMORY_SIZE 4

using namespace std;

namespace my
{
    template <class UsingType>
    class vector;
    template<>
    class vector<bool>;
}

template <class UsingType>
class my::vector
{
private:
    unsigned int VectorSize; //number of elements
    unsigned int MemorySize; //number of bytes allocated from heap
    char* Pointer;  //pointer to begin of vector
    void MemoryGrow(); //to reallocate memory
public:
    explicit vector();
    explicit vector(unsigned int); //creat a vector with specified initial MemorySize
    explicit vector(my::vector<UsingType> const & ); // copy a vector
    ~vector();
    void operator=(my::vector<UsingType> const &);
    UsingType const & operator[](unsigned int const) const;
    UsingType & operator[](unsigned int const);
    void PushBack(UsingType);
    int GetSize();
};

template<>
class my::vector<bool>
{
private:
    unsigned int VectorSize; //number of elements
    unsigned int MemorySize; //number of bytes allocated from heap
    char* Pointer;  //pointer to begin of vector
    void MemoryGrow(); //to reallocate memory
    class ToElem;
public:
    explicit vector();
    explicit vector(unsigned int); //creat a vector with specified initial MemorySize
    explicit vector(my::vector<bool> const & ); // copy a vector
    ~vector();
    void operator=(my::vector<bool> const &);
    bool const operator[](unsigned int const) const;
    my::vector<bool>::ToElem operator[](unsigned int const);
    void PushBack(bool);
    int GetSize();
};

class my::vector<bool>::ToElem
{
private:
    unsigned int const pos;
    unsigned char mask1;
    unsigned char mask0;
    char *pointer;
public:
    ToElem(unsigned int const _pos, char *_pointer);
    void operator =(bool _val);
    operator bool() const;
};

#include "classVector.cpp"

#endif // CLASSVECTOR_H
