//二叉搜索树的插入，删除，查找最值，查找指定结点 

#include<stdio.h>
#include<stdlib.h>

typedef int elementType;
typedef struct treeNode *pTreeNode;
struct treeNode{
	elementType value;
	pTreeNode leftChild;
	pTreeNode rightChild;
};

//没有返回值，根结点就必须单独处理 
void insert(pTreeNode rootNode, elementType insertValue)
{
	if(insertValue<rootNode->value)
	{
		if(rootNode->leftChild)
		{
			insert(rootNode->leftChild, insertValue);
		}
		else
		{
			rootNode->leftChild=(pTreeNode)malloc(sizeof(struct treeNode));
			rootNode->leftChild->value=insertValue;
			rootNode->leftChild->leftChild=NULL;
			rootNode->leftChild->rightChild=NULL;
		}
	}
	else
	{
		if(insertValue>rootNode->value)
		{
			if(rootNode->rightChild)
			{
				insert(rootNode->rightChild, insertValue);
			}
			else
			{
				rootNode->rightChild=(pTreeNode)malloc(sizeof(struct treeNode));
				rootNode->rightChild->value=insertValue;
				rootNode->rightChild->leftChild=NULL;
				rootNode->rightChild->rightChild=NULL;
			}
		}
	}
}

pTreeNode findMin(pTreeNode currentNode)
{
	if(!currentNode)//空树 
	{
		return currentNode;
	}
	while(currentNode->leftChild)
	{
		currentNode=currentNode->leftChild;
	}
	return currentNode;
 } 
 
pTreeNode findMax(pTreeNode currentNode)
{
	if(!currentNode)//空树 
	{
		return currentNode;
	}
	while(currentNode->rightChild)
	{
		currentNode=currentNode->rightChild;
	}
	return currentNode;
} 

pTreeNode findNode(pTreeNode currentNode, elementType value)
{
	if(!currentNode)
	{
		return currentNode;//空树 
	}
	while(value!=currentNode->value)
	{
		if(value<currentNode->value)
		{
			if(currentNode->leftChild)
			{
				currentNode=currentNode->leftChild;
			}
			else
			{
				return NULL;//没找到 
			}
		}
		else
		{
			if(currentNode->rightChild)
			{
				currentNode=currentNode->rightChild;
			}
			else
			{
				return NULL;//没找到 
			}
		}	
	}
	return currentNode;
}

pTreeNode deleteNode(pTreeNode currentNode, elementType deleteValue)
{
	pTreeNode tempNode;
	if(currentNode==NULL)
	{
		return currentNode;
	}
	if(deleteValue==currentNode->value)
	{
		if(currentNode->leftChild)
		{
			if(currentNode->rightChild)//2个子树 
			{
				currentNode->value=findMax(currentNode->leftChild)->value;
				currentNode->leftChild=deleteNode(currentNode->leftChild, currentNode->value);
			}
			else//1个子树，左子树 
			{
				tempNode=currentNode->leftChild;
				free(currentNode);
				currentNode=tempNode;
			}
		}
		else
		{
			if(currentNode->rightChild)//1个子树，右子树 
			{
				tempNode=currentNode->rightChild;
				free(currentNode);
				currentNode=tempNode;
			}
			else//没有子树 
			{
				free(currentNode);
				currentNode=NULL;
			}
		}
	}
	else//如果不相等 
	{
		if(deleteValue<currentNode->value)
		{
			currentNode->leftChild=deleteNode(currentNode->leftChild, deleteValue);
		}
		else
		{
			currentNode->rightChild=deleteNode(currentNode->rightChild, deleteValue);
		}
	}
	return currentNode;
}

void preOrderTraversal(pTreeNode rootNode)
{
	if(rootNode)
	{
		printf("%d ",rootNode->value);
		preOrderTraversal(rootNode->leftChild);
		preOrderTraversal(rootNode->rightChild);
	}
} 

void inOrderTraversal(pTreeNode rootNode)
{
	if(rootNode)
	{
		inOrderTraversal(rootNode->leftChild);
		printf("%d ",rootNode->value);
		inOrderTraversal(rootNode->rightChild);
	}
} 

int main()
{
	elementType tempValue;
	pTreeNode rootNode,testNode;
	rootNode=(pTreeNode)malloc(sizeof(struct treeNode));
	rootNode->leftChild=NULL;
	rootNode->rightChild=NULL;
	
	//initialize root node first
	printf("input root node:");
	scanf("%d",&rootNode->value);
	
	printf("input next node:");
	scanf("%d",&tempValue);
	while(tempValue!=-1)
	{
		insert(rootNode, tempValue);
		printf("input next node:");
		scanf("%d",&tempValue);
	}
	
	printf("\nPre-order traversal result:\n");
	preOrderTraversal(rootNode);
	printf("\nIn-order traversal result:\n");
	inOrderTraversal(rootNode);
	
	printf("\nmin node is:%d\n",findMin(rootNode)->value);
	printf("\nmax node is:%d\n",findMax(rootNode)->value);
	
	printf("input value to find:");
	scanf("%d",&tempValue);
	while(tempValue!=-1)
	{
		printf("the node address is:%d\n",findNode(rootNode,tempValue));
		printf("input value to find:");
		scanf("%d",&tempValue);
	}
	
	printf("input value to delete:");
	scanf("%d",&tempValue);
	while(tempValue!=-1)
	{
		rootNode=deleteNode(rootNode, tempValue);
		if(rootNode==NULL)
		{
			printf("\nall nodes deleted\n");
			break;
		}
		printf("Pre-order traversal result:\n");
		preOrderTraversal(rootNode);
		printf("\nIn-order traversal result:\n");
		inOrderTraversal(rootNode);
		
		printf("\n\ninput value to delete:");
		scanf("%d",&tempValue);
	}
}

