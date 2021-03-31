#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<wait.h>
int main(void)
{
        pid_t pid;
        int r;
        char buf[1024];
        char cp[70];
        char ans;
        int readpipe[2];
        int writepipe[2];
        long int a;
        int b;
        a=pipe(readpipe);
        b=pipe(writepipe);

        if (a == -1) { perror("pipe"); exit(EXIT_FAILURE); }
        if (b == -1) { perror("pipe"); exit(EXIT_FAILURE); }
        printf("\nTwo-way Parent-Child process communication \t");
        printf("\nEnter [Y] to send or [S] to stop: \t");
        scanf("%[^\n]%*c",&ans);
        fflush(stdin);
        pid=fork();
        if(pid==-1)
        {
                printf("pid:main");
                exit(1);
        }
        while(ans=='y' || ans=='Y')
        {
                if(pid==0)
                { 
                //CHILD PROCESS
                         if(ans=='n'||ans=='N'||ans=='S'||ans=='s')
                        {
                                //a=getpid();
                                //printf("\nPARENT PROCESS a=%ld",a);
                                kill(pid,SIGKILL);
                        }

                        close(readpipe[1]);
                        close(writepipe[0]);
                        if(read(readpipe[0],buf,sizeof(buf)) < 0)
                        {
                            break;
                        }
                        printf("\nChild Process Read from Parent: %s\n",buf);
                        printf("\n(CHILD)Enter data: \t");
                        fflush(stdin);
                        fgets(cp, 50, stdin);
                        printf("\nData Written to Parent: %s",cp);
                        if(/*!strncmp("Q",cp,1) || */write(writepipe[1],cp,strlen(cp)+1) < 0)
                        {
                            break;
                        }

                }
                else
                {
                        close(readpipe[0]);
                        close(writepipe[1]);
                        printf("\n(PARENT)Enter data: \t");
                        fgets(cp, 50, stdin);
                        printf("\nData Written to Child: %s",cp);
                        if(/*!strncmp("Q",cp,1) ||*/ write(readpipe[1],cp,strlen(cp)+1) < 0)
                        {
                            break;
                        }        

                        if(read(writepipe[0],buf,sizeof(buf)) < 0)
                        {
                            break;
                        }
                        printf("\nParent Process Read: %s\n",buf);
                        printf("\nTwo-way Parent-Child process communication \t");
                        printf("\nEnter [Y] to send or [S] to stop: \t");
                        fflush(stdin);
                        scanf(" %[^\n]%*c",&ans);
                        if(ans=='n'||ans=='N'||ans=='S'||ans=='s')
                        {
                                kill(pid,SIGKILL);
                        }
                }

        }
        close(readpipe[1]);
        close(writepipe[0]);
        close(readpipe[0]);
        close(writepipe[1]);
        return 0;
}
