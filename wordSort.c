#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int comp(const void* a, const void* b)
{
	return (strcmp(*(const char**)b, *(const char**)a));
}

void sort_words(char *words[], int count)
{
    	qsort(words, count, sizeof(char*), comp);
}

#ifndef RunTests
int main()
{
    char *words[] = { "cherry", "orange", "apple" };

    sort_words(words, 3);

    for (int i = 0; i < 3; i++)
    {
        printf("%s ", words[i]);
    }
}
#endif
