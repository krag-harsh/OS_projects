#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char x[64];
    long int sto[8];
    sto[0]=122;
    sto[1]=121;
    sto[2]=126;
    sto[3]=125;
    sto[4]=124;
    sto[5]=123;
    sto[6]=122;
    sto[7]=121;

    for(int i=0;i<8;i++)
    {
        memcpy(&x[i*8], &sto[i], 8);
    }

    return 0;
}
