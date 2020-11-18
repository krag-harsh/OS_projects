#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>

struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[500]; 
} message; 

int main() 
{ 
	key_t key; 
	int msgid; 

	key = ftok("progfile", 65);  
	msgid = msgget(key, 0666 | IPC_CREAT); 
   	int toend, countoffile=0;

	while(1)
	{
		msgrcv(msgid, &message, sizeof(message), 1, IPC_NOWAIT); 
		if(strcmp(message.mesg_text,"\n\n")!=0)
		printf("%s ",message.mesg_text); 
		int toend = strcmp(message.mesg_text,"\n\n");
		if (toend == 0)
		countoffile++;
		if(countoffile>1)
		break;
	}
	msgctl(msgid, IPC_RMID, NULL); 

	return 0; 
} 
