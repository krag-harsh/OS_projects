#include <stdio.h>
#include <string.h>

int main()
{
    
    // printf("size of int %ld\n",sizeof(int));
    // printf("size of long int %ld\n",sizeof(long int));
    // printf("pointer value of li is %p\n",pli);   

    unsigned char x[64];    //declaring as unsigned so that it do not retain -ve values
    int sto[16];
    sto[0]=257;
    sto[1]=121;
    sto[2]=126;
    sto[3]=125;
    sto[4]=124;
    sto[5]=123;
    sto[6]=122;
    sto[7]=121;
    sto[8]=22;
    sto[9]=21;
    sto[10]=26;
    sto[11]=25;
    sto[12]=24;
    sto[13]=23;
    sto[14]=22;
    sto[15]=21;

    for(int i=0;i<16;i++)
    {
        memcpy(&x[i*4], &sto[i], 4);
    }
    // x[0]= i  & 0xff;
    // x[1]= (i>>8)   & 0xFF;
    // x[2]= (i>>16)  & 0xFF;
    // x[3]= (i>>24)  & 0xFF;
    // printf("%d\n", x[0]);
    // printf("%d\n", x[1]);
    // printf("%d\n", x[2]);
    // printf("%d\n", x[3]);

    //memcpy(&x[4],&j,4);
    // printf("%d\n", x[4]);
    // printf("%d\n", x[5]);
    // printf("%d\n", x[6]);
    // printf("%d\n", x[7]);

    printf("run successful\n");
    return 0;
}
