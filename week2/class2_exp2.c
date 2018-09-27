//顺序表的定义与操作

#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>//注意使用bool型变量需要加入此头文件，这是C99特性 

#define MAXSIZE 10
#define ERROR -1

typedef int elementType;
typedef int position;

typedef struct seqList *pSeqList;
struct seqList{
	elementType list[MAXSIZE];
	int lastIndex;//length(list)=lastIndex+1
};

void PrintList( pSeqList L );
pSeqList MakeEmpty();//初始化 
position Find( pSeqList L, elementType X );//查找 
bool Insert( pSeqList L, elementType X, position P );//插入 
bool Delete( pSeqList L, position P );//删除 

int main()
{
//	struct seqList listA;
	pSeqList pListA;
	int i,inputNum,findIndex;
	
//	pListA=&listA;
	pListA=MakeEmpty();
	
	for(i=0;i<MAXSIZE;i++)
	{
		pListA->list[i]=i*2;
	}
	pListA->lastIndex=MAXSIZE-1;
	
	PrintList(pListA);
	
	printf("which number do you want to find?\n");
	scanf("%d",&inputNum);
	findIndex=Find(pListA,inputNum);
	if(findIndex!=ERROR)
	{
		printf("the index of %d is %d\n",inputNum,findIndex);
	}
	else
	{
		printf("no matching number\n");
	}
	
	printf("which index do you want to delete?\n");
	scanf("%d",&inputNum);
	if(Delete(pListA,inputNum))
	{
		printf("deletion succeeded\n");
	}
	else
	{
		printf("deletion failed\n");
	}
	PrintList(pListA);
	
	printf("which index do you want to insert?\n");
	scanf("%d",&inputNum);
	if(Insert(pListA,100,inputNum))
	{
		printf("insertion succeeded\n");
	}
	else
	{
		printf("insertion failed\n");
	}
	PrintList(pListA);
	
	return 0;
}

void PrintList( pSeqList L )
{
	int i;
	printf("index\tnumber\n");
	for(i=0;i<=L->lastIndex;i++)
	{
		printf("%d\t%d\n",i,L->list[i]);
	}
//	printf("%d\n",L->lastIndex);
}

pSeqList MakeEmpty()
{
	//wrong solution
	//这里定义的listA是一个局部变量，将局部变量的地址传出去，显然是不能用的 
//	struct seqList listA;
//	pSeqList pListA;
//	pListA=&listA;
//	return pListA;
	
	pSeqList pListA=(pSeqList)(malloc(sizeof(struct seqList)));
	return pListA;
}

position Find( pSeqList L, elementType X )
{
	int i;
	for(i=0;i<=L->lastIndex;i++)
	{
		if(X==L->list[i])
		{
			return i;
		}
	}
	return ERROR;
}

bool Insert( pSeqList L, elementType X, position P )//插入 
{
	int i;
	if(P<0 || P>L->lastIndex+1 || L->lastIndex==MAXSIZE-1)//异常输入处理：表满、位置不合法
	{
		return false;
	}
	else
	{
		for(i=L->lastIndex;i>=P;i--)
		{
			L->list[i+1]=L->list[i];
		}
		L->list[P]=X;
		L->lastIndex++;
		return true;
	}
} 

bool Delete( pSeqList L, position P )
{
	int i;
//	if(P<0 || P>L->lastIndex || L->lastIndex==-1)//异常输入处理：表空、位置不合法，注意表空是-1 
	if(P<0 || P>L->lastIndex)//表空时左式结果为1，不需要单独判断lastIndex 
	{
		return false;
	}
	else
	{
		for(i=P;i<L->lastIndex;i++)
		{
			L->list[i]=L->list[i+1];
		}
		L->lastIndex--;
		return true;
	}
}
