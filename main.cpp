#include "classVector.h"
#include <iostream>

int main()
{
    my::vector<int> k;
    my::vector<int> l(100);
    my::vector<int> v(k);
    my::vector<double> r;
    l = v;
    for (int i = 0; i < 10000; i++)
        k[i] = i;
    l = k;
    for (int i = 0; i < 10; i++)
        cout << l[i] << endl;
    return 0;
}
