#include <stdio.h>
#include <inttypes.h>


void checkGreater(int64_t, int64_t); 
int main() 
{
    int x=100,y=20;
    printf("Enter values of x and y respectively \n");
    scanf("%d %d", &x,&y);		//using this we are entering the number
    // extern checkGreater(int64_t, int64_t);
    checkGreater(x,y);
    return 0;
}


