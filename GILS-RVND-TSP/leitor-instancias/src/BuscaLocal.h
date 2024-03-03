#pragma once
#include "Data.h"
#include <vector>
#include <random>
#include "./auxFunctions/calcCost.h"
#include "./auxFunctions/swap.h"
#include "./auxFunctions/randInt.h"

bool bestImprovementSwap(vector<int> &solution, Data *data)
{

    vector<int> solutionCpy(solution);

    int randomIndex1 = rand() % (solutionCpy.size());

    int randomIndex2 = rand() % (solutionCpy.size());

    swap(solutionCpy, randomIndex1, randomIndex2);

    int newCost = calcCost(solutionCpy, data);
    int originalCost = calcCost(solution, data);

    if (newCost < originalCost)
    {
        solution = solutionCpy;
        return true;
    }
    else
    {
        return false;
    }
}

bool bestImprovement2Opt(vector<int> &solution, Data *data)
{
    vector<int> solutionCpy(solution);

    int index = randInt(0, solutionCpy.size());
    int sliceSize = solutionCpy.size() - randInt(index, solutionCpy.size() + 1);

    for (int i = 0; i < sliceSize / 2; i++)
    {
        swap(solutionCpy, index + i, index + sliceSize - 1 - i);
    }

    int originalCost = calcCost(solution, data);
    int newCost = calcCost(solutionCpy, data);

    if (newCost < originalCost)
    {
        solution = solutionCpy;
        return true;
    }

    return false;
}

bool bestImprovementOrOpt(vector<int> &solution, Data *data, int n)
{

    vector<int> solutionCpy(solution);
    int reinsertionNumbers[n];
    int randomIndex;

    randomIndex = rand() % (solutionCpy.size() - n);

    for (int i = 0; i < n; i++)
    {
        reinsertionNumbers[i] = solutionCpy[randomIndex];
        solutionCpy.erase(solutionCpy.begin() + randomIndex);
    }

    randomIndex = rand() % (solutionCpy.size() - n);

    for (int i = n - 1; i > -1; i--)
    {
        solutionCpy.insert(solutionCpy.begin() + randomIndex, reinsertionNumbers[i]);
    }

    int newCost = calcCost(solutionCpy, data);
    int originalCost = calcCost(solution, data);

    if (newCost < originalCost)
    {
        solution = solutionCpy;
        return true;
    }
    else
    {
        return false;
    }
}

void BuscaLocal(vector<int> &solution, Data *data)
{

    vector<int> options = {1, 2, 3, 4, 5};
    bool improved = false;
    bool modified = false;

    while (!options.empty())
    {
        int n = rand() % options.size();
        switch (options[n])
        {
        case 1:
            improved = bestImprovementSwap(solution, data);
            break;
        case 2:
            improved = bestImprovement2Opt(solution, data);
            break;
        case 3:
            improved = bestImprovementOrOpt(solution, data, 1);
            break;
        case 4:
            improved = bestImprovementOrOpt(solution, data, 2);
            break;
        case 5:
            improved = bestImprovementOrOpt(solution, data, 3);
            break;
        }

        if (improved)
        {
            options = {1, 2, 3, 4, 5};
            modified = true;
        }
        else
        {
            options.erase(options.begin() + n);
        }
    }
}