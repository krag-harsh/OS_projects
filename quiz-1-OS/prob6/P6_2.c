#include <stdio.h>

int main()
{
    char name[]="Harsh";
    //printf("Name= %s\n",name);
    FILE *fptr;
    fptr = fopen("scores.dat", "ab+");
    fputs("Harsh", fptr);
    fclose(fptr);
    printf("File created and saved successfully. :) \n");
    return 0;
}

