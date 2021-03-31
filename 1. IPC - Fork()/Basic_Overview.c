#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(void) {
    fork();
    fork();
    printf("1st Fork() Process Executed: PPID=%d and PID=%d\n",getppid(),getpid());
    printf("2nd Fork() Process Executed: PPID=%d and PID=%d\n",getppid(), getpid());
}
