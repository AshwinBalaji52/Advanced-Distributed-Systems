// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
  
int main()
{
    int fileDescriptor1;
    printf("\t\t\t\t\t\n SERVER NODE \n");
    // FIFO file path
    char * fifoBuffer = "/tmp/fifoBuffer";
  
    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(fifoBuffer, 0666);
  
    char buffer3[100], buffer4[100];
    while (1)
    {
        // First open in read only and read
        fileDescriptor1 = open(fifoBuffer,O_RDONLY);
        int check3 = strcmp(buffer3, "STOP");
        int check4 =  strcmp(buffer3, "stop");
        int check5 = strcmp(buffer3, "Stop");
        if (check3 == 1 || check4 == 1 || check5 == 1)
            {
                printf("Aborting Process .... Stop received");
                exit(0);
            }
        read(fileDescriptor1, buffer3, 100);
  
        // Print the read string and close
        printf("Server Received : %s\n", buffer3);
        close(fileDescriptor1);
  
        // Now open in write mode and write
        // string taken from user.
        fileDescriptor1 = open(fifoBuffer,O_WRONLY);

	printf("Write in Buffer : ");
        fgets(buffer4, 100, stdin);
        write(fileDescriptor1, buffer4, strlen(buffer4)+1);
        close(fileDescriptor1);
    }
    return 0;
}