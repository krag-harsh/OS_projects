#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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


    for(int i=0;i<argc;i++)
    {
        int i=remove(argv[i]);
        if(i!=0)
        printf("unable to delete file %s",argv[i]);
    }

    if(remove("har")!=0)
    {
        printf("\nunable to delete");
    }
    return 0;
}
