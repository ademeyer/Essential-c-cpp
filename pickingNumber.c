#include <stdio.h>

/*
 *Given an array of integers, find the longest subarray 
 *where the absolute difference between any two 
 *elements is less than or equal to .
 *Example: a = {1,1,2,2,4,4,5,5,5}
 *There are two subarrays meeting the criterion: {1,1,2,2}  
 *and {4,4,5,5,5}. The maximum length subarray has  elements.
 * */

int longestSubArray(const int* arr, int n)
{
	int l = 0;
	int maxsub = 0;
	for(int i = 1; i < n; ++i)
	{
		if(arr[i] - arr[i - 1] > 1)
		{
			// get maximum sub array
			maxsub = maxsub > l ? maxsub : l;
			l = 0;
		}
		else ++l;
	}

	return 1 + (maxsub > l ? maxsub : l);
}

int main()
{
	const int arr[] = {1,1,2,2,4,4,5,5,5};
	int n = sizeof(arr) / sizeof(arr[0]);

	int r = longestSubArray(arr, n);

	printf("longest subarray len: %d\n", r);

	return 0;
}
