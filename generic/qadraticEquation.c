#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void find_roots(double a, double b, double c, double *root1, double *root2)
{

	double discriminant = b * b - 4 * a * c;
	if(discriminant > 0)
	{
		*root1 = (-b + sqrt(discriminant)) / (2 * a);
		*root2 = (-b - sqrt(discriminant)) / (2 * a);
	}
	else if(discriminant == 0)
	{
		*root1 = -b / (2 * a);
	       	*root2 = 0;	
	}
	else // complex roots
	{
		// Not implemented
	}
}

#ifndef RunTests
int main()
{
    double root1, root2;
    find_roots(2, 10, 8, &root1, &root2);
    printf("Roots: %f, %f", root1, root2);
}
#endif
