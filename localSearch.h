#pragma once
#ifndef __localSearch_h__
#define __localSearch_h__
#include <vector>
#include <set>
#include "globalVariables.h"
double improve(vector<city> &tempSolution,double *tempValue,int tempSequence[], int* total);

void changeAirplaneLocation(vector<city> &tempSolution, int bestAirplane,int bestChange1city,int bestChange2City);
#endif