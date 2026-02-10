#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_WINDOW_SIZE 5
typedef struct
{
  int32_t history[MAX_WINDOW_SIZE];
  int64_t running_sum;
  size_t index;
  size_t count;
} moving_average_t;

void mv_init(moving_average_t *mv)
{
  if (mv == NULL)
    return;
  mv->running_sum = 0;
  mv->index = 0;
  mv->count = 0;
}

int32_t mv_average_update(moving_average_t *mv, int16_t sample)
{
  if (mv == NULL)
    return 0;

  int32_t sample_q16 = (int32_t)sample << 16;

  if (mv->count == MAX_WINDOW_SIZE)
    mv->running_sum -= mv->history[mv->index];
  else
    ++mv->count;

  mv->history[mv->index] = sample_q16;
  mv->running_sum += sample_q16;

  mv->index = (mv->index + 1) % MAX_WINDOW_SIZE;
  return (int32_t)mv->running_sum / mv->count;
}

int main()
{
  {
    const uint16_t samples[] = {223, 567, 123, 324, 908, 809, 503, 222, 112, 242, 586, 675, 900};
    const size_t sample_size = sizeof(samples) / sizeof(samples[0]);

    moving_average_t mv;
    mv_init(&mv);

    for (size_t i = 0; i < sample_size; ++i)
    {
      int32_t avg = mv_average_update(&mv, samples[i]);
      printf("current average %d: int32_t: %d, float: %.2f\n", i, avg, (float)avg);
    }
  }

  {
    const uint16_t samples[] = {7223, 8567, 5623, 6324, 9008, 1809, 5403, 2122, 7112, 9242, 4586, 8675, 4900};
    const size_t sample_size = sizeof(samples) / sizeof(samples[0]);

    moving_average_t mv;
    mv_init(&mv);

    for (size_t i = 0; i < sample_size; ++i)
    {
      int32_t avg = mv_average_update(&mv, samples[i]);
      printf("current average %d: int32_t: %d, float: %.2f\n", i, avg, (float)avg);
    }
  }

  return 0;
}