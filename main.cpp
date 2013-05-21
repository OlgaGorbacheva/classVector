#include "classVector.h"
#include <iostream>

int main()
{
    my::vector<bool> k;
    k.PushBack(false);
    k.PushBack(false);
    k.PushBack(true);
    k.PushBack(false);
    k.PushBack(false);
    k.PushBack(true);
    k.PushBack(false);
    k.PushBack(false);
    k.PushBack(true);
    k.PushBack(false);
    k.PushBack(false);
    k.PushBack(true);
    cout << endl;
    for (int i = 0; i < k.GetSize(); i++)
        cout << k[i] << endl;
    return 0;
}
