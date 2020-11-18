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


   FILE *fp = fopen("para1.txt","r");
   char chbuf[100];

   // char ch;
   // while((ch = fgetc(fp)) != EOF)
   // {
   //    strcpy(message.mesg_text,chbuf);
   //    int len = strlen(message.mesg_text);

   //    msgsnd(msgid, &message, sizeof(message), 0); 
	//    printf("Data send is : %s \n", message.mesg_text); 
   // }

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



// /* Filename: msgq_send.c */
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <errno.h>
// #include <sys/types.h>
// #include <sys/ipc.h>
// #include <sys/msg.h> 

// #define PERMS 0644
// struct my_msgbuf {
//    long mtype;
//    char mtext[200];
// }; 

// int main(void) {
//    struct my_msgbuf buf;
//    int msqid;
//    int len;
//    key_t key;
//    system("touch msgq.txt");
   
//    if ((key = ftok("msgq.txt", 'B')) == -1) {
//       perror("ftok");
//       exit(1);
//    }
   
//    if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
//       perror("msgget");
//       exit(1);
//    }
//    printf("lets try this");
//    // printf("message queue: ready to send messages.\n");
//    printf("Enter ^D to start:\n");
//    buf.mtype = 1; /* we don't really care in this case */

//    while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL)
//    {
//       printf("");
//    }

   
//    // while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
//       // len = strlen(buf.mtext);
//       // /* remove newline at end, if it exists */
//       // if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
//       // if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
//       // perror("msgsnd");
//    // }

//    FILE* stream = fopen("para1.txt", "r");
//    char line[500];
//    while (fgets(line, 500, stream))
//    {
//       char* tmp = strdup(line);
//       char *token = strtok(tmp," "); 
//       while (token != NULL) 
//       {
//          strcpy(buf.mtext,token);
//          len = strlen(buf.mtext);
//          // printf("%s %d",buf.mtext,len);
//          /* remove newline at end, if it exists */
//          if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
//          if(strlen(buf.mtext)<1)
//          {
//             token = strtok(NULL, " ");
//             continue;
//          }

//          // sleep(1);

//          if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
//          perror("msgsnd");
//          printf("%s ",buf.mtext);
//          token = strtok(NULL, " ");
//       } 
//       free(tmp);
//    }

   // FILE *fp = fopen("para1.txt","r");
   // char chbuf[100];
   // while(fscanf(fp, "%s", chbuf) != EOF )
   // {
   //    strcpy(buf.mtext,chbuf);
   //    len = strlen(buf.mtext);
   //    //if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
   //    if(len<1)
   //    continue;

   //    if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
   //    perror("msgsnd");
   //    printf("%s %ld\n", &chbuf,strlen(chbuf));
   // }



//    strcpy(buf.mtext, "end");
//    len = strlen(buf.mtext);
//    if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
//    perror("msgsnd");
   
//    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
//       perror("msgctl");
//       exit(1);
//    }

//    // while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL)
//    // {
//    //    printf("");
//    // }

//    printf("message queue: done sending messages.\n");
//    return 0;
// }