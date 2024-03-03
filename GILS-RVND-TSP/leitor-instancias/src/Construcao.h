#pragma once
#include <iostream>
#include <vector>
#include "Data.h"
#include "./auxFunctions/calcCost.h"

#include <iostream>
using namespace std;

typedef struct
{
    double cost;
    int j;
    int k;
    bool isUpdated = false;
} MinorCost;

void Construcao(vector<int> &avbCities, Data *data)
{

    vector<int> path;
    path.push_back(avbCities[0]);
    path.push_back(avbCities[data->getDimension() / 2]);
    path.push_back(avbCities[data->getDimension() - 1]);
    path.push_back(avbCities[0]);

    avbCities.erase(avbCities.begin() + (data->getDimension() / 2));
    avbCities.erase(avbCities.begin() + 0);
    avbCities.pop_back();

    double tDist = 0;

    for (int i = 0; i < path.size() - 1; i++)
    {
        tDist += data->getDistance(i, i + 1);
    }

    double cost;
    int ik;
    int kj;
    int ij;

    MinorCost minorCost;
    while (!avbCities.empty())
    {
        for (int i = 0; i < path.size() - 1; i++)
        {
            for (int j = 0; j < avbCities.size(); j++)
            {
                ik = data->getDistance(path[i], avbCities[j]);
                kj = data->getDistance(avbCities[j], path[i + 1]);
                ij = data->getDistance(path[i], path[i + 1]);
                cost = ik + kj - ij;

                if (!minorCost.isUpdated)
                {
                    minorCost.isUpdated = true;
                    minorCost.cost = cost;
                    minorCost.j = i + 1;
                    minorCost.k = j;
                }
                else if (minorCost.cost > cost)
                {
                    minorCost.cost = cost;
                    minorCost.j = i + 1;
                    minorCost.k = j;
                }
            }
        }

        minorCost.isUpdated = false;

        tDist += minorCost.cost;
        path.insert(path.begin() + minorCost.j, avbCities[minorCost.k]);
        avbCities.erase(avbCities.begin() + minorCost.k);
    }

    path.pop_back();

    avbCities = path;
}