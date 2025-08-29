#include <stdio.h>
#include <stdlib.h>

void printPattern(int n)
{
	int nz = 2 * n - 1;

	// generate & print the pattern
	for(int i = 0; i < nz; ++i)
	{
		for(int j = 0; j < nz; ++j)
		{
			int min_d = i < j ? i : j;
			min_d = min_d < nz - i ? min_d : nz - i - 1;
			min_d = min_d < nz - j ? min_d : nz - j - 1;
			printf("%d\t", (n - min_d));
		}
		printf("\n");
	}
	printf("\n");

}

int main()
{
	int n;
	scanf("%d", &n);
	printPattern(n);
}
