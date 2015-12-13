#include "Permutation.h"

Permutation::Permutation()
{
    //ctor
}

Permutation::~Permutation()
{
    //dtor
}

void Permutation::MulPermute(int* _old, int* _new, int n, int m)
{
    for (int i = 0; i < m; ++i)
    {
        Permute(_old, _new + i * n, n);
    }
}

void Permutation::Permute(int* _old, int* _new, int n)
{
    int temp = _old[_new[n - 1]];
    for (int i = n - 1; i > 0; --i)
        _old[_new[i]] = _old[_new[i - 1]];
    _old[_new[0]] = temp;
}
