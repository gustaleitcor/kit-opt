#pragma once
#include <iostream>

double calcCost(vector<int> &path, Data *data)
{
    double cost = 0;
    int i;
    for (i = 0; i < path.size() - 2; i++)
    {
        cost += data->getDistance(path[i], path[i + 1]);
    }

    cost += data->getDistance(path[i - 1], path[0]);

    return cost;
}