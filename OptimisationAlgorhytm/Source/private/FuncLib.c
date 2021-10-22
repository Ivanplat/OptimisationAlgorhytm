#include "../public/FuncLib.h"
#include <stdio.h>
#include <math.h>

float TestFunc(int n)
{
	const int A = 10;
	float x = -5.12f;
	float n2 = 0.0f;
	n2 = n * A;
	float summ = 0.0f;
	while(x<=5.12f)
	{
		summ = pow(x, 2) - A * cos(2 * 3.141592f * x);
		n2 += summ;
		x += 0.1f;
	}
	//printf_s("%f", n2);
	return n2;
}
