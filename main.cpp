#include "classVector.h"

int main()
{
    my::vector<int> k;
    my::vector<int> l(100);
    my::vector<int> v(k);
    my::vector<double> r;
    l = v;
    return 0;
}
