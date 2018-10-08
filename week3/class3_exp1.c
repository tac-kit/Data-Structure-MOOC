//二叉树的建立，树的前序、中序、后序遍历（递归实现） 

#include<stdio.h>
#include<stdlib.h>

typedef char elementType;
typedef struct treeNode *pTreeNode;
struct treeNode{
	elementType value;
	pTreeNode leftChild;
	pTreeNode rightChild;
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
	if(rootNode)
	{
		printf("%c ",rootNode->value);
		preOrderTraversal(rootNode->leftChild);
		preOrderTraversal(rootNode->rightChild);
	}
} 

void inOrderTraversal(pTreeNode rootNode)
{
	if(rootNode)
	{
		inOrderTraversal(rootNode->leftChild);
		printf("%c ",rootNode->value);
		inOrderTraversal(rootNode->rightChild);
	}
} 

void postOrderTraversal(pTreeNode rootNode)
{
	if(rootNode)
	{
		postOrderTraversal(rootNode->leftChild);
		postOrderTraversal(rootNode->rightChild);
		printf("%c ",rootNode->value);
	}
} 
