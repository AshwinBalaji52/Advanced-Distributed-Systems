// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
  
int main()
{
    int fileDescriptor;
    printf("\t\t\t\t\t\n CLIENT NODE \n");
    // FIFO file path
    char * fifoBuffer = "/tmp/fifoBuffer";
  
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(fifoBuffer, 0666);
  
    char buffer1[100], buffer2[100], stopbuffer[10];
    while (1)
    {
        // Open FIFO for write only
        fileDescriptor = open(fifoBuffer, O_WRONLY);
  
        // Take an input buffer2ing from user.
        // 100 is maximum length
        printf("Write in Buffer : ");
        fgets(buffer2, 100, stdin);
        int check = strcmp(buffer2, "STOP");
        int check1 =  strcmp(buffer2, "stop");
        int check2 = strcmp(buffer2, "Stop");
        if (check == 1 || check1 == 1 || check2 == 1)
            {
                printf("Aborting Process .... Stop received");
                exit(0);
            }
  
        // Write the input buffer2ing on FIFO
        // and close it
        write(fileDescriptor, buffer2, strlen(buffer2)+1);
        close(fileDescriptor);
  
        // Open FIFO for Read only
        fileDescriptor = open(fifoBuffer, O_RDONLY);
  
        // Read from FIFO
        read(fileDescriptor, buffer1, sizeof(buffer1));
  
        // Print the read message
        printf("Client Received : %s\n", buffer1);
        close(fileDescriptor);
    }
    return 0;
}