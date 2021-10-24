#include "public/FuncLib.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <xmemory>

int MaxIter = 100;
int CurrentIter = 0;


class SpecVec : public std::vector<double>
{
public:
	explicit SpecVec() noexcept : std::vector<double>() {};
	SpecVec operator+(const SpecVec&);
};


double TestFunc(std::vector<double>& Xi)
{
	int n = Xi.size();
	double res = 0;
	for (int i = 0; i < n; i++)
	{
		res+=pow(Xi[i], 2) - 10 * cos(Xi[i]) + 10;
	}
	return res;
}
std::vector<double> CalculateNewPosition(std::vector<double>& CurrentPosition)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> r1(0, 1);
	std::uniform_real_distribution<> r2(0, 1);


	auto r1i = r1(gen);
	auto r2i = r2(gen);

	auto a = 2 - (2 * CurrentIter) / MaxIter;

	auto Ai = 2 * a * r1i - a;
	auto Ci = 2 * r2i;

	auto X = CurrentPosition;
	auto Xt = CurrentPosition;
	std::vector<double> Xn;
	for (auto& i : X) 
	{
		i *= Ci;
	}
	for (int i = 0; i < X.size(); i ++)
	{
		Xn.push_back(abs(X[i] - Xt[i]));
	}


	//std::vector<double> newPos = Ai * Xn);
	return std::vector<double>();
}

int main()
{


	GWOAlgorhytm g(10, 200, -2, 2);
	g.FirstIter();





	//std::vector<double> X = {3,4,5};
	//TestFunc(X);

	/*SpecVec v1;
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	SpecVec v2;
	v2.push_back(7);
	v2.push_back(22);
	v2.push_back(16);


	SpecVec v4 = {4};

	auto v3 = v1 + v2;

	for (auto i : v3)
	{
		std::cout << i << std::endl;
	}*/



	//LibFunc LF;
	//float fc;
	//float fc2;
	//float h = 0.01;
	//std::vector<float> y;
	//std::vector <std::pair<float, float>> coords;

	////fc = (f(x + h) - f(x - h)) / (2 * h);

	//for (float x1 = -5.12f; x1 <= 5.12f; x1 += 0.01)
	//{
	//	for (float x2 = -5.12f; x2 <= 5.12f; x2 += 0.01)
	//	{
	//		fc = (LF.CalculateFunc(x1 + h, x2 + h) - LF.CalculateFunc(x1 - h, x2 - h)) / (2 * h);
	//		fc2 = (LF.CalculateFunc(x1 + h, x2 + h) - 2*LF.CalculateFunc(x1, x2) + LF.CalculateFunc(x1 - h, x2 - h)) / (pow(h,2));
	//		if (-0.01 < fc && fc < 0.01 && -0.01 < fc2 && fc2 < 0.01)
	//		{
	//			coords.push_back({ x1,x2 });
	//		}
	//		y.push_back(fc);
	//	}
	//}


	//for (const auto& i : coords)
	//{
	//	std::cout << "X1: " << i.first << " X2: " << i.second << std::endl;
	//}


	return 0;
}

SpecVec SpecVec::operator+(const SpecVec& other)
{
	SpecVec n = *this;
	for (int i = 0; i < this->size(); i++)
	{
		n[i] = *(this->begin()+i)+ other[i];
	}
	return n;
}
