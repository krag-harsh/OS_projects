#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    printf("We are in cat.c\n");
    printf("PID of try.c = %d\n", getpid());
    int i=0;
    printf("value of int argc passed= %d \n",argc);
    for(i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }
    return 0;
}
