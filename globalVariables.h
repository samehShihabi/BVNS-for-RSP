#pragma once
#ifndef __globalVariables_h__
#define __globalVariables_h__
#include <vector>
#include <set>
using namespace std;
extern int numberAirplanes;
extern int numberCitizens;
extern int numberCountries;
extern int numberCountries;
extern int numberGroups;
extern float priorities[10];
extern int countryGroup[300][10];
extern int totalCountryOriginal[300];
extern int  quarantineLocations;
extern int airplanesCapacities[100000];
extern int totalAllCities;
extern struct city {
    set<int>airplanes;
    int numberPerGroup[10];
    int cumulativeNumberGroup[10];
    int totalNumber;
    int repatriated;
    double value;
    int airplanesSumCapacities;
};

extern vector<city> citySolution;
extern int incumbentSolution[50000];
extern double incumbentValue;

#endif