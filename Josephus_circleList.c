//约瑟夫环的循环链表实现
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
}node, *pNode;

//n为总人数，k为从哪个开始，m为报数
void Josephus(int n, int k, int m)
{
    pNode p = NULL, curr = NULL, t = NULL;
    p = (pNode)malloc(sizeof(struct node));
    //创建一个自己指向自己的节点
    p->data = 1;
    p->next = p;
    curr = p;
    int i = 2;
    //创建循环链表
    for(; i <= n; i++)
    {
        pNode tt = (pNode)malloc(sizeof(struct node));
        tt->data = i;
        tt->next = curr->next;
        curr->next = tt;
        curr = tt;
    }
    
    //使curr指向k之前的那个节点，p指向k
    //k = k - 1;
    //while(k--)
    //{
    //    curr = p;
    //    p = p->next;
    //}
    while(p->data != k)
    {
        curr = p;
        p = p->next;
    }
    
    while(n)
    {
        //curr指向报m前的那个节点，p指向报m的节点
        for(i = 1; i <= m-1; i++)
        {
            curr = p;
            p = p->next;
        }
        //去掉报m的节点，并输出
        curr->next = p->next;
        printf("->%d",p->data);
        free(p);
        p = curr->next;
        n--;
    }
}

int main(void)
{
    Josephus(13,4,3);
}
