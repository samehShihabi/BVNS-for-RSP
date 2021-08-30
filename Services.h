#pragma once

#ifndef __Services_h__
#define __Services_h__
#include <vector>
#include <set>
#include "globalVariables.h"
int randomCityChoice(int number,int choices[]);
double cityValue(int cumulativeNumberGroup[], int numberPerGroup[], int total);
void copyAll(vector<city> &tempSolution,int tempSequence[],int *tempTotatl);
void copyAllback(vector<city> tempSolution, int tempSequence[], int *Total);
#endif