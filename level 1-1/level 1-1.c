#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
int main(void)
{
	int A, B, C, SUM;
	SUM = 0;

	scanf("%d %d %d", &A, &B, &C);
	printf("%d 0 0\n", C);

	while (A < C)
	{
		C--;
		SUM++;
	}
	while (A > C)
	{
		C++;
		SUM++;
	}
	while (A = C)
	{
		break;
	}

	printf("%d %d 1\n", A, SUM);

	while (A < B)
	{
		A++;
		SUM++;
	}
	while (A > B)
	{
		A--;
		SUM++;
	}
	while (A = B)
	{
		break;
	}

	printf("%d %d 0", B, SUM);

	return 0;

}