#include<stdio.h>

//循环实现 
//void printN(int num)
//{
//	int i;
//	for(i=0;i<num;i++)
//	{
//		printf("%d",i);
//	}
//}

//递归实现
void printN(int num)
{
	if(num>0)
	{
		printN(num-1);
	}
	printf("%d",num);
} 

void main()
{
	int num;
	scanf("%d",&num);
	printN(num);
}
