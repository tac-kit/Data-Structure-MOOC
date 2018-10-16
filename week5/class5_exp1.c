//堆的操作集

#include<stdio.h>
#include<stdlib.h>

#define MAX_DATA 1000
//完全二叉树，数组
//数组有空间限制，同时还需要一个指向第一个空结点的指针

typedef int elementType;
typedef struct heap *maxHeap;
struct heap{
	elementType *data;	//动态数组
	int size;			//当前元素个数 
	int capacity; 		//数组最大容量 
};

maxHeap createHeap(int heapCapa)//分配空间 
{
	maxHeap h;
	h=malloc(sizeof(struct heap));
	h->data=malloc((heapCapa+1)*sizeof(elementType));//下标从1开始
	h->size=0;
	h->capacity=heapCapa;
	h->data[0]=MAX_DATA;
	return h;
}

void insert(maxHeap h, elementType insertData)
{
	int currentIndex;
	if(h->size >= h->capacity)
	{
		printf("heap is full\n");
		return;
	}
	
	//而不是h->data[i]<h->data[2*i]，因为无法区分左右孩子 
	for(currentIndex=++(h->size);insertData>h->data[currentIndex/2];currentIndex/=2)
	{
		h->data[currentIndex]=h->data[currentIndex/2];
	}
	h->data[currentIndex]=insertData;
}

#define DELETE_ERROR -1

elementType deleteMax(maxHeap h)
{
	int parent, child;
	elementType maxData,tempData;
	if(h->size==0)
	{
		printf("heap is empty\n");
		return DELETE_ERROR;
	}
	maxData=h->data[1];
	tempData=h->data[(h->size)--];
	parent=1;
	while(parent*2<=h->size)
	{
		child=parent*2;
		if(child<h->size && h->data[child]<h->data[child+1])
		{
			child++;
		}
		
		if(tempData<h->data[child])
		{
			h->data[parent]=h->data[child];
			parent=child;
		}else{
			break;
		}
	}
	h->data[parent]=tempData;
	return maxData;
}

int main()
{
	elementType insertData;
	int i;
	maxHeap h=createHeap(10);
	
	scanf("%d",&insertData);
	while(insertData!=-1)
	{
		insert(h,insertData);
		scanf("%d",&insertData);
	}
	
	while(h->size>0)
	{
		printf("%d ",deleteMax(h));
	}
	
	return 0;
}
