//约瑟夫环josephus不追究过程，只求最后存活者的方法
//https://www.cnblogs.com/cmmdc/p/7216726.html
#include<stdio.h>
#include<stdlib.h>

//f[1] = 0; f(n) = ( f[n - 1] + m ) % n;
int main(void)
{
    int s = 0, n = 13, m = 3, i;
    for(i = 2; i < n; i++)
    {
        s = (s + m) % i;
    }
    printf("%d", s + 1);
    
    return 0;
}
