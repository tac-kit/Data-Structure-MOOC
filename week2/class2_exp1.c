//使用链表实现线性表 

#include<stdio.h>

typedef struct PolyNode *Polynomial;
struct PolyNode{
	int coefficient;
	int exponent;
	Polynomial nextNode;
};

int main()
{
	struct PolyNode fun[3];
	Polynomial a,b,c;
	a=&fun[0];
	b=&fun[1];
	c=&fun[2];
	
	a->coefficient=3;
	a->exponent=7;
	a->nextNode=b;
	b->coefficient=12;
	b->exponent=3;
	b->nextNode=c;
	c->coefficient=11;
	c->exponent=1;
	
	printf("%d",a->nextNode->nextNode->coefficient);
	
	return 0;
}
