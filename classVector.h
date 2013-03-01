#ifndef CLASSVECTOR_H
#define CLASSVECTOR_H

#include <string.h>
#include <iostream>
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
    int const SizeType; //size of type
    unsigned int MemorySize; //number of bytes allocated from heap
    void* Pointer;  //pointer to begin of vector
    int MemoryGrow() //to reallocate memory
    {
        void* BufPointer;
        try{
            BufPointer = (void*) new char[MemorySize * 2];
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
                       SizeType(sizeof(UsingType)),
                       MemorySize(MIN_MEMORY_SIZE * SizeType)
    {
        Pointer = (void*) new char[MemorySize];
    }

    explicit vector(unsigned int _MemorySize): VectorSize(0),
                                               SizeType(sizeof(UsingType)),
                                               MemorySize(_MemorySize * SizeType)
    {
        Pointer = (void*) new char[MemorySize];
    }

    explicit vector(my::vector<UsingType> const & _vector): VectorSize(_vector.VectorSize),
                                                            MemorySize(_vector.MemorySize),
                                                            SizeType(sizeof(UsingType))
    {
        Pointer = (void*) new char[MemorySize];
        for (int i = 0; i < VectorSize; i++){
            new ((char*)Pointer + i * SizeType) UsingType();
            this[i] = _vector[i];
        }
    }

    ~vector()
    {
        delete[] Pointer;
    }

    void operator=(my::vector<UsingType> const & _vector)
    {
        void* BufPointer;
        BufPointer = (void*) new char[_vector.MemorySize];
        delete[] Pointer;
        Pointer = BufPointer;
        MemorySize = _vector.MemorySize;
        VectorSize = _vector.VectorSize;
        for (int i = 0; i < VectorSize; i++){
            new ((char*)Pointer + i * SizeType) UsingType();
            this[i] = _vector[i];
        }
    }

    UsingType const & operator[](int const k) const
    {
        if (k <= VectorSize)
            ;
        else{
            if ((k + 1) * SizeType < MemorySize){
                for (int i = VectorSize; i < k; i++){
                    new ((char*)Pointer + i * SizeType) UsingType();
                }
            }
            else{
                while (k * SizeType >= MemorySize){
                    if (MemoryGrow())
                        return NULL;
                }
            }
        }
        return (UsingType const) *((char*)Pointer + k * SizeType);
    }

    UsingType & operator[](int const k)
    {
        if (k <= VectorSize)
            ;
        else{
            if ((k + 1) * SizeType < MemorySize){
                for (int i = VectorSize; i < k; i++){
                    new ((char*)Pointer + i * SizeType) UsingType();
                }
            }
            else{
                while (k * SizeType >= MemorySize){
                    if (MemoryGrow())
                        return NULL;
                }
            }
        }
        return (UsingType) *((char*)Pointer + k * SizeType);;
    }
//    //    void PushBack(Point);
//    //    int GetSize();
};

#endif // CLASSVECTOR_H
