#pragma once
#include <vector>
#include <functional>

enum class E_TestFunction
{
	Rastrigin,
	Other
};

class GWOAlgorhytm
{
	typedef std::vector<std::pair<std::vector<float>, float>> ResV;
public:
	explicit GWOAlgorhytm() noexcept = default;
	explicit GWOAlgorhytm(int NumberOfPopulation, int MaxIterations, float LBound, float UBound, E_TestFunction TestFunction) noexcept : NumberOfPopulation(NumberOfPopulation), MaxIterations(MaxIterations), LBound(LBound), UBound(UBound), TestFunction(TestFunction){}
	virtual ~GWOAlgorhytm() noexcept = default;
public:
	std::pair<std::vector<float>, float> TestFunc(std::vector<float> InV);
	void FirstIter();
	void Iters();
private:
	void InitLRes();
	void FindBestResults(ResV& res);
	void CalculateNewX();
	void CalculateX1();
	void CalculateX2();
	void CalculateX3();
	std::pair<std::vector<float>, float> FindBestLocal(ResV& lV);
	std::pair<float, float> CalculateAAndC();
private:
	ResV LRes;
	int NumberOfPopulation = 5;
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
	E_TestFunction TestFunction;
};


class TestingFunctions
{
	typedef std::vector<std::pair<std::vector<float>, float>> ResV;
	typedef std::pair<std::vector<float>, float> ResP;
public:
	explicit TestingFunctions() noexcept = default;
	virtual ~TestingFunctions() noexcept = default;
public:
	std::pair<std::vector<float>, float> DiffFunc(E_TestFunction TestFunction, std::vector<float>& InV);
	std::pair<std::vector<float>, float> RastriginFunction(std::vector<float> InV);
};