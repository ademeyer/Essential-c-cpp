#include <stdio.h>
#include <stdbool.h>
/**
 * @brief Get the max zero gaps
 * @attention: A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.

              For example, number 9 has binary representation 1001 and contains a binary gap of length 2. The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3. The number 20 has binary representation 10100 and contains one binary gap of length 1. The number 15 has binary representation 1111 and has no binary gaps. The number 32 has binary representation 100000 and has no binary gaps.

              Write a function:

              int solution(int N);

              that, given a positive integer N, returns the length of its longest binary gap. The function should return 0 if N doesn't contain a binary gap.

              For example, given N = 1041 the function should return 5, because N has binary representation 10000010001 and so its longest binary gap is of length 5. Given N = 32 the function should return 0, because N has binary representation '100000' and thus no binary gaps.

              Write an efficient algorithm for the following assumptions:

              N is an integer within the range [1..2,147,483,647].

 * @param N
 * @return int
 */
int get_max(int a, int b)
{
  return a > b ? a : b;
}

int solution(int N)
{
  int maxGap = 0;
  int cur_cnt = 0;
  bool start_count = false;
  for (int i = 0; i < 32; ++i)
  {
    if ((N >> i) & 0x01) /* if we hit bit 1 */
    {
      maxGap = get_max(maxGap, cur_cnt);
      cur_cnt = 0;
      start_count = true;
    }
    else /* It is a bit 0 */
    {
      if (start_count)
        ++cur_cnt;
    }
  }
  return maxGap;
}
/* 1000010000 */
int main()
{
  printf("max zero gaps for (9): %d\n", solution(9));
  printf("max zero gaps for (529): %d\n", solution(529));
  printf("max zero gaps for (20): %d\n", solution(20));
  printf("max zero gaps for (32): %d\n", solution(32));
  printf("max zero gaps for (15): %d\n", solution(15));
  printf("max zero gaps for (1041): %d\n", solution(1041));
  return 0;
}