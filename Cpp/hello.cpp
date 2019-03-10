#include <cstdio>
#define wu 2.2360679774998

int main()
{
    int n;
    scanf("%d", &n);
    int a = 0;
    int b = 1;
    if(0 == n){
        printf("0.00\n");
    }
    else if(1 == n){
        printf("1.00\n");
    }
    else{
        for(int i = 0; i < n - 2; i++){
            b = a + b;
            a = b - a;
        }
        printf("%.2f", (double)b);
    }
    return 0;
}