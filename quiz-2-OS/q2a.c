/* Filename: msgq_send.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h> 

#define PERMS 0644
struct my_msgbuf {
   long mtype;
   char mtext[200];
};

int main(void) {
   struct my_msgbuf buf;
   int msqid;
   int len;
   key_t key;
   system("touch msgq.txt");
   
   if ((key = ftok("msgq.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }
   
   if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
      perror("msgget");
      exit(1);
   }
   printf("lets try this");
   // printf("message queue: ready to send messages.\n");
   printf("Enter lines of text, ^D to quit:\n");
   buf.mtype = 1; /* we don't really care in this case */
   
   // while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
      // len = strlen(buf.mtext);
      // /* remove newline at end, if it exists */
      // if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
      // if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
      // perror("msgsnd");
   // }
   while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL)
   {
      printf("");
   }

   FILE* stream = fopen("para1.txt", "r");
   char line[500];
   //printf("Average marks of each student of section A :\n");
   // char che[2];
   // strcpy(che,"A");
   // char *backup;
   while (fgets(line, 500, stream))
   {
      char* tmp = strdup(line);
      char *token = strtok(tmp," "); 
      while (token != NULL) 
      {
         strcpy(buf.mtext,token);
         len = strlen(buf.mtext);
         // printf("%s %d",buf.mtext,len);
         /* remove newline at end, if it exists */
         if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
         // if (buf.mtext[len-1] == '\n')
         // {
         //    buf.mtext[len-1] = '\0';
         //    //len--;
         // }

         // printf("%s %d",buf.mtext,len);
         if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
         perror("msgsnd");
         printf("%s ",buf.mtext);

         token = strtok(NULL, " ");

         // int ret=strcmp(che,token);
         // if(ret==0)
         // {
         //    token = strtok(NULL, " ");
         //    int sum=0;
         //    for(int i=0;i<3;i++)
         //    {
         //       int marks= atoi(token);
         //       sum+=marks;
         //       token = strtok(NULL, " ");
         //    }
         //    int m=atoi(token);
         //    sum+=m;
         //    float f=sum/4.0f;
         //    printf("Student ID: %s Average marks = %.2f\n",backup,f);
         // }
         // else{
         //    backup=token;
         //    token = strtok(NULL, " "); 
         // }	
      } 
      free(tmp);
   }



   strcpy(buf.mtext, "end");
   len = strlen(buf.mtext);
   if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
   perror("msgsnd");
   
   if (msgctl(msqid, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
   }

   // while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL)
   // {
   //    printf("");
   // }

   printf("message queue: done sending messages.\n");
   return 0;
}