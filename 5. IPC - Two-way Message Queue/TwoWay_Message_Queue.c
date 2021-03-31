#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 128

void quit(char *s)
{
  perror(s);
  exit(1);
}

struct messageBuffer
{
    long    messageType;
    char    messageText[MAXSIZE];
    char    string1[MAXSIZE];
    char    string2[MAXSIZE];
};

main()
{
    int messageID;
    int msgflg = IPC_CREAT | 0666;
    int check;
    key_t key;
    size_t bufferLength;
    struct messageBuffer receiverBuffer;
    struct messageBuffer temp;
    struct messageBuffer senderBuffer;
    key = 1234;

    if ((messageID = msgget(key, msgflg )) < 0)   //Get the message queue ID for the given key
      quit("msgget");

    //Message Type
    senderBuffer.messageType = 1;
    receiverBuffer.messageType = 1;
    
    printf("\n\t\tTWO-WAY IPC : MESSAGE-QUEUE\n");
    
    printf("Message : ");
    scanf("%[^\n]",senderBuffer.messageText);
    getchar();
    
    strcpy(temp.string1, senderBuffer.messageText);
    strcpy(temp.string2, "STOP");
    check = strcmp(temp.string1, temp.string2);
    if(check == 0)
    {
        printf("[STOP] message received... Process Aborted !!!");
        exit(0);
    }

    bufferLength = strlen(senderBuffer.messageText) + 1 ;

    if (msgsnd(messageID, &senderBuffer, bufferLength, IPC_NOWAIT) < 0)
    {
        printf ("%d, %d, %s, %d\n", messageID, senderBuffer.messageType, senderBuffer.messageText, bufferLength);
        quit("msgsnd");
    }

    else
        printf("Message Sent to the server\n");
        
    if ((messageID = msgget(key, 0666)) < 0)
      quit("msgget()");
         //Receive an answer of message type 1.
    if (msgrcv(messageID, &receiverBuffer, MAXSIZE, 1, 0) < 0)
      quit("msgrcv");
    
    printf("Message Received by the server: ");
    printf("%s\n", receiverBuffer.messageText);
    printf("\n");

    //Receiver to sender
    //printf("Enter a message to add to message queue : ");
    //scanf("%[^\n]",receiverBuffer.messageText);
    //getchar();    
    
    bufferLength = strlen(receiverBuffer.messageText) + 1 ;

    if (msgsnd(messageID, &receiverBuffer, bufferLength, IPC_NOWAIT) < 0)
    {
        printf ("%d, %d, %s, %d\n", messageID, receiverBuffer.messageType, receiverBuffer.messageText, bufferLength);
        quit("msgsnd");
    }

    else
        printf("Message Sent to back to the client\n");
        
    if ((messageID = msgget(key, 0666)) < 0)
      quit("msgget()");
         //Receive an answer of message type 1.
    if (msgrcv(messageID, &senderBuffer, MAXSIZE, 1, 0) < 0)
      quit("msgrcv");
    
    printf("Message Received to the client: ");
    
    printf("%s\n", senderBuffer.messageText);
    printf("\n");

    //Receiver to sender
    //printf("Enter a message to add to message queue : ");
    //scanf("%[^\n]",senderBuffer.messageText);
    //getchar();  
    
    exit(0);
}