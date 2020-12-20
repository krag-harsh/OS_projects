#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/file.h>

int main()
{
   int num;
   FILE *fptr;
   FILE *fp1;
   char c;
   char buf[256];

   struct flock fl;
   memset(&fl,0, sizeof(fl));


   //appending
   // fp1=fopen("text","a");
   // printf("\nEnter data to append: ");
   // fflush(stdin);          // To clear extra white space characters in stdin
   // fgets(buf, 256, stdin);
   // fputs(buf,fp1);
   // fclose(fp1);


   //displaying
   fp1=fopen("text","r");
   if(fp1==NULL)
      printf("\n\tFile not found!");
   int t=fileno(fp1);
   fl.l_type =   F_WRLCK;
   fl.l_whence = SEEK_SET; // offset base is start of the file
   fl.l_start = 0;         // starting offset is zero
   fl.l_len = 0;
   if(fcntl(t, F_SETLK, &fl)==-1)
   {
      printf("WARNING:already sommeone else\n");
   }

   
   while(!feof(fp1))
   {
      c=getc(fp1);
      printf("%c",c);
   }
   getchar();

   fl.l_type= F_UNLCK;
   if(fcntl(t, F_SETLK, &fl)==-1)
   {
      perror("fcntl");
      exit(1);
   }

   fclose(fp1);

   return 0;
}