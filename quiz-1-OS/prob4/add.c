#include <stdio.h>
#include <inttypes.h>

int32_t long_add(int32_t, int32_t,int32_t,int32_t); 
int64_t extended_add(int64_t, int64_t,int64_t,int64_t);

int main() 
{
    int a=10,b=20,c=30,d=400;

    int s1=long_add(a,b,c,d);
    int s2=extended_add(a,b,c,d);

    printf("The sum of 4 variables by using long_add : %d \n",s1 );	
    printf("The sum of 4 variables by using  extended_add: %d \n", s2);	//calling add function writtern in assembly code and printing the returned value
    return 0;
}


