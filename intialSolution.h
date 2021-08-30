#pragma once
#ifndef __initialSolution_h__
#define __initialSolution_h__
#include <vector>
#include <set>
double generateInitialSolution(int solution[], int* total);
int chooseAirplane(int airplaneStatus[]);
int chooseCity(int chosenAirplane, double* tempValue);
#endif