#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_ELEMENT 1
#define MAX_ELEMENT 1000000

int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

int min(int count, ...) {
    va_list args;
    va_start(args, count);
    int min_val = INT_MAX;
    for (int i = 0; i < count; i++) {
        int current = va_arg(args, int);
        if (current < min_val) {
            min_val = current;
        }
    }
    va_end(args);
    return min_val;
}

int max(int count, ...) {
    va_list args;
    va_start(args, count);
    int max_val = INT_MIN;
    for (int i = 0; i < count; i++) {
        int current = va_arg(args, int);
        if (current > max_val) {
            max_val = current;
        }
    }
    va_end(args);
    return max_val;
}
