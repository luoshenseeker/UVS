#include <cstdio>
#define uchar unsigned char

union Double_to_uchar
{
    /* data */
    double a;
    uchar b[8];
};

int main()
{
    Double_to_uchar c;
    c.a = 0.5;
    c.b[0] = 0;
    c.b[1] = 0;
    c.b[2] = 0;
    c.b[3] = 0;
    c.b[4] = 0;
    c.b[5] = 0;
    c.b[6] = 0;
    c.b[7] = 0;
    c.b[6] = 224;
    c.b[7] = 63;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            printf("%d", (1<<(7-j))&c.b[i]?1:0);
        }
    }
    return 0;
}