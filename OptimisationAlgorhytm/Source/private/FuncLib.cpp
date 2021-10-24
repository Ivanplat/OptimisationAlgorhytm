#include "../public/FuncLib.hpp"
#include <math.h>
#include <random>
#include <iostream>

float LibFunc::CalculateFunc(float x1, float x2)
{
	const float Pi = 3.1415926;
	return 20 + pow(x1,2)+pow(x2, 2)-10*cos(2*Pi*x1)-10*cos(2*Pi*x2);
}

std::pair<std::vector<float>, float> GWOAlgorhytm::TestFunc(std::vector<float> InV)
{
	const float Pi = 3.1415926;
	int n = InV.size();
	float res = 0;
	for (int i = 0; i < n; i++)
	{
		res += pow(InV[i], 2) - 10 * cos(InV[i]) + 10;
	}
	return { InV,  res };
}

void GWOAlgorhytm::FirstIter()
{
	InitLRes();

	for (int i = 0; i < NumberOfPopulation; i++)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> r1(0, 1);
		std::uniform_real_distribution<> r2(0, 1);
		float x1 = LBound + r1(gen) * (UBound - LBound);
		float x2 = LBound + r2(gen) * (UBound - LBound);

		auto l = std::make_pair<std::vector<float>, float>(std::vector<float>(0.0f, 0.0f), float());
		LRes.push_back(l);


		LRes[i].first = { x1, x2 };
		LRes[i] = TestFunc(LRes[i].first);
	}
	X = LRes[0].first;
	CurrentY = TestFunc(X).second;

	for (const auto& [i, j] : LRes)
	{
		std::cout << "X1: " << i[0] << " X2: " << i[1] << " f: " << j << std::endl;
	}

	FindBestResults();

	
	std::cout << "START MAIN LOOP: " << std::endl;
	/*while (NewY < CurrentY)
	{
		a = 2 * (1 - t / MaxIterations);
		CalculateNewX();
		NewY = TestFunc(X).second;
		std::cout << "[" << TestFunc(X).first[0] << "; " << TestFunc(X).first[1] << "]" << " : " << TestFunc(X).second << ";" << std::endl;
	}*/
}

void GWOAlgorhytm::InitLRes()
{

}

void GWOAlgorhytm::FindBestResults()
{
	auto l = LRes;
	BestA = FindBestLocal(l);
	BestB = FindBestLocal(l);
	BestD = FindBestLocal(l);

	std::cout << std::endl << std::endl;
	std::cout << "BestA: [" << BestA.first[0] << "; " << BestA.first[1] << "]; " << "f: " << BestA.second << std::endl
		<< "BestB: [" << BestB.first[0] << "; " << BestB.first[1] << "]; " << "f: " << BestB.second  << std::endl
	    << "BestD: [" << BestD.first[0] << "; " << BestD.first[1] << "]; " << "f: " << BestD.second  << std::endl;
}

void GWOAlgorhytm::CalculateNewX()
{
	CalculateX1();
	CalculateX2();
	CalculateX3();

	for (int i = 0; i < X.size(); i++)
	{
		X[i] = (X1[i] + X2[i] + X3[i]) / 3;
	}
}

void GWOAlgorhytm::CalculateX1()
{
	auto [A, C] = CalculateAAndC();

	std::vector<float> D;
	auto BestACopy = BestA.first;
	for (auto& i : BestA.first)
	{
		i = i * C;
	}
	for (int i = 0; i < BestA.first.size(); i++)
	{
		BestA.first[i] = abs(BestA.first[i] - X[i]);
	}
	D = BestA.first;

	for (auto& i : D)
	{
		i = i * A;
	}
	for (int i = 0; i < BestACopy.size(); i++)
	{
		BestACopy[i] = BestACopy[i] - D[i];
	}
	X1 = BestACopy;
}

void GWOAlgorhytm::CalculateX2()
{
	auto [A, C] = CalculateAAndC();

	std::vector<float> D;
	auto BestBCopy = BestB.first;
	for (auto& i : BestB.first)
	{
		i = i * C;
	}
	for (int i = 0; i < BestB.first.size(); i++)
	{
		BestB.first[i] = abs(BestB.first[i] - X[i]);
	}
	D = BestB.first;

	for (auto& i : D)
	{
		i = i * A;
	}
	for (int i = 0; i < BestBCopy.size(); i++)
	{
		BestBCopy[i] = BestBCopy[i] - D[i];
	}
	X2 = BestBCopy;
}

void GWOAlgorhytm::CalculateX3()
{
	auto [A, C] = CalculateAAndC();

	std::vector<float> D;
	auto BestDCopy = BestD.first;
	for (auto& i : BestD.first)
	{
		i = i * C;
	}
	for (int i = 0; i < BestD.first.size(); i++)
	{
		BestD.first[i] = abs(BestD.first[i] - X[i]);
	}
	D = BestD.first;

	for (auto& i : D)
	{
		i = i * A;
	}
	for (int i = 0; i < BestDCopy.size(); i++)
	{
		BestDCopy[i] = BestDCopy[i] - D[i];
	}
	X3 = BestDCopy;
}

std::pair<std::vector<float>, float> GWOAlgorhytm::FindBestLocal(ResV& lV)
{
	float lCurMin = 10000000000.0f;
	std::pair<std::vector<float>, float> lp;
	std::vector<float> v;
	for (int i = 0; i < lV.size(); i++)
	{
		if (lV[i].second < lCurMin)
		{			
			v = { lV[i].first[0], lV[i].first[1] };
			lCurMin = lV[i].second;
			lp = { v, lCurMin };
		}
	}
	lV.erase(std::find(lV.begin(), lV.end(), lp));
	return lp;
}

std::pair<float, float> GWOAlgorhytm::CalculateAAndC()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> r1(0, 1);
	std::uniform_real_distribution<> r2(0, 1);

	float A = 2 * a * r1(gen) - a;
	float C = 2 * r2(gen);

	return { A, C };
}
