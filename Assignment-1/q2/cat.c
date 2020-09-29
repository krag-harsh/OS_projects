#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    //printf("We are in cat.c\n");
    if(argc==3)
    {
        if(strcmp(argv[1],"-E")==0)
        {
            FILE* stream = fopen(argv[2], "r");
            char line[1024];
            while (fgets(line, 1024, stream))
            {
                char* tmp = strdup(line);
                //printf("%s",tmp);
                for(int i=0;i<strlen(tmp);i++)
                {
                    if(tmp[i]=='\n')
                    printf("$");
                    printf("%c",tmp[i]);
                }
                free(tmp);
            }

        }

        else if(strcmp(argv[1],"-n")==0)
        {
            FILE* stream = fopen(argv[2], "r");
            int count=0;
            char line[1024];
            while (fgets(line, 1024, stream))
            {
                char* tmp = strdup(line);
                count++;
                printf("\t%d  %s",count,tmp);
                free(tmp);
            }

        }
        

    }
    else if (argc==2)
    {
        FILE* stream = fopen(argv[1], "r");
        char line[1024];
        while (fgets(line, 1024, stream))
        {
            char* tmp = strdup(line);
            printf("%s",tmp);
            free(tmp);
        }
    }
    
    return 0;
}
