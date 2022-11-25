#include <cstdio>

void print_bin(int n);

void print_bin(int n) {
    int l = sizeof(n) * 8;  //總位數。
    int i;
    if (n == 0) {
        putchar('0');
        return;
    }
    for (i = l - 1; i >= 0; i--)  //略去高位0.
    {
        if (n & (1 << i)) break;
    }

    for (; i >= 0; i--)
        putchar(((n & (1 << i)) != 0) + '0');
}