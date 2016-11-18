#include<stdio.h>
#include<stdlib.h>


int main()
{
	int* addr = (int*)malloc(sizeof(int)*10);
	addr[6] = 1087;
	printf("%d\n", addr[6]);
	return 0;
}
