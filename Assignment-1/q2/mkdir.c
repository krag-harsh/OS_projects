#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // printf("We are in mkdir.c\n");
    // printf("PID of try.c = %d\n", getpid());
    // int i=0;
    // printf("value of int argc passed= %d \n",argc);
    // for(i=0;i<argc;i++)
    // {
    //     printf("%s\n",argv[i]);
    // }

    // if(mkdir("harshfolder",0700)==-1)
    // printf("unable to create folder");

    //system("dir");
    if(argc==3)
    {
        if(strcmp(argv[1],"-v")==0)
        {
            if(mkdir(argv[2],0700)==-1)
            {
                printf("unable to create folder");
            }
            else 
            {
                printf("Foder created %s ",argv[2]);
            }
            
        }
    }
    else if (argc==4)
    {
        if(strcmp(argv[1],"-m")==0)
        {
            mkdir(argv[3],atoi(argv[2]));
        }
    }
    else if(argc==2)
    {
        if(mkdir(argv[1],0700)==-1)
        printf("unable to create folder");
    }
    return 0;
}
