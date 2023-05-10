#include "thread.h"

#define N 100000000

#define UNLOCK 0
#define LOCK 1

long sum = 0;

int locked=UNLOCK;

void Tsum(){
    retry:
        if(locked!=UNLOCK){
            goto retry;
        }

    locked=LOCK;

    sum++;

    locked=UNLOCK;

}

int main(){

    create(Tsum);
    create(Tsum);
    create(Tsum);
   
    join();
    printf("sum = %ld\n",sum);
    return 0;
}