#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countDistinctChars(const char *str)
{
	int chars[26] = {0};
	int cnt = 0;
	while(*str)
	{
		if(chars[*str - 'a'] == 0)
		{
			++cnt;
			chars[*str - 'a'] = 1;
		}
		++str;
	}
	return cnt;
}

int lexicographic_sort(const char* a, const char* b) 
{
	return strcmp(*(const char**)a, *(const char**)b);
}

int lexicographic_sort_reverse(const char* a, const char* b) 
{
	return strcmp(*(const char**)b, *(const char**)a);
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) 
{
    	int a_cnt = countDistinctChars(*(const char**)a);
	int b_cnt = countDistinctChars(*(const char**)b);
	if(a_cnt != b_cnt)
		return a_cnt - b_cnt;
	return lexicographic_sort(a, b); 	
}

int sort_by_length(const char* a, const char* b) 
{
	int a_len = strlen(*(const char**)a);
	int b_len = strlen(*(const char**)b);
	
	if(a_len != b_len)
		return a_len - b_len;
	return lexicographic_sort(a, b);
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
	qsort(arr, len, sizeof(char*), cmp_func);
}


int main() 
{
    int n = 4;
  
    char* arr[] = {"wkue", "qoi", "sbv", "fekls"};
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}
