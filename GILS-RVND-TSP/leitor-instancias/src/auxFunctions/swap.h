#pragma once


void swap(vector<int> &v, int index0, int index1)
{
    int aux = v[index0];
    v[index0] = v[index1];
    v[index1] = aux;
}