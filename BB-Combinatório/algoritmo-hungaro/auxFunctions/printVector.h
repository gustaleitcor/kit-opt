#pragma once
#include <iostream>

void printVector(vector<int> &v, bool wEndl = true)
{
    for (int i : v)
    {
        std::cout << i << ' ';
    }

    if (wEndl)
    {
        std::cout << std::endl;
    }
}