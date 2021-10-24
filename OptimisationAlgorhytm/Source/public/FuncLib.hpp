#pragma once
#include <vector>
class LibFunc
{
public:
	LibFunc() = default;
	float CalculateFunc(float x1, float x2);
};


class GWOAlgorhytm
{
	typedef std::vector<std::pair<std::vector<float>, float>> ResV;
public:
	GWOAlgorhytm() noexcept = default;
	explicit GWOAlgorhytm(int NumberOfPopulation, int MaxIterations, float LBound, float UBound) noexcept : NumberOfPopulation(NumberOfPopulation), MaxIterations(MaxIterations), LBound(LBound), UBound(UBound) {}
	virtual ~GWOAlgorhytm() noexcept = default;
public:
	std::pair<std::vector<float>, float> TestFunc(std::vector<float> InV);
	void FirstIter();
private:
	void InitLRes();
	void FindBestResults();
	void CalculateNewX();
	void CalculateX1();
	void CalculateX2();
	void CalculateX3();
	std::pair<std::vector<float>, float> FindBestLocal(ResV& lV);
	std::pair<float, float> CalculateAAndC();
private:
	ResV LRes;
	int NumberOfPopulation = 100;
	int MaxIterations = 200;
	int t = 0;
	float a = 2.0f;
	float LBound;
	float UBound;
	float CurrentY;
	float NewY;
	std::vector<float> X;
	std::vector<float> X1;
	std::vector<float> X2;
	std::vector<float> X3;
	std::pair<std::vector<float>, float> BestA;
	std::pair<std::vector<float>, float> BestB;
	std::pair<std::vector<float>, float> BestD;
};
