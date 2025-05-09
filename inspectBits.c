#include <stdlib.h>
#include <stdio.h>

int inspect_bits(unsigned int number)
{
	int  count = 0; // 1011
	for(int i = 31; i >= 0;  --i)
	{
		if(!number & (1 << i))
		{
			count = 0;
			continue;
		}
		++count;
		if(count >= 2) return 1;
	}
    	return 0;
}

#ifndef RunTests
int main ()
{
    printf("%d", inspect_bits(13));
}
#endif
