#include <iostream>
using namespace std;
#include <stdio.h>
#include <unistd.h>
int main()
{
    int flag, process_id1, process_id2, pipefds[2];
    char data[30]="Siblings Communicated";
    flag = pipe(pipefds); 
    if (flag == -1)
	{
		perror("Unsuccessful Communication");
		exit(1);
	}
	process_id1 = fork();
    process_id2 = fork();
    int ppid=getppid();
	if ((process_id1>1) and (process_id2>1))
	{
	   cout<<"Successful Execution of processess"<<endl;
	   cout<<process_id1<<endl;
	   cout<<process_id2<<endl;
	}
    else if ((process_id1 == 0) and (process_id2 > 1))    /* child1 write() to child2 read()*/
    {
		close(pipefds[0]);
		cout << "\nSending Message from Child 1 to Child 2 .... " << endl;
		cout<<"Parent process w.r.t Child 1: "<<ppid<<endl;
		cout<<"Child 1 Process: "<<process_id1<<endl;
		cout<<"Data placed into the pipe successfully and sending to child 2"<<endl;
		        write(pipefds[1], data, 22);  
		close(pipefds[1]);
		//open(pipefds[0]);
                read(pipefds[0], data, 22);
		cout << "Received Message at Child 2: "<<data<<endl;
		close(pipefds[0]);
		//exit(0);
	}
	else if ((process_id2 == 0) and (process_id1 > 1))    /* child1 write() to child2 read()*/
	{
		close(pipefds[0]);
		cout << "\nSending Message from Child 2 to Child 1 ...." <<endl;
		cout<<"Parent process w.r.t Child 2: "<<ppid<<endl;
		cout<<"Child 2 Process: "<<process_id1<<endl;
		cout<<"Data placed into the pipe successfully and sending to child 1 \n";
	        	write(pipefds[1], data,22);  
		close(pipefds[1]);
		/* Reading data from the pipe by the parent */
		//open(pipefds[1])
             read(pipefds[0], data, 22);
		cout << "Received Message at child 1: "<<data<<endl;
		close(pipefds[0]);
		//exit(0);
	}
}
