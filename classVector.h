#ifndef CLASSVECTOR_H
#define CLASSVECTOR_H

#include <string.h>
#include <iostream>
#include <stdlib.h>
#define MIN_MEMORY_SIZE 200
//#define UsingType int

using namespace std;

namespace my
{
    template <class UsingType>
    class vector;
}

template <class UsingType>
class my::vector
{
private:
    unsigned int VectorSize; //number of elements
    unsigned int MemorySize; //number of bytes allocated from heap
    UsingType* Pointer;  //pointer to begin of vector
    int MemoryGrow() //to reallocate memory
    {
        UsingType* BufPointer;
        try{
            BufPointer = (UsingType*) new char[MemorySize * 2];
        }
        catch(...){
            cerr << "Memory allocation error" << endl;
            return 1;
        }
        memcpy(BufPointer, Pointer, MemorySize);
        MemorySize = MemorySize * 2;
        Pointer = BufPointer;
        return 0;
    }
public:
    explicit vector(): VectorSize(0),
                       MemorySize(MIN_MEMORY_SIZE * sizeof(UsingType))
    {
        Pointer = (UsingType*) new char[MemorySize];
    }

    explicit vector(unsigned int _MemorySize): VectorSize(0),
                                               MemorySize(_MemorySize * sizeof(UsingType))
    {
        Pointer = (UsingType*) new char[MemorySize];
    }

    explicit vector(my::vector<UsingType> const & _vector): VectorSize(_vector.VectorSize),
                                                            MemorySize(_vector.MemorySize)
    {
        Pointer = (UsingType*) new char[MemorySize];
        for (unsigned int i = 0; i < VectorSize; i++){
            new (Pointer + i) UsingType();
            Pointer[i] = _vector[i];
        }
    }

    ~vector()
    {
        delete[] Pointer;
    }

    void operator=(my::vector<UsingType> const & _vector)
    {
        UsingType* BufPointer;
        BufPointer = (UsingType*) new char[_vector.MemorySize];
        delete[] Pointer;
        Pointer = BufPointer;
        MemorySize = _vector.MemorySize;
        VectorSize = _vector.VectorSize;
        for (unsigned int i = 0; i < VectorSize; i++){
            new (Pointer + i) UsingType();
            Pointer[i] = _vector[i];
        }
    }

    UsingType const & operator[](int const k) const
    {
        if (k < 0)
            throw "Unacceptable index";
        if ((unsigned int)k > VectorSize)
            throw "Unacceptable index";
        UsingType const & Obj = Pointer[k];
        return Obj;
    }

    UsingType & operator[](int const k)
    {
        if (k > VectorSize){
            while (k * sizeof(UsingType) >= MemorySize){
                if (MemoryGrow())
                    abort();
            }
            for (int i = VectorSize; i < k; i++){
                new (Pointer + i) UsingType();
            }
        }
        UsingType & Obj = Pointer[k];
        return Obj;
    }
//    //    void PushBack(Point);
//    //    int GetSize();
};

#endif // CLASSVECTOR_H
