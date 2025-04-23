#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
    int index;
    int value;
}data_t;

int cmp(const void* a, const void* b)
{
    	const data_t* int_a = (const data_t*)a;
    	const data_t* int_b = (const data_t*)b;
    
    	// Safe comparison that avoids overflow
    	if (int_a->value < int_b->value) return -1;
    	if (int_a->value > int_b->value) return 1;
    	return 0;
}

int min_pieces(int* original, int* desired, int length)
{
    	const int id = length;   
    	data_t valIdx1 [id];
    	data_t valIdx2 [id];
    	
	// Bind array's value with index.
    	for(int i = 0; i < length; ++i)
    	{
        	data_t t1 = {i , original[i]};
        	data_t t2 = {i , desired[i]};
        	valIdx1[i] = t1;
        	valIdx2[i] = t2;
    	}
        
    	// Sort valIdx1 and valIdx2 using .value
    	qsort(&valIdx1, length, sizeof(data_t), cmp);
    	qsort(&valIdx2, length, sizeof(data_t), cmp);
    	
	// Allocate space for tracking diff of sorted valIdx1[&2]
    	int* set = malloc(sizeof(int) * length);
    	int idx = 0;
	
	// Get diff in sorted valIdxs' indexes
	for(int i = 0; i < length; ++i)
	{
		data_t dt1 = valIdx1[i];
		data_t dt2 = valIdx2[i];
		int diff = dt1.index - dt2.index;
		if(idx > 0 && set[idx - 1] == diff)
			continue;
		else
			set[idx++] = diff;
	}
    	
	// Free allocations
	free(set);

    	return idx;
}

#ifndef RunTests
int main()
{
    int original1[] = {1, 4, 3, 2};
    int desired1[] = {1, 2, 4, 3};
    printf("%d\n", min_pieces(original1, desired1, 4));

    int original2[] = {1, 4, 3, 2, 9, 8};
    int desired2[] = {8, 1, 9, 4, 3, 2};
    printf("%d\n", min_pieces(original2, desired2, 6));

    int original3[] = {1, 4, 3, 2, 9, 8};
    int desired3[] = {8, 1, 9, 3, 4, 2};
    printf("%d\n", min_pieces(original3, desired3, 6));

    return 0;
}
#endif
