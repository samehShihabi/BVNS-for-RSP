#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "Services.h"
#include <vector>
#include <set>
#include "globalVariables.h"
using namespace std;
void copyAllback(vector<city> tempSolution, int tempSequence[], int *Total)
{
	for (int i = 0; i < numberAirplanes; i++)
		incumbentSolution[i]= tempSequence[i] ;
	citySolution.clear();
	int sum = 0;
	for (int i = 0; i < numberCountries; i++)
	{
		citySolution.push_back(tempSolution[i]);
		sum += citySolution[i].repatriated;
	//	printf("\n i=%d repatriated=%d sum=%d",i, citySolution[i].repatriated,sum);
	}
	*Total = 0;
	for (int i = 0; i < numberCountries; i++)
		(*Total) += citySolution[i].repatriated;
//	printf("\n total number=%d", *Total);
//	getchar();
}
void copyAll(vector<city> &tempSolution, int tempSequence[], int* tempTotal)
{
	for (int i = 0; i < numberAirplanes; i++)
		tempSequence[i] = incumbentSolution[i];
	tempSolution.clear();
	for (int i = 0; i < numberCountries; i++)
	{
		tempSolution.push_back(citySolution[i]);
	}
	(*tempTotal) = 0;
	for (int i = 0; i < numberCountries; i++)
		(*tempTotal) += tempSolution[i].repatriated;
//	printf("\n total number=%d",*tempTotal);
//	getchar();
	


}
int randomCityChoice(int number, int choices[])
{
	double cumulative[50000];
	cumulative[0] = 0;
	for (int i = 1; i <= number; i++)
		cumulative[i] = cumulative[i - 1] + 1.0 / (double)number;
	cumulative[number] = 1;
	int	temp = rand();
	double random = (double)temp / RAND_MAX;
	int loc = 0;
	while (cumulative[loc] < random)
	{
		loc++;
	}
	loc--;
	return choices[loc];

}
double cityValue(int cumulativeNumberGroup[],int numberPerGroup[], int total)
{
	double value = 0;
	int sum = 0;
	int loc = 0;
	if (total > cumulativeNumberGroup[numberGroups - 1])
		total = cumulativeNumberGroup[numberGroups - 1];
	while (cumulativeNumberGroup[loc] < total )
	{
		value += priorities[loc] * (cumulativeNumberGroup[loc]-sum);
		sum += numberPerGroup[loc];
		
		loc++;
	};

	value += priorities[loc] * ( total-sum);



	return value;
}