#pragma once
#ifndef __checks_h__
#define __checks_h__
#include <vector>
#include <set>
#include "globalVariables.h"
void checkValues(vector<city> tempSolution, double totalValue);
void checkRepatriatedNumber(vector<city> tempSolution, int incumbent[],int totalReturned,int sender);
void checkCapacities(vector<city> tempSolution);
#endif