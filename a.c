#include <unistd.h>

int main(){

int pid = fork();
printf("%d\n",pid);
// 在父进程中，fork返回子类的PID；在子进程中，fork返回零。

if(pid > 0) {
    printf("parent: child=%d\n", pid);
    pid = wait((int *) 0);
    printf("child %d is done\n", pid);
} else if(pid == 0) {
    printf("child: exiting\n");
    exit(0);
} else {
    printf("fork error\n");
}
}