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
#include "localSearch.h"
#include "VNS.h"
#include "checks.h"
using namespace::std;
void readCase(int number);
FILE* input;
int numberCitizens;
int numberCountries;
int numberGroups;
float priorities[10];
int countryGroup[300][10];
int totalCountryOriginal[300];
int  quarantineLocations;
int numberAirplanes;
int airplanesCapacities[100000];
int totalAllCities;
vector<city> citySolution;

int incumbentSolution[50000];
double incumbentValue = 0;
int sumAirplanes;
int main()
{
	readCase(1);
    double sum = 0;
    double sum2 = 0;
    int replications = 10;
    double bestAnswer = 0;
    for (int i = 0; i < replications; i++)
    {
        vector<city> tempSolution;
        int tempSequence[50000];
        int tempTotalReturned = 0;
        for (int i = 0; i < 50000; i++)
                incumbentSolution[i] = 1000000;

        for (int i = 0; i < numberCountries; i++)
        {
            citySolution[i].value = 0;
            citySolution[i].repatriated = 0;
            citySolution[i].airplanesSumCapacities = 0;
        }
        int totalReturned = 0;
        double initialValue = generateInitialSolution(incumbentSolution, &totalReturned);


        clock_t tStart = clock();

       printf("\n starting solution value=%f number out=%d quarantine=%d airplanes=%d total out=%d",
            initialValue, totalReturned, quarantineLocations, sumAirplanes, totalAllCities);
    //   getchar();
        double objectiveSum = 0;
        int sumOut = 0;
       
        for (int i = 0; i < numberCountries; i++)
        {
            int out = citySolution[i].repatriated;
            double val = citySolution[i].value;
            objectiveSum += val;
            sumOut += out;
         //   printf("\n i=%d out=%d val=%f sumOut=%d sumval=%f",i,out,val,sumOut,objectiveSum);
        //    getchar();

        }
   //     getchar();
        int tempReturned = 0;
    //    printf("\n before copying");
        copyAll(tempSolution, tempSequence, &tempReturned);
        double tempValue = initialValue;
        double newBest = improve(tempSolution, &tempValue, tempSequence, &tempReturned);
     //   printf("\n before copying new best=%f", newBest);
        copyAllback(tempSolution, tempSequence, &totalReturned);
        incumbentValue = newBest;
        checkRepatriatedNumber(citySolution, incumbentSolution, totalReturned, 0);
        checkValues(citySolution, incumbentValue);
     //   printf("\n after copying new best=%f", newBest);
     //    getchar();
        int changes = 1;
        double time;
        do {
            copyAll(tempSolution, tempSequence, &tempReturned);
            //    printf("\n checking the after copying 1");
    //        checkRepatriatedNumber(tempSolution, tempSequence, tempReturned, 0);
    //        checkValues(tempSolution, incumbentValue);
            //    printf("\n checking the after copying 2");
            newBest = incumbentValue;
            shake(tempSolution, tempSequence, &tempReturned, changes, &newBest);
            //    printf("\n 1 checking the after shaking solution");
     //       checkRepatriatedNumber(tempSolution, tempSequence, tempReturned, 0);
     //       checkValues(tempSolution, newBest);
            //    printf("\n 2 temp value before improving=%f", newBest);
            //    getchar();
            double valueAfterImprove = improve(tempSolution, &newBest, tempSequence, &tempReturned);
       //     printf("\n changes=%d value after shaking and improvement=%f incumbenet value=%f", changes, valueAfterImprove, incumbentValue);
       //     getchar();
            if (valueAfterImprove > incumbentValue)
            {
                incumbentValue = valueAfterImprove;
                copyAllback(tempSolution, tempSequence, &totalReturned);
     //           checkRepatriatedNumber(citySolution, incumbentSolution, totalReturned, 1);
     //           checkValues(citySolution, incumbentValue);
                printf("\n incumbent=%f", incumbentValue);

                if (incumbentValue > bestAnswer)
                    bestAnswer = incumbentValue;
                changes = 1;
            }
            else
                changes++;
            clock_t tEnd = clock();
            time = (double)(tEnd - tStart) / CLOCKS_PER_SEC;
        } while (time < 19);

        sum += incumbentValue;
        sum2 += incumbentValue * incumbentValue;
        
        
        printf("\n time=%f incumbent=%f",time, incumbentValue);
     //   getchar();
    }
    
    double average = sum / (double)replications;
    double std = sum2 / (double)replications - (average*average);
    printf("\n best=%f average=%f std=%f",bestAnswer,average,std);
    getchar();

}

void readCase(int number)
{
    int numberCases;
    input = fopen("Instances.txt", "r");
    fscanf(input, "%d", &numberCases);

    int dum;

    for (int i = 0; i < number; i++)
    {
        totalAllCities = 0;
        sumAirplanes = 0;
        fscanf(input, "%d", &dum);


        fscanf(input, "%d", &numberCountries);


        fscanf(input, "%d", &numberAirplanes);


        fscanf(input, "%d", &numberGroups);

        for (int airplane = 0; airplane < numberAirplanes; airplane++)
        {
            fscanf(input, "%d", &airplanesCapacities[airplane]);

            //		getchar();
            sumAirplanes += airplanesCapacities[airplane];
       //     printf("\n airplane=%d cap=%d sum=%d", airplane,airplanesCapacities[airplane], sumAirplanes);

        }
        //getchar();
        for (int country = 0; country < numberCountries; country++)
        {
            city tempCity;
            citySolution.push_back(tempCity);
            fscanf(input, "%d", &dum);
            //			printf("\n problem=%d", dum);
            //			getchar();
            totalCountryOriginal[country] = 0;
            for (int group = 0; group < numberGroups; group++)
            {
                fscanf(input, "%d", &countryGroup[country][group]);
                totalCountryOriginal[country] += countryGroup[country][group];
                citySolution[country].cumulativeNumberGroup[group] = totalCountryOriginal[country];
                citySolution[country].numberPerGroup[group] = countryGroup[country][group];
         //       printf("\n country=%d group=%d group number=%d total=%d", country,group,countryGroup[country][group], totalCountryOriginal[country]);
     	//		getchar();
            }

            citySolution[country].totalNumber = totalCountryOriginal[country];
            totalAllCities += citySolution[country].totalNumber;

        }
        for (int group = 0; group < numberGroups; group++)
        {
            fscanf(input, "%f", &priorities[group]);
            //			printf("\n priorities=%f", priorities[group]);
            //			getchar();
        }
        //fprintf(outfileSummary, "%d-%d-%d-D-%d\n", numberCountries, numberAirplanes, numberGroups, quarantine);
        fscanf(input, "%d", &quarantineLocations);
        //	printf("\n quarantine=%d", quarantineLocations);
            //		getchar();
       //     printf("\n end of loop");
        //    getchar();
    }
    // printf("\n countries=%d", numberCountries);
   // printf("\n airplanes=%d", numberAirplanes);
   //  printf("\n numberGroups=%d", numberGroups);
  //  printf("\n total all=%d airplanes=%d quarantine=%d", totalAllCities, sumAirplanes, quarantineLocations);
  //  getchar();
    if (totalAllCities < quarantineLocations)
        printf("\n problem");

    for (int airplane1 = 0; airplane1 < numberAirplanes - 1; airplane1++)
        for (int airplane2 = airplane1; airplane2 < numberAirplanes; airplane2++)
            if (airplanesCapacities[airplane2] < airplanesCapacities[airplane1])
            {
                int dum = airplanesCapacities[airplane2];
                airplanesCapacities[airplane2] = airplanesCapacities[airplane1];
                airplanesCapacities[airplane1] = dum;

            }


}
