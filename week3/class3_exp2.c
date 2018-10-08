//二叉树的建立，树的前序、中序、后序遍历（非递归实现） 

#include<stdio.h>
#include<stdlib.h>

typedef char elementType;
typedef struct treeNode *pTreeNode;
struct treeNode{
	elementType value;
	pTreeNode leftChild;
	pTreeNode rightChild;
}; 

//使用指针实现堆栈
typedef struct nodeLinkList *pNodeStack;
struct nodeLinkList{
	pTreeNode nodeAddress;
	pNodeStack nextNode;
};

typedef struct nodeLinkCount *pNodeStackCount;
struct nodeLinkCount{
	pTreeNode nodeAddress;
	int popCount;
	pNodeStackCount nextNode;
};

void createBinaryTree(pTreeNode rootNode);
void preOrderTraversal(pTreeNode rootNode);
void inOrderTraversal(pTreeNode rootNode);
void postOrderTraversal(pTreeNode rootNode);

int main()
{
	pTreeNode treeRoot;
	treeRoot=(pTreeNode)malloc(sizeof(struct treeNode));
	treeRoot->leftChild=NULL;
	treeRoot->rightChild=NULL;
	
	printf("input tree root:");
	scanf("%c",&treeRoot->value);
	
	createBinaryTree(treeRoot);
	
	printf("\nPre-order traversal result:\n");
	preOrderTraversal(treeRoot);
	printf("\nIn-order traversal result:\n");
	inOrderTraversal(treeRoot);
	printf("\nPost-order traversal result:\n");
	postOrderTraversal(treeRoot);
	
	return 0;
}


void createBinaryTree(pTreeNode rootNode)
{
	char temp;
	printf("input the left child of %c:",rootNode->value);
	scanf(" %c",&temp);
	if(temp!='-')//'-'表示该子树为空树 
	{
		rootNode->leftChild=(pTreeNode)malloc(sizeof(struct treeNode));
		rootNode->leftChild->value=temp;
		rootNode->leftChild->leftChild=NULL;
		rootNode->leftChild->rightChild=NULL;
		createBinaryTree(rootNode->leftChild);
	}
	printf("input the right child of %c:",rootNode->value);
	scanf(" %c",&temp);
	if(temp!='-')
	{
		rootNode->rightChild=(pTreeNode)malloc(sizeof(struct treeNode));
		rootNode->rightChild->value=temp;
		rootNode->rightChild->leftChild=NULL;
		rootNode->rightChild->rightChild=NULL;
		createBinaryTree(rootNode->rightChild);
	}
}

void preOrderTraversal(pTreeNode rootNode)
{
	pNodeStack stackTop,stackTemp;
	pTreeNode currentNode;
	stackTop=(pNodeStack)malloc(sizeof(struct nodeLinkList));
	stackTop->nextNode=NULL;
	stackTop->nodeAddress=NULL;
	
	currentNode=rootNode;
	do{
		while(currentNode)
		{
			printf("%c ",currentNode->value);
			
			stackTemp=(pNodeStack)malloc(sizeof(struct nodeLinkList));
			stackTemp->nextNode=stackTop;
			stackTemp->nodeAddress=currentNode;
			stackTop=stackTemp;
			
			currentNode=currentNode->leftChild;
		}
		currentNode=stackTop->nodeAddress;
		stackTemp=stackTop;
		stackTop=stackTop->nextNode;
		free(stackTemp);
		currentNode=currentNode->rightChild;
		
	}while(currentNode || stackTop->nodeAddress);
} 

void inOrderTraversal(pTreeNode rootNode)
{
	pNodeStack stackTop,stackTemp;
	pTreeNode currentNode;
	stackTop=(pNodeStack)malloc(sizeof(struct nodeLinkList));
	stackTop->nextNode=NULL;
	stackTop->nodeAddress=NULL;
	
	currentNode=rootNode;
	do{
		while(currentNode)
		{			
			stackTemp=(pNodeStack)malloc(sizeof(struct nodeLinkList));
			stackTemp->nextNode=stackTop;
			stackTemp->nodeAddress=currentNode;
			stackTop=stackTemp;
			
			currentNode=currentNode->leftChild;
		}
		currentNode=stackTop->nodeAddress;
		printf("%c ",currentNode->value);
		stackTemp=stackTop;
		stackTop=stackTop->nextNode;
		free(stackTemp);
		currentNode=currentNode->rightChild;
		
	}while(currentNode || stackTop->nodeAddress);
} 
/*
void postOrderTraversal(pTreeNode rootNode)
{
	pNodeStackCount stackTop,stackTemp;
	pTreeNode currentNode;
	stackTop=(pNodeStackCount)malloc(sizeof(struct nodeLinkCount));
	stackTop->nextNode=NULL;
	stackTop->nodeAddress=NULL;
	stackTop->popCount=0;
	
	currentNode=rootNode;
	do{
		if(stackTop->popCount==0)
		{	
			while(currentNode)
			{
	//			printf("%c ",currentNode->value);
				
				stackTemp=(pNodeStackCount)malloc(sizeof(struct nodeLinkCount));
				stackTemp->nextNode=stackTop;
				stackTemp->nodeAddress=currentNode;
				stackTemp->popCount=0;
				stackTop=stackTemp;
				
				currentNode=currentNode->leftChild;
			}
			currentNode=stackTop->nodeAddress;
			currentNode=currentNode->rightChild;
			stackTop->popCount++;
		}
		else
		{
			printf("%c ",currentNode->value); 
			stackTemp=stackTop;
			stackTop=stackTop->nextNode;
			free(stackTemp);
			currentNode=stackTop->nodeAddress;
		}
	}while(stackTop->nodeAddress);
//	}while(currentNode || stackTop->nodeAddress);
	//前序遍历和中序遍历都是以右下方的空树结尾，而后序遍历是以根结点结尾，因此判断条件要改 
} */

void postOrderTraversal(pTreeNode rootNode)
{
	pNodeStackCount stackTop,stackTemp;
	pTreeNode currentNode;
	
	stackTop=(pNodeStackCount)malloc(sizeof(struct nodeLinkCount));
	stackTop->nextNode=NULL;
	stackTop->nodeAddress=NULL;
	stackTop->popCount=0;
	
	stackTemp=(pNodeStackCount)malloc(sizeof(struct nodeLinkCount));
	stackTemp->nextNode=stackTop;
	stackTemp->nodeAddress=rootNode;
	stackTemp->popCount=0;
	stackTop=stackTemp;
	
	currentNode=rootNode;
	
	while(stackTop->nodeAddress)
	{
//		printf("current node:%c\tstack top:%c\tpop count:%d\n",currentNode->value,stackTop->nodeAddress->value,stackTop->popCount);
		if(stackTop->popCount==0)
		{
			stackTop->popCount++;
			if(currentNode->leftChild)
			{
				currentNode=currentNode->leftChild;
				stackTemp=(pNodeStackCount)malloc(sizeof(struct nodeLinkCount));
				stackTemp->nextNode=stackTop;
				stackTemp->nodeAddress=currentNode;
				stackTemp->popCount=0;
				stackTop=stackTemp;
			}
		}
		else
		{
			if(stackTop->popCount==1)
			{
				stackTop->popCount++;
				if(currentNode->rightChild)
				{
					currentNode=currentNode->rightChild;
					stackTemp=(pNodeStackCount)malloc(sizeof(struct nodeLinkCount));
					stackTemp->nextNode=stackTop;
					stackTemp->nodeAddress=currentNode;
					stackTemp->popCount=0;
					stackTop=stackTemp;
				}
			}
			else
			{
				printf("%c ",currentNode->value);//Pop一个结点的标准是这个结点的左子树和右子树都已遍历 
				stackTemp=stackTop;
				stackTop=stackTop->nextNode;
				free(stackTemp);
				currentNode=stackTop->nodeAddress;
			}
		}
	}
}
