#ifndef CLASSVECTOR_H
#define CLASSVECTOR_H

#include <string.h>
#include <iostream>
#define MIN_MEMORY_SIZE 200

using namespace std;

namespace my
{
    class vector;
}

template <class UsingType>
class my::vector
{
private:
    unsigned int MemorySize;
    unsigned int VectorSize;
    void* Pointer;
    /*тип*/ MemoryGrow() //довыделение памяти
    {
        void* BufPointer;
        try{
            BufPointer = (void*) new char[MemorySize * 2];
        }
        catch(...){
            cerr << "Memory allocate error" << endl;
//            return 1;
        }
        int SizeType = sizeof(UsingType);
        for (int i = 0; i < VectorSize; i++){
            new ((char*)Pointer + i * SizeType) UsingType();
            this[i] = h[i];
//        Pointer = BufPointer;
//        MemorySize = MemorySize * 2;
    }
public:
    explicit vector(): VectorSize(0), MemorySize(MIN_MEMORY_SIZE)
    {
        Pointer = (void*) new char[MemorySize * sizeof(UsingType)];
    }
    explicit vector(unsigned int _MemorySize): VectorSize(0), MemorySize(_MemorySize)
    {
        Pointer = (void*) new char[MemorySize * sizeof(UsingType)];
    }
    explicit vector(my::vector const & _vector): VectorSize(_vector.VectorSize), MemorySize(_vector.MemorySize)
    {
        Pointer = (void*) new char[MemorySize * sizeof(UsingType)];
        int SizeType = sizeof(UsingType);
        for (int i = 0; i < VectorSize; i++){
            new ((char*)Pointer + i * SizeType) UsingType();
            this[i] = _vector[i];
        }
    }
    ~vector();
    void operator=(MyVector const &);
    Point const & operator[](int) const;
    Point & operator[](int);
    void PushBack(Point);
    int GetSize();
};

#endif // CLASSVECTOR_H
