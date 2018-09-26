//多项式的计算 
#include<stdio.h>
#include<math.h>
#include<time.h>

#define MAX_N 100

//循环法 
double f1(int n, double a[], double x)
{
	int i;
	double sum;
	sum=a[0];
	for(i=1;i<=n;i++)
	{
		sum += a[i] * pow(x,i);
	}
	return sum;
}

//秦九韶法 
double f2(int n, double a[], double x)
{
	int i;
	double sum;
	sum = a[n];
	for(i=n;i>0;i--)
	{
		sum = a[i-1] + x*sum;
	}
	return sum;
}

int main()
{
	double a[MAX_N+1];
	double x=1.1;
	int i,start_time,stop_time;
	double duration,sum;
	
	//initialization of a
	a[0]=1;
	for(i=1;i<=100;i++)
	{
		//a[i]=1/i;//wrong
		a[i]=1.0/i;
//		printf("%f\n",a[i]);
	}
	 
	start_time=clock();
	for(i=0;i<100000;i++)
	{
		sum=f1(MAX_N, a, x);
	}
	stop_time=clock();
	printf("result=%f\n",sum);
	printf("duration=%.3f\n", (double)(stop_time-start_time)/CLK_TCK);
	
	start_time=clock();
	for(i=0;i<100000;i++)
	{
		sum=f2(MAX_N, a, x);
	}
	stop_time=clock();
	printf("result=%f\n",sum);
	printf("duration=%.3f\n", (double)(stop_time-start_time)/CLK_TCK);
	 
	printf("CLK_TCK=%d",CLK_TCK);
	return 0;
}
