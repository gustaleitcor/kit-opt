#pragma once
#include <iostream>

void printPath(vector<int> &path)
{
    for (int i : path)
    {
        cout << i << " -> ";
    }

    cout << path[0] << endl;
}