#include <stdio.h>

// size 8
struct twodata {
    long pee;
    long poo;
};

// size 8
struct onedata {
    long pee;
};

struct test {
    union {
        union {
            struct twodata too;
            struct onedata won;
        };
        int pay;
    };
};

int main() {
    struct test t1;
    struct twodata two1;
    printf("Size of test: %ld\n", sizeof(t1));
    printf("Size of twodata: %ld\n", sizeof(two1));
    return 0;
}