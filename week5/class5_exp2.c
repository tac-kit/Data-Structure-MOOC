//哈夫曼树的建立

#include<stdio.h>
#include<stdlib.h>

#define MIN_DATA -1

typedef struct treeNode *huffmanTree;
struct treeNode{
	int weight;
	huffmanTree left,right;
};

typedef struct heap *minHeap;
struct heap{
	huffmanTree *root;//保存哈夫曼树的树根
	int size;
	int capacity;
};

minHeap createHeap(int heapCapa)//分配空间 
{
	minHeap h;
	h=malloc(sizeof(struct heap));
	h->root=malloc((heapCapa+1)*sizeof(huffmanTree));//下标从1开始
	h->size=0;
	h->capacity=heapCapa;
	h->root[0]=malloc(sizeof(struct treeNode));
	h->root[0]->weight=MIN_DATA;
	return h;
}

void insert(minHeap h, huffmanTree insertNode)
{
	int currentIndex;
	if(h->size >= h->capacity)
	{
		printf("heap is full\n");
		return;
	}
	//而不是h->data[i]<h->data[2*i]，因为无法区分左右孩子 
	for(currentIndex=++(h->size);insertNode->weight < h->root[currentIndex/2]->weight;currentIndex/=2)
	{
		h->root[currentIndex] = h->root[currentIndex/2];
	}
	h->root[currentIndex] = insertNode;
}

huffmanTree deleteMin(minHeap h)
{
	int parent, child;
	huffmanTree minNode,tempNode;
	if(h->size==0)
	{
		printf("heap is empty\n");
		return NULL;
	}
	minNode=h->root[1];
	tempNode=h->root[(h->size)--];
	parent=1;
	while(parent*2<=h->size)
	{
		child=parent*2;
		if(child<h->size && h->root[child]->weight > h->root[child+1]->weight)
		{
			child++;
		}
		
		if(tempNode->weight > h->root[child]->weight)
		{
			h->root[parent]=h->root[child];
			parent=child;
		}else{
			break;
		}
	}
	h->root[parent]=tempNode;
	return minNode;
}

huffmanTree createHuffman(minHeap h)
{
	int i,heapSize;
	huffmanTree t;
	
	heapSize=h->size;
//	for(i=1;i<h->size;i++)//在建树的过程中，堆最终会只剩1个元素，因此需要循环size-1次 
	for(i=1;i<heapSize;i++)//示例代码没有考虑size的变化 
	{
		t=malloc(sizeof(struct treeNode));
		
		t->left=deleteMin(h);
		t->right=deleteMin(h);
		t->weight=t->left->weight + t->right->weight;
		
		insert(h,t);
	}
	
	t=deleteMin(h);//勿忘 
	
	return t;
}

void preOrderTraversal(huffmanTree tree)
{
	if(tree)
	{
		printf("%d ",tree->weight);
		preOrderTraversal(tree->left);
		preOrderTraversal(tree->right);
	}
}

void inOrderTraversal(huffmanTree tree)
{
	if(tree)
	{
		inOrderTraversal(tree->left);
		printf("%d ",tree->weight);
		inOrderTraversal(tree->right);
	}
}

int main()
{
	minHeap h;
	huffmanTree t;
	int i,temp;
	
	h=createHeap(10);
	scanf("%d",&temp);
	while(temp!=-1)
	{		
		t=malloc(sizeof(struct treeNode));
		t->left=NULL;
		t->right=NULL;
		t->weight=temp;
		insert(h,t);
		scanf("%d",&temp);
	}
	
	t=createHuffman(h);
	
	printf("\npre-order traversal:\n");
	preOrderTraversal(t);
	printf("\nin-order traversal:\n");
	inOrderTraversal(t);
	
	return 0;
}
