#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>
#include "globalVariables.h"
#include "intialSolution.h"
#include "Services.h"
#include "checks.h"
using namespace std;

double generateInitialSolution(int solution[], int* total)
{
    int airplaneStatus[50000];

    for (int i = 0; i < numberAirplanes; i++)
        airplaneStatus[i] = 1;

    int checkOut = 0;
    double tempValue;
    double sumValue = 0;
    int returnedNumber = 0;
    int totalNumber = 0;
	int chosenCity = -1;
	int numberAirplanesDum = 0;
    do {
        int chosenAirplane = chooseAirplane(airplaneStatus);
	//	printf("\n airplane=%d airplane capacity=%d",chosenAirplane,airplanesCapacities[chosenAirplane]);
		
		if (chosenAirplane != -1)
		{
			airplaneStatus[chosenAirplane] = 0;
			chosenCity = chooseCity(chosenAirplane, &tempValue);
	//		printf("\n airplane=%d airplane capacity=%d city=%d", chosenAirplane, airplanesCapacities[chosenAirplane],chooseCity);

			if (chosenCity != -1)
			{
				numberAirplanesDum++;
				int totalFlightCapacity = citySolution[chosenCity].airplanesSumCapacities + airplanesCapacities[chosenAirplane];
				if (totalFlightCapacity < citySolution[chosenCity].cumulativeNumberGroup[numberGroups - 1])
					returnedNumber = totalFlightCapacity;
				else
					returnedNumber = citySolution[chosenCity].cumulativeNumberGroup[numberGroups - 1];
				if (tempValue == 0)
				{
					checkOut = 1;
					break;

				}
				if (totalNumber - citySolution[chosenCity].repatriated + returnedNumber > quarantineLocations)
				{
					checkOut = 1;
					continue;


				}
				
				sumValue += tempValue;


				totalNumber -= citySolution[chosenCity].repatriated;
				totalNumber += returnedNumber;
				
				if (totalNumber <= quarantineLocations)
				{
					citySolution[chosenCity].repatriated = returnedNumber;
					citySolution[chosenCity].airplanes.insert(chosenAirplane);
					citySolution[chosenCity].value += tempValue;
					solution[chosenAirplane] = chosenCity;
					citySolution[chosenCity].airplanesSumCapacities += airplanesCapacities[chosenAirplane];
					
				//	checkRepatriatedNumber(citySolution, incumbentSolution, totalNumber,1);
				//	checkValues(citySolution, initialValue);
					
				}
				else {
					checkOut = 1;
					totalNumber -= returnedNumber;
					totalNumber += citySolution[chosenCity].repatriated;
					break;
				}
			}
		}
    } while (checkOut == 0 && totalNumber < quarantineLocations && totalNumber <totalAllCities && chosenCity != -1 && numberAirplanesDum < numberAirplanes);
 //   printf("\n value=%f total number=%d quarantine location=%d", sumValue, totalNumber, quarantineLocations);

    (*total) = totalNumber;
    
    return sumValue;
}

int chooseAirplane(int airplaneStatus[])
{
    int possibleChoices[50000];
    int choiceNumber = 0;
    double cumulative[60000];
    cumulative[0] = 0;
    for (int i = 0; i < numberAirplanes; i++)
    {
        //	printf("\n i=%d status=%d",i, airplaneStatus[i]);
            //	getchar();
        if (airplaneStatus[i] == 1)
        {
			return i;
        }
    }
	printf("\n choice number=%d",choiceNumber);

	return -1;
}
int chooseCity(int chosenAirplane, double* tempValue)
{

	//	printf("\n chosen airplane=%d capacity=%d",chosenAirplane, airplanesCapacities[chosenAirplane]);
	//	getchar();
	double bestValue = 0;
	int bestCities[300];
	int bestCitiesCounter = 0;
	for (int i = 0; i < numberCountries; i++)
	{
		int cap = airplanesCapacities[chosenAirplane];

		int numberLeft = 0;
	
		double value1 = citySolution[i].value;
		double value2 = cityValue(citySolution[i].cumulativeNumberGroup, citySolution[i].numberPerGroup,
			citySolution[i].airplanesSumCapacities + cap);
	
		double value = value2 - value1;
		int sum = 0;
	/*	if (chosenAirplane == 569)
		{ 
			sum += citySolution[i].totalNumber;
		//	printf("\n repatriated=%d total=%d sum=%d",citySolution[i].repatriated,citySolution[i].totalNumber,sum);
		//	getchar();
		}*/
		if (value > bestValue)
		{
			bestValue = value;
			bestCitiesCounter = 0;
			bestCities[bestCitiesCounter] = i;
			bestCitiesCounter++;
		}
		
	}
	if (bestCitiesCounter == 0)
	{
	//	printf("\n problem");
	//	getchar();
		return -1;

	}

	//	getchar();
	(*tempValue) = bestValue;
	
	//	printf("\n best city=%d",bestCity);
	return bestCities[0];
}