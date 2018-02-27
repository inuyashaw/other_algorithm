/*  汉诺塔问题是源于印度一个古老传说的益智玩具。大梵天创造世界的时候做了三根金刚石柱子，在一根柱子上从下往上按照大小顺序摞着64片黄金圆盘。
大梵天命令婆罗门把圆盘从下面开始按大小顺序重新摆放在另一根柱子上。并且规定，在小圆盘上不能放大圆盘，在三根柱子之间一次只能移动一个圆盘。*/

/* 假设有n片，移动最少次数是f(n),显然f(1)=1,f(2)=3,f(3)=7,且f(k+1)=2*f(k)+1
 * ，此后不难证明f(n)=2^n-1  */

/*** 汉诺塔的递归算法：
 * 1、当只有一个盘子的时候，只需要将塔A上的一个盘子移动到塔C上即可。
 * 2、当塔A上有2个盘子的时候，先将塔A上的1号盘子(编号从上到下)移动到塔B上，
 * 再将塔A上的2号盘子移到塔C上，最后将塔B上的小盘子移动到塔C上即可 
 * 3、当塔A上有3个盘子时，先将塔A上编号1到2的盘子(共2个)移动到塔B上(需借助塔C)
 * ，然后将塔A上的3号最大的盘子移动到C塔上，最后将塔B上的两个盘子借助塔A移动
 * 到塔C上去。
 * 4、当塔A上有n个盘子时，先将A塔上编号1到n-1的盘子(共n-1个)移动到塔B上，然后将
 * 最大的n号盘子移动到塔C上去，最后将塔B上的n-1个盘子记住塔A移动到塔C上。
 *   综上，除只有1个盘子的时候不需要借助其他塔，其余情况均相同。***/

#include<iostream>
#include<stdio.h>
#include<fstream>
#include<time.h>
using namespace std;

#if 0
int step=1;
void move(int n,char from,char to)
	//将编号为n的盘子由from移动到to
{
	//printf("第%d步：将%d号盘子%c--->%c\n",step++,n,from,to);
	cout<<"第"<<step++<<"步:"<<"将"<<n<<"号盘子"<<from<<"-->"<<to<<endl;
}

void hanoi(int n,char from,char depended_on,char to)
	//将n个盘子由初始塔移动到目标塔，利用借用塔
{
	if(n==1)
		move(1,from,to);//只有一个盘子时，直接从from到to
	else
	{
		//先将初始塔的前n-1个盘子借助目标塔移动到借用塔上
		hanoi(n-1,from,to,depended_on);
		//将剩余的一个盘子移动到目标塔上
		move(n,from,to);
		//最后将借用塔上的n-1个盘子移动到目标塔上
		hanoi(n-1,depended_on,from,to);
	}
}

int main()
{
	cout<<"请输入盘子的个数："<<endl;
	int n;
	cin>>n;
	clock_t start,finish;
	start=clock();
	char x='A',y='B',z='C';
	hanoi(n,x,y,z);
	finish=clock();
	printf("time cost:%.2f ms\n",(double)(finish-start));
}

#endif


/*通过非递归的思想来实现汉诺塔问题的求解：
 * 当盘子的个数为n时，移动的次数应等于2^n - 1。该方法仅仅需要轮流进行2步操作
 * 即可。
 * 首先把三根柱子按顺序排成品字型，把所有的圆盘按从大到小的顺序放在柱子A上。
 * 根据圆盘的数量确定柱子的排放顺序：若n为偶数，按顺时针方向依次摆放 A B C；
 * 若n为奇数，按顺时针方向依次摆放 A C B。
 *1、按照顺时针方向把圆盘1从现在的柱子移动到下一根柱子，即当n为偶数时，若圆盘
 *1在柱子A，则把它移动到B；若圆盘1在柱子B，则把它移动到C；若圆盘1在柱子C，则
 *把它移动到A。
 *2、接着，把另外两根柱子上可以移动的圆盘移动到新的柱子上。
 *即把非空柱子上的圆盘移动到空柱子上，当两根柱子都非空时，移动较小的圆盘。
 *3、反复进行（1）（2）操作，最后就能按规定完成汉诺塔的移动。*/

//圆盘个数最多为64
const int MAX=64;
//用来表示每根柱子的信息
struct st{
	int s[MAX];//柱子上的圆盘存储情况
	int top;//栈顶，表示最上面的圆盘
	char name;//柱子的名字，可以是A,B,C中任何一个
	int Top()//取栈顶的元素
	{
		return s[top];
	}
	int Pop()//出栈
	{
		return s[top--];
	}
	void Push(int x)//入栈
	{
		s[++top]=x;
	}
};

//计算x^y
long Pow(int x,int y)
{
	int sum=1;
		while(y!=0)
		{
			sum*=x;
			y--;
		}
        cout<<"sum:"<<sum<<endl;
	return sum;
}

//给结构体数组设置初值
void Create(st ta[],int n)
{
	ta[0].name='A';
	ta[0].top=n-1;
	//把所有的圆盘按照从大到小的顺序依次放在柱子上
	for(int i=0;i<n;i++)
		ta[0].s[i]=n-i;
	//柱子B、C上开始没有圆盘
	ta[1].top=ta[2].top=0;
	for(int i=0;i<n;i++)
		ta[1].s[i]=ta[2].s[i]=0;
	//若n为偶数，按照顺时针的方向依次摆放A B C
	if(n%2==0)
	{
		ta[1].name='B';
		ta[2].name='C';
	}
	//若n为奇数，按照顺时针的方向依次摆放A C B
	else
	{
		ta[1].name='C';
		ta[2].name='B';
	}
}

void Hanoi(st ta[],long max)
{
	int step=0;//累计移动的步数
	int i=0;
	int ch;
	while(step<max)
	{
		//按照顺时针方向把圆盘1从现在的柱子移动到下一根柱子
		ch=ta[i%3].Pop();
		ta[(i+1)%3].Push(ch);
		cout<<++step<<':'<<"move disk"<<ch<<"from"<<ta[i%3].name<<"to"<<ta[(i+1)%3].name<<endl;
		i++;
		//把另外的两根柱子上可移动的圆盘移动到到新的柱子上
		if(step<max)
		{
			//把非空柱子上的圆盘移动到空的柱子上，当两根都不为空，移动小的圆盘到大的
			if( ta[(i+1)%3].Top()==0 || ta[(i+1)%3].Top()>ta[(i-1)%3].Top() && ta[(i-1)%3].Top()>0)
			{
				ch=ta[(i-1)%3].Pop();
				ta[(i+1)%3].Push(ch);
				cout<<++step<<':'<<"move disk"<<ch<<"from"<<ta[(i-1)%3].name<<"to"<<ta[(i+1)%3].name<<endl;
			}
			else
			{
				ch=ta[(i+1)%3].Pop();
				ta[(i-1)%3].Push(ch);
				cout<<++step<<':'<<"move disk"<<ch<<"from"<<ta[(i+1)%3].name<<"to"<<ta[(i-1)%3].name<<endl;
                            
			}
		}
	}
}


int main()
{
clock_t start,finish;
int n;
cout<<"请输入汉诺塔的个数"<<endl;
cin>>n;
start=clock();
st ta[3];//三根柱子的信息用结构体数组存储
Create(ta,n);//给结构体数组设置初值
long max=Pow(2,n)-1;//移动的次数
Hanoi(ta,max);
finish=clock();
printf("time cost:%.2f ms\n",(double)(finish-start));
return 0;
}
