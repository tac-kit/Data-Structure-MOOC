//¶ş·Ö²éÕÒ 

#include<stdio.h>
#include<math.h>

#define MAX_N 10

int binarySearch(int a[], int n, int x)
{
	int left, right, middle;
	left = 0;
	right = n-1;
	
	while(left <= right)
	{
		middle = (left + right)/2;//floor()
		if(a[middle]==x)return middle;
		else
		{
			if(a[middle] < x)
			{
				left = middle + 1;
			}
			else
			{
				right = middle - 1;
			}
		}
	}
	
	return -1;
}

void main()
{
	int a[MAX_N],i,x,searchResult;
	
	for(i=0;i<MAX_N;i++)
	{
		a[i]=pow(2,i);
		printf("%d\t%d\n",i,a[i]);
	}
	
	scanf("%d",&x);
	searchResult = binarySearch(a, MAX_N, x);
	if(searchResult == -1)
		printf("no matching result\n");
	else
		printf("result is %d\n",searchResult);
}
