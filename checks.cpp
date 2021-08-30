#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "Services.h"
#include <vector>
#include <set>
#include "globalVariables.h"
#include "checks.h"

using namespace std;
void checkCapacities(vector<city> tempSolution)
{
	for (int i = 0; i < numberCountries; i++)
	{
		int tempSum = 0;
		for (set<int>::iterator it = tempSolution[i].airplanes.begin(); it != tempSolution[i].airplanes.end(); ++it)
		{
			int flight = *it;
			tempSum += airplanesCapacities[flight];
		}
		if (tempSum != tempSolution[i].airplanesSumCapacities)
		{
			printf("\n problem airplane capacity city=%d sum=%d given=%d",i,tempSum,tempSolution[i].airplanesSumCapacities);
			getchar();
		}

	}

}
void checkValues(vector<city> tempSolution, double totalValue)
{
	double total = 0;
	for (int i = 0; i < numberCountries; i++)
		{
		double tempValue = cityValue(tempSolution[i].cumulativeNumberGroup,
			tempSolution[i].numberPerGroup, tempSolution[i].airplanesSumCapacities);
		if((int)tempValue!=(int)tempSolution[i].value)
			{
			printf("\n problem value city=%d",i);
			getchar();
			}
		total += tempValue;
		}
	if ((int)totalValue != (int)total)
	{
		printf("\n problem in total toal1=%f total2=%f",totalValue,total);
		getchar();
	}



}
void checkRepatriatedNumber(vector<city> tempSolution,int incumbent[], int totalReturned, int sender)
{
	int totalSum = 0;
	for (int i = 0; i < numberCountries; i++)
	{
		int sum = 0;
		for (int j = 0; j < numberAirplanes; j++)
			if (incumbent[j] == i)
				sum += airplanesCapacities[j];
		int min = sum;
		if (tempSolution[i].totalNumber < min)
			min = tempSolution[i].totalNumber;
		totalSum += min;
		if ( min != tempSolution[i].repatriated)
		{
			printf("\n i=%d min=%d sum=%d solution number=%d repatriated=%d", i, min,sum, tempSolution[i].totalNumber, tempSolution[i].repatriated);
			getchar();
		}
	}
	if(totalSum!=totalReturned)
	{
		printf("\n Problem in total returned sum=%d total=%d sender=%d",totalSum,totalReturned,sender);
		getchar();
	}

}
