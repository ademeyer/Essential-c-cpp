#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char* a, char* b)
{
	char* temp = a;
	a = b;
	b = temp;
}

void reverse(char* start, char* nxt, int i_start, int i_nxt)
{
	while(i_start < i_nxt)
	{
		swap(start, nxt);
		++i_start;
		--i_nxt;
	}
}

int next_permutation(int n, char **s)
{
	
	// Find the largest index k such that s[k] < s[k+1]
    int k = -1;
    for (int i = 0; i < n - 1; i++) {
        if (strcmp(s[i], s[i+1]) < 0) {
            k = i;
        }
    }
    if (k == -1) {
        return 0; // No more permutations
    }

    // Find the largest index l greater than k such that s[k] < s[l]
    int l = -1;
    for (int i = k + 1; i < n; i++) {
        if (strcmp(s[k], s[i]) < 0) {
            l = i;
        }
    }

    // Swap s[k] and s[l]
    char *temp = s[k];
    s[k] = s[l];
    s[l] = temp;

    // Reverse the sequence from k+1 to n-1
    int left = k + 1;
    int right = n - 1;
    while (left < right) {
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }

    return 1;
}

int main()
{
	char *s[] = {"ab", "bc", "cd"};
	int n = 3;
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	return 0;
}
