#include <stdlib.h>
#include <stdio.h>

int lenofstring(const char* str)
{
	int i = 0;
	while(str[i] != '\0') ++i;
	return i;
}

void traverse1DArr(const int* arr, int N, int M)
{
	for(int i = 0; i < (N*M); ++i)
		printf("%d ", *(arr+i));
	printf("\n");
}

void traverse2DArr(const int* arr, int N, int M)
{
	for(int i = 0; i < N; ++i)
	{
		for(int j = 0; j < M; ++j)
			printf("%d\t", *(arr + i * M) + j);
		printf("\n");
	}
	printf("\n");
}

int main(int argv, char* argc[])
{
	int a[] = {1, 6, 8, 9};
	void* ptr = a;
	int n = sizeof(a) / sizeof(a[0]);
	int  i = 0;
	while(i < n)
	{
		printf("a[%d]: %d\n", i, *((int*)(ptr)+i));
		++i;
	}
	
	// Testing with char string
	const char* const str = "Hello world";
	const char* s = str;
	while(*s != '\0')
	{
		printf("%c", *s);
		++s;
	}
	printf("\nstrlen = %d\n", lenofstring(str));

	// Traverse 2D array with pointer
	const int N = 7, M = 5;
	int arr[N][M]; 
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < M; ++j)
			arr[i][j] = i*M + j;
	traverse2DArr((const int*)arr, N, M);
	traverse1DArr((const int*)arr, N, M);
	
	// Test dynamic memory allocation in c
	int* aptr = (int*)malloc(N * M * sizeof(int));
	if(!aptr)
	{
		printf("Unable to allocate memory\n");
		return 1;
	}

	for(int i = 0; i < N*M; ++i)
		*(aptr+i) = i;
	
	*aptr = -1;
	traverse2DArr((const int*)aptr, N, M);
	traverse1DArr((const int*)aptr, N, M);
	// free memory
	free(aptr);

	return 0;
}


