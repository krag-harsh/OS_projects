#include <stdio.h>
#include <inttypes.h>


void checkGreater(int64_t, int64_t); 
int main() 
{
    int a=100,b=20;
    //printf("Enter 2 numbers a and b \n");
    scanf("%d %d", &a,&b);		//using this we are entering the number
    // extern checkGreater(int64_t, int64_t);
    checkGreater(a,b);
    //printf("The sum of the entered values are: %d \n", s1);	//calling add function writtern in assembly code and printing the returned value
    //add(a,b);
    return 0;
}


