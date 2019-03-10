#include <cstdio>
#include <cstring>

struct comp_res
{
        bool above;
        int rest;
};

bool test(int a[], int n, int avg)
{
        for(int i = 0; i < n; i++){
                if(a[i] != avg){
                        return false;
                }
        }
        return true;
}

comp_res comp_avg(int a[], int start, int end, int avg)
{
        comp_res result;
        int tot = 0;
        for(int i = start; i < end; i++){
                tot += a[i];
        }
        if(tot >= avg * (end - start)){
                result.above = true;
        }
        else{
                result.above = false;
        }
}

int main()
{
        int n;
        scanf("%d", &n);
        int num[10005];
        for(int i = 0; i < n; i++){
                scanf("%d", num+i);
        }

        int tot = 0;
        for(int i = 0; i < n; i++){
                tot += num[i];
        }

        int avg = tot / n;
        int max = 0;
        int ind = 0;
        while(!test(num, n, avg)){
                for(int i = 0; i < n; i++){
                        if (num[i] > max){
                                max = num[i];
                                ind = i;
                        }
                }
                

        }
}