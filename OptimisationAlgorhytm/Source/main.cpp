#include "public/FuncLib.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <xmemory>

int main()
{

	GWOAlgorhytm g(5, 200, -5.12f, 5.12f, E_TestFunction::Rastrigin);
	g.Iters();

	return 0;
}
