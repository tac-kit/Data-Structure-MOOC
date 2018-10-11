//AVL���Ĳ��� 

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
//����תʱҪ����height 
AVLTree rightRotate(AVLTree root)
{
	AVLTree rootLeft;
	
	root->height--;//֤����
	
	rootLeft=root->left;
	root->left=rootLeft->right;
	rootLeft->right=root;
	root=rootLeft;
	return root;
}

AVLTree leftRotate(AVLTree root)
{
	AVLTree rootRight;
	
	root->height--;//֤����
	
	rootRight=root->right;
	root->right=rootRight->left;
	rootRight->left=root;
	root=rootRight;
	return root;
}

AVLTree insertNode(AVLTree currentNode, elementType insertValue)//�п��ܸ����ᷢ���ı䣬�����Ҫ���ظ�����ַ 
{
	AVLStack searchPath,tempStack;
	AVLTree parentNode;//Ϊʲô��ҪparentNode?��ΪҪ��parentNode��child���и��� 
	int leftHeight,rightHeight,balanceFactor;
	char queue[2]={0};
	searchPath=(AVLStack)malloc(sizeof(struct AVLNodeStack));
	searchPath->nextNode=NULL;
	searchPath->node=NULL;
	if(!currentNode)//����ǿ���
	{
		currentNode=(AVLTree)malloc(sizeof(struct AVLNode));
		currentNode->value=insertValue;
		currentNode->left=NULL;
		currentNode->right=NULL;
		currentNode->height=0;
	}else{
		//�ҵ������ 
		while(currentNode && currentNode->value != insertValue)
		{
			//push stack
			tempStack=(AVLStack)malloc(sizeof(struct AVLNodeStack));
			tempStack->node=currentNode;
			tempStack->nextNode=searchPath;
			searchPath=tempStack;
			
			currentNode = insertValue<currentNode->value ? currentNode->left : currentNode->right;
		}
		
		//���������ͬ��� 
		if(currentNode && currentNode->value == insertValue)
		{
			while(searchPath->node)//�ҵ�����㣬˳���ͷŶ�ջ 
			{
				currentNode=searchPath->node;
				tempStack=searchPath;
				searchPath=searchPath->nextNode;
				free(tempStack);
			}
			return currentNode;
		}
		
		//�ڲ��������� 
		parentNode=searchPath->node;//��ǰ���ĸ�����ջ
		//������Ҫ����㣬currentNode��ֵ��parentNode->childNode��ȣ����޸�currentNode��û�иı�parentNode->childNode
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
			//��ƽ������ 
			currentNode=searchPath->node;//��ǰ���ĸ�����ջ
			tempStack=searchPath;
			searchPath=searchPath->nextNode;
			free(tempStack);
			
			parentNode=searchPath->node;//ע�⴦���������
			
			leftHeight=currentNode->left ? currentNode->left->height : -1;
			rightHeight=currentNode->right ? currentNode->right->height : -1;
			balanceFactor=leftHeight-rightHeight;
			
			printf("balance factor of node %d is %d\n",currentNode->value,balanceFactor);
			
			//��¼������������������������������ 
			queue[1]=queue[0];
			queue[0]=insertValue > currentNode->value;//��0��1 
			
			//���� 
			if(balanceFactor<-1 || balanceFactor>1)
			{
				switch(2*queue[1] + queue[0])//������Բ�������㣬ֻҪ�����µĸ����ֵ���� 
				{
					case 0:currentNode=rightRotate(currentNode);break;
					case 1:currentNode->right=rightRotate(currentNode->right);currentNode=leftRotate(currentNode);break;
					case 2:currentNode->left=leftRotate(currentNode->left);currentNode=rightRotate(currentNode);break;
					case 3:currentNode=leftRotate(currentNode);break;
				}
				if(parentNode!=NULL)//�����ǰ��㲻�Ǹ���㣬����˫�׽������ 
				{
					if(currentNode->value < parentNode->value){
						parentNode->left=currentNode;
					}else{
						parentNode->right=currentNode;
					}
				}
				while(searchPath->node)//�ҵ�����㣬˳���ͷŶ�ջ 
				{
					currentNode=searchPath->node;
					tempStack=searchPath;
					searchPath=searchPath->nextNode;
					free(tempStack);
				}
				return currentNode;
				
			}else{//������ 
				currentNode->height=leftHeight>rightHeight ? leftHeight+1 : rightHeight+1;//���¸߶� 
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
