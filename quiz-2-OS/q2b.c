// C Program for Message Queue (Writer Process) 
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>
#include <stdlib.h>


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
	message.mesg_type = 1; 


   FILE *fp = fopen("para2.txt","r");
   char chbuf[100];
   while(fscanf(fp, "%s", chbuf) != EOF )
   {
      strcpy(message.mesg_text,chbuf);
      int len = strlen(message.mesg_text);

      msgsnd(msgid, &message, sizeof(message), 0); 
	   printf("Data send is : %s \n", message.mesg_text); 
   }
   
   strcpy(message.mesg_text,"\n\n");
   msgsnd(msgid, &message, sizeof(message), 0); 
   printf("Data send is : %s \n", message.mesg_text);

	return 0; 
} 


