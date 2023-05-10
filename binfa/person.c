#include "thread.h"

#define A 1
#define B 2


atomic_int nested;
atomic_long count;

void criticial_section()
{
    //     long cnt = atomic_fetch_add(&count, 1);
    //     assert(atomic_fetch_add(&nested, 1) == 0);
    //     atomic_fetch_add(&nested, -1);
    // sum++;
    // printf("sum = %d\n", sum);
    ;
}

int volatile x = 0, y = 0, turn = A;

void TA()
{
    while (1)
    {
        x = 1;
        turn = B;
        while (y && turn == B)
            ;
        criticial_section();
        
        printf("sum = 1\n");
        x = 0;
    }
}

void TB()
{
    while (1)
    {
        x = 1;
        turn = A;
        while (y && turn == A)
            ;
        criticial_section();
        
        printf("sum = 0\n");
        
        x = 0;
    }
}

int main()
{

    create(TA);
    create(TB);
    join();
    printf("sum = %d\n");
    return 0;
}

