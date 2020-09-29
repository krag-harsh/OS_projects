#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
// #include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct dirent *f;
	DIR *d;
    // struct  stat stats;
    char arr[1000];
    char pwd[1024];
    getcwd(pwd,1024);
    d = opendir(pwd);

    // printf("We are in ls.c\n");
    if(argc==2)
    {
        if(strcmp(argv[1],"-1")==0)
        {
            while((f = readdir(d)) !=NULL)
            {
                printf(" %s\n",f->d_name );
            }
            closedir(d);
            printf("\n");
            
        }

        else if(strcmp(argv[1],"-i")==0)
        {

            while((f = readdir(d)) !=NULL)
            {

                printf(" %ld %s \t\t",f->d_ino,f->d_name );     //inode number
            }
            closedir(d);
            printf("\n");

        }
    }
    else if(argc==1)
    {

        while((f = readdir(d)) !=NULL)
        {
            // sprintf(arr,"%s/%s",pwd,f->d_name);
		    // stat(arr,&stats);
  
            printf(" %s ",f->d_name );
        }
        closedir(d);
        printf("\n");
        
    }
   // system("dir");
  
    return 0;
}
