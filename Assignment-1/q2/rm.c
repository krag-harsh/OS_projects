#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    // printf("We are in rm.c\n");

    // if(argc==3)
    // {
    //     if(strcmp(argv[1],"-v")==0)
    //     {
    //         int status = remove(argv[2]);
    //         if(status==0)
    //             printf("deleted %s \n",argv[2]);
    //         else
    //             printf("File doesn't exist\n");
    //     }
    //     else if(strcmp(argv[1],"-i")==0)
    //     {
    //         printf("Do you want to delete the file %s? y/n : " ,argv[2]);
    //         char *i;
    //         i = (char*)malloc(sizeof(char*)*2);
    //         fgets(i,2,stdin);
    //         if(*i=='y')
    //         {
    //             remove(argv[2]);
    //         }	
    //         free(i);
    //     }
    // }
    // else if(argc==2)
    // {
    //     remove(argv[1]);
    // }


    if(argc>1)
    {
        if(strcmp(argv[1],"-v")==0)
        {
            for(int j=2;j<argc;j++)
            {
                int status = remove(argv[j]);
                if(status==0)
                    printf("deleted %s \n",argv[j]);
                else
                    printf("File doesn't exist\n");
            }
        }
        else if(strcmp(argv[1],"-i")==0)
        {
            for(int j=2;j<argc;j++)
            {
                char *i;
                i = (char*)malloc(sizeof(char*)*2);
                printf("Do you want to delete the file %s? y/n : " ,argv[j]);
                fgets(i,3,stdin);
                if(i[0]=='y')
                {
                    remove(argv[j]);
                }	
                free(i);
            }
            
            
        }
        else
        {
            for(int i=1;i<argc;i++)
            {
                int k=remove(argv[i]);
                if(k!=0)
                printf("unable to delete file %s",argv[i]);
            }
        }
        
    }
    else 
    {
        printf("please enter value with rm (name of the file to be deleted)\n");
    }
    

    return 0;
}
