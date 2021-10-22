#include <stdio.h>
#include <stdlib.h>
#include "public/FuncLib.h"

int main(void)
{
	float* b = (float*)malloc(sizeof(float) * 10);

	//TestFunc(1);

	for (int i = 0; i < 10; i++)
	{
		b[i] = TestFunc(i);

	}
	for (int i = 0; i < 10; i++)
	{
		printf_s("%f", b[i]);
		printf_s("%s", "\n");
	}

	free(b);

	return 0;
}