#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

int getPValue(const triangle t)
{
	return (t.a + t.b + t.c);
}

int cmp(const void* a, const void* b)
{
	triangle aV = *(const triangle*)a;
	triangle bV = *(const triangle*)b;
	return getPValue(aV) - getPValue(bV);
}

void sort_by_area(triangle* tr, int n) 
{
	qsort(tr, n, sizeof(triangle), cmp);
}

int main()
{
	int n = 3;
	triangle tr[] = {
		{.a = 7, .b = 24, .c = 25},
		{.a = 5, .b = 12, .c = 13},
		{.a = 3, .b = 4, .c = 5},
	};
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}
