#include <stdio.h>

typedef struct UserInfo
{
    int id;
    char* name;
    char gender;
    long long credit_amount;
    char credit_rating;
    float interest;
    int account_number;
    int years_member;
    short account_type_code;
} UserInfo;


typedef struct UserInfo1
{
    char* name;
    char gender;
    char credit_rating;
    short account_type_code;
    int account_number;
    int years_member;
    int id;
    float interest;
    long long credit_amount;
} UserInfo1;


int main()
{
	printf("size of unaligned struct: %ld byte(s)\n", sizeof(UserInfo));
	
	printf("size of aligned struct: %ld byte(s)\n", sizeof(UserInfo1));
	return 0;
}
