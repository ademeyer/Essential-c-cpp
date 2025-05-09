#include <stdio.h>
#include <stdint.h>
#include <string.h>

void PrintBin(const size_t number, int nBits)
{
	for(int i = nBits * 8; i >= 0; --i)
	{
		if(number & (1 << i))
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}

// Odd element is an element of array that occured just once
int findOddElement(const int* arr, int n)
{
	int res = 0;
	for(int i = 0; i < n; ++i)
		res ^= arr[i];
	return res;
}

int findMissingNumber(const int* arr, int n)
{
	n = n + 1;
	int xor1 = 0, xor2 = 0;
	for(int i = 0; i < n - 1; ++i)
		xor2 ^= arr[i];
	for(int i = 1; i <= n; ++i)
		xor1 ^= i;
	return xor1 ^ xor2;
}

void swapWithXor(void* first, void* second)
{
	uint32_t a = 0, b = 0;
	memcpy(&a, first, sizeof(a));
	memcpy(&b, second, sizeof(b));
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	first = &a;
	second = &b;
}

int bitset(const size_t val, int pos)
{
	return val | 1 << pos;
}

int bitclear(const size_t val, int pos)
{
	return val & (~(1 << pos));
}

int bittoggle(const size_t val, int pos)
{
	return val ^ (1 << pos);
}

int main(int argv, char* argc[])
{
	// numbers
	uint8_t i_8 = 0b01001100;
	uint16_t i_16 = 0b1001110010101001;
	uint32_t i_32 = 0b10011100101010011001110010101001;
	PrintBin(i_8, sizeof(i_8));
	PrintBin(i_16, sizeof(i_16));
	PrintBin(i_32, sizeof(i_32));

	// Use XOR operation to find an odd element
	const int arr[] = {1, 1, 3, 5, 3, 6, 6}; // expect 5
	int n = sizeof(arr) / sizeof(arr[0]);
	int r = findOddElement(arr, n);
	printf("Odd Element: %d\n", r);

	// Bit setting
	uint8_t b = bitset(i_8, 1);
	PrintBin(b, sizeof(b));

	// Bit clearing
	b = bitclear(i_8, 2);
	PrintBin(b, sizeof(b));

	// Bit toggling
	b = bittoggle(i_8, 7) & 0xFF;
	PrintBin(b, sizeof(b));

	// Algorithm using XOR operation
	// Find Missing Number in a sorted array
	const int num[] = {1,2,4,5,6};
	n = sizeof(num) / sizeof(num[0]);
	int mn = findMissingNumber(num, n);
	printf("missing number: %d\n", mn);

	// Swap two characters
	char c1 = 'A', c2 = 'B';
	printf("before swap: c1: %c, c2: %c", c1, c2);
	swapWithXor(&c1, &c2);
	printf(" after swap: c1: %c, c2: %c\n", c1, c2);

	printf("\nEnd of Program\n");
	return 0;
}

