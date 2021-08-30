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
#include "checks.h"
#include "Services.h"
#include "localSearch.h"
#include "VNS.h"
using namespace std;
void shake(vector<city>& tempSolution, int tempSequence[], int* tempTotal, int numberChanges, double* tempValue)
{
 //   printf("\n 1 shaking checking the comming solution");
 //   checkRepatriatedNumber(tempSolution, tempSequence, (*tempTotal),3);
 //   checkValues(tempSolution, (*tempValue));
 //   printf("\n 2 shaking temp value before improving=%f", *tempValue);

    int possibleChoices[50000];
    int choiceNumber = 0;
    double cumulative[60000];
    cumulative[0] = 0;
    int airplaneStauts[50000];
    for (int i = 0; i < numberAirplanes; i++)
        if (tempSequence[i] != 1000000)
            airplaneStauts[i] = 1;
    int numberChosen = 0;
 //   printf("\n total=%d",*tempTotal);
 //   getchar();
    do {
        int choiceNumber = 0;
        for (int i = 0; i < numberAirplanes; i++)
        {
            //	printf("\n i=%d status=%d",i, airplaneStatus[i]);
                //	getchar();
            if (airplaneStauts[i] == 1)
            {
                possibleChoices[choiceNumber] = i;
                choiceNumber++;
            }
        }
     //   printf("\n choice number=%d",choiceNumber);
      //  getchar();
        cumulative[0] = 0;
        for (int i = 1; i <= choiceNumber; i++)
            cumulative[i] = cumulative[i - 1] + 1.0 / (double)choiceNumber;
        cumulative[choiceNumber] = 1;
        int	temp = rand();
        double random = (double)temp / RAND_MAX;
        int loc = 0;
        do{
            loc++;
        //    printf("\n random=%f cumulative loc=%f",random,cumulative[loc]);
        //    getchar();
        } while (cumulative[loc]<random);
        loc--;
        int chosenAirplane = possibleChoices[loc];
        airplaneStauts[chosenAirplane] = 0;
        int possibleCitiesNumber = 0;
        int possibleCities[400];
        for(int i=0;i<numberCountries;i++)
            if(i!= tempSequence[chosenAirplane])
                {
                possibleCities[possibleCitiesNumber]=i;
                possibleCitiesNumber++;
                }
        cumulative[0] = 0;
        for (int i = 1; i <= possibleCitiesNumber; i++)
            cumulative[i] = cumulative[i - 1] + 1.0 / (double)possibleCitiesNumber;
        cumulative[possibleCitiesNumber] = 1;
        temp = rand();
        random = (double)temp / RAND_MAX;
        loc = 0;
        do {
            loc++;
            //    printf("\n random=%f cumulative loc=%f",random,cumulative[loc]);
            //    getchar();
        } while (cumulative[loc] < random);
        loc--;
        int nextCity = possibleCities[loc];
        int firstCity = tempSequence[chosenAirplane];
    //    printf("\n number=%d chosen Airplane=%d capacity=%d city1=%d city2=%d",numberChosen,chosenAirplane,airplanesCapacities[chosenAirplane], firstCity, nextCity);
     //   printf("\n city1 repatriated=%d city1 total=%d city airplanes=%d city2 repatriated=%d city 2 total=%d city 2 airplanes=%d", tempSolution[firstCity].repatriated, 
    //        tempSolution[firstCity].totalNumber,tempSolution[firstCity].airplanesSumCapacities ,tempSolution[nextCity].repatriated, tempSolution[nextCity].totalNumber,
     //       tempSolution[nextCity].airplanesSumCapacities);
    //    getchar();
        int leaving = 0;
        double startingValue = tempSolution[firstCity].value;
        int sum = tempSolution[firstCity].airplanesSumCapacities;
        int leftCapacity = sum - airplanesCapacities[chosenAirplane];
        if (tempSolution[firstCity].repatriated == sum)
            leaving = airplanesCapacities[chosenAirplane];
        if (tempSolution[firstCity].repatriated < sum)
        {
            if (tempSolution[firstCity].repatriated > leftCapacity)
                leaving = tempSolution[firstCity].repatriated - leftCapacity;
            else
                leaving = 0;

        }
           
        sum -= airplanesCapacities[chosenAirplane];
        double endingValue = cityValue(tempSolution[firstCity].cumulativeNumberGroup, tempSolution[firstCity].numberPerGroup, sum);
        double startingValueNext = tempSolution[nextCity].value;
        int nextSum = tempSolution[nextCity].airplanesSumCapacities;
        nextSum += airplanesCapacities[chosenAirplane];
        int joining;
        if (nextSum < tempSolution[nextCity].totalNumber)
            joining = airplanesCapacities[chosenAirplane];
        else
            joining = tempSolution[nextCity].totalNumber - tempSolution[nextCity].repatriated;

        double endingValueNext = cityValue(tempSolution[nextCity].cumulativeNumberGroup, tempSolution[nextCity].numberPerGroup, nextSum);

        int populationChange = joining - leaving;
         

        (*tempTotal) = (*tempTotal) + populationChange;
        (*tempValue) = (*tempValue) + (endingValueNext-tempSolution[nextCity].value)+(endingValue-tempSolution[firstCity].value);
        tempSequence[chosenAirplane] = nextCity;
        changeAirplaneLocation(tempSolution, chosenAirplane, firstCity, nextCity);
    //    checkRepatriatedNumber(tempSolution, tempSequence, (*tempTotal),3);
   //     checkValues(tempSolution, (*tempValue));
      //   printf("\n new value=%f total=%d joining =%d leaving=%d populationChange=%d",*tempValue,*tempTotal, joining,leaving,populationChange);
//       getchar();
        numberChosen++;
    } while (numberChosen < numberChanges);
   
  //  getchar();



}