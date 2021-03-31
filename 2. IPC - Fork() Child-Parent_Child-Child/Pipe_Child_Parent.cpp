using namespace std;
#include <iostream>
#include <stdio.h>
#include <unistd.h>

int main()
{
        int flag, process_id, pipefds[2];
        char data[20];

	/* Create the pipe and return 2 file descriptors in the pipefds array */
	/* This operation is done before the fork so that both processes will */
	/* know about the same pipe, which will allow them to communicate.  */
        flag = pipe(pipefds); 
	if (flag == -1)
	{
		perror("Unsuccessful Communication");
		exit(1);
	}

	/* Create child process as both processes continue from here */
        process_id = fork();
        if (process_id == -1)           
	{
		perror("Unsuccessful Communication");
		exit(2);
	}
        else if (process_id == 0)           /* child : sends message to parent*/
	{
		/* Closing read()/parent end */
		/* Performing write() by child */
		close(pipefds[0]);

		/* send 39 characters in the string, including end-of-string */
		cout << "Sending Message .... \n" << endl;
		cout<<"Data placed into the pipe successfully \n";
                write(pipefds[1], "Child-parent Communicated Successfully", 39);  

		close(pipefds[1]);
		exit(0);
	}
        else		/* parent : receives message from child */
	{
		/* Closing write() end*/
		/* We need to perform read () at the right/read() side by the parent */
		close(pipefds[1]);

		/* Reading data from the pipe by the parent */
                read(pipefds[0], data, 39);
		cout << "\nReceived Message: " << data << endl;

		close(pipefds[0]);
		exit(0);
	}
}
