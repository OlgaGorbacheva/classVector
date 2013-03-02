#ifndef CLASSVECTOR_HPP
#define CLASSVECTOR_HPP
#include "classVector.h"

template <class UsingType>
void my::vector<UsingType>::MemoryGrow()
{
    UsingType* BufPointer;
    BufPointer = (UsingType*) new char[MemorySize * 2];
    memcpy(BufPointer, Pointer, MemorySize);
    MemorySize = MemorySize * 2;
    Pointer = BufPointer;
}

template <class UsingType>
my::vector<UsingType>::vector(): VectorSize(0),
                                 MemorySize(MIN_MEMORY_SIZE * sizeof(UsingType))
{
    Pointer = (UsingType*) new char[MemorySize];
}

template <class UsingType>
my::vector<UsingType>::vector(unsigned int _MemorySize): VectorSize(0),
                                                         MemorySize(_MemorySize * sizeof(UsingType))
{
    Pointer = (UsingType*) new char[MemorySize];
}

template <class UsingType>
my::vector<UsingType>::vector(my::vector<UsingType> const & _vector): VectorSize(_vector.VectorSize),
                                                                      MemorySize(_vector.MemorySize)
{
    Pointer = (UsingType*) new char[MemorySize];
    for (unsigned int i = 0; i < VectorSize; i++){
        new (Pointer + i) UsingType();
        Pointer[i] = _vector[i];
    }
}

template <class UsingType>
my::vector<UsingType>::~vector()
{
    delete[] Pointer;
}

template <class UsingType>
void my::vector<UsingType>::operator=(my::vector<UsingType> const & _vector)
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

template <class UsingType>
UsingType const & my::vector<UsingType>::operator[](unsigned int const k) const
{
    if (k >= VectorSize)
        throw "Unexpectable index";
    UsingType const & Obj = Pointer[k];
    return Obj;
}

template <class UsingType>
UsingType & my::vector<UsingType>::operator[](unsigned int const k)
{
    if (k >= VectorSize){
        try{
            while (k * sizeof(UsingType) >= MemorySize)
                MemoryGrow();
        }
        catch(bad_alloc){
            abort();
        }
        for (;VectorSize <= k; VectorSize++){
            new (Pointer + VectorSize) UsingType();
        }
    }
    UsingType & Obj = Pointer[k];
    return Obj;
}

template <class UsingType>
void my::vector<UsingType>::PushBack(UsingType elem)
{
    VectorSize++;
    if (VectorSize * sizeof(UsingType) > MemorySize){
        try{
            MemoryGrow();
        }
        catch(bad_alloc){
            abort();
        }
    }
    Pointer[VectorSize] = elem;
}

template <class UsingType>
int my::vector<UsingType>::GetSize()
{
    return VectorSize;
}

#endif //CLASSVECTOR_HPP
