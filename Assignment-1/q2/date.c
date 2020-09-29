#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main(int argc, char *argv[])
{
    // printf("We are in date.c\n");

    time_t n;
    n=time(NULL);
    struct tm *pointer;
    char charr[1000];
    
    if(argc==1)
    {
        time(&n);
        printf("%s",ctime(&n));
    }
    else if(argc ==2)
    {
        if(strcmp(argv[1],"-R")==0)
        {
            pointer = localtime(&n);
            strftime(charr, 1000, "%a , %d %h %Y %T %z", pointer);
            printf("%s\n",charr);
        }

        else if(strcmp(argv[1],"-u")==0)
        {
            pointer = gmtime(&n);
            strftime(charr, 1000, "%c UTC", pointer);
            printf("%s\n",charr );

        }
    }
    else
    {
        printf("Error more than one argument passed try again\n");
    }
    
    return 0;
}
