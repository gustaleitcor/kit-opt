#pragma once
#include "Data.h"
#include <vector>
#include "./auxFunctions/randInt.h"

double magnitude = 1;

bool Pertubacao(vector<int> &solution, Data *data)
{
    vector<int> solutionCpy(solution);

    int indexA = randInt(0, solutionCpy.size());
    int sliceSizeA = magnitude * (solutionCpy.size() - randInt(indexA, solutionCpy.size())) / 10 + 1;

    int sliceA[sliceSizeA];

    for (int i = 0; i < sliceSizeA; i++)
    {
        sliceA[i] = solutionCpy[indexA];
        solutionCpy.erase(solutionCpy.begin() + indexA);
    }

    int indexB = randInt(0, solutionCpy.size());
    int sliceSizeB;

    if (indexB < indexA)
    {
        sliceSizeB = magnitude * (indexA - randInt(indexB, indexA)) / 10 + 1;
    }
    else
    {
        sliceSizeB = magnitude * (solutionCpy.size() - randInt(indexB, solutionCpy.size())) / 10 + 1;
    }

    int sliceB[sliceSizeB];

    for (int i = 0; i < sliceSizeB; i++)
    {
        sliceB[i] = solutionCpy[indexB];
        solutionCpy.erase(solutionCpy.begin() + indexB);
    }

    for (int i = 0; i < solution.size(); i++)
    {
        solutionCpy.push_back(-1);
    }

    for (int i = 0; i < sliceSizeA; i++)
    {
        solutionCpy.insert(solutionCpy.begin() + indexB, sliceA[i]);
    }

    for (int i = 0; i < sliceSizeB; i++)
    {
        solutionCpy.insert(solutionCpy.begin() + indexA, sliceB[i]);
    }

    for (int i = solutionCpy.size(); i >= 0; i--)
    {
        if (solutionCpy[i] == -1)
        {
            solutionCpy.erase(solutionCpy.begin() + i);
        }
    }

    BuscaLocal(solutionCpy, data);

    if (calcCost(solutionCpy, data) < calcCost(solution, data))
    {
        solution = solutionCpy;
        return true;
    }

    return false;
}