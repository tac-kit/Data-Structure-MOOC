//˳���Ķ��������

#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>//ע��ʹ��bool�ͱ�����Ҫ�����ͷ�ļ�������C99���� 

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
pSeqList MakeEmpty();//��ʼ�� 
position Find( pSeqList L, elementType X );//���� 
bool Insert( pSeqList L, elementType X, position P );//���� 
bool Delete( pSeqList L, position P );//ɾ�� 

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
	//���ﶨ���listA��һ���ֲ����������ֲ������ĵ�ַ����ȥ����Ȼ�ǲ����õ� 
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

bool Insert( pSeqList L, elementType X, position P )//���� 
{
	int i;
	if(P<0 || P>L->lastIndex+1 || L->lastIndex==MAXSIZE-1)//�쳣���봦��������λ�ò��Ϸ�
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
//	if(P<0 || P>L->lastIndex || L->lastIndex==-1)//�쳣���봦����ա�λ�ò��Ϸ���ע������-1 
	if(P<0 || P>L->lastIndex)//���ʱ��ʽ���Ϊ1������Ҫ�����ж�lastIndex 
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
