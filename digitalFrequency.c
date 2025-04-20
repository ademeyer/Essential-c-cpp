#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isDigit(const char c)
{
	return c >= 48 && c <= 57;
}

void digitalFreq(const char* s, int n, char* result)
{
	if(result == NULL || s == NULL || n == 0) return;
	int* arr = malloc(sizeof(int) * 10);
	memset(arr, 0, sizeof(int) * 10);
	for(int i = 0; i < n; ++i)
	{
		char c = s[i];
		if(!isDigit(c)) continue;
		arr[c - 48]++;
	}

	for(int i = 0; i < 10; ++i)
		result[i] = (char)(arr[i] + 48);
	free(arr);
}



int main()
{
	char* r = malloc(sizeof(char) * 10);
	digitalFreq("a11472o5t6", 10, r); 
	printf("%s\n", r);
	memset(r, 0, sizeof(char) * 10);

	digitalFreq("lw4n88j12n1", 11, r);
        printf("%s\n", r);
	memset(r, 0, sizeof(char) * 10);

	digitalFreq("1v88886l256338ar0ekk", 20, r);
        printf("%s\n", r);
	memset(r, 0, sizeof(char) * 10);

        if(r)
               free(r);
        r = NULL;

	return 0;
}
