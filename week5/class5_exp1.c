//�ѵĲ�����

#include<stdio.h>
#include<stdlib.h>

#define MAX_DATA 1000
//��ȫ������������
//�����пռ����ƣ�ͬʱ����Ҫһ��ָ���һ���ս���ָ��

typedef int elementType;
typedef struct heap *maxHeap;
struct heap{
	elementType *data;	//��̬����
	int size;			//��ǰԪ�ظ��� 
	int capacity; 		//����������� 
};

maxHeap createHeap(int heapCapa)//����ռ� 
{
	maxHeap h;
	h=malloc(sizeof(struct heap));
	h->data=malloc((heapCapa+1)*sizeof(elementType));//�±��1��ʼ
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
	
	//������h->data[i]<h->data[2*i]����Ϊ�޷��������Һ��� 
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
