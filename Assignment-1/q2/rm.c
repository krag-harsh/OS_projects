#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    // printf("We are in rm.c\n");
    // printf("PID of try.c = %d\n", getpid());
    // int i=0;
    // printf("value of int argc passed= %d \n",argc);
    // for(i=0;i<argc;i++)
    // {
    //     printf("%s\n",argv[i]);
    // }


    // for(int i=1;i<argc;i++)
    // {
    //     int i=remove(argv[i]);
    //     if(i!=0)
    //     printf("unable to delete file %s",argv[i]);
    // }

    // if(remove("harsh")!=0)
    // {
    //     printf("\nunable to delete\n");
    // }

    if(argc==3)
    {
        if(strcmp(argv[1],"-v")==0)
        {
            int status = remove(argv[2]);
            if(status==0)
                printf("deleted %s \n",argv[2]);
            else
                printf("File doesn't exist\n");
        }
        else if(strcmp(argv[1],"-i")==0)
        {
            printf("Do you want to delete the file %s? y/n : " ,argv[2]);
            char *i;
            i = (char*)malloc(sizeof(char*)*2);
            fgets(i,2,stdin);
            if(*i=='y')
            {
                remove(argv[2]);
            }	
            free(i);
        }
    }
    else if(argc==2)
    {
        remove(argv[1]);
    }

    return 0;
}
