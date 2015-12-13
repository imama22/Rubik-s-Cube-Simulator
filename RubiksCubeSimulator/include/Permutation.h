#ifndef PERMUTATION_H
#define PERMUTATION_H


class Permutation
{
    public:
        Permutation();
        virtual ~Permutation();
        static void MulPermute(int* _old, int* _new, int n, int m);
    protected:
    private:
        static void Permute(int* _old, int* _new, int n);
};

#endif // PERMUTATION_H

