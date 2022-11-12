#include<stdio.h>
#include"C_STL.h"
int main()
{
	struct list L;
	LMake(&L);
	for (int i = 0; i < 10; i++)
		LPush_back(&L, i+1);
	LInsert_back(&L, 4, 666);
	LDelete(&L, 6);
	for (int i = 0; i < 10; i++)
		printf("%d\n", LAt(&L,i+1));
	printf("List的长度为%d", LLength(&L));
	return 0;
}