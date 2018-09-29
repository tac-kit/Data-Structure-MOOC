//堆栈的顺序存储以及对应操作

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElementType;
typedef struct SNode *Stack;
struct SNode{
	ElementType *Data;//只是一个指针，因此可以改变栈的大小 
	int StackTop;
	int MaxSize;
};

Stack CreateStack( int MaxSize );
bool IsEmpty( Stack S );
bool IsFull( Stack S );
bool Push( Stack S, ElementType X );
ElementType Pop( Stack S );
void Print( Stack S );

int main()
{
	Stack s1;
	s1=CreateStack(10);

	Push(s1,1);
	Push(s1,2);
	Push(s1,3);
	Pop(s1);
	Pop(s1);
	Push(s1,4);
	Push(s1,5);
	Pop(s1);
	Push(s1,6);
	Push(s1,7);
	
	Print(s1);
	
	return 0;
}

Stack CreateStack( int MaxSize )
{
	Stack s1=malloc(sizeof(struct SNode));
	ElementType *pTempList=malloc(MaxSize*sizeof(ElementType));
	s1->Data=pTempList;
	s1->MaxSize=MaxSize;
	s1->StackTop=-1;
	return s1;
}

bool IsEmpty( Stack S )
{
//	if(S->StackTop==-1){
//		return true;
//	}else{
//		return false;
//	}
	return S->StackTop==-1;
}

bool IsFull( Stack S )
{
//	if(S->StackTop==S->MaxSize-1){//从下标0开始存储 
//		return true;
//	}else{
//		return false;
//	}
	return S->StackTop==S->MaxSize-1;
}

bool Push( Stack S, ElementType X )
{
	if((IsFull(S))){
		return false;
	}else{
		S->Data[++S->StackTop]=X;
		return true;
	}
}

ElementType Pop( Stack S )//最好是用指针把pop的值带出去 
{
	if((IsEmpty(S))){
		return 0;//pop的正常数据也可能是0 
	}else{
		return S->Data[S->StackTop--];
	}
}

void Print( Stack S )
{
	int i;
	for(i=0;i<=S->StackTop;i++)
	{
		printf("%d\t%d\n",i,S->Data[i]);
	} 
}

