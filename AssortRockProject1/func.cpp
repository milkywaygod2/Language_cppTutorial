#include "func.h"
#include "common.h"
#include <stdio.h>


int Add(int a, int b)
{
	printf("g_iStatic의 값은 : %d\n", g_iStatic);
	printf("g_iStatic의 값은 : %d\n", g_iExtern); //초파일간 전역변수임으로 main1.cpp의 500을 가져오게됨


	return a + b;
}

int Sub(int a, int b)
{
	return a - b;
}

int Mul(int a, int b)
{
	return a * b;
}