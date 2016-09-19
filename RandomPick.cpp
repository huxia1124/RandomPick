// RandomPick.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

#include <string>
#include <random>
#include <algorithm>
#include <iostream>
#include <iomanip>

//////////////////////////////////////////////////////////////////////////


std::mt19937 _randomGenerator;

#define BEGIN_PERFORMANCE_TEST(xName)\
		{CUniversalPerformanceCounter xxPerf(_T(#xName));

#define END_PERFORMANCE_TEST()\
		xxPerf.End();}

#define PERFORMANCE_TEST(xName)\
		CUniversalPerformanceCounter xxPerf(_T(#xName));

class CUniversalPerformanceCounter
{
public:
	CUniversalPerformanceCounter(LPCTSTR lpszPerformanceName)
	{
		_name = lpszPerformanceName;
		_tickStart = GetTickCount64();
	}
	~CUniversalPerformanceCounter()
	{
	}

protected:
	LONGLONG _tickStart;
	std::wstring _name;

public:
	void End()
	{
		LONGLONG nElapsed = GetTickCount64() - _tickStart;
		_tprintf(_T("[%s]\t Time Elapsed = %I64d Milliseconds\n"), _name.c_str(), nElapsed);
	}

};


long long NormalRandomPick(long long *possibilityArray, long long length, long long totalFactor)
{
	//Assume that possibilityArray is already sorted in ascending order

	int n = _randomGenerator() % totalFactor;
	for (int i = 0; i < length; i++)
	{
		if (n < possibilityArray[i])
		{
			return i;
		}
	}
	return length - 1;
}

long long FastRandomPick(long long *possibilityArray, long long length, long long totalFactor)
{
	//Assume that possibilityArray is already sorted in ascending order

	long long n = _randomGenerator() % totalFactor;
	long long *pos = std::lower_bound(possibilityArray, possibilityArray + length, n, std::less<long long>());
	return pos - possibilityArray;
}

void PrintProbability(long long *possibilityArray, long long *actualHit, long long nCandidates, long long nTestPickCount)
{
	long long maxProbabilityValue = possibilityArray[nCandidates - 1];
	long long scaledHit = actualHit[0] * maxProbabilityValue / nTestPickCount ;

	std::cout << std::setw(16) << "Designed" << std::setw(16) << "Scaled Hits" << std::setw(16) << "Actual Hits" << std::endl;
	std::cout << std::setw(16) << possibilityArray[0] << std::setw(16) << scaledHit << std::setw(16) << actualHit[0] << std::endl;

	long long nPrint = min(nCandidates, 5);
	for (long long i = 1; i < nPrint; i++)
	{
		scaledHit = actualHit[i] * maxProbabilityValue / nTestPickCount;
		std::cout << std::setw(16) << possibilityArray[i] - possibilityArray[i - 1] << std::setw(16) << scaledHit << std::setw(16) << actualHit[i] << std::endl;
	}
}


void Test(long long nCandidates, long long nTestPickCount, int nTestRound, long long probabilityScale = 8000)
{
	std::cout << "Preparing " << nCandidates << " candidates with random probability of being selected... " << std::endl;

	long long *candidates = new long long[nCandidates];
	long long *actualHit = new long long[nCandidates];
	candidates[0] = (_randomGenerator() % probabilityScale) + 1;
	actualHit[0] = 0;
	for (long long i = 1; i < nCandidates; i++)
	{
		candidates[i] = candidates[i - 1] + (_randomGenerator() % probabilityScale) + 1;
		actualHit[i] = 0;
	}

	//std::sort(candidates, candidates + nCandidates);		//already in ascending order. no need to sort
	std::cout << "Picking " << nTestPickCount << " random items from " << nCandidates << " candidates" << std::endl;

	for (int p = 0; p < nTestRound; p++)
	{
		std::cout << "------------------------- Round " << p + 1 << " -------------------------" << std::endl;

		BEGIN_PERFORMANCE_TEST(FastRandomPick);
		for (long long t = 0; t < nTestPickCount; t++)
		{
			long long index = FastRandomPick(candidates, nCandidates, candidates[nCandidates - 1]);
			actualHit[index]++;
		}
		END_PERFORMANCE_TEST();

		PrintProbability(candidates, actualHit, nCandidates, nTestPickCount);

		//Clear the hit count
		for (int i = 0; i < nCandidates; i++)
		{
			actualHit[i] = 0;
		}

		BEGIN_PERFORMANCE_TEST(NormalRandomPick);
		for (long long t = 0; t < nTestPickCount; t++)
		{
			long long index = NormalRandomPick(candidates, nCandidates, candidates[nCandidates - 1]);
			actualHit[index]++;
		}
		END_PERFORMANCE_TEST();

		PrintProbability(candidates, actualHit, nCandidates, nTestPickCount);

		//Clear the hit count
		for (int i = 0; i < nCandidates; i++)
		{
			actualHit[i] = 0;
		}
	}
	delete[]candidates;
	delete[]actualHit;
	std::cout << std::endl;
	std::cout << std::endl;
}


int main()
{

	long long nCandidates = 1000;			//Number of available candidates
	long long nTestPickCount = 100000;		//Number of pick attempt
	long long nProbabilityScale = 12000;
	int nTestRound = 2;						//How many round of test

	Test(nCandidates, nTestPickCount, nTestRound, nProbabilityScale);

	nCandidates *= 2;
	nTestPickCount *= 2;
	nProbabilityScale *= 2;
	Test(nCandidates, nTestPickCount, nTestRound, nProbabilityScale);

	nCandidates *= 2;
	nTestPickCount *= 2;
	nProbabilityScale *= 2;
	Test(nCandidates, nTestPickCount, nTestRound, nProbabilityScale);

	nCandidates *= 2;
	nTestPickCount *= 2;
	nProbabilityScale *= 2;
	Test(nCandidates, nTestPickCount, nTestRound, nProbabilityScale);


	return 0;
}

