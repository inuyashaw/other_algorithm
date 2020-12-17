//约瑟夫环的递归实现 从0开始 n个人 c次(不能应用于从第k个人开始的情况)
// https://blog.csdn.net/byn12345/article/details/79487253

int Josephus(int n, int m, int c)
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
//输出的是从0开始的
int main(void)
{
    int i;
    i = Josephus(13, 3, 1);
    printf("->%d", i);
    i = Josephus(13, 3, 2);
    printf("->%d", i);
    i = Josephus(13, 3, 3);
    printf("->%d", i);
    i = Josephus(13, 3, 4);
    printf("->%d", i);
}
