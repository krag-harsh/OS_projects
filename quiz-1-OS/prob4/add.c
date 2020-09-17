#include <stdio.h>
#include <inttypes.h>


int64_t add(int64_t, int64_t,int64_t,int64_t); 
int main() 
{
    int a=10,b=20,c=30,d=400;
    //printf("Enter 2 numbers a and b \n");
    //scanf("%d %d", &a,&b);		//using this we are entering the number
    int s1=add(a,b,c,d);
    printf("The sum of the entered values are: %d \n", s1);	//calling add function writtern in assembly code and printing the returned value
    //add(a,b);
    return 0;
}


