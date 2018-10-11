//AVL树的插入 

#include<stdio.h>
#include<stdlib.h>

typedef int elementType;
typedef struct AVLNode *AVLTree;
struct AVLNode{
	elementType value;
	AVLTree left;
	AVLTree right;
	int height;
};

typedef struct AVLNodeStack *AVLStack;
struct AVLNodeStack{
	AVLTree node;
	AVLStack nextNode;
};

/*

	 root  	 ===>	rootLeft
	 /					\
	/					 \
rootLeft				root

*/
//在旋转时要更新height 
AVLTree rightRotate(AVLTree root)
{
	AVLTree rootLeft;
	
	root->height--;//证明？
	
	rootLeft=root->left;
	root->left=rootLeft->right;
	rootLeft->right=root;
	root=rootLeft;
	return root;
}

AVLTree leftRotate(AVLTree root)
{
	AVLTree rootRight;
	
	root->height--;//证明？
	
	rootRight=root->right;
	root->right=rootRight->left;
	rootRight->left=root;
	root=rootRight;
	return root;
}

AVLTree insertNode(AVLTree currentNode, elementType insertValue)//有可能根结点会发生改变，因此需要返回根结点地址 
{
	AVLStack searchPath,tempStack;
	AVLTree parentNode;//为什么需要parentNode?因为要对parentNode的child进行更新 
	int leftHeight,rightHeight,balanceFactor;
	char queue[2]={0};
	searchPath=(AVLStack)malloc(sizeof(struct AVLNodeStack));
	searchPath->nextNode=NULL;
	searchPath->node=NULL;
	if(!currentNode)//如果是空树
	{
		currentNode=(AVLTree)malloc(sizeof(struct AVLNode));
		currentNode->value=insertValue;
		currentNode->left=NULL;
		currentNode->right=NULL;
		currentNode->height=0;
	}else{
		//找到插入点 
		while(currentNode && currentNode->value != insertValue)
		{
			//push stack
			tempStack=(AVLStack)malloc(sizeof(struct AVLNodeStack));
			tempStack->node=currentNode;
			tempStack->nextNode=searchPath;
			searchPath=tempStack;
			
			currentNode = insertValue<currentNode->value ? currentNode->left : currentNode->right;
		}
		
		//如果存在相同结点 
		if(currentNode && currentNode->value == insertValue)
		{
			while(searchPath->node)//找到根结点，顺便释放堆栈 
			{
				currentNode=searchPath->node;
				tempStack=searchPath;
				searchPath=searchPath->nextNode;
				free(tempStack);
			}
			return currentNode;
		}
		
		//在插入点插入结点 
		parentNode=searchPath->node;//当前结点的根结点出栈
		//这里需要父结点，currentNode的值与parentNode->childNode相等，但修改currentNode并没有改变parentNode->childNode
		currentNode=(AVLTree)malloc(sizeof(struct AVLNode));
		currentNode->value=insertValue;
		currentNode->left=NULL;
		currentNode->right=NULL;
		currentNode->height=0;
		
		if(currentNode->value < parentNode->value)
		{
			parentNode->left=currentNode;
		}else
		{
			parentNode->right=currentNode;
		}
		
		while(searchPath->node)
		{
			//求平衡因子 
			currentNode=searchPath->node;//当前结点的根结点出栈
			tempStack=searchPath;
			searchPath=searchPath->nextNode;
			free(tempStack);
			
			parentNode=searchPath->node;//注意处理根结点情况
			
			leftHeight=currentNode->left ? currentNode->left->height : -1;
			rightHeight=currentNode->right ? currentNode->right->height : -1;
			balanceFactor=leftHeight-rightHeight;
			
			printf("balance factor of node %d is %d\n",currentNode->value,balanceFactor);
			
			//记录最近的两个结点是左子树还是右子树 
			queue[1]=queue[0];
			queue[0]=insertValue > currentNode->value;//左0右1 
			
			//调整 
			if(balanceFactor<-1 || balanceFactor>1)
			{
				switch(2*queue[1] + queue[0])//这里可以不传父结点，只要返回新的根结点值即可 
				{
					case 0:currentNode=rightRotate(currentNode);break;
					case 1:currentNode->right=rightRotate(currentNode->right);currentNode=leftRotate(currentNode);break;
					case 2:currentNode->left=leftRotate(currentNode->left);currentNode=rightRotate(currentNode);break;
					case 3:currentNode=leftRotate(currentNode);break;
				}
				if(parentNode!=NULL)//如果当前结点不是根结点，更新双亲结点子树 
				{
					if(currentNode->value < parentNode->value){
						parentNode->left=currentNode;
					}else{
						parentNode->right=currentNode;
					}
				}
				while(searchPath->node)//找到根结点，顺便释放堆栈 
				{
					currentNode=searchPath->node;
					tempStack=searchPath;
					searchPath=searchPath->nextNode;
					free(tempStack);
				}
				return currentNode;
				
			}else{//不调整 
				currentNode->height=leftHeight>rightHeight ? leftHeight+1 : rightHeight+1;//更新高度 
			}
		}
	}
	
	return currentNode;
}

void preOrderTraversal(AVLTree rootNode)
{
	if(rootNode)
	{
		printf("%d ",rootNode->value);
		preOrderTraversal(rootNode->left);
		preOrderTraversal(rootNode->right);
	}
} 

void inOrderTraversal(AVLTree rootNode)
{
	if(rootNode)
	{
		inOrderTraversal(rootNode->left);
		printf("%d ",rootNode->value);
		inOrderTraversal(rootNode->right);
	}
} 

int main()
{
	AVLTree rootNode,tempNode;
	elementType insertValue;
	rootNode=NULL;
	printf("input root value:");
	scanf("%d",&insertValue);
	while(insertValue!=-1)
	{
		rootNode=insertNode(rootNode, insertValue);
		
		printf("Pre-order traversal result:");
		preOrderTraversal(rootNode);
		putchar('\n');
		
		printf("\ninput node value:");
		scanf("%d",&insertValue);
	}
	
	printf("\nPre-order traversal result:\n");
	preOrderTraversal(rootNode);
	printf("\nIn-order traversal result:\n");
	inOrderTraversal(rootNode);
	
	return 0;
}
