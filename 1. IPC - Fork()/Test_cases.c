#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
 
int main(void) {
  for(int i = 1; i <= 3; i++) {
    pid_t pid = fork();
 
    if(pid == 0) {
      printf("Child process => PPID=%d, PID=%d\n", getppid(), getpid());
      exit(0);
    }
    else
      printf("Parent process => PID=%d\n", getpid());}
}
