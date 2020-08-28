#include <stdio.h>
#include <inttypes.h>


int64_t add(int64_t, int64_t);
int main() 
{
    int a=0,b=0;
    printf("Enter 2 numbers a and b \n");
    scanf("%d %d", &a,&b);
    printf("The sum of the entered values are: %ld\n", add(a, b));
    //add(a,b);
    return 0;
}