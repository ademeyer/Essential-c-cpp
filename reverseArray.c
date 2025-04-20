#include <stdio.h>

void reverseArray(int* arr, int n)
{
	int r = n - 1;
	int l = 0;
	while (l < r)
	{
		int temp = arr[l];
		arr[l] = arr[r];
		arr[r] = temp;
		++l;
		--r;
	}
}

int main()
{
	int arr[] = {1,2,4,5,6,7,8,8};
	int n = sizeof(arr) / sizeof(arr[0]);
	reverseArray(arr, n);
	for(int i = 0; i < n; ++i)
		printf("%d, ", arr[i]);
	printf("\n");
	return 0;	
}
