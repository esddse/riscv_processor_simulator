#include<stdio.h>
#include<stdlib.h>

int GG = 99;
int G;

void add(int a, int b)
{
	G = a+b;
}

int main()
{
	int a = 3;
	static int  b = 2;
	add(a,b);
	//int* mem = (int*) malloc (sizeof(int)*2);
	int c = G + GG;
	float d = c + 1.0;
	return 0;
}
