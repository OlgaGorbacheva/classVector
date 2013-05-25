#ifndef CLASSVECTOR_HPP
#define CLASSVECTOR_HPP
#include "classVector.h"

template <class UsingType>
void my::vector<UsingType>::MemoryGrow()
{
    char* BufPointer;
    BufPointer = new char[MemorySize * 2];
    for (unsigned int i = 0; i < VectorSize; i++){
        new ((UsingType*)BufPointer + i) UsingType();
        *((UsingType*)BufPointer + i) = *((UsingType*)Pointer + i);
    }
    MemorySize = MemorySize * 2;
    Pointer = BufPointer;
}

template <class UsingType>
my::vector<UsingType>::vector(): VectorSize(0),
                                 MemorySize(MIN_MEMORY_SIZE * sizeof(UsingType))
{
    Pointer = new char[MemorySize];
}

template <class UsingType>
my::vector<UsingType>::vector(unsigned int _MemorySize): VectorSize(0),
                                                         MemorySize(_MemorySize * sizeof(UsingType))
{
    Pointer = new char[MemorySize];
}

template <class UsingType>
my::vector<UsingType>::vector(my::vector<UsingType> const & _vector): VectorSize(_vector.VectorSize),
                                                                      MemorySize(_vector.MemorySize)
{
    Pointer = new char[MemorySize];
    for (unsigned int i = 0; i < VectorSize; i++){
        new ((UsingType*)Pointer + i) UsingType();
        *((UsingType*)Pointer + i)= _vector[i];
    }
}

template <class UsingType>
my::vector<UsingType>::~vector()
{
    for (unsigned int i = 0; i < VectorSize; i++){
        ((UsingType*)Pointer + i)->~UsingType();
    }
    delete[] Pointer;
}

template <class UsingType>
void my::vector<UsingType>::operator=(my::vector<UsingType> const & _vector)
{
    char* BufPointer;
    BufPointer = new char[_vector.MemorySize];
    delete[] Pointer;
    Pointer = BufPointer;
    MemorySize = _vector.MemorySize;
    VectorSize = _vector.VectorSize;
    for (unsigned int i = 0; i < VectorSize; i++){
        new ((UsingType*)Pointer + i) UsingType();
        *((UsingType*)Pointer + i) = _vector[i];
    }
}

template <class UsingType>
UsingType const & my::vector<UsingType>::operator[](unsigned int const k) const
{
    if (k >= VectorSize)
        throw "Unexpectable index";
    UsingType const & Obj = *((UsingType*)Pointer + k);
    return Obj;
}

template <class UsingType>
UsingType & my::vector<UsingType>::operator[](unsigned int const k)
{
    if (k >= VectorSize){
            while (k * sizeof(UsingType) >= MemorySize)
                MemoryGrow();
        for (;VectorSize <= k; VectorSize++){
            new ((UsingType*)Pointer + VectorSize) UsingType();
        }
    }
    UsingType & Obj = *((UsingType*)Pointer + k);
    return Obj;
}

template <class UsingType>
void my::vector<UsingType>::PushBack(UsingType elem)
{
    VectorSize++;
    if (VectorSize * sizeof(UsingType) > MemorySize){
        MemoryGrow();
    }
    *((UsingType*)Pointer + VectorSize) = elem;
}

template <class UsingType>
int my::vector<UsingType>::GetSize()
{
    return VectorSize;
}

/////////////bool////////////////

void my::vector<bool>::MemoryGrow()
{
    char* BufPointer;
    BufPointer = new char[MemorySize * 2];
    for (unsigned int i = 0; i < VectorSize / 8; i++)
        BufPointer[i] = Pointer[i];
    MemorySize = MemorySize * 2;
    Pointer = BufPointer;
}

my::vector<bool>::vector(): VectorSize(0),
                                 MemorySize(MIN_MEMORY_SIZE)
{
    Pointer = new char[MemorySize];
}

my::vector<bool>::vector(unsigned int _MemorySize): VectorSize(0),
                                                         MemorySize(_MemorySize / 8)
{
    Pointer = new char[MemorySize];
}

my::vector<bool>::vector(my::vector<bool> const & _vector): VectorSize(_vector.VectorSize),
                                                                      MemorySize(_vector.MemorySize)
{
    Pointer = new char[MemorySize];
    for (unsigned int i = 0; i < VectorSize / 8; i++){
        Pointer[i] = _vector.Pointer[i];
    }
}

my::vector<bool>::~vector()
{
    delete[] Pointer;
}

void my::vector<bool>::operator=(my::vector<bool> const & _vector)
{
    if (MemorySize < _vector.MemorySize){
        char* BufPointer;
        BufPointer = new char[_vector.MemorySize];
        delete[] Pointer;
        Pointer = BufPointer;
    }
    MemorySize = _vector.MemorySize;
    VectorSize = _vector.VectorSize;
    for (unsigned int i = 0; i < VectorSize / 8; i++){
        Pointer[i] = _vector.Pointer[i];
    }
}

bool const my::vector<bool>::operator[](unsigned int const k) const
{
    if (k >= VectorSize)
        throw "Unexpectable index";
    unsigned char mask = 1 << (7 - k % 8);
    bool const ret = Pointer[k / 8] & mask ? true : false;
//    cout <<ret;
    return  ret;
}

my::vector<bool>::ToElem my::vector<bool>::operator[](unsigned int const k)
{
    if (k >= VectorSize)
        throw "Unexpectable index";
    my::vector<bool>::ToElem result(k, Pointer);
    return result;
}

void my::vector<bool>::PushBack(bool elem)
{
    if (VectorSize / 8 > MemorySize){
        MemoryGrow();
    }
    unsigned char mask = 1 << (7 - VectorSize % 8);
    if (elem == true)
        Pointer[VectorSize / 8] = Pointer[VectorSize / 8] | mask;

    VectorSize++;
}

int my::vector<bool>::GetSize()
{
    return VectorSize;
}

my::vector<bool>::ToElem::ToElem(unsigned int const _pos, char *_pointer):pos(_pos), pointer(_pointer)
{
    mask1 = 1 << (7 - pos % 8);
    mask0 = ~mask1;
}

void my::vector<bool>::ToElem::operator =(bool _val)
{
    if (_val)
        pointer[pos / 8] = pointer[pos / 8] | mask1;
    else pointer[pos / 8] = pointer[pos / 8] & mask0;
}

my::vector<bool>::ToElem::operator bool() const
{
    return (pointer[pos / 8] & mask1) ? true : false;
}

#endif //CLASSVECTOR_HPP
