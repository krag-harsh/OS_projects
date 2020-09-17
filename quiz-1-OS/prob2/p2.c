#include <stdio.h>
#include <math.h>

float add(float a, float b)
{
    // return (float)(round(a)+round(b));
	return (round(a)+round(b));

}

int main(){


	float a=10.02;
	float b=20;

	printf("value of a is %f and of b is %f \n", a , b);
    float f=add(a,b);
    printf("Output : %f\n",f);
	return 0;

}

