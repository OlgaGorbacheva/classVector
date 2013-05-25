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
        cout << k[i];
    k[0] = true;
    k[2] = false;
    cout << endl;
    for (int i = 0; i < k.GetSize(); i++)
        cout << k[i];
    return 0;
}
