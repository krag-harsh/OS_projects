#include <stdio.h>

int main()
{
    char name[]="Harsh";  //we are creating a variable which is storing name
    FILE *fptr;          //creating a file pointer
    fptr = fopen("name.txt", "ab+");    //opening the file, create in disk if not present
    fputs("Harsh", fptr);             //writing to the file created
    fclose(fptr);
    printf("File created and saved successfully. :) \n");
    return 0;
}

