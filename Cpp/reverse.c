#include <stdio.h>

/*  使用说明：
*       1.编译并运行
*	2.输入总个数
*	3.输入序列，用空格隔开或一个个输入
*	4.最后看结果
*/

int main()
{
    int buff[100];
    int n;
    int reverse = 0;
    printf("Please tell me how manny are the numbers you are going to input.\n");
    scanf("%d", &n);
    printf("Input the numbers.\n");
    for(int i = 0; i < n; i++){
        scanf("%d", &buff[i]);
    }

    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(buff[j] > buff[i]){
                reverse++;
            }
        }
    }
    printf("The total reverse is:%d\n", reverse);
    return 0;
}
