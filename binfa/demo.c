#include "thread.h"

int x;

void Thell0(int id)
{
    printf("Thread id: %d\n", id);
    usleep(id * 100000);
    printf("Hello from thread #%c\n", "123456789ABCDEF"[x++]);
}

int main()
{
    for (int i = 0; i < 10; ++i)
    {
        create(Thell0);
    }
}