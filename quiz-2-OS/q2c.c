// C Program for Message Queue (Reader Process) 
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>

// structure for message queue 
struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[100]; 
} message; 

int main() 
{ 
	key_t key; 
	int msgid; 

	// ftok to generate unique key 
	key = ftok("progfile", 65); 

	// msgget creates a message queue 
	// and returns identifier 
	msgid = msgget(key, 0666 | IPC_CREAT); 
   int toend;

	while(1)
   {
      // msgrcv to receive message 
      msgrcv(msgid, &message, sizeof(message), 1, IPC_NOWAIT); 

      // display the message 
      printf("%s ",message.mesg_text); 

      toend = strcmp(message.mesg_text,"\n\n");
      if (toend == 0)
      break;

      // toend = strcmp(message.mesg_text,"end");
      // if (toend == 0)
      // break;

   }

	// to destroy the message queue 
	//msgctl(msgid, IPC_RMID, NULL); 

	return 0; 
} 
