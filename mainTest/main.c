#include <stdio.h>


typedef struct data
{
    int index;
    int value;
}data_t;

int min_pieces(int* original, int* desired, int length)
{
    int count = 0;
    const int id = length;
    
    data_t valIdx1 [id];
    data_t valIdx2 [id];
    
    for(int i = 0; i < length; ++i)
    {
        data_t t1 = {i , original[i]};
        data_t t2 = {i , desired[i]};
        valIdx1[i] = t1;
        valIdx2[i] = t2;
    }

    for(int i = 0; i < length; ++i)
    {
        data_t t1 = valIdx1[i];
        data_t t2 = valIdx2[i];
        if(t1.index != t2.index && t1.value != t2.value)
        ++count;
    }
    // {1, 4, 3, 2} - original
    // {1, 2, 4, 3} - desired
    // {0, 1}, {1, 4} {2, 3} {3, 2}
    // {0, 1}, {1, 2} {2, 4} {3, 3}

    return count;
}

#ifndef RunTests
int main()
{
    int original[] = {1, 4, 3, 2};
    int desired[] = {1, 2, 4, 3};
    printf("%d\n", min_pieces(original, desired, 4));

    return 0;
}
#endif