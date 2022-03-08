#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BITS_PER_LONG 64
#define GENMASK(h, l) \
    (((~0UL) >> (63 - h)) & ((~0UL) << (l)))

#define LINUX_GENMASK(h, l)        \
    (((~0UL) - (1UL << (l)) + 1) & \
     (~0UL >> (BITS_PER_LONG - 1 - (h))))

int check(int h, int l)
{
    __uint64_t expect = LINUX_GENMASK(h, l);
    __uint64_t result = GENMASK(h, l);
    int r = expect == result;
    if (!r)
    {
        printf("%lX != %lX\r\n", result, expect);
    }
    else
    {
        // printf("%lX == %lX\r\n", result, expect);
    }
    return r;
}
int main()
{
    srand(time(NULL));
    int tests = 100000;
    int ok = 1;
    while (tests--)
    {
        ok = check(rand() % 64, rand() % 64) & ok;
    }
    if (ok)
    {
        printf("Passed\r\n");
    }
}