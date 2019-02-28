//约瑟夫环的递归实现 从0开始 n个人 c次(不能应用于从第k个人开始的情况)
// https://blog.csdn.net/byn12345/article/details/79487253

#include<stdio.h>
#include<stdlib.h>

int Josephus(n, m, c)
{
    if(c == 1)
    {
        return (n + m - 1) % n;
    }
    else
    {
        return (Josephus(n - 1, m, c - 1) + m) % n;
    }
}

int main(void)
{
    int i;
    i = Josephus(13, 3, 1);
    prinft("->%d", i);
    i = Josephus(13, 3, 2);
    prinft("->%d", i);
    i = Josephus(13, 3, 3);
    prinft("->%d", i);
    i = Josephus(13, 3, 4);
    prinft("->%d", i);
}
