#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>
#include <stdlib.h>

struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[100]; 
} message; 

int main() 
{ 
	key_t key; 
	int msgid; 
	key = ftok("progfile", 65); 

	msgid = msgget(key, 0666 | IPC_CREAT); 
	message.mesg_type = 1; 

   FILE *fp = fopen("para2.txt","r");
   char chbuf[100];

   while(fscanf(fp, "%s", chbuf) != EOF )
   {
      strcpy(message.mesg_text,chbuf);
      msgsnd(msgid, &message, sizeof(message), 0); 
   }

   strcpy(message.mesg_text,"\n\n");
   msgsnd(msgid, &message, sizeof(message), 0); 
   
	return 0; 
} 

