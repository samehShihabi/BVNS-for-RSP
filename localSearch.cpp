#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>
#include <vector>
#include <set>
#include "globalVariables.h"
#include "Services.h"
#include "localSearch.h"
using namespace std;
double improve(vector<city> &tempSolution, double* tempValue, int tempSequence[], int* total)
{
	double bestImprovement = 0;
//	printf("\n 1 improve checking the comming solution total=%d",*total);
//	checkRepatriatedNumber(tempSolution, tempSequence, (*total),2);
//	checkValues(tempSolution, (*tempValue));
//	printf("\n 2 improve temp value before improving=%f total=%d",*tempValue,*total);
	do {
		int tempTotal = *total;
		//printf("\n total=%d quarantine location=%d", tempTotal,quarantineLocations);
		//getchar();
		bestImprovement = 0;
		int bestChange1city = 0;
		int bestAirplane = 0;
		int bestChange2City = 0;
		int populationChange = 0;
		for (int airplane = 0; airplane < numberAirplanes; airplane++)
		{
			int leaving = 0;
			int checkStatus = 0;
			
			if (tempSequence[airplane] == 1000000)
				checkStatus = 1;
			//	printf("\n airplane=%d status=%d solution=%d",airplane,checkStatus, tempSequence[airplane]);
			//	getchar();
			if (checkStatus == 0)
			{
				int startingCity = tempSequence[airplane];
				double startingValue = tempSolution[startingCity].value;
				int sum = tempSolution[startingCity].airplanesSumCapacities;
				
				if (tempSolution[startingCity].repatriated == sum)
					leaving = airplanesCapacities[airplane];
				/*if (sum > tempSolution[startingCity].repatriated)
				{
					printf("\n problem");
					getchar();
					getchar();
					getchar();

				}*/
				if (tempSolution[startingCity].repatriated < sum && tempSolution[startingCity].repatriated >(sum - airplanesCapacities[airplane]))
				{
						leaving = tempSolution[startingCity].repatriated-(sum- airplanesCapacities[airplane]); 
						if (leaving < 0) {
							printf("\n stop");
							getchar();
						}
				}
				if (tempSolution[startingCity].repatriated < sum && tempSolution[startingCity].repatriated <(sum - airplanesCapacities[airplane]))
				{
					leaving = 0;
				}
				sum -= airplanesCapacities[airplane];
				double endingValue = cityValue(tempSolution[startingCity].cumulativeNumberGroup, tempSolution[startingCity].numberPerGroup, sum);

				//	printf("\n airplane=%d cityOriginal=%d value1=%f value2=%f", airplane, startingCity, startingValue, endingValue);
				//	printf("\n leaving=%d", leaving);
				//	getchar();

				for (int nextCity = 0; nextCity < numberCountries; nextCity++)
					if (nextCity != startingCity)
					{
						int joining = 0;
						double startingValueNext = tempSolution[nextCity].value;
						int nextSum = tempSolution[nextCity].airplanesSumCapacities;
						nextSum += airplanesCapacities[airplane];
						if (nextSum < tempSolution[nextCity].totalNumber)
							joining = airplanesCapacities[airplane];
						else
							joining = tempSolution[nextCity].totalNumber - tempSolution[nextCity].repatriated;

						double endingValueNext = cityValue(tempSolution[nextCity].cumulativeNumberGroup, tempSolution[nextCity].numberPerGroup, nextSum);
						/*	if ((endingValueNext - startingValueNext)- ( startingValue-endingValue)>0 && (tempTotal+joining-leaving)<quarantineLocations)
							{
								printf("\n airplane=%d city=%d value1next=%f value2next=%f leaving=%d joining=%d", airplane, nextCity, startingValueNext, endingValueNext,
									leaving,joining);

							}*/
						if (((endingValueNext - startingValueNext) - (startingValue - endingValue)) > bestImprovement &&
							tempTotal+joining-leaving < quarantineLocations)
						{
							bestImprovement = (endingValueNext - startingValueNext) - (startingValue - endingValue);

							bestChange1city = startingCity;
							bestAirplane = airplane;
							bestChange2City = nextCity;
							populationChange = joining - leaving;
		//					printf("\n airplane=%d city1=%d city2=%d value1next=%f value2next=%f leaving=%d joining=%d improvement=%f", airplane, startingCity, nextCity, startingValueNext, endingValueNext,
		//						leaving, joining,bestImprovement);
		//					printf("\n starting1=%f ending1=%f starting2=%f ending2=%f", startingValue, endingValue, startingValueNext, endingValueNext);
						//	getchar();
						}
					}
					
			}

		}
		if (bestImprovement == 0)
			break;
		(*total) = (*total) + populationChange;
		(*tempValue) = (*tempValue) + bestImprovement;
		tempSequence[bestAirplane] = bestChange2City;
		changeAirplaneLocation(tempSolution,bestAirplane, bestChange1city, bestChange2City);
		double sumT = 0;
		for (int i = 0; i < numberCountries; i++)
			sumT += tempSolution[i].value;
	//	printf("\n best improvement=%f airplane=%d capacity=%d city1=%d city2=%d population change=%d new best=%f sum=%f total=%d poultation change=%d", bestImprovement, bestAirplane,
	//	airplanesCapacities[bestAirplane], bestChange1city, bestChange2City, populationChange, (*tempValue),sumT,*total,populationChange);
	//	checkRepatriatedNumber(tempSolution, tempSequence, (*total),2);
	//	checkValues(tempSolution, (*tempValue));
	
	//	getchar();
	} while(bestImprovement>0);
	return (*tempValue);
}
void changeAirplaneLocation(vector<city> &tempSolution, int bestAirplane, int bestChange1city, int bestChange2City)
{
	
	tempSolution[bestChange1city].airplanesSumCapacities-=airplanesCapacities[bestAirplane];
	tempSolution[bestChange1city].value= cityValue(tempSolution[bestChange1city].cumulativeNumberGroup, tempSolution[bestChange1city].numberPerGroup,  tempSolution[bestChange1city].airplanesSumCapacities);
	tempSolution[bestChange1city].airplanes.erase(bestAirplane);
	if (tempSolution[bestChange1city].airplanesSumCapacities < tempSolution[bestChange1city].totalNumber)
		tempSolution[bestChange1city].repatriated = tempSolution[bestChange1city].airplanesSumCapacities;
	else
		tempSolution[bestChange1city].repatriated = tempSolution[bestChange1city].totalNumber;


	tempSolution[bestChange2City].airplanesSumCapacities += airplanesCapacities[bestAirplane];
	/*if (bestAirplane == 30)
	{
		printf("\n city=%d capacity=%d", bestChange2City, tempSolution[bestChange2City].airplanesSumCapacities);
		getchar();
	}*/
	tempSolution[bestChange2City].value = cityValue(tempSolution[bestChange2City].cumulativeNumberGroup, tempSolution[bestChange2City].numberPerGroup,  tempSolution[bestChange2City].airplanesSumCapacities);
	tempSolution[bestChange2City].airplanes.insert(bestAirplane);
	if (tempSolution[bestChange2City].airplanesSumCapacities < tempSolution[bestChange2City].totalNumber)
		tempSolution[bestChange2City].repatriated = tempSolution[bestChange2City].airplanesSumCapacities;
	else
		tempSolution[bestChange2City].repatriated = tempSolution[bestChange2City].totalNumber;

}